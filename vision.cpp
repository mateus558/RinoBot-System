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
    stop = true;
    showArea = sentPoints = teamsChanged = false;
    mode = 0;
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

    if(!read_points("Config/map", map_points)){
        cerr << "The map could not be read from the file!" << endl;
    }
    if(!read_points("Config/attack_area", atk_points)){
        cerr << "The attack area could not be read from the file!" << endl;
    }
    if(!read_points("Config/defense_area", def_points)){
        cerr << "The defense area could not be read from the file!" << endl;
    }
    x_axis_slope = map_points[0] - map_points[9];

    last_P = MatrixXd::Identity(3,3);

    /*for( Point p : map_points)
        cout << p.x << " " << p.y << endl;
    cout << map_points.size() << endl;
    */
}

Mat Vision::detect_colors(Mat vision_frame, vector<int> low, vector<int> upper) //Detect colors in [low,upper] range
{
    Mat mask;
    //Generate mask with the points in the range
    inRange(vision_frame, Scalar(low[0],low[1],low[2]), Scalar(upper[0],upper[1],upper[2]), mask);
    //Attempt to removelibgtk2.0-dev noise (or small objects)
    morphologyEx(mask, mask, MORPH_OPEN, Mat(), Point(-1, -1), 2);
    morphologyEx(mask, mask, MORPH_CLOSE, Mat(), Point(-1, -1), 2);

    return mask;
}

vector<Robot> Vision::fill_robots(vector<pMatrix> contours, vector<Robot> robots)
{
    int i, j, csize, k, tsize, r_label = 0, min, t1size, tmin;
    double dista = 0.0, angle, last_angle;
    bool not_t1;
    Moments ball_moment, temp_moment;
    Point ball_cent(-1, -1), unk_robot, centroid, line_slope, last_cent;
    //Point2f pos;
    vector<vector<Moments> > r_m(3, vector<Moments>());
    vector<vector<Moments> > t_m(2, vector<Moments>());
    vector<pVector > r_col_cent(3, pVector());
    vector<pVector > tirj_cent(2, pVector());
    pair<Point, pair<int, int> > col_select;
    Vector3d pos_cam, last_pos;
    Vector2d v_w;
    pair<Matrix3d, Vector3d> kalman_res;

//cout << 1 << endl;
    //Get the ball moment from the contour
    if(contours[0].size() != 0){
        ball_moment = moments(contours[0][contours[0].size()-1]);
        //Get ball centroid
        ball_cent = Point(ball_moment.m10/ball_moment.m00, ball_moment.m01/ball_moment.m00);
        ball_last_pos = ball_cent;
    }else{
        cout << "Ball not found!" << endl;
        ball_cent = ball_last_pos;
    }
    sort(contours[1].begin(), contours[1].end(), sort_by_larger_area);
    sort(contours[2].begin(), contours[2].end(), sort_by_larger_area);
    //cout << 2 << endl;
    //Get the robots moments (their team color half)
    for(i = 0; i < 2; ++i){
        for(j = 0; j < contours[i+1].size(); ++j){
            temp_moment = moments(contours[i+1][j]);
            t_m[i].push_back(temp_moment);
            //Get centroid from robot team color half
            tirj_cent[i].push_back(Point(t_m[i][j].m10/t_m[i][j].m00, t_m[i][j].m01/t_m[i][j].m00));

        }
    }
    //cout << tirj_cent[1].size() << " robots found on team 2" << endl;
    //cout << tirj_cent[0].size() << " robots found on team 1" << endl;
    //Get the robots moments (their color half)
    for(i = 0; i < 3; ++i){
        //cout <<"" <<contours.size() << endl;
        //cout <<"" <<contours[i+3].size() << endl;
        //cout << i << endl;
        csize = contours[i + 3].size();
        if(csize > 0){
            //cout << "csize = " << csize << endl;
            for(j = 0; j < csize; ++j){
              //  cout << "j = " << j << endl;
                temp_moment = moments(contours[i + 3][j]);
                r_m[i].push_back(temp_moment);
            }
            //Get centroid from robot color half
            for(j = 0; j < csize; ++j){
                r_col_cent[i].push_back(Point(r_m[i][j].m10/r_m[i][j].m00, r_m[i][j].m01/r_m[i][j].m00));
                //cout << "j = " << j << endl;
            }

        }else{
            r_col_cent[i].push_back(null_point);
            cout << robots[i].get_nick() << " not found!" << endl;
            robots[i].set_centroid(robots[i].get_from_pos_hist(0));
        }
    }
    vector<bool> r_set(r_col_cent.size(), false);

    tsize = tirj_cent[0].size();
    t1size = (tirj_cent[1].size() < 3)?3+tirj_cent[1].size():6;
    //cout << tsize << endl;
    //Define team 1 centroids and angles
    for(i = 0; i < tsize; ++i){
        unk_robot = tirj_cent[0][i];
        not_t1 = false;

        for(j = 0, min = 20000; j < r_col_cent.size(); ++j){
            if(r_set[j]) continue;
            for(k = 0; k < r_col_cent[j].size(); ++k){
                dista = euclidean_dist(unk_robot, r_col_cent[j][k]);

                if(dista < min){
                    //cout << dista << " " << j << " " <<r_col_cent[j][k].x << "," << r_col_cent[j][k].y << " " <<unk_robot.x << "," <<unk_robot.y << endl;
                    min = dista;
                    tmin = min;
                    col_select = make_pair(r_col_cent[j][k], make_pair(j, k));
                }
            }
        }
        for(k = 3; k < t1size; ++k){
            dista = euclidean_dist(tirj_cent[1][k-3], col_select.first);
            if(dista < tmin){
                not_t1 = true;
                break;
            }
        }
        //cout << col_select.second.first << "," << col_select.second.second << endl;

        r_label = col_select.second.first;
        last_cent = robots[r_label].get_from_pos_hist(0);
        last_angle = robots[r_label].get_last_angle();

        if(!not_t1){
            line_slope = col_select.first - unk_robot;

            robots[r_label].set_team_cent(unk_robot);
            robots[r_label].set_color_cent(col_select.first);
            robots[r_label].set_line_slope(line_slope);

            centroid = Point((unk_robot.x + col_select.first.x)/2, (unk_robot.y + col_select.first.y)/2);
            angle = (col_select.first.x >= unk_robot.x)?angle_two_points(line_slope, x_axis_slope):-angle_two_points(line_slope, x_axis_slope);
            if(teamsChanged) angle = angle * -1;

            /*pos_cam << centroid.x / 100,
                       centroid.y / 100,
                       angle;
            last_pos << last_cent.x / 100,
                        last_cent.y / 100,
                        last_angle;
            v_w << 5,
                   4;

            kalman_res = kalman_filter(pos_cam, v_w, last_pos, 9, last_P);
            last_P = kalman_res.first;
            centroid.x = kalman_res.second(0) * 100;
            centroid.y = kalman_res.second(1) * 100;
            angle = kalman_res.second(2);*/

            robots[r_label].set_angle(angle);
            robots[r_label].set_centroid(centroid);
            //robots[r_label].set_pos(coords[centroid.x][centroid.y]);
            //cout << "line slope = (" << line_slope.x << ", " << line_slope.y << ")" <<endl;
            //cout << "x axis slope = (" << x_axis_slope.x << ", " << x_axis_slope.y << ")" <<endl;
            //cout << robots[r_label].get_nick() << " angle = " << robots[r_label].get_angle() << endl;
            //cout << robots[r_label].get_nick() << " CENTROID = (" << centroid.x << ", " << centroid.y << ") " << endl;
            //cout << robots[r_label].get_nick() << " color CENTROID = (" << col_select.first.x << ", " << col_select.first.y << ") " << endl;
            //cout << robots[r_label].get_nick() << " team CENTROID = (" << unk_robot.x << ", " << unk_robot.y << ") " << endl;
            //cout<< "map[0] = (" << x_axis_slope.x << ", " << x_axis_slope.y << ") " << endl;
            //cout<< "map[9] = (" << line_slope.x << ", " << line_slope.y << ") " << endl;
            //pos = robots[r_label].get_pos();
            //cout << robots[r_label].get_nick() << "pos in cm = (" << pos.x << ", " << pos.y << ") " << endl;
        }else{
            robots[r_label].set_centroid(last_cent);
            robots[r_label].set_angle(last_angle);
        }
        r_set[col_select.second.first] = true;

        //cout << "Robo " << r_label << ", team cent = (" << unk_robot.x << "," <<unk_robot.y << "), "
        //    << "color cent= (" << col_select.first.x << "," << col_select.first.y << "), angle=" <<robots[i].get_angle() << endl;

    }

    for(i = 0; i < r_set.size(); ++i){
       if(!r_set[i]) cout << robots[i].get_nick() << " was not found!" << endl;
    }

    //Define team 2 centroids and angles
    //cout << t1size << endl;
    for(i = 3, dista = INFINITY; i < t1size; ++i){
        robots[i].set_team_cent(tirj_cent[1][i-3]);
        //cout << tirj_cent[1][i-3].x << " " << tirj_cent[1][i-3].y << endl;
        robots[i].set_centroid(robots[i].get_team_cent());
    }
    ball_pos_cm.x = ball_pos.x * X_CONV_CONST;
    ball_pos_cm.y = ball_pos.y * Y_CONV_CONST;
    ball_pos = ball_cent;
    //cout << "OK!" << endl;
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

    out_ball = detect_colors(frame, low, upper);

    findContours(out_ball, contours[0], hierarchy[0], RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    findContours(out_team1, contours[1], hierarchy[1], RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    findContours(out_team2, contours[2], hierarchy[2], RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    findContours(out_r[0], contours[3], hierarchy[3], RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    findContours(out_r[1], contours[4], hierarchy[4], RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    findContours(out_r[2], contours[5], hierarchy[5], RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

    ret.first = hierarchy;
    ret.second = contours;

  /*imshow("t1", out_team1);
    imshow("r2", out_r[1]);
    imshow("r3", out_r[2]);*/
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

Mat Vision::CLAHE_algorithm(Mat org)    //Normalize frame histogram
{
    Mat lab_image, dst;
    vector<Mat> lab_planes(3);

    cvtColor(org, lab_image, CV_BGR2Lab);
    split(lab_image, lab_planes);

    //Apply CLAHE to the luminosity plane of the LAB frame
    Ptr<CLAHE> clahe = createCLAHE(2.0, Size(8,8));
    clahe->apply(lab_planes[0], dst);

    //Merge back the planes
    dst.copyTo(lab_planes[0]);
    merge(lab_planes, lab_image);

    cvtColor(lab_image, dst, CV_Lab2RGB);

    return dst;
}

Mat Vision::crop_image(Mat org){
    Mat cropped;
    Size size;
    Point2f pts[4], pts1[3], pts2[3];
    RotatedRect box;
    pVector roi(4), aux_y;
    vector<Point2f> vec;

    pts2[0] = Point(0, 0);
    pts2[1] = Point(0, size.height-1);
    pts2[2] = Point(size.width-1, 0);

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
        transform(map_points, tmap_points, transf_matrix);
        transform(def_points, tdef_points, transf_matrix);
        transform(atk_points, tatk_points, transf_matrix);
        emit mapPoints(tmap_points);
        emit atkPoints(tatk_points);
        emit defPoints(tdef_points);
        sentPoints = true;
    }
    warpAffine(org, cropped, transf_matrix, size, INTER_LINEAR, BORDER_CONSTANT);
    //  imshow("crop", cropped);
    return cropped;
}

Mat Vision::proccess_frame(Mat orig, Mat dest) //Apply enhancement algorithms
{
    dest = orig.clone();
    //Gamma correction
    dest = adjust_gamma(1.5 , dest);
    //Apply histogram normalization
    //dest = CLAHE_algorithm(dest);
    //Apply gaussian blur
     GaussianBlur(dest, dest, Size(5,5), 2);

     return dest;
}

Mat Vision::setting_mode(Mat raw_frame, Mat vision_frame, vector<int> low, vector<int> upper)   //Detect colors in [low,upper] range
{
    Mat mask, res;

    mask = detect_colors(vision_frame, low, upper);
    cvtColor(raw_frame, raw_frame, CV_BGR2RGB);
    raw_frame.copyTo(res, mask);

    return res;
}

Mat Vision::draw_robots(Mat frame, vector<Robot> robots)
{
    int i, size = robots.size();
    Point cent, team_cent, color_cent, inter;

    if(ball_pos != null_point)
        circle(frame, ball_pos, 20, Scalar(255, 0, 0));

    for(i = 0; i < size-3; ++i){
        cent = robots[i].get_centroid();
        team_cent = robots[i].get_team_cent();
        color_cent = robots[i].get_color_cent();

        if(cent == null_point) continue;
        //circle(frame, team_cent, 5, Scalar(0, 255, 0), 1*(i+1));
        //circle(frame, color_cent, 5, Scalar(0, 255, 0), 1*(i+1));
        //circle(frame, cent, 5, Scalar(0, 255, 0), 1*(i+1));
        circle(frame, cent, 20, Scalar(0, 255, 0), 1.5);
        inter = Point(cent.x + 20 * cos(robots[i].get_angle() * PI / 180.0), cent.y + 20 * sin(robots[i].get_angle() * PI / 180.0));
        //circle(frame, inter, 5, Scalar(0, 0, 255), 1*(i+1));
        line(frame, cent, inter, Scalar(0, 255, 0), 1);
        //line(frame, cent, color_cent, Scalar(0, 255, 0), 1);
        putText(frame, robots[i].get_nick(), cent + Point(0, -2), FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 0), 2);
    }

    for(i = size-3; i < size; ++i){
        cent = robots[i].get_centroid();
        if(cent == null_point) continue;
        else cent += Point(2,2);
        circle(frame, cent , 20, Scalar(0, 0, 255), 1);
    }

    return frame;
}

void Vision::run()
{
    int delay = (1000/this->FPS);
    int i = 0, atk_size = atk_points.size(), map_size = map_points.size(), def_size = def_points.size();
    double elapsed_secs;
    clock_t begin, end;
    vector<pMatrix> obj_contours;
    Point def_cent, atk_cent;

    while(!stop){
        begin = clock();

        if(!cam.read(raw_frame)){
            stop = true;
            cerr << "A frame could not be read! (Vision)" << endl;
            return;
        }

        raw_frame = crop_image(raw_frame);

        rows = raw_frame.rows;
        cols = raw_frame.cols;
        vision_frame = raw_frame.clone();
        vision_frame = proccess_frame(raw_frame, vision_frame);

        switch(mode){
            case 0: //Visualization mode
                obj_contours = detect_objects(vision_frame, robots).second;
                robots = fill_robots(obj_contours, robots);
                vision_frame = draw_robots(vision_frame, robots);

                cvtColor(vision_frame, vision_frame, CV_BGR2RGB);
                break;
            case 1: //Set color mode
                vision_frame = setting_mode(raw_frame, vision_frame, low, upper);

                break;
            default:
                break;
         }

        if(showArea && map_size > 0){
            for(i = 0; i < map_size; ++i){
                circle(vision_frame, tmap_points[i], 1, Scalar(0,0,255), 2);
            }
            for(i = 0; i < atk_size; ++i){
                circle(vision_frame, tatk_points[i], 1, Scalar(255,0,0), 2);
                atk_cent = atk_cent + tatk_points[i];
            }
            atk_cent = Point(atk_cent.x/tatk_points.size(), atk_cent.y/tatk_points.size());
            //cout << atk_cent.x << " " << atk_cent.y << endl;
            putText(vision_frame, "ATK Area", atk_cent, FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 0), 2);
            for(i = 0; i < def_size; ++i){
                circle(vision_frame, tdef_points[i], 1, Scalar(0,255,0), 2);
                def_cent = def_cent + tdef_points[i];
            }
            def_cent = Point(def_cent.x/tdef_points.size(), def_cent.y/tdef_points.size());
           //cout << def_cent.x << " " << def_cent.y << endl;
            putText(vision_frame, "DEF Area", def_cent, FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 0), 2);
        }
        //cvtColor(raw_frame, raw_frame, CV_BGR2RGB);
        //img = QImage((uchar*)(raw_frame.data), raw_frame.cols, raw_frame.rows, raw_frame.step, QImage::Format_RGB888);
        img = QImage((uchar*)(vision_frame.data), vision_frame.cols, vision_frame.rows, vision_frame.step, QImage::Format_RGB888);
        end = clock();
        elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        FPS = 1/elapsed_secs;

        emit ballPos(ball_pos_cm);
        emit robotsInfo(robots);
        emit processedImage(img);
        if(i%10 == 0){
            emit framesPerSecond(FPS);
            i = 0;
        }

        msleep(delay);
        i++;
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
        start(LowPriority);
    }
}

void Vision::switch_teams_areas(){
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

void Vision::save_image(){
    time_t t;
    string fname, path;
    Mat to_save;

    srand((unsigned) time(&t));
    fname = to_string(rand() % 100000);
    fname = fname + "_img.jpg";
    path = "Img/" + fname;

    cvtColor(raw_frame, to_save, CV_BGR2RGB);
    imwrite(path.c_str(), to_save);
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
