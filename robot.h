#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include <opencv2/core.hpp>


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
    Point get_centroid();
    void set_centroid(Point p = Point(-1, -1));
    int get_channel();
    void set_channel(int channel = -1);
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
