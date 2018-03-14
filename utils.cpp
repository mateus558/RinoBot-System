#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include "utils.h"

using namespace std;
using namespace Eigen;

double euclidean_dist(Point2d p, Point2d q)
{
    return sqrt((q.x-p.x)*(q.x-p.x) + (q.y-p.y)*(q.y-p.y));
}

double angle_two_points(Point2d p, Point2d q)
{
    double theta;
    double dot, pnorm, qnorm;

    dot = p.x * q.x + p.y * q.y;
    pnorm = sqrt(p.x * p.x + p.y * p.y);
    qnorm = sqrt(q.x * q.x + q.y * q.y);
    theta = acos(dot/(pnorm*qnorm));

    return theta * 180.0 / PI;
}

double min_function(double p, double q){
    if(p <= q)
    {
        return p;
    }
    else
        return q;
}

double max_function(double p, double q){
    if(p >= q)
    {
        return p;
    }
    else
        return q;
}

bool read_points(string fname, vector<Point> &points){
    ifstream input(fname.c_str());
    int x, y, size = 0, i;

    if(!input){
        cerr << "The file could not be opened! (Utils)" << endl;
        return false;
    }

    while(input >> x >> y){
        size++;
    }

    points.resize(size);

    input.clear();
    input.seekg(0, ios::beg);

    for(i = 0; i < size; ++i){
        input >> points[i].x >> points[i].y;
    }

    return true;
}

pair<Matrix3d, Vector3d> kalman_filter(Vector3d pos_cam, Vector2d v_w, Vector3d last_pos , double dt, Matrix3d last_P){
    double v = 1.14 * v_w[0], w = 1.14 * v_w[1], ds = v * dt, dw = w * dt;
    double b = 0.055; //Distância entre eixos do carrinho 'CHECK'
    double dsr = ds + (b*dw)/2, dsl = ds - (b*dw)/2;
    double kr = 9, kl = 9;
    Vector3d prediction, pos_predicted, pos_current;
    Matrix2d covar;
    Matrix3d P = last_P, C, R, I, fp, P_predicted, K;
    MatrixXd fdrl(3, 2), inv;
    pair<Matrix3d, Vector3d> res;

    C = MatrixXd::Identity(3,3);
    I = MatrixXd::Identity(3,3);

    R << 0,0                ,0  ,
         0                ,0,0  ,
         0                ,0                ,6.14071137584  ;

    //6.14071137584 estava no lugar do 6 a matrix R 9.23765359168e-07 7.93803166352e-07
    //Kalman Extended
    prediction << ds*cos((last_pos(2,0)+dw/2)*PI/180),
                  ds*sin((last_pos(2,0)+dw/2)*PI/180),
                  dw;

    pos_predicted = last_pos + prediction;

    covar << kr*abs(dsr),0          ,
             0          ,kl*abs(dsl);

    fp << 1, 0, -ds*sin((last_pos(2,0)+dw/2)*PI/180),
          0, 1, ds*cos((last_pos(2,0)+dw/2)*PI/180) ,
          0, 0, 1                                   ;

    fdrl << (1/2)*cos((last_pos(2,0)+dw/2)*PI/180)-ds/(2*b)*sin((last_pos(2,0)+dw/2)*PI/180),  (1/2)*cos((last_pos(2,0)+dw/2)*PI/180)+ds/(2*b)*sin((last_pos(2,0)+dw/2)*PI/180),
            (1/2)*sin((last_pos(2,0)+dw/2)*PI/180)+ds/(2*b)*cos((last_pos(2,0)+dw/2)*PI/180),  (1/2)*sin((last_pos(2,0)+dw/2)*PI/180)-ds/(2*b)*cos((last_pos(2,0)+dw/2)*PI/180),
            1/b                                                                           , -1/b                                                                           ;

    P_predicted = (fp * P * fp.transpose()) + (fdrl * covar * fdrl.transpose());
    inv = C * P_predicted * C.transpose() + R;
    K = P_predicted * C.transpose() * inv.inverse();
    pos_current = pos_predicted + K * (pos_cam - C * pos_predicted);
    P = (I - K * C) * P_predicted;

    res.first = P;
    res.second = pos_current;

    return res;
}

vector<int> hsv2rgb(vector<int> in)
{
    double      hh, p, q, t, ff;
    long        i;
    vector<int>         out(3);
    if(in[1] <= 0.0) {       // < is bogus, just shuts up warnings
        out[0] = in[2];
        out[1] = in[2];
        out[2] = in[2];
        return out;
    }
    hh = in[0];
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in[2] * (1.0 - in[1]);
    q = in[2] * (1.0 - (in[1] * ff));
    t = in[2] * (1.0 - (in[1] * (1.0 - ff)));

    switch(i) {
    case 0:
        out[0] = in[2];
        out[1] = t;
        out[2] = p;
        break;
    case 1:
        out[0] = q;
        out[1] = in[2];
        out[2] = p;
        break;
    case 2:
        out[0] = p;
        out[1] = in[2];
        out[2] = t;
        break;

    case 3:
        out[0] = p;
        out[1] = q;
        out[2] = in[2];
        break;
    case 4:
        out[0] = t;
        out[1] = p;
        out[2] = in[2];
        break;
    case 5:
    default:
        out[0] = in[2];
        out[1] = p;
        out[2] = q;
        break;
    }
        //cout << out[0] << " " << out[1] << " " << out[2] << endl;

    return out;
}

bool sort_by_smallest_x(Point a, Point b){
    return a.x < b.x;
}

bool sort_by_smallest_y(Point a, Point b){
    return a.y < b.y;
}

bool sort_by_largest_x(Point a, Point b){
    return a.x > b.x;
}

bool sort_by_largest_y(Point a, Point b){
    return a.y > b.y;
}

bool sort_by_larger_area(vector<Point> p0, vector<Point> p1)
{
    if(p0.size() == 0 || p1.size() == 0) return false;
    return contourArea(p0) < contourArea(p1);
}

bool area_limit(vector<Point> p){
    if(contourArea(p) < MIN_ROBOT_AREA || contourArea(p) > MAX_ROBOT_AREA){
        return 1;
    }
    return 0;
}

bool ball_area_limit(vector<Point> p){
    if(contourArea(p) > MAX_BALL_AREA){
        return 1;
    }
    return 0;
}

pair <double, double> Low_pass_filter_coeff (float cutoff)
{
    pair <double, double> coeff;
    double a;
    double b;
    a = ( 1 - sin(cutoff) ) / cos(cutoff);
    b = ( 1 - a)/2;
    coeff.first = a;
    coeff.second = b;
    return coeff;
}

Point Low_pass_filter_Centroid(Point centroid, Point last_centroid, Point last_proc_centroid, pair<double, double> coeff)
{

    double x;
    double y;

    x = coeff.second * centroid.x + coeff.second * last_centroid.x + coeff.first * last_proc_centroid.x;
    y = coeff.second * centroid.y + coeff.second * last_centroid.y + coeff.first * last_proc_centroid.y;

    Point centroid_proc = Point(x, y);

    return centroid_proc;
}

double Low_pass_filter_Theta(double angle, double last_angle, double last_proc_angle, pair<double, double> coeff)
{
    return coeff.second * angle + coeff.second * last_angle + coeff.first * last_proc_angle;
}

double sign(double aux){
    if (aux < 0)
        return -1;
    else if (aux > 0)
        return 1;
    else
        return 0;

}





