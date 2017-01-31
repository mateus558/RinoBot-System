#ifndef VISION_H
#define VISION_H

#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <QtConcurrent/QtConcurrent>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <queue>
#include <utility>
#include <vector>
#include "robot.h"
#include "utils.h"

using namespace std;
using namespace cv;

class Vision: public QThread {  Q_OBJECT
private:
    bool stop, showArea, sentPoints;
    int mode, rows, cols, camid, x_offset, y_offset;
    double FPS;
    QMutex mutex;
    QWaitCondition condition;
    QImage img;
    Mat raw_frame, transf_matrix;
    Mat vision_frame;
    VideoCapture cam;
    vector<int> low;
    vector<int> upper;
    pair<vector<int>, vector<int> > ball_color;
    Point ball_pos;
    Point ball_last_pos;
    pVector map_points, tmap_points;
    pVector atk_points, tatk_points;
    pVector def_points, tdef_points;
    vector<Robot> robots;
signals:
    void ballPos(Point ball);
    void robotsInfo(const rVector &robots);
    void processedImage(const QImage &image);
    void framesPerSecond(double FPS);
    void mapPoints(const pVector &map_points);
    void atkPoints(const pVector &atk_points);
    void defPoints(const pVector &def_points);
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
    void set_low(vector<int> low);
    void set_def_area(pVector def_points);
    void set_atk_area(pVector atk_points);
    void show_area(bool show);
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
