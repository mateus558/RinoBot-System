#ifndef VISION_H
#define VISION_H

#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <QtConcurrent/QtConcurrent>
//#include <QFuture>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <robot.h>
#include <queue>
#include <vector>

using namespace std;
using namespace cv;

class Vision: public QThread {  Q_OBJECT
private:
    bool stop;
    int mode, rows, cols;
    double FPS;
    QMutex mutex;
    QWaitCondition condition;
    QImage img;
    Mat raw_frame;
    Mat vision_frame;
    VideoCapture cam;
    vector<Robot> robots;

    void add_adjacents(queue<Point> &pilha, Point u, bool **visited);
signals:
    void processedImage(const QImage &image);
    void framesPerSecond(double FPS);
protected:
    void run();
    void msleep(int ms);
public:
    vector<int> low;
    vector<int> upper;
    Vision(QObject *parent = 0);
    void proccess_frame(Mat, Mat);
    Mat detect_colors(Mat vision_frame, vector<int> low, vector<int> upper);
    Mat setting_mode(Mat raw_frame, Mat vision_frame, vector<int> low, vector<int> upper);
    Mat adjust_gamma(double gamma, Mat org);
    Mat CLAHE_algorithm(Mat org);
    vector<Robot> get_robots();
    void set_robots(vector<Robot> robots);
    void detect_robots(Mat frame, vector<Robot> robots);
    bool open_camera(int camid = 0);
    void Play();
    void Stop();
    void set_mode(int m = 0);
    bool isStopped() const;
    bool is_open();
    void release_cam();
    ~Vision();
};

#endif // VISION_H
