#include "vision.h"
#include <time.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <QMessageBox>

using namespace std;

Vision::Vision(QObject *parent): QThread(parent)
{
    stop = true;
    mode = 0;
    robots.resize(3);
    robots[0].set_nick("Leona");
    robots[1].set_nick("Gandalf");
    robots[2].set_nick("Presto");
    low.resize(3);
    upper.resize(3);
    low = {0,0,0};
    upper = {255, 255, 255};
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

Mat Vision::adjust_gamma(double gamma, Mat org)
{
    if(gamma == 1.0)
        return org;

    double inv_gamma = 1.0 / gamma;

    Mat lut_matrix(1, 256, CV_8UC1);
    uchar *ptr = lut_matrix.ptr();

    for(int i = 0; i < 256; i++)
        ptr[i] = (int)(pow((double)i / 255.0, inv_gamma) * 255.0);

    Mat result;
    LUT(org, lut_matrix, result);

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

void Vision::proccess_frame(Mat orig, Mat dest) //Apply enhancement algorithms
{
    dest = orig.clone();
    //Gamma correction
    dest = adjust_gamma(1.0, dest);
    //Apply histogram normalization
    dest = CLAHE_algorithm(dest);
    //Apply gaussian blur
    GaussianBlur(dest, dest, Size(5,5), 2);
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

Mat Vision::setting_mode(Mat raw_frame, Mat vision_frame, vector<int> low, vector<int> upper)   //Detect colors in [low,upper] range
{
    Mat mask, res;

    mask = detect_colors(vision_frame, low, upper);
    cvtColor(raw_frame, raw_frame, CV_BGR2RGB);
    raw_frame.copyTo(res, mask);

    return res;
}

void Vision::run()
{
    int delay = (1000/this->FPS);
    int i = 0;
    Mat res;
    double elapsed_secs;
    clock_t begin, end;

    while(!stop){
        begin = clock();

        if(!cam.read(raw_frame)){
            stop = true;
            continue;
        }

        vision_frame = raw_frame.clone();
        proccess_frame(raw_frame, vision_frame);

        switch(mode){
            case 0: //Visualization mode
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

        emit processedImage(img);
        if(i%10 == 0){
            emit framesPerSecond(FPS);
            i = 0;
        }

        msleep(delay);
        i++;
    }
}

vector<Robot> Vision::get_robots(){
    return robots;
}

void Vision::set_robots(vector<Robot> robots){
    this->robots = robots;
    cout << this->robots[0].get_ID() << " " << this->robots[1].get_ID() << " " << this->robots[2].get_ID() << endl;
}

void Vision::set_mode(int m)
{
    mode = m;
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

Vision::~Vision(){
    mutex.lock();
    stop = true;
    cam.release();
    condition.wakeOne();
    mutex.unlock();
    wait();
}
