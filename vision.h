#ifndef VISION_H
#define VISION_H

#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <robot.h>
#include <vector>

using namespace std;
using namespace cv;

class Vision: public QThread {  Q_OBJECT
private:
    bool stop;
    QMutex mutex;
    QWaitCondition condition;
    QImage img;
    Mat raw_frame;
    Mat vision_frame;
    double FPS;
    VideoCapture cam;
    int mode;
    vector<Robot> robots;
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
