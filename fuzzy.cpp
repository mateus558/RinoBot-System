#include <iostream>
#include <iomanip>
#include <cmath>
#include "fuzzy.h"
#include "utils.h"
#include "robot.h"

using namespace std;

double parameters[][3] = {{-0.3, 0, 0.3},{0.111, 0.333, 0.555},{0.444, 0.666, 0.888},{0.7, 1 , 1.3}};
Point2d eixo_x(1.0,0.0);
int cont_fuzzy = 0;


//no construtor define as entradas do sistema FD, FC e FA
Fuzzy::Fuzzy(){

    stop = true;
    duniverse_initialized = false;
    output = 0.0;
    enemy_pos_grid = pVector(3);
    team_pos_grid = pVector(3);

    pertinencia.resize(3);
    D.resize(64);
    y_output.resize(101);
    y_output1.resize(101);
    y_output2.resize(101);
    y_baixo.resize(101);
    y_medio1.resize(101);
    y_medio2.resize(101);
    y_alto.resize(101);
    d_universe.resize(101);
    decisao_robo.resize(3);
    input.resize(3);
    mi_output.resize(3);

    mi = dMatrix(3, vector<double>(4, 0.0));
    limite = dMatrix(64, vector<double>(101, 0.0));


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
    struct timespec ts = {ms / 1000, (ms % 1000) * 1000 * 1000};
    nanosleep(&ts, NULL);
}

void Fuzzy::run(){
    if(!duniverse_initialized){
        init_duniverse();
        init_funcao_pertinencia();
        duniverse_initialized = true;
    }
    if (num_strategy == 1){
        if(ball_pos.x > 0 && ball_pos.y > 0){
            //Pro primeiro robô
            calcula_input(selec_robot.r1);
            fuzzification();
            decisao_robo[0] = defuzzification();

            //Pro segundo robô
            calcula_input(selec_robot.r2);
            fuzzification();
            decisao_robo[1] = defuzzification();

        }else{
            //tratar bola aqui
        }
    }
    else if (num_strategy == 2){
        calcula_another_input();
        another_fuzzification();
        another_defuzzification();
    }
    else{
        // tratar aqui
    }

    set_objectives();

    emit emitRobots(selec_robot);
    flag_finish_fuzzy = true;
    //cout << flag_finish_fuzzy << endl;


}

void Fuzzy::set_to_select(Robot r1, Robot r2, Robot r3){
    selec_robot.r1 = r1;
    selec_robot.r2 = r2;
    selec_robot.r3 = r3;
}

void Fuzzy::calcula_input(Robot r){

    double aux1,aux2;
    Point2d robot_pos = r.get_pos();

    double angle = r.get_angle();
    if(angle != angle){
        angle = r.get_last_angle();
        if(angle != angle) angle = 0;
    }

    //Calculo do FD - distGOLDEF ate nosso player e distGOLATK ate nosso player
    input[0] = pow(2.7183,-0.6931*(euclidean_dist(centroid_atk,robot_pos)/euclidean_dist(centroid_def,robot_pos)));
    input[0] = (round(input[0]*100))/100;

    //Calculo FC - distBallTeam, distBallEnemy

    //Define Inimigo mais prox

    Point2d enemy_prox;
    if ((euclidean_dist(ball_pos,enemy_pos[0]) <= euclidean_dist(ball_pos,enemy_pos[1])) && (euclidean_dist(ball_pos,enemy_pos[0]) <= euclidean_dist(ball_pos,enemy_pos[2])))
        enemy_prox = enemy_pos[0];
    else if (euclidean_dist(ball_pos,enemy_pos[1]) <= euclidean_dist(ball_pos,enemy_pos[2]))
        enemy_prox = enemy_pos[1];
    else
        enemy_prox = enemy_pos[2];

    input[1] =pow(2.7183,-0.6931*(euclidean_dist(ball_pos,robot_pos)/euclidean_dist(ball_pos,enemy_prox)));
    input[1] = (round(input[1]*100))/100;


    //Calculo FA - AngBallAliado e AngAtkAliado

        //Corrige Posicionamento
        ball_pos.y = -ball_pos.y;
        robot_pos.y = -robot_pos.y;
        centroid_atk.y=-centroid_atk.y;

        //Calcula angulo entre robo e bola
        Point2d vec_ball_robot = ball_pos-robot_pos;
        double ang_vec_ball_eixox = angle_two_points(vec_ball_robot,eixo_x);
        //cout << ball_pos.x << endl;
        //Corrige o angulo
        if (vec_ball_robot.y < 0)
                ang_vec_ball_eixox = -ang_vec_ball_eixox;

        double ang_ball_robot = ang_vec_ball_eixox - angle;

        //Calcula angulo entre robo e gol adversario
        Point2d vec_atk_robot = centroid_atk-robot_pos;
        double ang_vec_atk_eixox = angle_two_points(vec_atk_robot,eixo_x);

        //Corrige o angulo
        if (vec_atk_robot.y < 0)
                ang_vec_atk_eixox = -ang_vec_atk_eixox;

        double ang_atk_robot = ang_vec_atk_eixox - angle;

        //ajusta angulos para menores que 180 e maiores que -180
        if (ang_ball_robot>180) ang_ball_robot = ang_ball_robot - 360;
        else if (ang_ball_robot<-180) ang_ball_robot = ang_ball_robot + 360;
        if (ang_atk_robot>180) ang_atk_robot = ang_atk_robot - 360;
        else if (ang_atk_robot<-180) ang_atk_robot = ang_atk_robot + 360;


        if (ang_ball_robot <= 90 && ang_ball_robot >= -90)
            aux1 = (90 - fabs(ang_ball_robot))/90;
        else
            aux1 = (-90 + fabs(ang_ball_robot))/90;
        if (ang_atk_robot <= 90 && ang_atk_robot >= -90)
            aux2 = (90 - fabs(ang_atk_robot))/90;
        else
            aux2 = (-90 + fabs(ang_atk_robot))/90;

        input[2]= 0.7*aux1+0.3*aux2;
        input[2] = (round(input[2]*100))/100;

        ball_pos.y = -ball_pos.y;
        robot_pos.y = -robot_pos.y;
        centroid_atk.y=-centroid_atk.y;
}

//Inicio fuzzy 4x4

//COnversão das posições para intervalo 0 1
void Fuzzy::calcula_another_input(){
    if (centroid_atk.x > ball_pos.x )/*atcando para direita*/{
       input[0] = round((ball_pos.x-10)/1.5); //Arrumado para x max 150 e valor inteiro *100
       input[1] = round(ball_pos.y /1.3);
    }
    else if (centroid_atk.x <= ball_pos.x){
       input[0] = round((160 - ball_pos.x) / 1.5); //Arrumado para x max 150 e valor inteiro *100
       input[1] = round((130 - ball_pos.y) / 1.3);
    }
}

void Fuzzy::another_fuzzification(){
    int i=0, j=0, k=0, cont = 0, aux1;
    double aux2 = 0, aux3;

    //Criando matriz de possibilidade 2x4
    for(i=0;i<2;i++)
    {
        for(j=0;j<4;j++)
        {
            aux1 = input[i];
            if(j == 0)
            {
                mi[i][j] = y_baixo[aux1];
            }
            if(j == 1)
            {
                mi[i][j] = y_medio1[aux1];
            }
            if(j == 2)
            {
                mi[i][j] = y_medio2[aux1];
            }
            if(j == 3)
            {
                mi[i][j] = y_alto[aux1];
            }
        }
    }

    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
                aux3 = min_function(mi[0][i],mi[1][j]);//Mapeando póssibilidades
                D[cont] = aux3; //armazena os mim das funções de pertinencia
                cont++;
        }

    }

    for(i=0;i<cont;i++)//Percorre o vetor D
    {
        if((i >= 0 && i <= 7))
        {
            for(j=0;j<=100;j++)
            {
                limite[i][j] = min_function(D[i],y_baixo[j]); //Gera o grafico para ser gerado o max
            }
        }
        else if(i >= 8 && i <= 11){
            for(j=0;j<=100;j++)
            {
                limite[i][j] = min_function(D[i],y_medio1[j]);
            }
        }
       //Referente ao no fuzzy ALTO
        else if( i >= 12 && i <= 15)
        {
            for(j=0;j<=100;j++)
            {
                limite[i][j] = min_function(D[i],y_alto[j]);
            }
        }
    }

    for(i=0;i<=100;i++)
    {
        for(k=0; k < cont; k++)
        {
            aux2 = max_function(limite[k][i],aux2);
        }
        y_output1[i] = aux2;//Grafico resultante do max dos limites gerados anteriormente
        aux2 = 0;
    }

    for(i=0;i<cont;i++)//Percorre o vetor D
    {
       if(i%2 == 0){
            for(j=0;j<=100;j++)
            {
                limite[i][j] = min_function(D[i],y_medio1[j]);
            }
        }
        else
        {
            for(j=0;j<=100;j++)
            {
                limite[i][j] = min_function(D[i],y_medio2[j]);
            }
        }
    }

    for(i=0;i<=100;i++)
    {
        for(int k = 0; k < cont; k++)
        {
            aux2 = max_function(limite[k][i],aux2);
        }
        y_output2[i] = aux2;//Grafico resultante do max dos limites gerados anteriormente
        aux2 = 0;
    }

}

void Fuzzy::another_defuzzification(){
    double sum1 = 0,sum2 = 0, aux2;
    int i,j,aux1;
    for(i=0;i<=100;i++)
    {
    //Formula que gera o centro de massa da função de maximo
        sum1 = sum1 + d_universe[i]*y_output1[i];
        sum2 = sum2 + y_output1[i];
    }
    output1 = sum1/sum2; //posição de saida em x

    sum1 = 0;
    sum2 = 0;

    for(i=0;i<=100;i++)
    {
    //Formula que gera o centro de massa da função de maximo
        sum1 = sum1 + d_universe[i]*y_output2[i];
        sum2 = sum2 + y_output2[i];
    }
    output2 = sum1/sum2; //posição de saida em y    

    //Passando saidas para gamefunction
    if(centroid_atk.x > ball_pos.x ){
       output_meta.x = output1*150 +10;
       output_meta.y = output2*130;
    }
    else if (centroid_atk.x <= ball_pos.x ){
       output_meta.x = 160 - output1*150;
       output_meta.y = 130 - output2*130;
    }

}

//Fim fuzzy 4x4

//Inicio fuzzy antigo

void Fuzzy::fuzzification(){

    int i=0, j=0, k=0, cont = 0, aux1;
    double aux2 = 0, aux3;


    pertinencia[0] = input[0]/0.01;
    pertinencia[1] = input[1]/0.01;
    pertinencia[2] = input[2]/0.01;


    for(i=0;i<3;i++)
    {
        for(j=0;j<4;j++)
        {
            aux1 = pertinencia[i];
            if(j == 0)
            {
                mi[i][j] = y_baixo[aux1];
            }
            if(j == 1)
            {
                mi[i][j] = y_medio1[aux1];
            }
            if(j == 2)
            {
                mi[i][j] = y_medio2[aux1];
            }
            if(j == 3)
            {
                mi[i][j] = y_alto[aux1];
            }
        }
    }

    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            for(k=0;k<4;k++)
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
        if((i >= 0 && i <= 1) || (i >= 4 && i <= 5) || (i == 16) || (i == 22))
        {
            for(j=0;j<=100;j++)
            {
                limite[i][j] = min_function(D[i],y_baixo[j]);
            }
        }
        else if((i >= 2 && i <= 3) || (i >= 6 && i <= 10) || (i >= 12 && i <= 13) || (i >= 17 && i <= 20) || (i >= 24 && i <= 25) || (i >= 28 && i <= 29) || (i >= 32 && i <= 34) || (i >= 36 && i <= 37) || (i >= 48 && i <= 49) || (i >= 52 && i <= 53))
        {
            for(j=0;j<=100;j++)
            {
                limite[i][j] = min_function(D[i],y_medio1[j]);
            }
        }
        else if((i == 11) || (i >= 14 && i <= 15) || (i == 21) || (i == 23) || (i >= 26 && i <= 27) || (i >= 30 && i <= 31) || (i == 35) || (i == 38) || (i >= 40 && i <= 42) || (i >= 44 && i <= 45) || (i >= 50 && i <= 51) || (i == 54) || (i >= 56 && i <= 57) || (i >= 60 && i <= 61))
        {
            for(j=0;j<=100;j++)
            {
                limite[i][j] = min_function(D[i],y_medio2[j]);
            }
        }
        else if((i == 39) || (i == 43) || (i >= 46 && i <= 47) || (i == 55) || (i >= 58 && i <= 59) || (i >= 62 && i <= 63))
        {
            for(j=0;j<=100;j++)
            {
                limite[i][j] = min_function(D[i],y_alto[j]);
            }
        }

    }

    for(i=0;i<=100;i++)
    {
        for(k=0;k<cont;k++)
        {
            aux2 = max_function(limite[k][i],aux2);
        }
        y_output[i] = aux2;
        aux2 = 0;
    }
}

int Fuzzy::defuzzification(){
    double sum1 = 0,sum2 = 0, aux2;
    int i,j,aux1;
    for(i=0;i<=100;i++)
    {
        sum1 = sum1 + d_universe[i]*y_output[i];
        sum2 = sum2 + y_output[i];
    }
    output = sum1/sum2;

    //Calcular a pertinencia da saida
    aux1 = output/0.01;

    for(j=0;j<4;j++)
    {
        if(j == 0)
        {
            mi_output[j] = y_baixo[aux1];
        }
        if(j == 1)
        {
            mi_output[j] = y_medio1[aux1];
        }
        if(j == 2)
        {
            mi_output[j] = y_medio2[aux1];
        }
        if(j == 3)
        {
            mi_output[j] = y_alto[aux1];
        }
    }

    aux2 = max_function(mi_output[0],mi_output[1]);
    aux2 = max_function(aux2,mi_output[2]);
    aux2 = max_function(aux2,mi_output[3]);


    if (aux2 == mi_output[0])
        return 0;
    else if (aux2 == mi_output[1])
        return 1;
    else if (aux2 == mi_output[2])
        return 2;
    else
        return 3;


}

void Fuzzy::set_objectives(){

    if (num_strategy == 1){
        if (decisao_robo[0] >= 2 && decisao_robo[1] >= 2){
                if(fabs(selec_robot.r1.get_pos().x - centroid_def.x) > fabs(selec_robot.r2.get_pos().x - centroid_def.x)){
                    decisao_robo[1] = 1;
                }
                else {
                    decisao_robo[0] = 1;
                }
            }
            else{
                //tratar aqui
            }
            if (decisao_robo[0] <= 1 && decisao_robo[1] <= 1){
                if(fabs(selec_robot.r1.get_pos().x - centroid_def.x) > fabs(selec_robot.r2.get_pos().x - centroid_def.x)){
                    decisao_robo[0] = 2;
                }
                else {
                    decisao_robo[1] = 2;
                }
            }
            else{
                //tratar aqui
            }
            decisao_robo[2] = 4;


            if (cont_fuzzy == 0){
                selec_robot.r1.set_flag_fuzzy(decisao_robo[0], centroid_atk, centroid_def, ball_pos);
                selec_robot.r2.set_flag_fuzzy(decisao_robo[1], centroid_atk, centroid_def, ball_pos);
                selec_robot.r3.set_flag_fuzzy(decisao_robo[2], centroid_atk, centroid_def, ball_pos);
            }

            cont_fuzzy++;

            if (cont_fuzzy == 20){
                cont_fuzzy = 0;
            }
    }
    else if(num_strategy == 2){
        int i = 0;
        if (euclidean_dist(selec_robot.r1.get_pos(),centroid_def) <= euclidean_dist(selec_robot.r2.get_pos(),centroid_def) && euclidean_dist(selec_robot.r1.get_pos(),centroid_def) <= euclidean_dist(selec_robot.r3.get_pos(),centroid_def)){
            decisao_robo[0] = 4; // goleiro
            if (euclidean_dist(selec_robot.r2.get_pos(),ball_pos) <= euclidean_dist(selec_robot.r3.get_pos(),ball_pos)){
                decisao_robo[1] = 10; // o que vai na bola (killer)
                decisao_robo[2] = 11; // o que guarda a posição (guardian)
            }
            else{
                decisao_robo[1] = 11;
                decisao_robo[2] = 10;
            }
        }
        else if (euclidean_dist(selec_robot.r2.get_pos(),centroid_def) <= euclidean_dist(selec_robot.r3.get_pos(),centroid_def) && euclidean_dist(selec_robot.r2.get_pos(),centroid_def) <= euclidean_dist(selec_robot.r1.get_pos(),centroid_def)){
            decisao_robo[1] = 4; //goleiro
            if (euclidean_dist(selec_robot.r1.get_pos(),ball_pos) <= euclidean_dist(selec_robot.r3.get_pos(),ball_pos)){
                decisao_robo[0] = 10; // o que vai na bola (killer)
                decisao_robo[2] = 11; // o que guarda a posição (guardian)
            }
            else{
                decisao_robo[0] = 11;
                decisao_robo[2] = 10;
            }
        }
        else if(euclidean_dist(selec_robot.r3.get_pos(),centroid_def) <= euclidean_dist(selec_robot.r1.get_pos(),centroid_def) && euclidean_dist(selec_robot.r3.get_pos(),centroid_def) <= euclidean_dist(selec_robot.r2.get_pos(),centroid_def)){
            decisao_robo[2] = 4; // goleiro
            if (euclidean_dist(selec_robot.r1.get_pos(),ball_pos) <= euclidean_dist(selec_robot.r2.get_pos(),ball_pos)){
                decisao_robo[0] = 10; // o que vai na bola (killer)
                decisao_robo[1] = 11; // o que guarda a posição (guardian)
            }
            else{
                decisao_robo[0] = 11;
                decisao_robo[1] = 10;
            }
        }
        selec_robot.r1.set_flag_fuzzy(decisao_robo[0], centroid_atk, centroid_def, ball_pos);
        selec_robot.r2.set_flag_fuzzy(decisao_robo[1], centroid_atk, centroid_def, ball_pos);
        selec_robot.r3.set_flag_fuzzy(decisao_robo[2], centroid_atk, centroid_def, ball_pos);

        selec_robot.r1.set_output_fuzzy(output_meta);
        selec_robot.r2.set_output_fuzzy(output_meta);
        selec_robot.r3.set_output_fuzzy(output_meta);
    }
    else{
        // tratar aqui
    }
}

bool Fuzzy::get_flag_finish(){
    return this->flag_finish_fuzzy;
}

void Fuzzy::zera_flag_finish(){
    flag_finish_fuzzy = false;
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
            y_medio1[i] = 0;
        }
        else if(d_universe[i] < parameters[1][1])
        {
            y_medio1[i] = (d_universe[i] - parameters[1][0])/(parameters[1][1] - parameters[1][0]);
        }
        else if(d_universe[i] >= parameters[1][1])
        {
            y_medio1[i] = (d_universe[i] - parameters[1][2])/(parameters[1][1] - parameters[1][2]);
        }
    }
    for(i=0;i<=100;i++)
    {
        if(d_universe[i] < parameters[2][0] || d_universe[i] > parameters[2][2])
        {
            y_medio2[i] = 0;
        }
        else if(d_universe[i] < parameters[2][1])
        {
            y_medio2[i] = (d_universe[i] - parameters[2][0])/(parameters[2][1] - parameters[2][0]);
        }
        else if(d_universe[i] >= parameters[2][1])
        {
            y_medio2[i] = (d_universe[i] - parameters[2][2])/(parameters[2][1] - parameters[2][2]);
        }
    }
    for(i=0;i<=100;i++)
    {
        if(d_universe[i] < parameters[3][0] || d_universe[i] > parameters[3][2])
        {
            y_alto[i] = 0;
        }
        else if(d_universe[i] < parameters[3][1])
        {
            y_alto[i] = (d_universe[i] - parameters[3][0])/(parameters[3][1] - parameters[3][0]);
        }
        else if(d_universe[i] >= parameters[3][1])
        {
            y_alto[i] = (d_universe[i] - parameters[3][2])/(parameters[3][1] - parameters[3][2]);
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
