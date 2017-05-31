/*#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

#include <QThread>
#include <QMutex>
#include <vector>
#include "robot.h" //Robot class
#include "utils.h" //Utils library
#include "fuzzy.h"
#include "mover.h"
#include "navigation.h"


class GAME_FUNCTIONS: public QThread
{
    Q_OBJECT
private:
    static const int dx = 5;
    static const int dy = 5;
    int i;
    QMutex mutex;
    pVector enemy_pos_grid; //posicao em grid dos inimigos
    pVector team_pos_grid; //posicao em grid do time
    Point  ball_pos_grid;
    p2dVector enemy_pos; //posicao em cm dos inimigos
    p2dVector team_pos; //posicao em cm dos aliados
    Point2d ball_pos; //posicao em cm da bola
    Point2d centroid_atk; //posicao em cm do centro da area de atk
    Point2d centroid_def; //posicao em cm do centro da area de def
    pVector def_area;
    pair<double, double> ball_vel;
    bool stop, game_functions_initialized,flag_finish_functions; //variavel de controle de thread
    bool calc_Gandalf, calc_Presto, calc_Leona;
    Selector selec_robot; //estrutura de selecao dos robos que vao sair do fuzzy
    Selec selec_iterador; //estrutura de selecao dos objetos da classe navegacao

protected:
    void msleep(int ms);
    void run(); //rotina que a thread executa
signals:
    void emitRobots(Selector);

public:
    GAME_FUNCTIONS();
    //void set_to_select_iterador(NAVEGATION *, NAVEGATION *,NAVEGATION *);
    void set_to_select(Robot, Robot, Robot);
    void set_enemy_pos(p2dVector);
    void set_team_pos(p2dVector);
    void set_ball_pos(Point2d);
    void set_ball_vel(pair<double, double>);
    void set_def_area(pVector);
    void set_centroid_atk(Point2d);
    void set_centroid_def(Point2d);
    Point convert_C_to_G(Point2d);
    void set_game_function(Robot *);
    void set_calc_Gandalf(bool);
    void set_calc_Presto(bool);
    void set_calc_Leona(bool);

    /*void goalkeeper(NAVEGATION *);
    void defender(NAVEGATION *);
    void defensive_midfielder(NAVEGATION *);
    void ofensive_midfielder(NAVEGATION *);
    void striker(NAVEGATION *);

    bool get_flag_finish();
    void zera_flag_finish();
    void Play();
    bool is_running();
    void Stop();
    bool isStopped() const;
    ~GAME_FUNCTIONS();

};

#endif // GAME_FUNCTIONS_H*/
