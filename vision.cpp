#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <QMessageBox>
#include "utils.h"
#include "vision.h"

using namespace std;

Point null_point = Point(-1, -1);

Vision::Vision(QObject *parent): QThread(parent)
{
    Point a, b;
    stop = true;
    showArea = sentPoints = teamsChanged = showErrors = showNames = ball_found = showCenters = trained= false;
    mode = 0;
    cont = 0;
    robots.resize(6);
    robots[0].set_nick("Leona");
    robots[1].set_nick("Gandalf");
    robots[2].set_nick("Presto");
    robots[3].set_nick("T2");
    robots[4].set_nick("T2");
    robots[5].set_nick("T2");
    low.assign(3, 0);
    upper.assign(3, 255);
    ball_color.first.assign(3, 0);
    ball_color.second.assign(3, 255);
    info.enemy_robots.resize(3);
    info.team_robots.resize(3);
    info.ball_pos_cm = Point2d(0.0, 0.0);
    info.ball_pos = Point(0, 0);
    info.ball_last_pos = Point(0, 0);
    info.ball_found = false;

    if(!read_points("Config/map", map_points)){
        cerr << "The map could not be read from the file!" << endl;
    }
    if(!read_points("Config/attack_area", atk_points)){
        cerr << "The attack area could not be read from the file!" << endl;
    }
    if(!read_points("Config/defense_area", def_points)){
        cerr << "The defense area could not be read from the file!" << endl;
    }
    a = (map_points[4] + map_points[5])/2;
    b = (map_points[14] + map_points[13])/2;
    x_axis_slope = b - a;
    ball_pos = null_point;
    ball_last_pos = null_point;

 // last_P = MatrixXd::Identity(3,3);
}

Mat Vision::detect_colors(Mat vision_frame, vector<int> low, vector<int> upper) //Detect colors in [low,upper] range
{
    Mat mask;

    //Generate mask with the points in the range
    inRange(vision_frame, Scalar(low[0],low[1],low[2]), Scalar(upper[0],upper[1],upper[2]), mask);

    //Attempt to remove noise (or small objects)
    morphologyEx(mask, mask, MORPH_OPEN, Mat(), Point(-1, -1), 2);
    morphologyEx(mask, mask, MORPH_CLOSE, Mat(), Point(-1, -1), 2);

    return mask;
}

bool invalid_contour(vector<Point> p){
    return p.size() == 0;
}

vector<Robot> Vision::fill_robots(vector<pMatrix> contours, vector<Robot> robots)
{
    size_t i, j, k, l;
    int csize, tsize, r_label = 0, min, t1size, tmin;
    double dista = 0.0, angle, last_angle;
    bool not_t1, error;
    Moments ball_moment, temp_moment;
    Point ball_cent = null_point, unk_robot, centroid, line_slope, last_cent;
    vector<bool> r_set;
    vector<vector<Moments> > r_m(3, vector<Moments>());
    vector<vector<Moments> > t_m(2, vector<Moments>());
    vector<pVector > r_col_cent(3, pVector());
    vector<pVector > tirj_cent(2, pVector());
    pair<Point, pair<int, int> > col_select;

    //Candidate selection from the ball contours
    auto it = remove_if(contours[0].begin(), contours[0].end(), ball_area_limit);
    contours[0].erase(it, contours[0].end());
    it = remove_if(contours[0].begin(), contours[0].end(), invalid_contour);
    contours[0].erase(it, contours[0].end());

    if(contours[0].size() > 0){
        sort(contours[0].begin(), contours[0].end(), sort_by_larger_area);
        //Get the ball moment from the contour
        ball_moment = moments(contours[0][contours[0].size()-1]);
        //Get ball centroid
        ball_cent = Point(ball_moment.m10/ball_moment.m00, ball_moment.m01/ball_moment.m00);
        ball_found = true;
        info.ball_contour = contours[0][contours[0].size()-1];
    }else{
        //If there's no candidate for the ball, get the last recorded position
        ball_cent = ball_last_pos;
        ball_found = false;
        info.ball_contour = pVector();
    }


    ball_pos_cm = ball_pos_cm;
    ball_pos = ball_cent;
    ball_pos_cm.x = ball_pos.x * X_CONV_CONST;
    ball_pos_cm.y = ball_pos.y * Y_CONV_CONST;

    //Compute the variation of the position for posterior velocity computation
    info.ball_vel.first = double(ball_pos.x - ball_last_pos.x) * X_CONV_CONST;
    info.ball_vel.second = double(ball_pos.y - ball_last_pos.y) * Y_CONV_CONST;

    ball_last_pos = ball_cent;

    //Candidate selection for the team 1 from contours detected
    it = remove_if(contours[1].begin(), contours[1].end(), invalid_contour);
    contours[1].erase(it, contours[1].end());
    sort(contours[1].begin(), contours[1].end(), sort_by_larger_area);
    it = remove_if(contours[1].begin(), contours[1].end(), area_limit);
    contours[1].erase(it, contours[1].end());

    //Candidate selection for the team 2 from contours detected
    it = remove_if(contours[2].begin(), contours[2].end(), invalid_contour);
    contours[2].erase(it, contours[2].end());
    sort(contours[2].begin(), contours[2].end(), sort_by_larger_area);
    it = remove_if(contours[2].begin(), contours[2].end(), area_limit);
    contours[2].erase(it, contours[2].end());

    //Get the robots moments and centroids for each team (their team color half)
    for(i = 0; i < 2; ++i){
        if(contours[i+1].size() > 0){
            for(j = 0; j < contours[i+1].size(); ++j){
                temp_moment = moments(contours[i+1][j]);
                t_m[i].push_back(temp_moment);
                //Get centroid from robot team color half
                tirj_cent[i].push_back(Point(t_m[i][j].m10/t_m[i][j].m00, t_m[i][j].m01/t_m[i][j].m00));

            }
            //If there's less than 3 centroids, set the remaining as null
            if(contours[i+1].size() < 3){
                l = 3 - contours[i+1].size();
                for(j = 0; j < l; ++j){
                    tirj_cent[i].push_back(null_point);
                }
            }
        }
    }

    //Get the robots moments only for team 1 (their color half)
    for(i = 0; i < 3; ++i){
        csize = contours[i + 3].size();
        if(csize > 0){
            for(j = 0; j < csize; ++j){
                temp_moment = moments(contours[i + 3][j]);
                r_m[i].push_back(temp_moment);
            }
            //Get centroid from robot color half
            for(j = 0; j < csize; ++j){
                r_col_cent[i].push_back(Point(r_m[i][j].m10/r_m[i][j].m00, r_m[i][j].m01/r_m[i][j].m00));
            }

        }else{
            //If there's no contour, the robot wasn't detected, set the last valid position
            r_col_cent[i].push_back(null_point);
            robots[i].set_centroid(robots[i].get_last_centroid());
            robots[i].was_detected(false);
        }
    }

    r_set = vector<bool>(r_col_cent.size(), false);
    tsize = tirj_cent[0].size();
    t1size = (tirj_cent[1].size() < 3)?3+tirj_cent[1].size():6;

    //Define team 1 centroids and angles
    for(i = 0; i < tsize; ++i){
        unk_robot = tirj_cent[0][i];
        if(unk_robot == null_point) continue;
        not_t1 = false;
        col_select = make_pair(null_point, make_pair(-1, -1));

        for(j = 0, min = 20000; j < r_col_cent.size(); ++j){
            if(r_set[j]) continue;
            for(k = 0; k < r_col_cent[j].size(); ++k){
                if(r_col_cent[j][k] == null_point) continue;
                dista = euclidean_dist(unk_robot, r_col_cent[j][k]);
                if(dista < min && dista < 20){
                    min = dista;
                    tmin = min;
                    pair<int, int> ind = make_pair(j, k);
                    col_select = make_pair(r_col_cent[j][k], ind);
                }
            }
        }

        //Verify if the color assigned is not from the other team
        for(k = 3; k < t1size; ++k){
            dista = euclidean_dist(tirj_cent[1][k-3], col_select.first);
            if(dista < tmin){
                not_t1 = true;
                break;
            }
        }

        r_label = col_select.second.first;
        //If the robot could be identified
        if(r_label != -1){
            //Get the last valid state from the robot historic
            last_cent = robots[r_label].get_from_pos_hist(0);
            last_angle = robots[r_label].get_last_angle();
        }

        if(!not_t1 && r_label != -1){   //If the robot is from team 1 and he could be identified by the color half
            line_slope =  unk_robot - col_select.first;
            centroid = Point((unk_robot.x + col_select.first.x)/2, (unk_robot.y + col_select.first.y)/2);
            angle = fabs(angle_two_points(line_slope, x_axis_slope));
            angle = (col_select.first.y <= unk_robot.y)?angle:-angle;

            robots[r_label].set_team_contour(contours[1][i]);
            robots[r_label].set_role_contour(contours[r_label + 3][col_select.second.second]);
            robots[r_label].set_team_cent(unk_robot);
            robots[r_label].set_color_cent(col_select.first);
            robots[r_label].set_line_slope(line_slope);
            robots[r_label].set_angle(angle);
            robots[r_label].set_centroid(centroid);
            robots[r_label].was_detected(true);
            r_set[r_label] = true;
       }else if(r_label != -1){
            robots[r_label].set_centroid(last_cent);
            robots[r_label].set_angle(last_angle);
            robots[r_label].was_detected(false);
            r_set[r_label] = true;
        }
    }

    error = false;
    for(i = 0; i < r_set.size(); ++i){
        if(!r_set[i]){
            error = true;
            if(showErrors) cerr << robots[i].get_nick() << " was not found!" << endl;
            robots[i].set_angle(robots[i].get_last_angle());
            robots[i].set_centroid(robots[i].get_last_centroid());
            robots[i].was_detected(false);
        }
    }

    //Define team 2 centroids and angles
    for(i = 3, j = 0, dista = INFINITY; i < 6; ++i, ++j){
        if(tirj_cent[1].size() == 0) continue;
        robots[i].set_team_cent(tirj_cent[1][i-3]);
        robots[i].set_centroid(robots[i].get_team_cent());
        robots[i].was_detected(true);
    }
    for(i = t1size; i < 6; ++i){
        robots[i].set_centroid(null_point);
        robots[i].was_detected(false);
    }


    if(error && showErrors) cerr << endl;

    cont++;
    return robots;
}

pair<vector<vector<Vec4i> >, vector<pMatrix> > Vision::detect_objects(Mat frame, vector<Robot> robots){
    int i, rsize = robots.size();
    Mat out_team1, out_team2, out_r[3], out_ball;
    vector<int> low, upper;
    vector<pMatrix> contours(6);
    vector<vector<Vec4i> > hierarchy(6);
    pair<vector<vector<Vec4i> >, vector<pMatrix> > ret;

    for(i = 0; i < rsize-3; ++i){
        low = robots[i].get_low_color();
        upper = robots[i].get_upper_color();
        out_r[i] = detect_colors(frame, low, upper);
    }

    low = robots[0].get_team_low_color();
    upper = robots[0].get_team_upper_color();

    out_team1 = detect_colors(frame, low, upper);

    low = robots[4].get_team_low_color();
    upper = robots[4].get_team_upper_color();

    out_team2 = detect_colors(frame, low, upper);

    low = ball_color.first;
    upper = ball_color.second;
    info.ball_color = ball_color;

    out_ball = detect_colors(frame, low, upper);

    findContours(out_ball, contours[0], hierarchy[0], RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    findContours(out_team1, contours[1], hierarchy[1], RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    findContours(out_team2, contours[2], hierarchy[2], RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    findContours(out_r[0], contours[3], hierarchy[3], RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    findContours(out_r[1], contours[4], hierarchy[4], RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    findContours(out_r[2], contours[5], hierarchy[5], RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

    ret.first = hierarchy;
    ret.second = contours;

    return ret;
}

Mat Vision::adjust_gamma(double gamma, Mat org)
{
    if(gamma == 1.0)
        return org;

    double inverse_gamma = 1.0 / gamma;

     Mat lut_matrix(1, 256, CV_8UC1);
     uchar * ptr = lut_matrix.ptr();
     for( int i = 0; i < 256; i++ )
       ptr[i] = (int)( pow( (double) i / 255.0, inverse_gamma ) * 255.0 );

     Mat result;
     LUT( org, lut_matrix, result );

    return result;
}

Mat Vision::crop_image(Mat org){
    Mat cropped;
    Size size;
    Point2f pts[4], pts1[3], pts2[3];
    RotatedRect box;
    pVector roi(4), aux_y, map_points1;

    pts2[0] = Point(0, 0);
    pts2[1] = Point(0, size.height-1);
    pts2[2] = Point(size.width-1, 0);

    map_points1 = map_points;
    aux_y = map_points;
    sort(map_points.begin(), map_points.end(), sort_by_smallest_x);
    sort(aux_y.begin(), aux_y.end(), sort_by_smallest_y);

    roi[0] = Point(map_points[0].x, aux_y[aux_y.size()-1].y);
    roi[3] = Point(map_points[map_points.size()-1].x, aux_y[0].y);
    roi[1] = Point(roi[0].x, roi[3].y);
    roi[2] = Point(roi[3].x, roi[0].y);

    box = minAreaRect(Mat(roi));
    box.points(pts);

    pts1[0] = pts[0];
    pts1[1] = pts[1];
    pts1[2] = pts[3];

    pts2[0] = Point(0, 0);
    pts2[1] = Point(box.boundingRect().width-1, 0);
    pts2[2] = Point(0, box.boundingRect().height-1);
    size = Size(box.boundingRect().width, box.boundingRect().height);

    if(!sentPoints){
        transf_matrix = getAffineTransform(pts1, pts2);
        transform(map_points1, tmap_points, transf_matrix);
        transform(def_points, tdef_points, transf_matrix);
        transform(atk_points, tatk_points, transf_matrix);

        atk_centroid = (tatk_points[2] + tatk_points[3] + tatk_points[4] + tatk_points[5])/4;
        def_centroid = (tdef_points[2] + tdef_points[3] + tdef_points[4] + tdef_points[5])/4;
        info.map_area = tmap_points;
        info.atk_area = tatk_points;
        info.def_area = tdef_points;

        sentPoints = true;
    }
    warpAffine(org, cropped, transf_matrix, size, INTER_LINEAR, BORDER_CONSTANT);
    map_points = map_points1;

    return cropped;
}

Mat Vision::proccess_frame(Mat orig, Mat dest) //Apply enhancement algorithms
{
    dest = orig.clone();
    //Gamma correction
    dest = adjust_gamma(1.0 , dest);
    //Apply gaussian blur
    GaussianBlur(dest, dest, Size(5,5), 1.8);

    return dest;
}

Mat Vision::setting_mode(Mat raw_frame, Mat vision_frame, vector<int> low, vector<int> upper)   //Detect colors in [low,upper] range
{
    Mat mask, res;

    cvtColor(vision_frame, vision_frame, CV_BGR2HSV);
    mask = detect_colors(vision_frame, low, upper);
    raw_frame.copyTo(res, mask);

    return res;
}

Mat Vision::draw_robots(Mat frame, vector<Robot> robots)
{
    int i, size = robots.size();
    double angle, predic_angle;
    Point cent, predic_cent, team_cent, color_cent, inter;

    if(ball_pos != null_point){
        circle(frame, ball_pos, 10, Scalar(255, 0, 0));
    }
    for(i = 0; i < size-3; ++i){
        cent = robots[i].get_centroid();
        predic_cent = robots[i].get_predic_centroid();
        team_cent = robots[i].get_team_cent();
        color_cent = robots[i].get_color_cent();
        angle = robots[i].get_angle();
        predic_angle = robots[i].get_predic_angle();

        if(cent == null_point) continue;

        // Funcao que desenha as circunferencias com centros nos centroides das cores da equipa e do robo
        if(showCenters){
            circle(frame, team_cent, 5, Scalar(0, 255, 0), 1*(i+1));
            circle(frame, color_cent, 5, Scalar(0, 255, 0), 1*(i+1));
        }

        // Desenha as circunferencia com centro no centroide do robo
        // e a linha que indica a orientacao da direcao do robo (para onde ele esta olhando)
        circle(frame, cent, 20, Scalar(0, 255, 0), 1.5);
        inter = Point(cent.x + 20 * cos(angle * PI / 180.0), cent.y - 20 * sin(angle * PI / 180.0));
        line(frame, cent, inter, Scalar(0, 255, 0), 1);

        // Desenha a posicao prevista do robo
        if(predic_cent != cent){
            circle(frame, predic_cent, 20, Scalar(255, 0, 255), 1.5);
            inter = Point(predic_cent.x + 20 * cos(predic_angle * PI / 180.0), predic_cent.y - 20 * sin(predic_angle * PI / 180.0));
            line(frame, predic_cent, inter, Scalar(255, 0, 255), 1);
        }

        if(showNames)
            putText(frame, robots[i].get_nick(), cent + Point(0, -2), FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 0), 2);
    }

    // Desenha o time adversario (por meio de circunferencias)
    for(i = size-3; i < size; ++i){
        cent = robots[i].get_centroid();
        if(cent == null_point) continue;
        else cent += Point(2,2);
        circle(frame, cent , 20, Scalar(0, 0, 255), 1);
    }

    return frame;
}

Mat Vision::draw_field(Mat frame)
{
    int i = 0, atk_size = atk_points.size(), map_size = map_points.size(), def_size = def_points.size();
    Point def_cent, atk_cent;

    if(showArea && map_size > 0){
        //Draw map area points
        for(i = 0; i < map_size; ++i){
            circle(frame, tmap_points[i], 1, Scalar(0,0,255), 2);
        }

        //Draw attack area points
        for(i = 0; i < atk_size; ++i){
            circle(frame, tatk_points[i], 1, Scalar(255,0,0), 2);
        }

        atk_cent = (tatk_points[0]+tatk_points[7])/2;
        putText(frame, "ATK Area", atk_cent, FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 0), 2);

        //Draw defense area points
        for(i = 0; i < def_size; ++i){
            circle(frame, tdef_points[i], 1, Scalar(0,255,0), 2);
        }

        def_cent = (tdef_points[0]+tdef_points[7])/2;
        putText(frame, "DEF Area", def_cent, FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 0), 2);
    }

    return vision_frame;
}


void Vision::run()
{
    int delay = (1000/this->FPS);
    int i = 0, itr = 0;
    double elapsed_secs, xScaleFactor = 1.0, yScaleFactor = 1.0;
    clock_t begin, end;
    bool scaleFactorComputed = false;
    vector<pMatrix> obj_contours;
    vector<Point> to_transf, transf;

    to_transf.resize(6);
    transf.resize(6);

    while(!stop){
        begin = clock();
        itr++;

        //Read a frame from the camera
        if(!cam.read(raw_frame)){
            stop = true;
            cerr << "A frame could not be read! (Vision)" << endl;
            return;
        }

        /**************************************
         *         Pre-Processing Step        *
         **************************************/

        //Get sub frame and fit in the frame size (cropping)
        raw_frame = crop_image(raw_frame);
        info.img_size.x = raw_frame.cols;
        info.img_size.y = raw_frame.rows;

        //Resize the image for the default image size.
        //For downsampling the area interpolation method is being used.
        //For upsampling the cubic interpolation method is being used.
        if(raw_frame.cols > DEFAULT_NCOLS && raw_frame.rows > DEFAULT_NROWS){
            resize(raw_frame, vision_frame, Size(DEFAULT_NCOLS, DEFAULT_NROWS), 0, 0, INTER_AREA); // resize to 1024x768 resolution
        }else if(raw_frame.cols < DEFAULT_NCOLS && raw_frame.rows < DEFAULT_NROWS){
            resize(raw_frame, vision_frame, Size(DEFAULT_NCOLS, DEFAULT_NROWS), 0, 0, INTER_CUBIC);
        }else if(raw_frame.cols > DEFAULT_NCOLS || raw_frame.rows > DEFAULT_NROWS){
            resize(raw_frame, vision_frame, Size(DEFAULT_NCOLS, DEFAULT_NROWS), 0, 0, INTER_AREA);
        }else{
            resize(raw_frame, vision_frame, Size(DEFAULT_NCOLS, DEFAULT_NROWS), 0, 0, INTER_CUBIC);
        }

        /*
         *  Tentativa de ajustar escala nos pontos delimitantes do campo
         *
         * if(!scaleFactorComputed){
            xScaleFactor = DEFAULT_NCOLS / raw_frame.cols;
            yScaleFactor = DEFAULT_NROWS / raw_frame.rows;

            scaleFactorComputed = !scaleFactorComputed;
            for(i = 0; i < tatk_points.size(); i++){
                tatk_points[i].x *= xScaleFactor;
                tatk_points[i].y *= yScaleFactor;
            }
            for(i = 0; i < tdef_points.size(); i++){
                tdef_points[i].x *= xScaleFactor;
                tdef_points[i].y *= yScaleFactor;
            }
            for(i = 0; i < tmap_points.size(); i++){
                tmap_points[i].x *= xScaleFactor;
                tmap_points[i].y *= yScaleFactor;
            }
            info.map_area = tmap_points;
            info.atk_area = tatk_points;
            info.def_area = tdef_points;
        }*/
        //Apply blurring and gamma corretion methods
        vision_frame = proccess_frame(vision_frame, vision_frame);

        switch(mode){
            case 0: //Visualization mode
                //Convert the frame from RGB color space to HSV
                cvtColor(vision_frame, vision_frame, CV_BGR2HSV);

                //Get the contours of the candidates to game objects
                obj_contours = detect_objects(vision_frame, robots).second;
                //Get the robots from the best candidates selected to game objects
                robots = fill_robots(obj_contours, robots);

                //Compute the variation of time for physics computations
                end = clock();
                elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
                deltaT = elapsed_secs;

                /***********************************
                 *     Physics Computations Step   *
                 ***********************************/

                //Compute the linear and angular velocity of the ball
                info.ball_vel.first /= deltaT;
                info.ball_vel.second /= deltaT;

                for(i = 0; i < 6; i++){
                    //Compute the linear and angular velocity of each robot
                    robots[i].compute_velocity(deltaT);
                    //Predict the robot state in the next n frames
                    robots[i].predict_info(deltaT*2);
                }

                if(!play){
                    //Draw information in the frame if the game is not being played
                    vision_frame = draw_robots(vision_frame, robots);
                    vision_frame = draw_field(vision_frame);
                }
                break;
            case 1: //Set color mode
                resize(raw_frame, raw_frame, Size(DEFAULT_NCOLS, DEFAULT_NROWS), 0, 0, INTER_CUBIC); // resize to 1024x768 resolution
                raw_frame = setting_mode(raw_frame, vision_frame, low, upper);

                break;
            default:
                break;
        }

       if(!play){
            //If the game is not being played, resize the frame, convert to QImage and send to be shown in the GUI
            cvtColor(raw_frame, raw_frame, CV_BGR2RGB);
            img = QImage((const uchar*)(raw_frame.data), raw_frame.cols, raw_frame.rows, raw_frame.step, QImage::Format_RGB888);
            img.bits();
        } 


       /***********************************
        *   Setting info to be sent step  *
        ***********************************/

        //Setting ball information
        info.ball_found = ball_found;
        if(ball_pos != null_point){
            info.ball_pos_cm = ball_pos_cm;
            info.ball_pos = ball_pos;
            info.ball_last_pos = ball_last_pos;
        }else{
            info.ball_pos_cm = Point2d(0.0, 0.0);
            info.ball_pos = Point(0, 0);
            info.ball_last_pos = Point(0, 0);
        }

        //Setting robots information
        info.enemy_robots[0] = robots[3];
        info.enemy_robots[1] = robots[4];
        info.enemy_robots[2] = robots[5];
        info.team_robots[0] = robots[0];
        info.team_robots[1] = robots[1];
        info.team_robots[2] = robots[2];

        FPS = 1.0/deltaT;

        //Sending information
        emit infoPercepted(info);
        emit processedImage(img);

        if(itr%10 == 0){
            emit framesPerSecond(FPS);
        }

        msleep(delay);
    }
}

bool Vision::open_camera(int camid)
{
    if(!cam.isOpened()){
        cam.open(camid);
    }

    if(cam.isOpened()){
        FPS = 60;
        return true;
    }

    this->camid = camid;

    return false;
}

void Vision::Play()
{
    if(!isRunning()){
        if(isStopped())
            stop = false;
        start();
    }
}

void Vision::updateFuzzyRobots(std::vector<Robot> team_robots){
    robots[0].set_flag_fuzzy(team_robots[0].get_flag_fuzzy());
    robots[1].set_flag_fuzzy(team_robots[1].get_flag_fuzzy());
    robots[2].set_flag_fuzzy(team_robots[2].get_flag_fuzzy());

    robots[0].set_output_fuzzy(team_robots[0].get_output_fuzzy());
    robots[1].set_output_fuzzy(team_robots[1].get_output_fuzzy());
    robots[2].set_output_fuzzy(team_robots[2].get_output_fuzzy());
}

void Vision::updateMoverRobots(std::vector<Robot> team_robots){
    robots[0].set_lin_vel(make_pair(team_robots[0].get_l_vel(), team_robots[0].get_r_vel()));
    robots[1].set_lin_vel(make_pair(team_robots[1].get_l_vel(), team_robots[1].get_r_vel()));
    robots[2].set_lin_vel(make_pair(team_robots[2].get_l_vel(), team_robots[2].get_r_vel()));
}

void Vision::switch_teams_areas(){
    Point temp = atk_centroid;
    atk_centroid = def_centroid;
    def_centroid = temp;

    teamsChanged = (teamsChanged)?false:true;
}

vector<Robot> Vision::get_robots()
{
    return robots;
}

void Vision::set_robots(vector<Robot> robots)
{
    this->robots = robots;
}

void Vision::set_ball(pair<vector<int>, vector<int> > ball){
    this->ball_color = ball;
}

void Vision::set_low(vector<int> low)
{
    this->low = low;
}

void Vision::set_upper(vector<int> upper)
{
    this->upper = upper;
}

vector<int> Vision::get_low(){
    return low;
}

vector<int> Vision::get_upper(){
    return upper;
}

void Vision::set_mode(int m)
{
    mode = m;
}

void Vision::set_camid(int cam){
    this->camid = cam;
}

void Vision::Stop()
{
    stop = true;
}

bool Vision::isStopped() const
{
    return this->stop;
}

bool Vision::is_open()
{
    return cam.isOpened();
}

void Vision::msleep(int ms)
{
    struct timespec ts = {ms / 1000, (ms % 1000) * 1000 * 1000};
    nanosleep(&ts, NULL);
}

void Vision::release_cam()
{
    cam.release();
}

int Vision::get_camID()
{
    return camid;
}

void Vision::show_area(bool show){
    showArea = show;
}

void Vision::show_names(bool show){
    showNames = show;
}

void Vision::show_centers(bool show){
    showCenters = show;
}

void Vision::show_errors(bool show){
    showErrors = show;
}

void Vision::togglePlay(bool play)
{
    this->play = play;
}

void Vision::save_image(){
    time_t t;
    string fname, path;

    srand((unsigned) time(&t));
    fname = to_string(rand() % 100000);
    fname = fname + "_img.jpg";
    path = "Img/" + fname;

    //cvtColor(raw_frame, to_save, CV_BGR2RGB);
    imwrite(path.c_str(), raw_frame);
}

void Vision::set_def_area(pVector def_points){
    this->tdef_points = def_points;
    //sentPoints = false;
}

void Vision::set_atk_area(pVector atk_points){
    this->tatk_points = atk_points;
    //sentPoints = false;
}

Vision::~Vision(){
    mutex.lock();
    stop = true;
    if(cam.isOpened())
        cam.release();
    condition.wakeOne();
    mutex.unlock();
    wait();
}

