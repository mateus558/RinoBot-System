#include <iostream>
#include <iomanip>
#include <cmath>
#include "mover.h"
#include "robot.h"
#include "utils.h"

using namespace std;
double limiar_theta = 90;
double v_max = 0.6;
double w_max = 7;
double v_max_gol = 0.4;
double v_max_gol_ef = 1.2;
double w_max_gol = 5;
double k = (w_max/v_max);
double kgol = (w_max_gol/v_max_gol);
double l = 0.028; // caso mudar de robo trocar esse valor (robo antigo 0.0275 - robo novo 0.028)
double dist_giro = 7;
double vel_giro_lado = 1.0;
double vel_giro_atk = 0.8;
int cont = 0;
int cont_desvia = 0;

Serial Mover::serial;

Mover::Mover()
{
    stop = true;
    media_ball_v.resize(5);
    for (int i = 0; i < 5; i++){
        media_ball_v[i].x = 0;
        media_ball_v[i].y = 0;
    }
    mover_initialized = false;
    enemy_pos_grid = pVector(3);
    team_pos_grid = pVector(3);
    team_chang = false;
    vels.assign(3, make_pair(0, 0));
}

Mover::~Mover(){

}

bool Mover::isStopped() const
{
    return this->stop;
}

void Mover::Play(){
    if(isStopped())
        stop = false;
   start();
}

void Mover::Stop(){
    stop = true;
}

bool Mover::is_running(){
    return isRunning();
}

void Mover::msleep(int ms){
    struct timespec ts = {ms / 1000, (ms % 1000) * 1000 * 1000};
    nanosleep(&ts, NULL);
}

void Mover::run(){
    if(!mover_initialized){
        //init_mover();
        mover_initialized = true;
    }

    //Pro primeiro robô - Gandalf
    calcula_velocidades(&selec_robot.r1,selec_iterador.gandalf, &vels[0]);
    selec_robot.r1.set_lin_vel(vels[0]);
    //cout << "Velocidades: " << vels[0].first << " " <<  vels[0].second << endl;

    //Pro segundo robô - Presto
    calcula_velocidades(&selec_robot.r2,selec_iterador.presto, &vels[1]);
    selec_robot.r2.set_lin_vel(vels[1]);

    //Pro terceiro robô - Leona
    calcula_velocidades(&selec_robot.r3,selec_iterador.leona, &vels[2]);
    selec_robot.r3.set_lin_vel(vels[2]);
    //cout << "left " << vels[0].first << "   right " << vels[0].second << endl;

    emit emitRobots(selec_robot);
}

void Mover::set_to_select(Robot r1, Robot r2, Robot r3){
    selec_robot.r1 = r1;
    selec_robot.r2 = r2;
    selec_robot.r3 = r3;
}

void Mover::set_to_select_iterador(Game_functions *gandalf, Game_functions *presto, Game_functions *leona){
    selec_iterador.gandalf = gandalf;
    selec_iterador.presto = presto;
    selec_iterador.leona = leona;
}

void Mover::set_ball_vel(pair<double, double> ball_vel){
    this->ball_vel = ball_vel;
}

double Mover::set_ang(double robot_angle, double angle, double w){
    int acceptance;
    double ang, err;

    acceptance = 10;
    err = angle - robot_angle;

    if(fabs(err) > acceptance){
        if(err < 0){
            w = -w;
        }
    }else w = 0;

    return w;
}

void Mover::set_def_area(pVector def_area){
    this->def_area = def_area;
}

void Mover::team_changed(){
    if(!team_chang){
        team_chang = true;
    }else{
        team_chang = false;
    }
}


void Mover::calcula_velocidades(Robot *r, Game_functions *potencial_fields, pair<float, float> *vels){
    switch (r->get_flag_fuzzy()){
        case 0:
            velocity_defender(r, potencial_fields , vels);
            break;
        case 1:
            velocity_defensive_midfielder(r, potencial_fields , vels);
            break;
        case 2:
            velocity_ofensive_midfielder(r, potencial_fields , vels);
            break;
        case 3:
            velocity_striker(r, potencial_fields , vels);
            break;
        case 4:
            velocity_goalkeeper(r, potencial_fields , vels);
            break;
        case 10:
            velocity_killer(r, potencial_fields , vels);
            break;
        case 11:
            velocity_guardian(r, potencial_fields , vels);
            break;
        case 100:
            velocity_test(r, potencial_fields , vels);
            break;
    }
}

void Mover::velocity_goalkeeper(Robot *robo, Game_functions *pot_fields, pair<float, float> *vels){
    Point2d robot_pos = robo->get_pos();
    Point robot_grid = convert_C_to_G(robot_pos);

    Point2d ball_v;

    double v,w,theta,alpha;
    pair<float, float> vel;

    ball_v.x = ball_vel.first / 100;
    ball_v.y = -ball_vel.second / 100;

    for (int cont_vel = 0; cont_vel < 4; cont_vel ++){
        media_ball_v[cont_vel] = media_ball_v[cont_vel+1];
    }
    media_ball_v[4] = ball_v;
    ball_v = 0.35*media_ball_v[4]+0.25*media_ball_v[3]+0.2*media_ball_v[2]+0.15*media_ball_v[1]+0.05*media_ball_v[0];
    //cout << ball_v.x << endl;

    vels->first = 0;
    vels->second = 0;

    alpha = 90 - robo->get_angle();
    alpha = ajusta_angulo(alpha);
    if (fabs(alpha) <= limiar_theta){
        w = kgol*v_max*alpha/180;
    }
    else{
        alpha = ajusta_angulo(alpha+180);
        w = kgol*v_max*alpha/180;
    }
    if (ball_pos.x <= centroid_atk.x){
        double tempo;
        double aux_position_y;
        tempo = (robot_pos.x - 3.75 - ball_pos.x)/ball_v.x;
        aux_position_y = ball_pos.y - tempo*ball_v.y;
        //previsao de bola
        if (ball_v.x < 0 && (aux_position_y > centroid_def.y-25) && (aux_position_y < centroid_def.y+25)){
            if (robo->get_angle() > 0){
                v = -(aux_position_y-robot_pos.y)/tempo;
                if(v > 1){
                    v = 1;
                }
                vels->first = v - w*l;
                vels->second = v + w*l;
            }
            else if (robo->get_angle() < 0){
                v = (aux_position_y-robot_pos.y)/tempo;
                if(v > v_max_gol_ef){
                    v = v_max_gol_ef;
                }
                else if(v < -v_max_gol_ef){
                    v = -v_max_gol_ef;
                }
                vels->first = v - w*l;
                vels->second = v + w*l;
            }
        }
        else{
            if (ball_pos.x < 90 && ball_pos.y > 45 && ball_pos.y < 95 && robot_pos.x < centroid_def.x+20){
                //FollowBall
                if (fabs(ball_v.y < 0.4))
                {
                    //ball_v.y = (ball_v.y / fabs(ball_v.y)) * 0.4;

                    if (robo->get_angle() > 0 && ball_pos.y < robot_pos.y ){
                        v = fabs(ball_v.y) - 0.01*(ball_pos.y-robot_pos.y);
                    }
                    else if (robo->get_angle() > 0 && ball_pos.y > robot_pos.y){
                        v = -fabs(ball_v.y) - 0.01*(ball_pos.y-robot_pos.y);
                    }
                    else if (robo->get_angle() < 0 && ball_pos.y < robot_pos.y ){
                        v = -fabs(ball_v.y) + 0.01*(ball_pos.y-robot_pos.y);
                    }
                    else if (robo->get_angle() < 0 && ball_pos.y > robot_pos.y ){
                        v = fabs(ball_v.y) + 0.01*(ball_pos.y-robot_pos.y);
                    }
                }
                if(v > v_max_gol_ef){
                    v = v_max_gol_ef;
                }
                else if(v < -v_max_gol_ef){
                    v = -v_max_gol_ef;
                }
                vels->first = v - w*l;
                vels->second = v + w*l;

                //cout << "FollowBall" << endl;
            }
            else {
                //Return2Goal
                theta = pot_fields->get_direction(robot_grid);
                alpha = theta - robo->get_angle();
                alpha = ajusta_angulo(alpha);
                if (fabs(alpha) <= limiar_theta){
                    w = kgol*v_max_gol*alpha/180;
                    v = -v_max_gol*fabs(alpha)/limiar_theta + v_max_gol;
                }
                else{
                    alpha = ajusta_angulo(alpha+180);
                    w = kgol*v_max_gol*alpha/180;
                    v = v_max_gol*fabs(alpha)/limiar_theta - v_max_gol;
                }
                if (fabs(alpha) > 65 && fabs(alpha) < 115){
                    v = 0;
                }
                if(v > v_max_gol_ef){
                    v = v_max_gol_ef;
                }
                else if(v < -v_max_gol_ef){
                    v = -v_max_gol_ef;
                }
                vels->first = v - w*l;
                vels->second = v + w*l;
                //AdjustRobo
                if((euclidean_dist(robot_pos, pot_fields->get_meta_goalkeeper()) < 5) && (fabs(robo->get_angle()) > 85) && (fabs(robo->get_angle()) < 95)){
                    vels->first = 0;
                    vels->second = 0;
                }
                else if (euclidean_dist(robot_pos, pot_fields->get_meta_goalkeeper()) < 5){
                    goalkeeper_orientation(robo,vels);
                    //cout << "AdjustRobo" << endl;
                }

                //cout << "Return2Goal" << endl;

            }
        }
    }
    else if (ball_pos.x < centroid_def.x){
        double tempo;
        double aux_position_y;
        tempo = (robot_pos.x - 3.75 - ball_pos.x)/ball_v.x;
        aux_position_y = ball_pos.y - tempo*ball_v.y;
        //previsao de bola
        if (ball_v.x > 0 && (aux_position_y > centroid_def.y-25) && (aux_position_y < centroid_def.y+25)){

            if (robo->get_angle() > 0){
                v = -(aux_position_y-robot_pos.y)/tempo;
                if(v > 1){
                    v = 1;
                }
                else if(v < -1){
                    v = -1;
                }
                vels->first = v - w*l;
                vels->second = v + w*l;
            }
            else if (robo->get_angle() < 0){
                v = (aux_position_y-robot_pos.y)/tempo;
                if(v > 1){
                    v = 1;
                }
                else if(v < -1){
                    v = -1;
                }
                vels->first = v - w*l;
                vels->second = v + w*l;
            }
        }
        else{
            if (ball_pos.x > 90 && ball_pos.y > 45 && ball_pos.y < 95 && robot_pos.x > centroid_def.x-20){
                //FollowBall
                if (fabs(ball_v.y < 0.4))
                {
                    //ball_v.y = (ball_v.y / fabs(ball_v.y)) * 0.4;

                    if (robo->get_angle() > 0 && ball_pos.y < robot_pos.y ){
                        v = fabs(ball_v.y) - 0.01*(ball_pos.y-robot_pos.y);
                    }
                    else if (robo->get_angle() > 0 && ball_pos.y > robot_pos.y){
                        v = -fabs(ball_v.y) - 0.01*(ball_pos.y-robot_pos.y);
                    }
                    else if (robo->get_angle() < 0 && ball_pos.y < robot_pos.y ){
                        v = -fabs(ball_v.y) + 0.01*(ball_pos.y-robot_pos.y);
                    }
                    else if (robo->get_angle() < 0 && ball_pos.y > robot_pos.y ){
                        v = fabs(ball_v.y) + 0.01*(ball_pos.y-robot_pos.y);
                    }
                    //cout << "FollowBall" << endl;

                }
                if(v > 1){
                    v = 1;
                }
                else if(v < -1){
                    v = -1;
                }
                vels->first = v - w*l;
                vels->second = v + w*l;               

            }
            else {
                //Return2Goal
                theta = pot_fields->get_direction(robot_grid);
                alpha = theta - robo->get_angle();
                alpha = ajusta_angulo(alpha);
                if (fabs(alpha) <= limiar_theta){
                    w = kgol*v_max_gol*alpha/180;
                    v = -v_max_gol*fabs(alpha)/limiar_theta + v_max_gol;
                }
                else{
                    alpha = ajusta_angulo(alpha+180);
                    w = kgol*v_max_gol*alpha/180;
                    v = v_max_gol*fabs(alpha)/limiar_theta - v_max_gol;
                }
                if (fabs(alpha) > 65 && fabs(alpha) < 115){
                    v = 0;
                }
                if(v > 1){
                    v = 1;
                }
                else if(v < -1){
                    v = -1;
                }
                vels->first = v - w*l;
                vels->second = v + w*l;
                //AdjustRobo
                if((euclidean_dist(robot_pos, pot_fields->get_meta_goalkeeper()) < 5) && (fabs(robo->get_angle()) > 85) && (fabs(robo->get_angle()) < 95)){
                    vels->first = 0;
                    vels->second = 0;
                }
                else if (euclidean_dist(robot_pos, pot_fields->get_meta_goalkeeper()) < 5){
                    goalkeeper_orientation(robo,vels);

                    //cout << "AdjustRobo" << endl;
                }

                //cout << "Return2Goal" << endl;
            }
        }
    }
    //cout << "esquerda " << vels->first << endl;
    //cout << "direita " << vels->second << endl;
    //cout << "angular " << w << endl;
    //cout << "linear " << v << endl;
}

void Mover::velocity_defender(Robot *robo, Game_functions *pot_fields, pair<float, float> *vels){
    // Calcula velocidades
    Point robot_grid = convert_C_to_G(robo->get_pos());

    double v,w,theta,alpha;
    pair<float, float> vel;

    theta = pot_fields->get_direction(robot_grid);
    alpha = theta - robo->get_angle();
    alpha = ajusta_angulo(alpha);

    if (fabs(alpha) <= limiar_theta){
        w = k*v_max*alpha/180;
        v = -v_max*fabs(alpha)/limiar_theta + v_max;
    }
    else{
        alpha = ajusta_angulo(alpha+180);
        w = k*v_max*alpha/180;
        v = v_max*fabs(alpha)/limiar_theta - v_max
                ;
    }
    //Desvio obstáculos
    if (fabs(alpha) > 70 && fabs(alpha) < 110){
        v = 0;
    }
    vels->first = v-w*l;
    vels->second = v+w*l;

    rotate(robo,vels);
}

void Mover::velocity_defensive_midfielder(Robot *robo, Game_functions *pot_fields, pair<float, float> *vels){
    // Calcula velocidades
    Point robot_grid = convert_C_to_G(robo->get_pos());

    double v,w,theta,alpha;
    pair<float, float> vel;

    theta = pot_fields->get_direction(robot_grid);
    alpha = theta - robo->get_angle();
    alpha = ajusta_angulo(alpha);

    if (fabs(alpha) <= limiar_theta){
        w = k*v_max*alpha/180;
        v = -v_max*fabs(alpha)/limiar_theta + v_max;
    }
    else{
        alpha = ajusta_angulo(alpha+180);
        w = k*v_max*alpha/180;
        v = v_max*fabs(alpha)/limiar_theta - v_max;
    }
    //Desvio obstáculos
    if (fabs(alpha) > 70 && fabs(alpha) < 110){
        v = 0;
    }
    vels->first = v-w*l;
    vels->second = v+w*l;
    //cout << "Robo " << robo->get_pos() << endl;

    rotate(robo,vels);
}

void Mover::velocity_ofensive_midfielder(Robot *robo, Game_functions *pot_fields, pair<float, float> *vels){
    Point2d ball_v;

    ball_v.x = ball_vel.first / 100;
    ball_v.y = -ball_vel.second / 100;

    // Calcula velocidades
    Point robot_grid = convert_C_to_G(robo->get_pos());
    Point2d eixo_x(1.0,0.0);
    Point2d robo_pos = robo->get_pos();

    double v,w,theta,alpha;
    pair<float, float> vel;

    atk_situation(robo,pot_fields,vels);

    theta = pot_fields->get_direction(robot_grid);
    alpha = theta - robo->get_angle();
    alpha = ajusta_angulo(alpha);

    if (fabs(alpha) <= limiar_theta){
        w = k*v_max*alpha/180;
        v = -v_max*fabs(alpha)/limiar_theta + v_max;
    }
    else{
        alpha = ajusta_angulo(alpha+180);
        w = k*v_max*alpha/180;
        v = v_max*fabs(alpha)/limiar_theta - v_max;
    }
    //Desvio obstáculos
    if (fabs(alpha) > 70 && fabs(alpha) < 110){
        v = 0;
    }
    vels->first = v - w*l;
    vels->second = v + w*l;

    //cout << "x " << centroid_atk.x << endl;

/*
    // Ajusta ângulo nas situações em que o robô está a 90º para a bola e bem próximo dela
    Point2d vec_ball_prediction = prevision_atk(robo) - robo_pos;
    double ang_vec_prediction = angle_two_points(vec_ball_prediction,eixo_x);
    if (vec_ball_prediction.y < 0)
        ang_vec_prediction = -ang_vec_prediction;

    double prediction_robot = ang_vec_prediction - robo->get_angle();
    //ajusta angulos para menores que 180 e maiores que -180
    if (prediction_robot>180) prediction_robot = prediction_robot - 360;
    else if (prediction_robot<-180) prediction_robot = prediction_robot + 360;

    //ajusta angulos para valores entre -90 e 90
    if (prediction_robot >= 90)
        prediction_robot = prediction_robot-180;
    else if (prediction_robot <= -90)
        prediction_robot = 180+prediction_robot;

    Point2d aux;
    aux.x = 0;
    aux.y = 0;

    if(euclidean_dist(ball_pos,robo->get_pos()) < 10 && fabs(prediction_robot) >= 30 && euclidean_dist(ball_v,aux) < 0.1){
        alpha = ang_vec_prediction;
        alpha = ajusta_angulo(alpha);
        w = k*v_max*alpha/180;
        //vels->first = -w*l;
        //vels->second = w*l;
    }*/

    atk_orientation(robo,vels);
    rotate(robo,vels);
  /*  if (euclidean_dist(ball_pos,robo->get_pos()) < 10 && fabs(ang_ball_robot) < 15 && fabs(ang_atk_robot) < 15){
        cout << 123 << endl;
        if (centroid_atk.x > centroid_def.x){
            if(fabs(robo->get_angle())<90){
                vels->first =  1.6;
                vels->second = 1.6;
            }
            else{
                vels->first =  -1.6;
                vels->second = -1.6;
            }
        }else{
            if(fabs(robo->get_angle())<90){
                vels->first =  -1.6;
                vels->second = -1.6;
            }
            else{
                vels->first =  1.6;
                vels->second = 1.6;
            }
        }
    }
*/

}

void Mover::velocity_striker(Robot *robo, Game_functions *pot_fields, pair<float, float> *vels){

    Point2d ball_v;
    ball_v.x = ball_vel.first / 100;
    ball_v.y = -ball_vel.second / 100;

    // Calcula velocidades
    Point robot_grid = convert_C_to_G(robo->get_pos());
    Point2d eixo_x(1.0,0.0);
    Point2d robo_pos = robo->get_pos();

    double v,w,theta,alpha;
    pair<float, float> vel;

    atk_situation(robo,pot_fields,vels);


    theta = pot_fields->get_direction(robot_grid);
    alpha = theta - robo->get_angle();
    alpha = ajusta_angulo(alpha);

    if (fabs(alpha) <= limiar_theta){
        w = k*v_max*alpha/180;
        v = -v_max*fabs(alpha)/limiar_theta + v_max;
    }
    else{
        alpha = ajusta_angulo(alpha+180);
        w = k*v_max*alpha/180;
        v = v_max*fabs(alpha)/limiar_theta - v_max;
    }
    //Desvio obstáculos
    if (fabs(alpha) > 70 && fabs(alpha) < 110){
        v = 0;
    }
    vels->first = v-w*l;
    vels->second = v+w*l;
    atk_orientation(robo,vels);

/*
    // Ajusta ângulo nas situações em que o robô está mal orientado para a bola e bem próximo dela
    Point2d vec_ball_prediction = prevision_atk(robo) - robo_pos;
    double ang_vec_prediction = angle_two_points(vec_ball_prediction,eixo_x);
    if (vec_ball_prediction.y < 0)
        ang_vec_prediction = -ang_vec_prediction;

    double prediction_robot = ang_vec_prediction - robo->get_angle();
    //ajusta angulos para menores que 180 e maiores que -180
    if (prediction_robot>180) prediction_robot = prediction_robot - 360;
    else if (prediction_robot<-180) prediction_robot = prediction_robot + 360;

    //ajusta angulos para valores entre -90 e 90
    if (prediction_robot >= 90)
        prediction_robot = prediction_robot-180;
    else if (prediction_robot <= -90)
        prediction_robot = 180+prediction_robot;

    Point2d aux;
    aux.x = 0;
    aux.y = 0;

    if(euclidean_dist(ball_pos,robo->get_pos()) < 10 && fabs(prediction_robot) >= 30 && euclidean_dist(ball_v,aux) < 0.1){
        alpha = ang_vec_prediction - robo->get_angle();
        alpha = ajusta_angulo(alpha);
        w = k*v_max*alpha/180;
        //vels->first = -w*l;
        //vels->second = w*l;
    }
*/
    rotate(robo,vels);
 /*   if (euclidean_dist(ball_pos,robo->get_pos()) < 10 && fabs(ang_ball_robot) < 15 && fabs(ang_atk_robot) < 15){
        //cout << 123 << endl;
        if (centroid_atk.x > centroid_def.x){
            if(fabs(robo->get_angle())<90){
                vels->first =  1.6;
                vels->second = 1.6;
            }
            else{
                vels->first =  -1.6;
                vels->second = -1.6;
            }
        }else{
            if(fabs(robo->get_angle())<90){
                vels->first =  -1.6;
                vels->second = -1.6;
            }
            else{
                vels->first =  1.6;
                vels->second = 1.6;
            }
        }
    }
*/
}

void Mover::velocity_guardian(Robot *robo, Game_functions *pot_fields, pair<float, float> *vels){
    Point2d ball_v;
    ball_v.x = ball_vel.first / 100;
    ball_v.y = -ball_vel.second / 100;


    // Calcula velocidades
    Point robot_grid = convert_C_to_G(robo->get_pos());
    Point2d eixo_x(1.0,0.0);
    Point2d robo_pos = robo->get_pos();

    double v,w,theta,alpha;
    pair<float, float> vel;

     if(euclidean_dist(robo_pos, pot_fields->get_meta()) > 30)
        v_max = 1;
     else
        v_max = 0.6;

    theta = pot_fields->get_direction(robot_grid);
    alpha = theta - robo->get_angle();
    alpha = ajusta_angulo(alpha);

    if (fabs(alpha) <= limiar_theta){
        w = (k*v_max*alpha/180);
        v = -v_max*fabs(alpha)/limiar_theta + v_max;
    }
    else{
        alpha = ajusta_angulo(alpha+180);
        w = k*v_max*alpha/180;
        v = v_max*fabs(alpha)/limiar_theta - v_max;
    }

    //Desvio obstáculos
    if (fabs(alpha) > 70 && fabs(alpha) < 110){
        v = 0;
        //w = 2*w;
    }

    vels->first = v-w*l;   //Esquerda
    vels->second = v+w*l;  //Direita


   /* if(euclidean_dist(robo->get_pos(),pot_fields->get_meta())<10){
        vels->first = 0;
        vels->second = 0;
    }*/
    robot_orientation(robo, pot_fields, vels); // Se o robo estiver na meta, ele aponta para a bola
    rotate(robo, vels);  //Gira nos cantos

}

void Mover::velocity_killer(Robot *robo, Game_functions *pot_fields, pair<float, float> *vels){
    Point2d ball_v;
    ball_v.x = ball_vel.first / 100;
    ball_v.y = -ball_vel.second / 100;

    // Calcula velocidades
    Point robot_grid = convert_C_to_G(robo->get_pos());
    Point2d eixo_x(1.0,0.0);
    Point2d robo_pos = robo->get_pos();

    double v,w,theta,alpha;
    pair<float, float> vel;

     if(euclidean_dist(robo_pos, pot_fields->get_meta()) > 30){
        v_max = 1;
        //cout << "Aumentou " << endl;
     }
     else{
        v_max = 0.6;
    }

    //atk_situation(robo,pot_fields,vels);

    theta = pot_fields->get_direction(robot_grid);
    alpha = theta - robo->get_angle();
    alpha = ajusta_angulo(alpha);


    if (fabs(alpha) <= limiar_theta){
        w = (k*v_max*alpha/180);
        //w = k*v_max*pow(alpha/180,2)*(alpha/fabs(alpha));
        v = -v_max*fabs(alpha)/limiar_theta + v_max;
    }
    else{
        alpha = ajusta_angulo(alpha+180);
        w = k*v_max*alpha/180;
        //w = k*v_max*pow(alpha/180,2)*(alpha/fabs(alpha));
        v = v_max*fabs(alpha)/limiar_theta - v_max;
    }

    //Desvio obstáculos
    if (fabs(alpha) > 80 && fabs(alpha) < 110){
        v = 0;
        //cont_desvia = cont_desvia+1;
        //cout << "Desviou: " << cont_desvia << endl;
        //w = 1.5*w;
    }




    vels->first = v-w*l;
    vels->second = v+w*l;


     // Calculo do angulo de orientacao usar no ataque leve para dribles
    /*//Corrige Posicionamento
    Point2d aux = prevision_atk(robo);
    aux.y = -aux.y;
    ball_pos.y = -ball_pos.y;
    centroid_atk.y = -centroid_atk.y;
    robo_pos.y = -robo_pos.y;

    //Calcula angulo entre a bola e o gol de ataque
    Point2d vec_ball_robot = aux-robo_pos;
    double ang_ball_robot = angle_two_points(vec_ball_robot,eixo_x);
    if (vec_ball_robot.y < 0)
        ang_ball_robot = -ang_ball_robot;

    cout << "ang " << ang_ball_robot << endl;

    //ajusta angulos para menores que 180 e maiores que -180
    if (ang_ball_robot > 180) ang_ball_robot = ang_ball_robot - 360;
    else if (ang_ball_robot < -180) ang_ball_robot = ang_ball_robot + 360;
    //cout << "Angulo bola atk: " << ang_ball_atk << endl;

    //Corrige Posicionamento novamente
    aux.y = -aux.y;
    ball_pos.y = -ball_pos.y;
    centroid_atk.y=-centroid_atk.y;
    robo_pos.y = -robo_pos.y;

    ang_ball_robot = ang_ball_robot - robo->get_angle();

    //ajusta angulos para menores que 180 e maiores que -180
    if (ang_ball_robot>180) ang_ball_robot = ang_ball_robot - 360;
    else if (ang_ball_robot<-180) ang_ball_robot = ang_ball_robot + 360;

    //ajusta angulos para valores entre -90 e 90
    if (ang_ball_robot >= 90)
        ang_ball_robot = ang_ball_robot-180;
    else if (ang_ball_robot <= -90)
        ang_ball_robot = 180+ang_ball_robot;*/


    /*if (euclidean_dist(robo->get_pos(),pot_fields->get_meta()) < 7 && fabs(ang_ball_robot) > 35){
        alpha = ang_ball_robot;
        alpha = ajusta_angulo(alpha);
        if (fabs(alpha) <= limiar_theta){
            w = 5*alpha/180;
        }
        else{
            alpha = ajusta_angulo(alpha+180);
            w = 5*alpha/180;
        }

        vels->first = -w*l;
        vels->second = w*l;
        //cout << "bola x " << ball_pos.x << "   y " << ball_pos.y << endl;
        //cout << "meta x " << pot_fields->get_meta().x << "   y " << pot_fields->get_meta().y << endl;
    }
    else if(euclidean_dist(robo->get_pos(),pot_fields->get_meta()) < 7){
        theta = pot_fields->get_direction(robot_grid);
        alpha = theta - robo->get_angle();
        alpha = ajusta_angulo(alpha);


        if (fabs(alpha) <= limiar_theta){
            w = (k*v_max*alpha/180);
            //w = k*v_max*pow(alpha/180,2)*(alpha/fabs(alpha));
            v = -v_max*fabs(alpha)/limiar_theta + v_max;
        }
        else{
            alpha = ajusta_angulo(alpha+180);
            w = k*v_max*alpha/180;
            //w = k*v_max*pow(alpha/180,2)*(alpha/fabs(alpha));
            v = v_max*fabs(alpha)/limiar_theta - v_max;
        }

        vels->first = v-w*l;
        vels->second = v+w*l;
    }*/




    /*double ang_vel;
    ang_vel = robo->get_ang_vel();
    ang_vel = ang_vel*3.141592/180;
    vel = robo->get_velocities();
    vel.first = vel.first*X_CONV_CONST;
    vel.second = vel.second*Y_CONV_CONST;
    double mod_vel = sqrt(pow(vel.first,2) + pow(vel.second,2));
    cout << "Angular Calculada:" << w << endl;
    cout << "Linear Calculada:" << v << endl;
    cout << "Linear:" << mod_vel/100 << endl << endl << endl;
    cout << "Angular:" << ang_vel << endl;*/

    atk_orientation(robo, vels); // Se o robo estiver perto da bola no ataque, ele aponta para a bola
    rotate(robo, vels);

}

void Mover::velocity_test(Robot *robo, Game_functions *pot_fields, pair<float, float> *vels){
    Point2d ball_v;
    pair <double,double> vel;
    double ang_vel;
    ball_v.x = ball_vel.first / 100;
    ball_v.y = -ball_vel.second / 100;

    // Calcula velocidades
    Point robot_grid = convert_C_to_G(robo->get_pos());
    Point2d eixo_x(1.0,0.0);
    Point2d robo_pos = robo->get_pos();

    double v,w,theta,alpha,last_alpha;
    theta = pot_fields->get_direction(robot_grid);
    alpha = theta - robo->get_angle();
    alpha = ajusta_angulo(alpha);
    //cout << "valor de alpha" << alpha << endl;

    if (fabs(alpha) <= limiar_theta){
        w = (k*v_max*alpha/180);
        //w = k*v_max*pow(alpha/180,2)*(alpha/fabs(alpha));
        v = -v_max*fabs(alpha)/limiar_theta + v_max;
    }
    else{
        alpha = ajusta_angulo(alpha+180);
        w = k*v_max*alpha/180;
        //w = k*v_max*pow(alpha/180,2)*(alpha/fabs(alpha));
        v = v_max*fabs(alpha)/limiar_theta - v_max;
    }
    //Desvio obstáculosim
    if (fabs(alpha) > 80 && fabs(alpha) < 100){
        //w = w*3;
        v = 0;
    }

    cout << "Angular Calculada:" << w << endl;

    vels->first = v-w*l;
    vels->second = v+w*l;

    //cout << "Vel Esquerda:" << vels->first << endl;
    //cout << "Vel Direita:" << vels->second << endl;

    ang_vel = robo->get_ang_vel();
    ang_vel = ang_vel*3.141592/180;

    vel = robo->get_velocities();

    vel.first = vel.first*X_CONV_CONST;
    vel.second = vel.second*Y_CONV_CONST;

    cout << "Angular:" << ang_vel << endl;

    double mod_vel = sqrt(pow(vel.first,2) + pow(vel.second,2));

    cout << "Linear Calculada:" << v << endl;
    cout << "Linear:" << mod_vel/100 << endl << endl << endl;
    cont = cont + 1;
    cout << "Contador: " << cont << endl;

    rotate(robo, vels);

}

void Mover::goalkeeper_orientation(Robot *r, pair<float, float> *vels){
    double alpha,w;
    alpha = 90 - r->get_angle();
    alpha = ajusta_angulo(alpha);
    if (fabs(alpha) <= limiar_theta){
        w = k*v_max*alpha/180;
    }
    else{
        alpha = ajusta_angulo(alpha+180);
        w = k*v_max*alpha/180;
    }
    vels->first = -w*l;
    vels->second = w*l;
}

void Mover::robot_orientation(Robot *robo, Game_functions *pot_fields, pair<float, float> *vels){
    double alpha,w;

    Point2d ball_v;
    ball_v.x = ball_vel.first / 100;
    ball_v.y = -ball_vel.second / 100;


    // Calcula velocidades
    //Point robot_grid = convert_C_to_G(robo->get_pos());
    Point2d eixo_x(1.0,0.0);
    Point2d robo_pos = robo->get_pos();

    //Corrige Posicionamento
    ball_pos.y = -ball_pos.y;
    robo_pos.y = -robo_pos.y;
    centroid_atk.y=-centroid_atk.y;


    //Calcula angulo entre robo e bola
    Point2d vec_ball_robot = ball_pos-robo_pos;
    double ang_vec_ball_eixox = angle_two_points(vec_ball_robot,eixo_x);
    //cout << ball_pos.x << endl;
    //Corrige o angulo
    if (vec_ball_robot.y < 0)
        ang_vec_ball_eixox = -ang_vec_ball_eixox;

    double ang_ball_robot = ang_vec_ball_eixox - robo->get_angle();


    //Calcula angulo entre robo e gol adversario
    Point2d vec_atk_robot = centroid_atk-robo_pos;
    double ang_vec_atk_eixox = angle_two_points(vec_atk_robot,eixo_x);

    //Corrige o angulo
    if (vec_atk_robot.y < 0)
        ang_vec_atk_eixox = -ang_vec_atk_eixox;

    double ang_atk_robot = ang_vec_atk_eixox - robo->get_angle();

    //ajusta angulos para menores que 180 e maiores que -180
    if (ang_atk_robot>180) ang_atk_robot = ang_atk_robot - 360;
    else if (ang_atk_robot<-180) ang_atk_robot = ang_atk_robot + 360;

    //Recorrige o Posicionamento
    ball_pos.y = -ball_pos.y;
    robo_pos.y = -robo_pos.y;
    centroid_atk.y=-centroid_atk.y;


    //orienta o robo se tiver na meta
    if(euclidean_dist(robo->get_pos(),pot_fields->get_meta())<10){
        if(fabs(euclidean_dist(ball_pos,centroid_def)) < 130){
            alpha = ang_ball_robot;
            //cout << "aaaaaa" << endl;
        }
        else{
            alpha = ang_atk_robot;
            //cout << "bbbbbb" << endl;
        }
        alpha = ajusta_angulo(alpha);
        if (fabs(alpha) <= limiar_theta){
            w = k*v_max*alpha/180;
        }
        else{
            alpha = ajusta_angulo(alpha+180);
            w = k*v_max*alpha/180;
        }

        vels->first = -w*l;
        vels->second = w*l;
    }

}

void Mover::atk_orientation(Robot *robo, pair<float, float> *vels){
    Point2d robo_pos = robo->get_pos();
    Point2d ball_v;
    Point2d eixo_x(1.0,0.0);
    ball_v.x = ball_vel.first / 100;
    ball_v.y = -ball_vel.second / 100;

    // Ajusta ângulo nas situações em que o robô está mal orientado para a bola e bem próximo dela
    Point2d vec_ball_prediction = prevision_atk(robo) - robo->get_pos();
    double ang_vec_prediction = angle_two_points(vec_ball_prediction,eixo_x);
    if (vec_ball_prediction.y < 0)
        ang_vec_prediction = -ang_vec_prediction;

    double prediction_robot = ang_vec_prediction - robo->get_angle();
    //ajusta angulos para menores que 180 e maiores que -180
    if (prediction_robot>180) prediction_robot = prediction_robot - 360;
    else if (prediction_robot<-180) prediction_robot = prediction_robot + 360;

    //ajusta angulos para valores entre -90 e 90
    if (prediction_robot >= 90)
        prediction_robot = prediction_robot-180;
    else if (prediction_robot <= -90)
        prediction_robot = 180+prediction_robot;

    Point2d aux;
    aux.x = 0;
    aux.y = 0;


    //Corrige Posicionamento
    ball_pos.y = -ball_pos.y;
    robo_pos.y = -robo_pos.y;
    centroid_atk.y=-centroid_atk.y;

    //Calcula angulo entre robo e bola
    Point2d vec_ball_robot = ball_pos-robo_pos;
    double ang_vec_ball_eixox = angle_two_points(vec_ball_robot,eixo_x);
    //cout << ball_pos.x << endl;
    //Corrige o angulo
    if (vec_ball_robot.y < 0)
        ang_vec_ball_eixox = -ang_vec_ball_eixox;

    double ang_ball_robot = ang_vec_ball_eixox - robo->get_angle();


    //Calcula angulo entre robo e gol adversario
    Point2d vec_atk_robot = centroid_atk-robo_pos;
    double ang_vec_atk_eixox = angle_two_points(vec_atk_robot,eixo_x);

    //Corrige o angulo
    if (vec_atk_robot.y < 0)
        ang_vec_atk_eixox = -ang_vec_atk_eixox;

    double ang_atk_robot = ang_vec_atk_eixox - robo->get_angle();

    //ajusta angulos para menores que 180 e maiores que -180
    if (ang_ball_robot>180) ang_ball_robot = ang_ball_robot - 360;
    else if (ang_ball_robot<-180) ang_ball_robot = ang_ball_robot + 360;
    if (ang_atk_robot>180) ang_atk_robot = ang_atk_robot - 360;
    else if (ang_atk_robot<-180) ang_atk_robot = ang_atk_robot + 360;

    //ajusta angulos para valores entre -90 e 90
    if (ang_ball_robot >= 90)
        ang_ball_robot = ang_ball_robot-180;
    else if (ang_ball_robot <= -90)
        ang_ball_robot = 180+ang_ball_robot;

    if (ang_atk_robot >= 90)
        ang_atk_robot = ang_atk_robot-180;
    else if (ang_atk_robot <= -90)
        ang_atk_robot = 180+ang_atk_robot;


    //Recorrige o Posicionamento
    ball_pos.y = -ball_pos.y;
    robo_pos.y = -robo_pos.y;
    centroid_atk.y=-centroid_atk.y;


    // Função para fazer o robô girar no ataque
    if (centroid_atk.x > ball_pos.x){
        if ((ball_pos.y > centroid_atk.y) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro) && fabs(prediction_robot) >= 30 && euclidean_dist(ball_v,aux) < 0.1 && fabs(ang_ball_robot) > 50){
            vels->first = -vel_giro_atk;
            vels->second = vel_giro_atk;
        }
        else if ((ball_pos.y < centroid_atk.y) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro) && fabs(prediction_robot) >= 30 && euclidean_dist(ball_v,aux) < 0.1 && fabs(ang_ball_robot) > 50){
            vels->first = vel_giro_atk;
            vels->second = -vel_giro_atk;
        }
    }
    else{
        if ((ball_pos.y > centroid_atk.y) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro) && fabs(prediction_robot) >= 30 && euclidean_dist(ball_v,aux) < 0.1 && fabs(ang_ball_robot) > 50){
            vels->first = vel_giro_atk;
            vels->second = -vel_giro_atk;
        }
        else if ((ball_pos.y < centroid_atk.y) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro) && fabs(prediction_robot) >= 30 && euclidean_dist(ball_v,aux) < 0.1 && fabs(ang_ball_robot) > 50){
            vels->first = -vel_giro_atk;
            vels->second = vel_giro_atk;
        }
    }
}

void Mover::atk_situation(Robot *robo, Game_functions *pot_fields, pair<float, float> *vels){
    Point2d robo_pos = robo->get_pos();
    Point2d eixo_x(1.0,0.0);

    //Cálculo das variáveis utilizadas para aumentar a velocidade do robô

    //Corrige Posicionamento
    ball_pos.y = -ball_pos.y;
    robo_pos.y = -robo_pos.y;
    centroid_atk.y=-centroid_atk.y;

    //Calcula angulo entre robo e bola
    Point2d vec_ball_robot = ball_pos-robo_pos;
    double ang_vec_ball_eixox = angle_two_points(vec_ball_robot,eixo_x);
    //cout << ball_pos.x << endl;
    //Corrige o angulo
    if (vec_ball_robot.y < 0)
        ang_vec_ball_eixox = -ang_vec_ball_eixox;

    double ang_ball_robot = ang_vec_ball_eixox - robo->get_angle();


    //Calcula angulo entre robo e gol adversario
    Point2d vec_atk_robot = centroid_atk-robo_pos;
    double ang_vec_atk_eixox = angle_two_points(vec_atk_robot,eixo_x);

    //Corrige o angulo
    if (vec_atk_robot.y < 0)
        ang_vec_atk_eixox = -ang_vec_atk_eixox;

    double ang_atk_robot = ang_vec_atk_eixox - robo->get_angle();

    //ajusta angulos para menores que 180 e maiores que -180
    if (ang_ball_robot>180) ang_ball_robot = ang_ball_robot - 360;
    else if (ang_ball_robot<-180) ang_ball_robot = ang_ball_robot + 360;
    if (ang_atk_robot>180) ang_atk_robot = ang_atk_robot - 360;
    else if (ang_atk_robot<-180) ang_atk_robot = ang_atk_robot + 360;

    //ajusta angulos para valores entre -90 e 90
    if (ang_ball_robot >= 90)
        ang_ball_robot = ang_ball_robot-180;
    else if (ang_ball_robot <= -90)
        ang_ball_robot = 180+ang_ball_robot;

    if (ang_atk_robot >= 90)
        ang_atk_robot = ang_atk_robot-180;
    else if (ang_atk_robot <= -90)
        ang_atk_robot = 180+ang_atk_robot;


    //Recorrige o Posicionamento
    ball_pos.y = -ball_pos.y;
    robo_pos.y = -robo_pos.y;
    centroid_atk.y=-centroid_atk.y;



    //Aumenta a velocidade do robô em situações claras de gol
    if (euclidean_dist(ball_pos,robo->get_pos()) < 10 && fabs(ang_ball_robot) < 30 && fabs(ang_atk_robot) < 30){
        v_max = 1.6;
        k = (w_max/v_max);
        cout << "Atk-situation " << endl;
    }
    else{
        v_max = 0.6;
        k = (w_max/v_max);
        //cout << "saiu mover-striker " << endl;
        //cout << "Angulo bola robo: " << ang_ball_robot << " - Angulo ataque robo: " << ang_atk_robot << endl;
    }


}

void Mover::rotate(Robot *robo, pair<float, float> *vels){
    // Função para fazer o robô girar nos cantos
    if (centroid_atk.x > ball_pos.x){
        if ((ball_pos.y > centroid_atk.y+55) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro) ){
            //cout << "3" << endl;
            vels->first = -vel_giro_lado;
            vels->second = vel_giro_lado;
        }
        else if ((ball_pos.y < centroid_atk.y-55) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro)){
            //cout << "4" << endl;
            vels->first = vel_giro_lado;
            vels->second = -vel_giro_lado;
        }
    }
    else{
        if ((ball_pos.y > centroid_atk.y+55) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro)){
            vels->first = vel_giro_lado;
            vels->second = -vel_giro_lado;
        }
        else if ((ball_pos.y < centroid_atk.y-55) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro)){
            vels->first = -vel_giro_lado;
            vels->second = vel_giro_lado;
        }
    }

    // Função para fazer o robô girar na linha de fundo
    if (centroid_atk.x > ball_pos.x){
        if ((ball_pos.y > centroid_atk.y+35) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro) && fabs(ball_pos.x - centroid_atk.x) < 15){
            //cout << "3" << endl;
            vels->first = -vel_giro_lado;
            vels->second = vel_giro_lado;
            //cout << "foi" << endl;
        }
        else if ((ball_pos.y < centroid_atk.y-35) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro && fabs(ball_pos.x - centroid_atk.x) < 15)){
            //cout << "4" << endl;
            vels->first = vel_giro_lado;
            vels->second = -vel_giro_lado;
            //cout << "foi" << endl;
        }
    }
    else{
        if ((ball_pos.y > centroid_atk.y+35) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro && fabs(ball_pos.x - centroid_atk.x) < 15)){
            vels->first = vel_giro_lado;
            vels->second = -vel_giro_lado;
            //cout << "foi" << endl;
        }
        else if ((ball_pos.y < centroid_atk.y-35) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro && fabs(ball_pos.x - centroid_atk.x) < 15)){
            vels->first = -vel_giro_lado;
            vels->second = vel_giro_lado;
            //cout << "foi" << endl;
        }
    }

    // Função para fazer o robô girar na linha de fundo
    if (centroid_atk.x > ball_pos.x){
        if ((ball_pos.y > centroid_atk.y+35) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro) && fabs(ball_pos.x - centroid_atk.x) < 15){
            //cout << "3" << endl;
            vels->first = -vel_giro_lado;
            vels->second = vel_giro_lado;
            //cout << "foi" << endl;
        }
        else if ((ball_pos.y < centroid_atk.y-35) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro && fabs(ball_pos.x - centroid_atk.x) < 15)){
            //cout << "4" << endl;
            vels->first = vel_giro_lado;
            vels->second = -vel_giro_lado;
            //cout << "foi" << endl;
        }
    }
    else{
        if ((ball_pos.y > centroid_atk.y+35) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro && fabs(ball_pos.x - centroid_atk.x) < 15)){
            vels->first = vel_giro_lado;
            vels->second = -vel_giro_lado;
            //cout << "foi" << endl;
        }
        else if ((ball_pos.y < centroid_atk.y-35) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro && fabs(ball_pos.x - centroid_atk.x) < 15)){
            vels->first = -vel_giro_lado;
            vels->second = vel_giro_lado;
            //cout << "foi" << endl;
        }
    }

    // Função para fazer o robô girar na linha de fundo
    if (centroid_atk.x > ball_pos.x){
        if ((ball_pos.y > centroid_def.y+35) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro) && fabs(ball_pos.x - centroid_def.x) < 15){
            //cout << "3" << endl;
            vels->first = -vel_giro_lado;
            vels->second = vel_giro_lado;
            //cout << "foi" << endl;
        }
        else if ((ball_pos.y < centroid_def.y-35) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro && fabs(ball_pos.x - centroid_def.x) < 15)){
            //cout << "4" << endl;
            vels->first = vel_giro_lado;
            vels->second = -vel_giro_lado;
            //cout << "foi" << endl;
        }
    }
    else{
        if ((ball_pos.y > centroid_def.y+35) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro && fabs(ball_pos.x - centroid_def.x) < 15)){
            vels->first = vel_giro_lado;
            vels->second = -vel_giro_lado;
            //cout << "foi" << endl;
        }
        else if ((ball_pos.y < centroid_def.y-35) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro && fabs(ball_pos.x - centroid_def.x) < 15)){
            vels->first = -vel_giro_lado;
            vels->second = vel_giro_lado;
            //cout << "foi" << endl;
        }
    }

}

Point2d Mover::prevision_atk(Robot *robo){
    Point2d next_ball_pos;
    Point2d ball_v;

    ball_v.x = ball_vel.first / 100;
    ball_v.y = ball_vel.second / 100;

    double dist = euclidean_dist(robo->get_pos(),ball_pos);
    double time = dist/30;
    next_ball_pos = ball_pos + ball_v*time;
    //cout << "atual " << "x " << ball_pos.x << "   y " << ball_pos.y << endl;
    //cout << "proxima " << "x " << next_ball_pos.x << "   y " << next_ball_pos.y << endl;
    return next_ball_pos;

}


Point Mover::convert_C_to_G(Point2d coord){
    Point i;

    coord.x = int(coord.x) + 5;
    coord.y = int(coord.y) + 5;

    if((coord.x / dx < 35) && (coord.x / dx > 0)){
        i.x = coord.x / dx;
    }
    else if(coord.x / dx >=35){
        i.x = 34;
    }
    else if(coord.x / dx <=0){
        i.x = 1;
    }

    if((coord.y / dy < 27) && (coord.y / dy > 0)){
        i.y = coord.y / dy;
    }
    else if(coord.y / dy >= 27){
        i.y = 26;
    }
    else if(coord.y / dy <= 0){
        i.y = 1;
    }
    //cout << "i.x = " << i.x << " i.y = " << i.y << endl;
    return i;
}
void Mover::set_enemy_pos(p2dVector enemy_pos){
    this->enemy_pos = enemy_pos;
}

void Mover::set_ball_pos(Point2d ball_pos){
    this->ball_pos = ball_pos;
}

void Mover::set_centroid_atk(Point2d centroid_atk){
    this->centroid_atk = centroid_atk;
}

void Mover::set_centroid_def(Point2d centroid_def){
    this->centroid_def = centroid_def;
}

double Mover::ajusta_angulo(double angle){
    if (angle < -180)
        angle = angle + 360;
    else if (angle > 180)
        angle = angle - 360;
    else
        angle = angle;
    return angle;
}
