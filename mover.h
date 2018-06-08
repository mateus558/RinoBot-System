#ifndef MOVER_H
#define MOVER_H


#include <QThread>
#include <vector>
#include "robot.h" //Robot class
#include "utils.h" //Utils library
#include "fuzzy.h"
#include "game_functions.h"
#include "navigation.h"
#include "serial.h"

struct Selec{
    Game_functions *gandalf;
    Game_functions *presto;
    Game_functions *leona;
};

class Mover: public QThread
{
    Q_OBJECT
private:
    const int dx = 5;
    const int dy = 5;
    pVector enemy_pos_grid; //posicao em grid dos inimigos
    pVector team_pos_grid; //posicao em grid do time
    p2dVector enemy_pos; //posicao em cm dos inimigos
    Point2d ball_pos; //posicao em cm da bola
    Point2d centroid_atk; //posicao em cm do centro da area de atk
    Point2d centroid_def; //posicao em cm do centro da area de def
    double line_root_defender = 45;
    pVector def_area;
    pair<double, double> ball_vel;
    vector<pair<float, float> > vels;
    vector<Point2d> media_ball_v;
    static Serial serial;

    bool stop, mover_initialized; //variavel de controle de thread
    bool team_chang;
    Selector selec_robot; //estrutura de selecao dos robos que vao entrar no fuzzy
    Selec selec_iterador;
    bool killer_direction = 1; // frente = 1; tras = 0

protected:
    void msleep(int ms);
    void run(); //rotina que a thread executa
signals:
    void emitRobots(Selector);
public:
    Mover();
    double set_ang(double robot_angle, double angle, double w);
    pair<double, double> potDefense(double katt, double kw, Robot r, Point2d obj, bool correct);
    pair<double, double> defenderGK(Robot r);

    void init_mover();
    void calcula_velocidades(Robot *, Game_functions  *, pair<float, float>*);
    void velocity_goalkeeper(Robot *, Game_functions  *, pair<float, float>*);
    void velocity_defender(Robot *, Game_functions  *, pair<float, float>*);
    void velocity_defensive_midfielder(Robot *, Game_functions  *, pair<float, float>*);
    void velocity_ofensive_midfielder(Robot *, Game_functions  *, pair<float, float>*);
    void velocity_striker(Robot *, Game_functions  *, pair<float, float>*);
    void velocity_guardian(Robot *, Game_functions  *, pair<float, float>*);
    void velocity_killer(Robot *, Game_functions  *, pair<float, float>*);
    void velocity_test(Robot *, Game_functions  *, pair<float, float>*);
    void goalkeeper_orientation(Robot *, pair<float, float>*);
    void robot_orientation(Robot *, Game_functions  *, pair<float, float>*);
    void atk_orientation(Robot *, Game_functions  *, pair<float, float>*);
    void atk_situation(Robot *,Game_functions *,pair<float,float>*);
    void atk_situation_inv(Robot *,Game_functions *,pair<float,float>*);
    void rotate(Robot *, pair<float, float>*);
    void rotate_inv(Robot *, pair<float, float>*);
    void kick_rotate(Robot *, pair<float, float>*);
    Point2d prevision_atk(Robot *);
    double ajusta_angulo(double);
    void Play();
    bool is_running();
    void Stop();
    bool isStopped() const;
    void team_changed();
    void set_def_area(pVector def_area);
    void set_ball_vel(pair<double, double>);
    void set_to_select(Robot, Robot, Robot);
    void set_to_select_iterador(Game_functions *,Game_functions *, Game_functions *);
    void set_enemy_pos(p2dVector);
    void set_ball_pos(Point2d);
    void set_centroid_atk(Point2d);
    void set_centroid_def(Point2d);
    Point convert_C_to_G(Point2d);

    void velocity_killer_cpu(Robot *, Game_functions  *, pair<float, float>*);
    void velocity_defender_root(Robot *, Game_functions  *, pair<float, float>*);

    void set_params(Robot *);
    ~Mover();
};

#endif // MOVER_H

