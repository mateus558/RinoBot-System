#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include <utility>
#include <opencv2/core.hpp>

#include "serial.h"
#include "settingsdialog.h"

using namespace std;
using namespace cv;

//union usado para converter float em byte e vice versa
typedef union{
    float  Float;
    unsigned char Bytes[4];
} Float2Char;

//union usado para converter short em byte e vice versa
typedef union{
    unsigned short Short;
    unsigned char Bytes[2];
}Short2Char;

struct Encoder{
    int robot;
    double battery;
    pair<float, float> vel;
};

class Robot
{
private:
    int channel;                            //Communication channel
    int n_loss, n_detected;
    int flag_fuzzy;
    Point2d output_fuzzy;
    double angle, angle_raw, last_angle, ang_predict, last_angle_raw;   //Rotation angle
    double ang_tolerance;
    double w;                                //Angular velocity
    double loss_rate;                        //Rate of detection failure of the robot.
    bool detected;
    Point centroid, centroid_raw, last_centroid, last_centroid_raw;  //Robot general centroid in pixels
    Point2d centroid_cm, last_centroid_cm;
    Point centroid_predict;
    double pos_tolerance;
    Point color_cent, team_cent;             //Centroid from the half role color and from team color
    Point line_slope;
    string nick, ID, role;
    vector<Point> pos_hist;
    vector<Point> team_contour, role_contour;
    vector<int> low_color_team, upper_color_team, low_color, upper_color;
    pair<float,float> vel;  //Velocity sent to the robots by the estrategy
    pair<float, float> _vel; //Velocity percepted by the camera Vx, Vy
    static Serial serial;
public:
    bool LPF_filter;

    Robot();

    /**************************************
     *  Serial (Communication) functions. *
     **************************************/

    static bool encoders_reading(int &robot, pair<float, float> &vels, float &battery);
    static bool send_velocities(int channel, pair<float, float> vels);
    static void config_serial(SettingsDialog::Settings settings);
    static bool is_serial_open();
    static void open_serial();
    static void close_serial();

    /******************
     *  Get functions *
     ******************/

    float get_l_vel();
    float get_r_vel();
    double get_ang_vel(); //get angular velocity w
    pair<float, float> get_velocities();
    Point get_centroid();
    Point get_centroid_raw();
    Point get_last_centroid();
    Point get_last_centroid_raw();
    Point2d get_pos();
    Point get_predic_centroid();
    pair<vector<Point>, vector<Point> > get_contour();
    Point2d get_output_fuzzy();
    int get_flag_fuzzy();
    int get_channel();
    double get_angle();
    double get_angle_raw();
    double get_last_angle_raw();
    double get_last_angle();
    double get_predic_angle();
    double get_loss_rate();
    Point get_line_slope();
    Point get_from_pos_hist(int rank);
    Point get_color_cent();
    Point get_team_cent();
    string get_nick();
    string get_role();
    string get_ID();
    vector<int> get_team_low_color();
    vector<int> get_team_upper_color();
    vector<int> get_low_color();
    vector<int> get_upper_color();

    /******************
     *  Set functions *
     ******************/

    void set_flag_fuzzy(int, Point, Point, Point2d);
    void set_flag_fuzzy(int);
    void set_output_fuzzy(Point2d);
    void set_channel(int channel = -1);
    void set_angle(double angle);
    void set_angle_raw(double angle_raw);
    void set_lin_vel(pair<float, float>);
    void set_centroid(Point p = Point(-1, -1));
    void set_centroid_raw(Point p = Point(-1, -1));
    void set_line_slope(Point p);
    void set_color_cent(Point p);
    void set_team_cent(Point p);
    void set_team_contour(vector<Point> team_contour);
    void set_role_contour(vector<Point> role_contour);
    void set_nick(string nick);
    void set_role(string role);
    void set_ID(string ID);
    void set_team_low_color(vector<int> low_color);
    void set_team_upper_color(vector<int> upper_color);
    void set_low_color(vector<int> low_color);
    void set_upper_color(vector<int> upper_color);

    /***************************
     *  Miscelaneous functions *
     ***************************/

    double min_function(double, double);
    double max_function(double, double);
    void compute_velocity(double deltaT);  //Compute the percepted velocity
    void correct_angle();
    void predict_info(double deltaT);
    pair<float, float> get_velocity();
    bool is_detected();
    void was_detected(bool detected);
    void add_pos_hist(Point p);

    ~Robot(){}
};

#endif // ROBOT_H


