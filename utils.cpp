#include <iostream>
#include <vector>
#include <cmath>
#include "utils.h"

using namespace std;

double euclidean_dist(Point p, Point q){
    Point diff = p - q;

    return sqrt(diff.x*diff.x - diff.y*diff.y);
}
