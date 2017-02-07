#ifndef CPH_H
#define CPH_H

#include <QThread>
#include <vector>
#include "robot.h" //Robot class
#include "utils.h" //Utils library


class CPH : public QThread
{
    Q_OBJECT
private:
    int dx;
    int dy;
    QMutex mutex;
    dMatrix pGrid;
    iMatrix tGrid;
    p2dVector enemy_pos;
    p2dVector team_pos;
    Point2d ball_pos;
    bool stop;

protected:
    void msleep(int ms);
    void run();

public:
    CPH();
    double iterator();
    double get_neighborhood(int, int, int);
    void set_potential(int, int, double);
    double get_potential(int, int);
    int get_occupancy(int, int);
    Point convert_C_to_G(Point2d);
    void set_enemy_pos(p2dVector);
    void set_team_pos(p2dVector);
    void set_ball_pos(Point2d);
    void set_direction();
    void init_grid();
    void print_grid();
    void Play();
    bool is_running();
    void Stop();
    bool isStopped() const;
    ~CPH();
};

#endif // CPH_H
