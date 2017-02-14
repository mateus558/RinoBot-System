#include <iostream>
#include <iomanip>
#include <cmath>
#include "fuzzy.h"
#include "utils.h"
#include "robot.h"

using namespace std;

double parameters[][3] = {{-0.4, 0, 0.4},{0.3, 0.5, 0.7},{0.6, 1, 1.4}};
Point2d eixo_x(1.0,0.0);


//no construtor define as entradas do sistema FD, FC e FA
Fuzzy::Fuzzy(){

    stop = true;
    duniverse_initialized = false;
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

bool Fuzzy::isStopped() const
{
    return this->stop;
}

void Fuzzy::Play(){
    if(isStopped())
        stop = false;
   start();
}

void Fuzzy::Stop(){
    stop = true;
}

bool Fuzzy::is_running(){
    return isRunning();
}

void Fuzzy::msleep(int ms){
    /*struct timespec ts = {ms / 1000, (ms % 1000) * 1000 * 1000};
    nanosleep(&ts, NULL);*/
}

void Fuzzy::run(){
    if(!duniverse_initialized){
        init_duniverse();
        init_funcao_pertinencia();
        duniverse_initialized = true;
    }

    //Pro primeiro robô
    calcula_input(selec_robot.r1);
    cout << "Vai sua Puta!" << endl;
    fuzzification();
    selec_robot.r1.set_flag_fuzzy(defuzzification());

    //Pro segundo robô
    //calcula_input(selec_robot.r2);
    //fuzzification();
    //selec_robot.r2.set_flag_fuzzy(defuzzification());

}

void Fuzzy::set_to_select(Robot r1, Robot r2){
    selec_robot.r1 = r1;
    selec_robot.r2 = r2;
}

void Fuzzy::calcula_input(Robot r){

    Point2d robot_pos = r.get_pos();
    //Point2d robot2_pos = selec_robot.r2.get_pos();

    double angle = r.get_angle();
   //double angle2 = selec_robot.r2.get_angle();

    //Calculo do FD - distGOLDEF ate nosso player e distGOLATK ate nosso player
    input[0] = pow(2.7183,-0.6931*(euclidean_dist(centroid_atk,robot_pos)/euclidean_dist(centroid_def,robot_pos)));
    input[0] = (round(input[0]*100))/100;
    cout << "FD: "<< input[0] << endl;

    //Calculo FC - distBallTeam, distBallEnemy, AngBallAliado, RangeAng

    ball_pos.y = -ball_pos.y;
    robot_pos.y = -robot_pos.y;

    //Calcula angulo entre robo e bola
    Point2d vec_ball_robot = ball_pos-robot_pos;
    double ang_vec_eixox = angle_two_points(vec_ball_robot,eixo_x);

    if (robot_pos.y > ball_pos.y)
            ang_vec_eixox = -ang_vec_eixox;

    double ang_ball_robot = ang_vec_eixox - angle;

    if(ang_ball_robot < 0)
        ang_ball_robot = -ang_ball_robot;
    if(ang_ball_robot >= 90 && ang_ball_robot <= 180)
        ang_ball_robot = 180 - ang_ball_robot;

    cout << "Angulo entre bola e robo: "<< ang_ball_robot << endl;
    cout << "Angulo vetor bola robo: "<< ang_vec_eixox << endl;
    cout << "Angulo de orientacao robo: "<< angle << endl;

    //Define Inimigo mais prox
    ball_pos.y = -ball_pos.y;
    robot_pos.y = -robot_pos.y;

    Point2d enemy_prox;
    if ((euclidean_dist(ball_pos,enemy_pos[0]) <= euclidean_dist(ball_pos,enemy_pos[1])) && (euclidean_dist(ball_pos,enemy_pos[0]) <= euclidean_dist(ball_pos,enemy_pos[2])))
        enemy_prox = enemy_pos[0];
    else if (euclidean_dist(ball_pos,enemy_pos[1]) <= euclidean_dist(ball_pos,enemy_pos[2]))
        enemy_prox = enemy_pos[1];
    else
        enemy_prox = enemy_pos[2];
/*
    cout << "Distancia inimigo1: "<<euclidean_dist(ball_pos,enemy_pos[0]) << endl;
    cout << "Distancia inimigo2: "<<euclidean_dist(ball_pos,enemy_pos[1]) << endl;
    cout << "Distancia inimigo3 "<<euclidean_dist(ball_pos,enemy_pos[2]) << endl;

    cout << "Inimigo mais prox bola: " << endl;
    cout << "Em x: " << enemy_prox.x << " Em y: " << enemy_prox.y << endl;*/

    input[1] = 0.5*(pow(2.7183,-0.6931*(euclidean_dist(ball_pos,robot_pos)/euclidean_dist(ball_pos,enemy_prox))) + pow(2.7183,-0.6931*(ang_ball_robot/30)));
    input[1] = (round(input[1]*100))/100;
    cout << "FC: "<< input[1] << endl;


    //Calculo FA - AngBallAliado
    input[2] = (90 - ang_ball_robot)/90;
    input[2] = (round(input[2]*100))/100;
    cout << "FA: "<< input[2] << endl;

}

void Fuzzy::fuzzification(){
    int i=0, j=0, k=0, cont = 0, aux1;
    double aux2 = 0, aux3;


    pertinencia[0] = input[0]/0.01;
    pertinencia[1] = input[1]/0.01;
    pertinencia[2] = input[2]/0.01;

    //cout<<"\n Entradas:"<< endl;
    //cout<<input[0]<<" "<<input[1]<<" "<<input[2]<<endl;

    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            aux1 = pertinencia[i];
            if(j == 0)
            {
                mi[i][j] = y_baixo[aux1];
            }
            if(j == 1)
            {
                mi[i][j] = y_medio[aux1];
            }
            if(j == 2)
            {
                mi[i][j] = y_alto[aux1];
            }
        }
    }

    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            for(k=0;k<3;k++)
            {
                aux3 = min_function(mi[0][i],mi[1][j]);
                aux3 = min_function(aux3,mi[2][k]);
                D[cont] = aux3;
                cont++;
            }
        }

    }

    for(i=0;i<cont;i++)
    {
        if((i >= 0 && i <= 3) || (i >= 9 && i <= 12))
        {
            for(j=0;j<=100;j++)
            {
                limite[i][j] = min_function(D[i],y_baixo[j]);
            }
        }
        else if((i >= 4 && i <= 8) || (i >= 13 && i <= 15) || (i >= 18 && i <= 22) || (i == 24))
        {
            for(j=0;j<=100;j++)
            {
                limite[i][j] = min_function(D[i],y_medio[j]);
            }
        }
        else if((i >= 16 && i <= 17) || (i == 23) || (i >= 25 && i <= 26))
        {
            for(j=0;j<=100;j++)
            {
                limite[i][j] = min_function(D[i],y_alto[j]);
            }
        }

    }

    for(i=0;i<=100;i++)
    {
        for(k=0;k<27;k++)
        {
            aux2 = max_function(limite[k][i],aux2);
        }
        y_output[i] = aux2;
        aux2 = 0;
    }
}

double Fuzzy::defuzzification(){
    double sum1=0,sum2=0;
    int i=0;
    for(i=0;i<=100;i++)
    {
        sum1 = sum1 + d_universe[i]*y_output[i];
        sum2 = sum2 + y_output[i];
    }
    output = sum1/sum2;
    cout << "Saida Fuzzy: "<< output << endl;
    return output;
}


double Fuzzy::min_function(double p, double q){
    if(p <= q)
    {
        return p;
    }
    else
        return q;
}

double Fuzzy::max_function(double p, double q){
    if(p >= q)
    {
        return p;
    }
    else
        return q;
}

void Fuzzy::init_duniverse(){
    int i;
    double aux = 0.01;
    for(i=0;i<=100;i++)
    {
        d_universe[i] = i*aux;
    }

}

void Fuzzy::init_funcao_pertinencia(){
    int i;
    for(i=0;i<=100;i++)
    {
        if(d_universe[i] < parameters[0][0] || d_universe[i] > parameters[0][2])
        {
            y_baixo[i] = 0;
        }
        else if(d_universe[i] < parameters[0][1])
        {
            y_baixo[i] = (d_universe[i] - parameters[0][0])/(parameters[0][1] - parameters[0][0]);
        }
        else if(d_universe[i] >= parameters[0][1])
        {
            y_baixo[i] = (d_universe[i] - parameters[0][2])/(parameters[0][1] - parameters[0][2]);
        }
    }
    for(i=0;i<=100;i++)
    {
        if(d_universe[i] < parameters[1][0] || d_universe[i] > parameters[1][2])
        {
            y_medio[i] = 0;
        }
        else if(d_universe[i] < parameters[1][1])
        {
            y_medio[i] = (d_universe[i] - parameters[1][0])/(parameters[1][1] - parameters[1][0]);
        }
        else if(d_universe[i] >= parameters[1][1])
        {
            y_medio[i] = (d_universe[i] - parameters[1][2])/(parameters[1][1] - parameters[1][2]);
        }
    }
    for(i=0;i<=100;i++)
    {
        if(d_universe[i] < parameters[2][0] || d_universe[i] > parameters[2][2])
        {
            y_alto[i] = 0;
        }
        else if(d_universe[i] < parameters[2][1])
        {
            y_alto[i] = (d_universe[i] - parameters[2][0])/(parameters[2][1] - parameters[2][0]);
        }
        else if(d_universe[i] >= parameters[2][1])
        {
            y_alto[i] = (d_universe[i] - parameters[2][2])/(parameters[2][1] - parameters[2][2]);
        }
    }
}

Point Fuzzy::convert_C_to_G(Point2d coord){
    Point i;

    coord.x = int(coord.x) + 5;
    coord.y = int(coord.y) + 5;

    if(coord.x / 5 != 35){
        i.x = coord.x / 5;
    }else{
        i.x = coord.x / 5 - 1;
    }

    if(coord.y / 5 != 27){
        i.y = coord.y / 5;
    }else{
        i.y = coord.y / 5 - 1;
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
