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
//#include <opencv2/
#include <queue>
#include <utility>
#include <vector>
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
//#include <opencv2/tracking.hpp>

#include "robot.h"
#include "utils.h"

using namespace std;
using namespace cv;

/*!
 * \brief The Vision class is used to extract useful information from an image for robot soccer using
 * computer vision algorithms.
 */

class Vision: public QThread {  Q_OBJECT
public:
    struct Perception{
        bool ball_found;
        pair<double, double> ball_vel;
        Point ball_pos, ball_last_pos;
        Point2d ball_pos_cm;
        rVector enemy_robots, team_robots;
        pVector map_area, atk_area, def_area;
    };
private:
    bool stop, showArea, sentPoints, teamsChanged, showNames, showCenters, showErrors, trained;
    int mode, rows, cols, camid, x_offset, y_offset, cont;
    double FPS, deltaT;
    Mat kmeans_centers, labels, centers;
    Perception info;
    QMutex mutex;
    QWaitCondition condition;
    QImage img;
    Mat raw_frame, transf_matrix;
    Mat vision_frame;
    VideoCapture cam;
    vector<int> low;
    Rect2d ball_tracker;
    vector<Rect2d> objects_tracker;
    vector<bool> track_init;
    vector<int> upper;
    pair<vector<int>, vector<int> > ball_color;
    Point ball_pos;
    bool ball_found;
    Point2d ball_pos_cm;
    Point ball_last_pos;
    Point x_axis_slope, def_centroid, atk_centroid;
    pVector map_points, tmap_points;
    pVector atk_points, tatk_points;
    pVector def_points, tdef_points;
    Matrix3d last_P;
    vector<Robot> robots;

public slots:
    void updateFuzzyRobots(rVector);
    void updateGameFunctionsRobots(rVector);

signals:
    void infoPercepted(Vision::Perception);
    void processedImage(const QImage &image);
    void framesPerSecond(double FPS);
protected:
    void run();
    void msleep(int ms);
public:
    Vision(QObject *parent = 0);

    /*
     * Functions for pre-processing of the image.
     */

    /**
     * @brief train_kmeans Train kmeans to classify the pixels of the img.
     * @param img  Image used as sample.
     * @param nClusters Number of clusters used.
     * @return  Mat
     */
    Mat train_kmeans(Mat img, int nClusters);
    /**
     * @brief adjust_gamma  Adjust the luminosity of the image.
     * @param gamma Gamma value for the algorithm.
     * @param org Image to apply the adjustment.
     * @return Mat
     */
    Mat adjust_gamma(double gamma, Mat org);
    /**
     * @brief crop_image Crop a region from the image.
     * @param org Image to use.
     * @return Mat
     */
    Mat crop_image(Mat org);
    /**
     * @brief CLAHE_algorithm Used to improve the contrast of the image.
     * @param org Image to use.
     * @return Mat
     */
    Mat CLAHE_algorithm(Mat org);
    /**
     * @brief proccess_frame Pre-proccess the image for improvements.
     * @return Mat
     */
    Mat proccess_frame(Mat, Mat);

    /*
     * Functions for the detection and drawing of the robots.
     */

    /**
     * @brief fill_robots Identify the game objects and compute the centroids and angles.
     * @param contours Candidates to game objects.
     * @param robots Where the robots information will be stored.
     * @return vector<Robot>
     */
    vector<Robot> fill_robots(vector<pMatrix> contours, vector<Robot> robots);
    /**
     * @brief draw_robots Draw the robots and their info to the screen.
     * @param frame Frame where they will be draw.
     * @param robots Robots to draw.
     * @return Mat
     */
    Mat draw_robots(Mat frame, vector<Robot> robots);
    /**
     * @brief draw_field Draw the field points to the screen.
     * @param frame Frame where they will be draw.
     * @return Mat
     */
    Mat draw_field(Mat frame);
    /**
     * @brief detect_colors Returns a mask with the pixels in the given range (Thresholding).
     * @param vision_frame Frame where the thresholding will be applied.
     * @param low Lower limit of the pixel range.
     * @param upper Upper limit of the pixel range.
     * @return Mat
     */
    Mat detect_colors(Mat vision_frame, vector<int> low, vector<int> upper);
    /**
     * @brief detect_objects Detect the contours of the game objects.
     * @param frame Frame used for the detection.
     * @param robots Where the robots info will be stored.
     * @return vector of Contours
     */
    pair<vector<vector<Vec4i> >, vector<pMatrix> > detect_objects(Mat frame, vector<Robot> robots);

    /*
     * Configuration functions.
     */

    Mat setting_mode(Mat raw_frame, Mat vision_frame, vector<int> low, vector<int> upper);
    bool open_camera(int camid = CV_CAP_FIREWIRE);
    void Play();
    void Stop();
    void switch_teams_areas();
    void show_area(bool show);
    void show_centers(bool show);
    void show_names(bool show);
    void show_errors(bool show);
    void save_image();
    void release_cam();

    /*
     * Get and set functions.
     */

    vector<Robot> get_robots();
    int get_camID();
    void set_robots(vector<Robot> robots);
    void set_ball(pair<vector<int>, vector<int> > ball);   
    void set_low(vector<int> low);
    void set_def_area(pVector def_points);
    void set_atk_area(pVector atk_points);
    void set_upper(vector<int> upper);
    void set_camid(int cam);
    vector<int> get_low();
    vector<int> get_upper();
    void set_mode(int m = 0);
    bool isStopped() const;
    bool is_open();
    ~Vision();
};

#endif // VISION_H

