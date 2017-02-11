#ifndef FUZZY_H
#define FUZZY_H

#include <QThread>
#include <vector>
#include "robot.h" //Robot class
#include "utils.h" //Utils library

struct Selector{
    Robot r1,r2;
};

class Fuzzy: public QThread
{
    Q_OBJECT
private:
    QMutex mutex;
    pVector enemy_pos_grid;
    pVector team_pos_grid;
    p2dVector enemy_pos;
    Point  ball_pos_grid;
    Point2d ball_pos;
    Point2d centroid_atk;
    Point2d centroid_def;

    dMatrix mi;
    dMatrix limite;
    vector<double> pertinencia;
    vector<double> D;
    vector<double> y_output;
    vector<double> y_baixo;
    vector<double> y_medio;
    vector<double> y_alto;
    vector<double> input;
    vector<double> d_universe;
    double output;
    bool stop;
    Selector selec_robot;



protected:
    void msleep(int ms);
    void run();

public:
    Fuzzy();

    void init_duniverse();
    void init_funcao_pertinencia(int);
    void fuzzification();
    void calcula_input(Robot, Robot);
    double defuzzification();
    double min_function(double, double);
    double max_function(double, double);
    void print_decision();
    void Play();
    bool is_running();
    void Stop();
    bool isStopped() const;
    void set_to_select(Robot, Robot);
    void set_enemy_pos(p2dVector);
    void set_ball_pos(Point2d);
    void set_centroid_atk(Point2d);
    void set_centroid_def(Point2d);
    Point convert_C_to_G(Point2d);
    ~Fuzzy();
};


#endif // FUZZY_H
