#ifndef NAVEGATION_H
#define NAVEGATION_H

#include <QThread>
#include <QMutex>
#include <vector>
#include "robot.h" //Robot class
#include "utils.h" //Utils library


class NAVEGATION : public QThread
{
    Q_OBJECT
private:
    static const int dx = 5;
    static const int dy = 5;
    int i;
    double orientation;
    double e;
    QMutex mutex;
    dMatrix pGrid;
    dMatrix tGrid;
    pVector enemy_pos_grid;
    pVector team_pos_grid;
    pVector def_area;
    p2dVector enemy_pos;
    p2dVector team_pos;
    Point ball_pos_grid;
    Point2d ball_pos;
    Point2d centroid_atk;
    Point2d centroid_def;
    Point2d meta;
    bool stop, grid_initialized, flag_finish_navegation;

protected:
    void msleep(int ms);
    void run();

public:
    NAVEGATION();
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
    Point convert_C_to_G(Point2d); // colocar na utils
    Point2d get_meta_aux();
    void set_meta_aux(Point2d);
    /*void set_enemy_pos(p2dVector);
    void set_team_pos(p2dVector);
    void set_ball_pos(Point2d);
    void set_def_area(pVector);
    void set_centroid_atk(Point2d);
    void set_centroid_def(Point2d);*/
    void set_epsilon(double);
    void set_orientation(double);
    bool get_flag_finish();
    void zera_flag_finish();
    void Play();
    bool is_running();
    void Stop();
    bool isStopped() const;
    ~NAVEGATION();

};

#endif // NAVEGATION_H


