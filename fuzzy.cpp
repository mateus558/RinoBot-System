#include <iostream>
#include <iomanip>
#include <cmath>
#include "fuzzy.h"

using namespace std;

double parameters[][3] = {{-0.4, 0, 0.4},{0.1, 0.5, 0.9},{0.6, 1, 1.4}};

//no construtor define as entradas do sistema FD, FC e FA
Fuzzy::Fuzzy(){

    stop = true;
    output = 0.0;
    enemy_pos_grid = pVector(3);
    team_pos_grid = pVector(3);

    pertinencia.resize(3);
    D.resize(27);
    y_output.resize(101);
    y_baixo.resize(101);
    y_medio.resize(101);
    y_alto.resize(101);
    d_universe.resize(101);
    input.resize(3);

    mi = dMatrix(3, vector<double>(3, 0.0));
    limite = dMatrix(27, vector<double>(101, 0.0));

}

Fuzzy::~Fuzzy(){

}


void Fuzzy::msleep(int ms){
    /*struct timespec ts = {ms / 1000, (ms % 1000) * 1000 * 1000};
    nanosleep(&ts, NULL);*/
}

void Fuzzy::run(){

}

void Fuzzy::set_to_select(Robot r1, Robot r2){
    selec.robot.r1 = r1;
    selec.robot.r2 = r2;
}

void Fuzzy::calcula_input(Robot, Robot){

    Point2d robot1_pos = selec_robot.r1.get_pos();
    Point2d robot2_pos = selec_robot.r2.get_pos();

    double angle1 = selec_robot.r1.get_angle();
    double angle2 = selec_robot.r2.get_angle();

}

void Fuzzy::fuzzification(){

}

void Fuzzy::init_duniverse(){

}

void Fuzzy::init_funcao_pertinencia(int){

}

Point Fuzzy::convert_C_to_G(Point2d coord){
    Point i;

    coord.x = int(coord.x) + 5;
    coord.y = int(coord.y) + 5;

    if(coord.x / dx != 35){
        i.x = coord.x / dx;
    }else{
        i.x = coord.x / dx - 1;
    }

    if(coord.y / dy != 27){
        i.y = coord.y / dy;
    }else{
        i.y = coord.y / dy - 1;
    }
    return i;
}

void Fuzzy::set_enemy_pos(p2dVector enemy_pos){
    this->enemy_pos = enemy_pos;
}

void Fuzzy::set_ball_pos(Point2d ball_pos){
    this->ball_pos = ball_pos;
}

void Fuzzy::set_centroid_atk(Point2d centroid_atk){
    this->centroid_atk = centroid_atk;
}

void Fuzzy::set_centroid_def(Point2d centroid_def){
    this->centroid_def = centroid_def;
}
