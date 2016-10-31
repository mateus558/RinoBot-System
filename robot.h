#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include <opencv2/core.hpp>


using namespace std;
using namespace cv;

class Robot{
private:
    Point centroid;
    int channel;
    string nick;
    string ID;
    string role;
    vector<Point> pos_hist;
public:
    Robot(): centroid(Point(-1, -1)),   channel(-1),    ID("None"),   role("None"), nick("None") {}
    Point get_centroid();
    void set_centroid(Point p = Point(-1, -1));
    int get_channel();
    void set_channel(int channel = -1);
    void set_nick(string nick);
    string get_role();
    void set_role(string role);
    string get_ID();
    void set_ID(string ID);
    ~Robot(){}
};

#endif // ROBOT_H
