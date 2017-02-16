#ifndef VISION_H
#define VISION_H

#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <QtConcurrent/QtConcurrent>
//#include <opencv2/core/core.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
#include <queue>
#include <utility>
#include <vector>
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>

#include "robot.h"
#include "utils.h"

using namespace std;
using namespace cv;

class Vision: public QThread {  Q_OBJECT
public:
    struct Perception{
        bool ball_found;
        Point ball_pos, ball_last_pos;
        Point2d ball_pos_cm;
        rVector enemy_robots, team_robots;
        pVector map_area, atk_area, def_area;
    };
private:
    bool stop, showArea, sentPoints, teamsChanged, showNames, showCenters, showErrors;
    int mode, rows, cols, camid, x_offset, y_offset, cont;
    double FPS;
    Perception info;
    QMutex mutex;
    QWaitCondition condition;
    QImage img;
    Mat raw_frame, transf_matrix;
    Mat vision_frame;
    VideoCapture cam;
    vector<int> low;
    Ptr<Tracker> tracker;
    Rect2d ball_tracker;
    vector<Rect2d> objects_tracker;
    vector<bool> track_init;
    vector<int> upper;
    pair<vector<int>, vector<int> > ball_color;
    Point ball_pos;
    bool ball_found;
    Point2d ball_pos_cm;
    Point ball_last_pos;
    Point x_axis_slope;
    pVector map_points, tmap_points;
    pVector atk_points, tatk_points;
    pVector def_points, tdef_points;
    Matrix3d last_P;
    vector<Robot> robots;
signals:
    void infoPercepted(Vision::Perception);
    void processedImage(const QImage &image);
    void framesPerSecond(double FPS);
protected:
    void run();
    void msleep(int ms);
public:
    Vision(QObject *parent = 0);
    Mat detect_colors(Mat vision_frame, vector<int> low, vector<int> upper);
    pair<vector<vector<Vec4i> >, vector<pMatrix> > detect_objects(Mat frame, vector<Robot> robots);
    Mat setting_mode(Mat raw_frame, Mat vision_frame, vector<int> low, vector<int> upper);
    Mat adjust_gamma(double gamma, Mat org);
    Mat crop_image(Mat org);
    Mat CLAHE_algorithm(Mat org);
    vector<Robot> get_robots();
    vector<Robot> fill_robots(vector<pMatrix> contours, vector<Robot> robots);
    Mat draw_robots(Mat frame, vector<Robot> robots);
    Mat proccess_frame(Mat, Mat);
    int get_camID();
    void set_robots(vector<Robot> robots);
    void set_ball(pair<vector<int>, vector<int> > ball);
    bool open_camera(int camid = CV_CAP_FIREWIRE);
    void Play();
    void Stop();
    void switch_teams_areas();
    void set_low(vector<int> low);
    void set_def_area(pVector def_points);
    void set_atk_area(pVector atk_points);
    void show_area(bool show);
    void show_centers(bool show);
    void show_names(bool show);
    void show_errors(bool show);
    void save_image();
    void set_upper(vector<int> upper);
    void set_camid(int cam);
    vector<int> get_low();
    vector<int> get_upper();
    void set_mode(int m = 0);
    bool isStopped() const;
    bool is_open();
    void release_cam();
    ~Vision();
};

#endif // VISION_H
