#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <utility>
#include <Eigen/Dense>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include "robot.h"

#define FIELD_WIDTH 132
#define FIELD_HEIGHT 175
#define MIN_ROBOT_AREA 50
#define MAX_ROBOT_AREA 500
#define MIN_BALL_AREA 50
#define MAX_BALL_AREA 100
#define MAX_CENT_DIST 20
#define DEFAULT_NROWS 382   //Default number of the rows of the frame
#define DEFAULT_NCOLS 505   //Default number of the columns of the frame
#define X_CONV_CONST 0.346534653   //Conversion constant for the X axis (cm/px) height/cols
#define Y_CONV_CONST 0.345549738 //Conversion constant for the Y axis (cm/px) width/rows
#define COORD_BLOCK_SIZE 1  //Size of the coord unit in cm^2
#define PI 3.14159265
#define INF 2000000

//175cmx132cm - field
using namespace cv;
using namespace Eigen;

//typedef std::vector<Robot> rVector; //Robots vector
typedef std::vector<Point> pVector; //Point vector
typedef std::vector<Point2d> p2dVector; //Point of doubles vector
typedef std::vector<std::vector<int> > iMatrix; //int matrix template
typedef std::vector<std::vector<double> > dMatrix;  //Double Matrix template
typedef std::vector<std::vector<Point> > pMatrix; //Point matrix template
typedef std::vector<std::vector<Point2d> > p2dMatrix; //double precision Point matrix template

IplImage* img_resize(IplImage* src_img, int new_width,int new_height);
double euclidean_dist(Point2d p, Point2d q);
double angle_two_points(Point2d p, Point2d q);
std::pair<Matrix3d, Vector3d> kalman_filter(Vector3d pos_cam, Vector2d v_w, Vector3d last_pos , double dt, Matrix3d last_P);
vector<int> hsv2rgb(vector<int> in);
bool read_points(std::string fname, std::vector<Point> &points);
bool sort_by_larger_area(std::vector<Point> p0, std::vector<Point> p1);
bool sort_by_smallest_y(Point a, Point b);
bool sort_by_smallest_x(Point a, Point b);
bool sort_by_largest_y(Point a, Point b);
bool sort_by_largest_x(Point a, Point b);
bool area_limit(std::vector<Point> p);
bool ball_area_limit(std::vector<Point> p);


#endif // UTILS_H
