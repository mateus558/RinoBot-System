#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <cmath>
#include <ctime>
#include <QMessageBox>
#include "vision.h"

using namespace std;

Point null_point = Point(-1, -1);

Vision::Vision(QObject *parent): QThread(parent)
{
    stop = true;
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

bool sort_by_larger_area(vector<Point> p0, vector<Point> p1)
{
    return contourArea(p0) < contourArea(p1);
}

vector<Robot> Vision::fill_robots(vector<pMatrix> contours, vector<Robot> robots)
{
    int i, j, csize, k;
    double dista = 0.0, distb = 0.0, radius = 100;
    Moments ball_moment;
    Point ball_cent(-1, -1), unk_robot, centroid;
    vector<vector<Moments> > r_m(3, vector<Moments>());
    vector<vector<Moments> > t_m(2, vector<Moments>(3, Moments()));
    vector<vector<Point> > r_col_cent(3, vector<Point>());
    vector<vector<Point> > tirj_cent(2, vector<Point>(3, Point(-1, -1)));

    //Get the ball moment from the contour
    if(contours[0].size() != 0){
        ball_moment = moments(contours[0][contours[0].size()-1]);
        //Get ball centroid
        ball_cent = Point(ball_moment.m10/ball_moment.m00, ball_moment.m01/ball_moment.m00);
    }else{
        cout << "Ball not found!" << endl;
        ball_cent = null_point;
    }
    sort(contours[1].begin(), contours[1].end(), sort_by_larger_area);
    sort(contours[2].begin(), contours[2].end(), sort_by_larger_area);

    //Get the robots moments (their team color half)
    for(i = 0; i < 2; ++i){
        for(j = 0; j < contours[i+1].size(); ++j){
            if(contours[i+1].size() > 0){
                t_m[i][j] = moments(contours[i+1][j]);
                //Get centroid from robot team color half
                tirj_cent[i][j] = Point(t_m[i][j].m10/t_m[i][j].m00, t_m[i][j].m01/t_m[i][j].m00);
            }else{
                tirj_cent[i][j] = Point(-1, -1);
            }
        }
    }
    cout << contours[2].size() << " robots found on team 2" << endl;
    cout << contours[1].size() << " robots found on team 1" << endl;
    //Get the robots moments (their color half)
    for(i = 0; i < 3; ++i){
        csize = contours[i + 3].size();
        if(csize > 0){
            r_m[i] = vector<Moments>(csize);
            for(j = 0; j < csize; ++j)
                r_m[i][j] = moments(contours[i + 3][j]);
            //Get centroid from robot color half
            r_col_cent[i] = vector<Point>(csize, Point(-1, -1));
            for(j = 0; j < csize; ++j){
                r_col_cent[i][j] = Point(r_m[i][j].m10/r_m[i][j].m00, r_m[i][j].m01/r_m[i][j].m00);
            }
        }else{
            r_col_cent[i] = vector<Point>(1);
            r_col_cent[i][0] = null_point;
            cout << robots[i].get_nick() << " not found!" << endl;
            robots[i].set_centroid(Point(-1, -1));
        }
    }

    vector<bool> r_set(r_col_cent.size(), false);
    int tsize, r_label = 0, col_size, cand_size, min;
    pair<Point, pair<int, int> > col_select;

    tsize = tirj_cent[0].size();
    cout << tsize << endl;
    //Define team 1 centroids and angles
    for(i = 0; i < tsize; ++i){
        unk_robot = tirj_cent[0][i];

        for(j = 0, min = 20000; j < r_col_cent.size(); ++j){
            if(r_set[j]) continue;
            for(k = 0; k < r_col_cent[j].size(); ++k){
                dista = euclidean_dist(unk_robot, r_col_cent[j][k]);

                if(dista < min){
                    min = dista;
                    cout << dista << " " << j << " " <<r_col_cent[j][k].x << "," << r_col_cent[j][k].y << " " <<unk_robot.x << "," <<unk_robot.y << endl;

                    col_select = make_pair(r_col_cent[j][k], make_pair(j, k));
                }
            }
        }
        cout << col_select.second.first << "," << col_select.second.second << endl;

        r_label = col_select.second.first;
        centroid = (unk_robot + col_select.first)/2;
        robots[r_label].set_team_cent(unk_robot);
        robots[r_label].set_color_cent(col_select.first);
        centroid = Point((unk_robot.x + col_select.first.x)/2, (unk_robot.y + col_select.first.y)/2);
        robots[r_label].set_centroid(centroid);
        robots[r_label].set_angle(angle_two_points(centroid, col_select.first));
        r_set[col_select.second.first] = true;
        cout << "Robo " << r_label << ", team cent = (" << unk_robot.x << "," <<unk_robot.y << "), "
             << "color cent= (" << centroid.x << "," << centroid.y << "), angle=" <<robots[i].get_angle() << endl;

    }

    for(i = 0; i < r_set.size(); ++i){
       if(!r_set[i]) cout << robots[i].get_nick() << " was not found!" << endl;
    }
    //Define team 2 centroids and angles
    for(i = 3, dista = INFINITY; i < 6; ++i){
        robots[i].set_team_cent(tirj_cent[1][i-3]);
        robots[i].set_centroid(robots[i].get_team_cent());
    }

    ball_pos = ball_cent;
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
    imshow("t1", out_team1);

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
    Point cent, team_cent, color_cent;

    if(ball_pos != null_point)
        circle(frame, ball_pos, 20, Scalar(255, 0, 0));

    for(i = 0; i < size-3; ++i){
        cent = robots[i].get_centroid();
        team_cent = robots[i].get_team_cent();
        color_cent = robots[i].get_color_cent();

        if(cent == null_point) continue;
        circle(frame, team_cent, 5, Scalar(0, 255, 0), 1*(i+1));
        circle(frame, color_cent, 5, Scalar(0, 255, 0), 1*(i+1));
        circle(frame, cent, 5, Scalar(0, 255, 0), 1*(i+1));
        circle(frame, color_cent, 20, Scalar(0, 255, 0), 1.5);
        line(frame, cent,Point(cent.x + 20 * cos((robots[i].get_angle()* PI) / 180), cent.y - 20 * sin((robots[i].get_angle() * PI)/180)) , Scalar(0, 255, 0), 1);
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
    int i = 0;
    Mat res;
    double elapsed_secs;
    clock_t begin, end;
    vector<pMatrix> obj_contours;

    while(!stop){
        begin = clock();

        if(!cam.read(raw_frame)){
            stop = true;
            continue;
        }

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
                img = QImage((uchar*)(vision_frame.data), vision_frame.cols, vision_frame.rows, QImage::Format_RGB888);
                break;
            case 1: //Set color mode
                res = setting_mode(raw_frame, vision_frame, low, upper);
                img = QImage((uchar*)(res.data), res.cols, res.rows, QImage::Format_RGB888);
                break;
            default:
                break;
         }

        end = clock();
        elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        FPS = 1/elapsed_secs;

        emit robotsInfo(robots);
        emit ballPos(ball_pos);
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

Vision::~Vision(){
    mutex.lock();
    stop = true;
    cam.release();
    condition.wakeOne();
    mutex.unlock();
    wait();
}
