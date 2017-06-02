#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <QThread>
#include <QMutex>
#include <vector>
#include "robot.h" //Robot class
#include "utils.h" //Utils library


class Navigation : public QThread
{
    Q_OBJECT
protected:
    static const int dx = 4;
    static const int dy = 4;
    int i;
    double orientation;
    double e;
    QMutex mutex;
    dMatrix pGrid;
    dMatrix tGrid;
    Point2d meta;
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
    void set_direction();
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
    Point2d get_meta_aux();
    void set_meta_aux(Point2d);
    void set_epsilon(double);
    void set_orientation(double);
    bool get_flag_finish();
    void zera_flag_finish();
    void Play();
    bool is_running();
    void Stop();
    bool isStopped() const;
    ~Navigation();

};

#endif // NAVIGATION_H


