#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <QThread>
#include <QMutex>
#include <vector>
#include "robot.h" //Robot class
#include "utils.h" //Utils library
#define pi 3.1415


class Navigation : public QThread
{
    Q_OBJECT
protected:
    static const int dx = 5;
    static const int dy = 5;
    int i;
    double orientation;
    double e;
    QMutex mutex;
    dMatrix pGrid;
    dMatrix tGrid;
    bool stop, grid_initialized, flag_finish_navegation;

    void msleep(int ms);
    void run();

public:
    Navigation();
    double iterator_cph();
    double iterator_cpo();
    double get_neighborhood(int, int, int);
    void set_potential(int, int, double);
    double get_potential(int, int);
    int get_occupancy(int, int);
    void set_grid_orientation(Point);
    void set_direction(Point2d,Point2d);
    double get_direction(Point);
    void init_grid();
    void print_grid();
    void set_enemy_pos(p2dVector);
    void set_team_pos(p2dVector);
    void set_ball_vel(pair<double, double>);
    void set_def_area(pVector);
    void set_centroid_atk(Point2d);
    void set_centroid_def(Point2d);
    Point convert_C_to_G(Point2d); // colocar na utils
    void set_epsilon(double);
    void set_orientation(double);
    bool get_flag_finish();
    void zera_flag_finish();
    void Play();
    bool is_running();
    void Stop();

    bool isStopped() const;
    ~Navigation();

    void univector_field(Robot*, Point2d, Point2d);
    float repulsive_angle(float, float, Point2d);
    float hyperbolic_spiral(float, float, Point2d);
    float Gaussian_Func(float);
    void set_thetaDir(float);
    float get_direction_CPU();
    float tangencial_repulsive(Robot*, Point2d, Point2d, float );
    float whirlpool_repulsive(Robot*, Point2d, Point2d obstaculo, float );
    float theta_dir,the_fih,phi,g_size,Kr;
    void set_kr(float);
    float get_kr();

};

#endif // NAVIGATION_H


