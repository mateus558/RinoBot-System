#ifndef CPO2_H
#define CPO2_H

#include <QThread>
#include <QMutex>
#include <vector>
#include "robot.h" //Robot class
#include "utils.h" //Utils library


class CPO2 : public QThread
{
    Q_OBJECT
private:
    bool stop;

    int dx;
    int dy;
    double orientation;
    QMutex mutex;

    dMatrix pGrid;
    dMatrix tGrid;

    pVector enemy_pos_grid;
    pVector team_pos_grid;
    p2dVector enemy_pos;
    p2dVector team_pos;
    Point2d ball_pos;
    Point ball_pos_grid;
    Point2d centroid_atk;
    Point2d centroid_def;

    bool grid_initialized,flag_finish_CPO2;

protected:
    void run();
    void msleep(int ms);
signals:

public:
    CPO2();
    double iterator();
    double get_neighborhood(int, int, int);
    void set_potential(int, int, double);
    double get_potential(int, int);
    int get_occupancy(int, int);
    Point convert_C_to_G(Point2d);
    void set_direction();
    double get_direction(Point);
    bool get_flag_finish();
    void zera_flag_finish();
    void init_grid();
    void print_grid();
    void set_orientation(double);
    void set_enemy_pos(p2dVector);
    void set_team_pos(p2dVector);
    void set_ball_pos(Point2d);
    void set_centroid_atk(Point2d);
    void set_centroid_def(Point2d);
    void Play();
    bool is_running();
    void Stop();
    bool isStopped() const;
    ~CPO2();
};

#endif // CPO2_H
