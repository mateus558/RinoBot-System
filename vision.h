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
    bool stop;
    int mode, rows, cols, camid;
    double FPS;
    QMutex mutex;
    QWaitCondition condition;
    QImage img;
    Mat raw_frame;
    Mat vision_frame;
    VideoCapture cam;
    vector<int> low;
    vector<int> upper;
    pair<vector<int>, vector<int> > ball_color;
    Point ball_pos;
    vector<Robot> robots;
signals:
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
    Mat CLAHE_algorithm(Mat org);
    vector<Robot> get_robots();
    vector<Robot> fill_robots(vector<pMatrix> contours, vector<Robot> robots);
    Mat draw_robots(Mat frame, vector<Robot> robots);
    void proccess_frame(Mat, Mat);
    int get_camID();
    void set_robots(vector<Robot> robots);
    void set_ball(pair<vector<int>, vector<int> > ball);
    bool open_camera(int camid = CV_CAP_FIREWIRE);
    void Play();
    void Stop();
    void set_low(vector<int> low);
    void set_upper(vector<int> upper);
    vector<int> get_low();
    vector<int> get_upper();
    void set_mode(int m = 0);
    bool isStopped() const;
    bool is_open();
    void release_cam();
    ~Vision();
};

#endif // VISION_H
