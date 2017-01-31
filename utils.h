#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include <utility>
#include <Eigen/Dense>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#define PI 3.14159265

using namespace cv;
using namespace Eigen;

typedef std::vector<std::vector<Point> > pMatrix; //Point matrix type

double euclidean_dist(Point p, Point q);
double angle_two_points(Point p, Point q);
std::pair<Matrix3d, Vector3d> kalman_filter(Vector3d pos_cam, Vector2d v_w, Vector3d last_pos , double dt, Matrix3d last_P);
bool read_points(std::string fname, std::vector<Point> &points);
bool sort_by_larger_area(std::vector<Point> p0, std::vector<Point> p1);
bool sort_by_smallest_y(Point a, Point b);
bool sort_by_smallest_x(Point a, Point b);
bool sort_by_largest_y(Point a, Point b);
bool sort_by_largest_x(Point a, Point b);

#endif // UTILS_H
