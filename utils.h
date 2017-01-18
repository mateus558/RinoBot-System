#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include <opencv2/core/core.hpp>

#define PI 3.14159265

using namespace cv;

typedef std::vector<std::vector<Point> > pMatrix; //Point matrix type

double euclidean_dist(Point p, Point q);
double angle_two_points(Point p, Point q);

#endif // UTILS_H
