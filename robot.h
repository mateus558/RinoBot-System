#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include <utility>
#include <opencv2/core.hpp>
#include <QtSerialPort/QSerialPort>

using namespace std;
using namespace cv;

class Robot{
private:
    int channel;    //Communication channel
    double angle;   //Rotation angle
    Point centroid; //Robot general centroid
    Point color_cent, team_cent;    //Centroid from the half role color and from team color
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
    pair<double, double> encoders_reading(QSerialPort serial);
    int get_channel();
    void set_channel(int channel = -1);
    void set_angle(double angle);
    double get_angle();
    Point get_centroid();
    void set_centroid(Point p = Point(-1, -1));
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
