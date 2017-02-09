#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include <utility>
#include <opencv2/core.hpp>
#include <QtSerialPort/QSerialPort>
#include "serial.h"

using namespace std;
using namespace cv;

class Robot{
private:
    int channel;    //Communication channel
    int n_loss, n_detected;
    double angle, last_angle;   //Rotation angle
    double loss_rate;
    bool detected;
    Point centroid; //Robot general centroid
    Point2d centroid_cm;
    Point color_cent, team_cent;    //Centroid from the half role color and from team color
    Point line_slope;
    string nick;
    string ID;
    string role;
    vector<Point> pos_hist;    
    vector<int> low_color_team;
    vector<int> upper_color_team;
    vector<int> low_color;
    vector<int> upper_color;

public:
    Robot();
    static bool encoders_reading(Serial *serial, int &robot, pair<double, double> &vels, double &battery);
    bool send_velocities(Serial *serial, pair<double, double> vels);
    int get_channel();
    void set_channel(int channel = -1);
    void set_angle(double angle);
    double get_angle();
    double get_last_angle();
    void set_lin_vel(double vel);
    bool is_detected();
    void was_detected(bool detected);
    double get_loss_rate();
    double get_lin_vel(double vel);
    void set_ang_vel(double vel);
    double get_ang_vel(double vel); //angular velocity w
    Point get_centroid();
    Point2d get_pos();
    void set_centroid(Point p = Point(-1, -1));
    void set_line_slope(Point p);
    Point get_line_slope();
    void add_pos_hist(Point p);
    Point get_from_pos_hist(int rank);
    Point get_color_cent();
    void set_color_cent(Point p);
    Point get_team_cent();
    void set_team_cent(Point p);
    string get_nick();
    void set_nick(string nick);
    string get_role();
    void set_role(string role);
    string get_ID();
    void set_ID(string ID);
    vector<int> get_team_low_color();
    void set_team_low_color(vector<int> low_color);
    vector<int> get_team_upper_color();
    void set_team_upper_color(vector<int> upper_color);
    vector<int> get_low_color();
    void set_low_color(vector<int> low_color);
    vector<int> get_upper_color();
    void set_upper_color(vector<int> upper_color);
    ~Robot(){}
};

#endif // ROBOT_H
