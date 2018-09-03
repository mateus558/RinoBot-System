#include <iostream>
#include <iomanip>
#include <cmath>
#include "mover.h"
#include "robot.h"
#include "utils.h"

using namespace std;

// Constantes para qualquer robô
double delta_limiar = 10; //Cinemática: 15, PID:
double limiar_theta = 90 + delta_limiar;
//double l = 0.028; // caso mudar de robo trocar esse valor (robo antigo 0.0275 - robo novo 0.028)

// Constantes para robôs de linha
double v_max = 0.6; //0.75
double v_delta = 0.2;
double w_max = 7;
double k = (w_max/v_max);
double dist_giro = 10.0;
double vel_giro_lado = 1.6;
double vel_giro_atk = 0.5;
double v_atk = 0.95;
double last_angle = 0;

// Constantes para o goleiro
double v_max_gol = 0.38;  //0.5
double v_delta_gol = 0.15;
double v_max_gol_ef = 0.6;
double w_max_gol = 5;
double kgol = (w_max_gol/v_max_gol);
double dist_giro_gol = 10.0;
double vel_giro_gol = 1.0;

// Constantes para a movimentação com PID
double last_phi = 0; // Última orientação do robô
double last_theta_control = 0;
double ka = 0.15;

//double kp = 15;  // Ganho proporcional 13
//double kd = 0.003;  // Ganho derivativo

//Constantes para teste do novo controlador
double last_robo_pos_x = 0;
double last_robo_pos_y = 0;
double v = 0.5;
double v_min = 0.5;
double Kw = 0.1;
double k_distance = 0.5;
double last_theta;
double Rm = v_max*w_max;
int test = 0;


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
    last_killer.x = 0;
    last_killer.y = 0;
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
    line_root_defender = 38;
    //Pro primeiro robô - Gandalf
    calcula_velocidades(&selec_robot.r1,selec_iterador.gandalf, &vels[0]);
    selec_robot.r1.set_lin_vel(vels[0]);
    ////cout << "Velocidades: " << vels[0].first << " " <<  vels[0].second << endl;

    //Pro segundo robô - Presto
    calcula_velocidades(&selec_robot.r2,selec_iterador.presto, &vels[1]);
    selec_robot.r2.set_lin_vel(vels[1]);

    line_root_defender = 75;
    //Pro terceiro robô - Leona
    calcula_velocidades(&selec_robot.r3,selec_iterador.leona, &vels[2]);
    selec_robot.r3.set_lin_vel(vels[2]);
    ////cout << "left " << vels[0].first << "   right " << vels[0].second << endl;



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
    double err;
    //double ang;

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
    set_params(r);
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
    case 9:
        velocity_fake9(r, potencial_fields , vels);  //velocity_killer
        break;
    case 10:
        velocity_killer_cpu(r, potencial_fields , vels);  //velocity_killer
        break;
    case 11:
        velocity_guardian(r, potencial_fields , vels);
        break;
    case 21:
        velocity_defender_root(r, potencial_fields , vels);
        break;
    case 100:
        velocity_test(r, potencial_fields , vels); //velocity_test
        break;
    }
}

void Mover::velocity_goalkeeper(Robot *robo, Game_functions *pot_fields, pair<float, float> *vels){
    Point2d robot_pos = robo->get_pos();
    double robot_angle = ajusta_angulo(robo->get_angle());
    Point robot_grid = convert_C_to_G(robot_pos);

    double kp = robo->get_kp();
    double kd = robo->get_kd();
    double l = robo->get_l_size();


    double v,w,theta,alpha;
    pair<float, float> vel;

    Point2d ball_v;
    ball_v.x = ball_vel.first / 100;
    ball_v.y = -ball_vel.second / 100;


    for (int cont_vel = 0; cont_vel < 4; cont_vel ++){
        media_ball_v[cont_vel] = media_ball_v[cont_vel+1];
    }
    media_ball_v[4] = ball_v;
    ball_v = 0.35*media_ball_v[4]+0.25*media_ball_v[3]+0.2*media_ball_v[2]+0.15*media_ball_v[1]+0.05*media_ball_v[0];

    ////cout << ball_v.x << endl;

    ////cout << "x " << ball_pos.x << "   y " << ball_pos.y << endl;

    vels->first = 0;
    vels->second = 0;

    alpha = 90 - robot_angle;
    alpha = ajusta_angulo(alpha);


    //PID
    if (fabs(alpha) <= limiar_theta ){
        w = kp*alpha/180 + kd*(alpha - last_phi);
        limiar_theta = 90 - delta_limiar;
    }
    else{
        alpha = ajusta_angulo(alpha+180);
        w = kp*alpha/180 + kd*(alpha - last_phi);
        limiar_theta = 90 + delta_limiar;
    }
    v_max_gol = 0.35;




    //Cinemática

    //        if (fabs(alpha) <= limiar_theta){
    //            w = kgol*v_max_gol*alpha/180;
    //        }
    //        else{
    //            alpha = ajusta_angulo(alpha+180);
    //            w = kgol*v_max_gol*alpha/180;
    //        }
    if (centroid_def.x <= centroid_atk.x){
        double tempo;
        double aux_position_y;
        tempo = (robot_pos.x + 4.5 - ball_pos.x)/ball_v.x;
        aux_position_y = ball_pos.y - tempo*ball_v.y;
        //previsao de bola
        if (ball_v.x < 0 && (aux_position_y > centroid_def.y-25) && (aux_position_y < centroid_def.y+25)){
            if (robot_angle > 0){
                v = -0.8*(aux_position_y-robot_pos.y)/tempo;
                if(v > 0.6){
                    v = 0.6;
                }
                else if (v < -0.6){
                    v = -0.6;
                }
                vels->first = v - w*l;
                vels->second = v + w*l;
            }
            else if (robot_angle < 0){
                v = 0.8*(aux_position_y-robot_pos.y)/tempo;
                if(v > 0.6){
                    v = 0.6;
                }
                else if(v < -0.6){
                    v = -0.6;
                }

                vels->first = v - w*l;
                vels->second = v + w*l;
            }
            ////cout << "Prevision" << endl;
        }
        else{
            if (ball_pos.x < 90 && ball_pos.y > 45 && ball_pos.y < 95 && robot_pos.x < centroid_def.x+20){
                //FollowBall


                alpha = 90 - robot_angle;
                alpha = ajusta_angulo(alpha);


                //PID
                if (fabs(alpha) <= limiar_theta ){
                    w = 17*alpha/180 + kd*(alpha - last_phi);
                    limiar_theta = 90 - delta_limiar;
                }
                else{
                    alpha = ajusta_angulo(alpha+180);
                    w = 17*alpha/180 + kd*(alpha - last_phi);
                    limiar_theta = 90 + delta_limiar;
                }


                if (fabs(ball_v.y < 2))
                {
                    //cout << "angle " << robot_angle << endl;
                    //ball_v.y = (ball_v.y / fabs(ball_v.y)) * 0.4;
                    if(fabs(robo->get_pos().y-ball_pos.y) < 3){
                        v = 0;
                    }
                    else if (robot_angle > 0 && ball_pos.y < robot_pos.y ){
                        v = 0.23; // Cinemática 0.005
                        //  cout << "1" << endl;
                    }
                    else if (robot_angle > 0 && ball_pos.y > robot_pos.y){
                        v = -0.23; //PID 0.03
                        // cout << "2" << endl;
                    }
                    else if (robot_angle < 0 && ball_pos.y < robot_pos.y ){
                        v = -0.23;
                        //cout << "3" << endl;
                    }
                    else if (robot_angle < 0 && ball_pos.y > robot_pos.y ){
                        v = 0.23;
                        //cout << "4" << endl;
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

                ////cout << "FollowBall" << endl;

            }

            else {
                //Return2Goal
                //v_max_gol = 0.5;
                theta = pot_fields->get_direction(robot_grid);
                alpha = theta - robot_angle;
                alpha = ajusta_angulo(alpha);


                //PID
                if (fabs(alpha) <= limiar_theta ){
                    //v = v_max;
                    v = -v_delta_gol*fabs(alpha)/limiar_theta + v_max_gol;
                    w = kp*alpha/180 + kd*(alpha - last_phi);
                    limiar_theta = 90 - delta_limiar;
                    ////cout << "Frente" << endl;
                }
                else{
                    alpha = ajusta_angulo(alpha+180);
                    //v = - v_max;
                    v = v_delta_gol*fabs(alpha)/limiar_theta - v_max_gol;
                    w = kp*alpha/180 + kd*(alpha - last_phi);
                    limiar_theta = 90 + delta_limiar;
                    ////cout << "Trás" << endl;
                }

                //Cinemática
                //                if (fabs(alpha) <= limiar_theta){
                //                    w = kgol*v_max_gol*alpha/180;
                //                    v = -v_max_gol*fabs(alpha)/limiar_theta + v_max_gol;
                //                }
                //                else{
                //                    alpha = ajusta_angulo(alpha+180);
                //                    w = kgol*v_max_gol*alpha/180;
                //                    v = v_max_gol*fabs(alpha)/limiar_theta - v_max_gol;
                //                }
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
                if((fabs(robo->get_pos().x - pot_fields->get_meta_goalkeeper().x) < 4) && (fabs(robo->get_pos().y - pot_fields->get_meta_goalkeeper().y) < 5) &&(fabs(robot_angle) > 85) && (fabs(robot_angle) < 95)){
                    vels->first = 0;
                    vels->second = 0;
                }
                else if ((fabs(robo->get_pos().x - pot_fields->get_meta_goalkeeper().x) < 4) && (fabs(robo->get_pos().y - pot_fields->get_meta_goalkeeper().y) < 5)){
                    goalkeeper_orientation(robo,vels);
                    ////cout << "AdjustRobo" << endl;
                }

                ////cout << "Return2Goal" << endl;
            }
        }

        // Função para fazer o goleiro girar quando a bola está próxima a ele
        if ((robo->get_pos().y > ball_pos.y) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro_gol)){
            ////cout << "3" << endl;
            vels->first = vel_giro_gol;
            vels->second = -vel_giro_gol;
        }
        else if ((robo->get_pos().y < ball_pos.y) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro_gol)){
            ////cout << "4" << endl;
            vels->first = -vel_giro_gol;
            vels->second = vel_giro_gol;
        }
    }
    else if (centroid_atk.x < centroid_def.x){
        double tempo;
        double aux_position_y;
        tempo = (robot_pos.x - 4.5 - ball_pos.x)/ball_v.x;
        aux_position_y = ball_pos.y - tempo*ball_v.y;
        //previsao de bola

        if (ball_v.x > 0 && (aux_position_y > centroid_def.y-25) && (aux_position_y < centroid_def.y+25)){

            if (robot_angle > 0){
                v = -0.8*(aux_position_y-robot_pos.y)/tempo;
                if(v > 0.6){
                    v = 0.6;
                }
                else if(v < -0.6){
                    v = -0.6;
                }
                vels->first = v - w*l;
                vels->second = v + w*l;
            }
            else if (robot_angle < 0){
                v = 0.8*(aux_position_y-robot_pos.y)/tempo;
                if(v > 0.6){
                    v = 0.6;
                }
                else if(v < -0.6){
                    v = -0.6;
                }
                vels->first = v - w*l;
                vels->second = v + w*l;
            }
        }
        else{
            if (ball_pos.x > 90 && ball_pos.y > 45 && ball_pos.y < 95 && robot_pos.x > centroid_def.x-20){
                //FollowBall

                alpha = 90 - robot_angle;
                alpha = ajusta_angulo(alpha);


                //PID
                if (fabs(alpha) <= limiar_theta ){
                    w = 17*alpha/180 + kd*(alpha - last_phi);
                    limiar_theta = 90 - delta_limiar;
                }
                else{
                    alpha = ajusta_angulo(alpha+180);
                    w = 17*alpha/180 + kd*(alpha - last_phi);
                    limiar_theta = 90 + delta_limiar;
                }


                if (fabs(ball_v.y < 2))
                {
                    //ball_v.y = (ball_v.y / fabs(ball_v.y)) * 0.4;
                    if(fabs(robo->get_pos().y-ball_pos.y) < 3){
                        v = 0;
                    }
                    else if (robot_angle > 0 && ball_pos.y < robot_pos.y ){
                        v = 0.23; // Cinemática 0.005
                    }
                    else if (robot_angle > 0 && ball_pos.y > robot_pos.y){
                        v = -0.23; //PID 0.03
                    }
                    else if (robot_angle < 0 && ball_pos.y < robot_pos.y ){
                        v = -0.23;
                    }
                    else if (robot_angle < 0 && ball_pos.y > robot_pos.y ){
                        v = 0.23;
                    }
                    ////cout << "FollowBall" << endl;

                }
                if(v > 0.6){
                    v = 0.6;
                }
                else if(v < -0.6){
                    v = -0.6;
                }
                vels->first = v - w*l;
                vels->second = v + w*l;

            }
            else {
                //Return2Goal
                //v_max_gol = 0.5;
                theta = pot_fields->get_direction(robot_grid);
                alpha = theta - robot_angle;
                alpha = ajusta_angulo(alpha);

                //PID
                if (fabs(alpha) <= limiar_theta ){
                    //v = v_max;
                    v = -v_delta_gol*fabs(alpha)/limiar_theta + v_max_gol;
                    w = kp*alpha/180 + kd*(alpha - last_phi);
                    limiar_theta = 90 - delta_limiar;
                    ////cout << "Frente" << endl;
                }
                else{
                    alpha = ajusta_angulo(alpha+180);
                    //v = - v_max;
                    v = v_delta_gol*fabs(alpha)/limiar_theta - v_max_gol;
                    w = kp*alpha/180 + kd*(alpha - last_phi);
                    limiar_theta = 90 + delta_limiar;
                    ////cout << "Trás" << endl;
                }
                //                if (fabs(alpha) <= limiar_theta){
                //                    w = kgol*v_max_gol*alpha/180;
                //                    v = -v_max_gol*fabs(alpha)/limiar_theta + v_max_gol;
                //                }
                //                else{
                //                    alpha = ajusta_angulo(alpha+180);
                //                    w = kgol*v_max_gol*alpha/180;
                //                    v = v_max_gol*fabs(alpha)/limiar_theta - v_max_gol;
                //                }
                if (fabs(alpha) > 65 && fabs(alpha) < 115){
                    v = 0;
                }
                if(v > 0.6){
                    v = 0.6;
                }
                else if(v < -0.6){
                    v = -0.6;
                }
                vels->first = v - w*l;
                vels->second = v + w*l;
                //AdjustRobo
                if((fabs(robo->get_pos().x - pot_fields->get_meta_goalkeeper().x) < 4) && (fabs(robo->get_pos().y - pot_fields->get_meta_goalkeeper().y) < 5) && (fabs(robot_angle) > 85) && (fabs(robot_angle) < 95)){
                    vels->first = 0;
                    vels->second = 0;
                }
                else if ((fabs(robo->get_pos().x - pot_fields->get_meta_goalkeeper().x) < 4) && (fabs(robo->get_pos().y - pot_fields->get_meta_goalkeeper().y) < 5)){
                    goalkeeper_orientation(robo,vels);

                    ////cout << "AdjustRobo" << endl;
                }

                ////cout << "Return2Goal" << endl;
            }
        }

        // Função para fazer o goleiro girar quando a bola está próxima a ele
        if ((robo->get_pos().y > ball_pos.y) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro_gol)){
            ////cout << "3" << endl;
            vels->first = -vel_giro_gol;
            vels->second = vel_giro_gol;
        }
        else if ((robo->get_pos().y < ball_pos.y) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro_gol)){
            ////cout << "4" << endl;
            vels->first = vel_giro_gol;
            vels->second = -vel_giro_gol;
        }
    }

    ////cout << "esquerda " << vels->first << endl;
    ////cout << "direita " << vels->second << endl;
    ////cout << "angular " << w << endl;
    ////cout << "linear " << v << endl;
    last_phi = alpha;

}

void Mover::velocity_defender(Robot *robo, Game_functions *pot_fields, pair<float, float> *vels){
    // Calcula velocidades
    Point robot_grid = convert_C_to_G(robo->get_pos());
    Point2d eixo_x(1.0,0.0);
    Point2d robo_pos = robo->get_pos();

    double kp = robo->get_kp();
    double kd = robo->get_kd();
    double l = robo->get_l_size();

    double v,w,theta,alpha;
    pair<float, float> vel;

    //    if(euclidean_dist(robo_pos, pot_fields->get_meta()) > 30){
    //        v_max = 1;
    //        k = w_max/v_max;
    //    }
    //    else{
    //        v_max = 0.5;
    //        k = w_max/v_max;
    //    }

    theta = pot_fields->get_direction(robot_grid);
    alpha = theta - robo->get_angle();
    alpha = ajusta_angulo(alpha);


    //PID
    if (fabs(alpha) <= limiar_theta ){
        //v = v_max;
        v = -v_delta*fabs(alpha)/limiar_theta + v_max;
        w = kp*alpha/180 + kd*(alpha - last_phi);
        limiar_theta = 90 - delta_limiar;
        ////cout << "Frente" << endl;
    }
    else{
        alpha = ajusta_angulo(alpha+180);
        //v = - v_max;
        v = v_delta*fabs(alpha)/limiar_theta - v_max;
        w = kp*alpha/180 + kd*(alpha - last_phi);
        limiar_theta = 90 + delta_limiar;
        ////cout << "Trás" << endl;
    }

    last_phi = alpha;


    //Cinemática
    //    if (fabs(alpha) <= limiar_theta){
    //        w = k*v_max*alpha/180;
    //        v = -v_max*fabs(alpha)/limiar_theta + v_max;
    //    }
    //    else{
    //        alpha = ajusta_angulo(alpha+180);
    //        w = k*v_max*alpha/180;
    //        v = v_max*fabs(alpha)/limiar_theta - v_max;
    //    }
    //Desvio obstáculos
    if (fabs(alpha) > 70 && fabs(alpha) < 110){
        v = 0;
    }
    vels->first = v-w*l;
    vels->second = v+w*l;

    atk_orientation(robo, pot_fields, vels);
    rotate(robo, vels);
    atk_situation(robo,pot_fields,vels);
}

void Mover::velocity_defensive_midfielder(Robot *robo, Game_functions *pot_fields, pair<float, float> *vels){
    // Calcula velocidades
    Point robot_grid = convert_C_to_G(robo->get_pos());
    Point2d eixo_x(1.0,0.0);
    Point2d robo_pos = robo->get_pos();
    double v,w,theta,alpha;
    pair<float, float> vel;

    double kp = robo->get_kp();
    double kd = robo->get_kd();
    double l = robo->get_l_size();

    //    if(euclidean_dist(robo_pos, pot_fields->get_meta()) > 30){
    //        v_max = 1;
    //        k = w_max/v_max;
    //    }
    //    else{
    //        v_max = 0.5;
    //        k = w_max/v_max;
    //    }

    theta = pot_fields->get_direction(robot_grid);
    alpha = theta - robo->get_angle();
    alpha = ajusta_angulo(alpha);

    //PID
    if (fabs(alpha) <= limiar_theta ){
        //v = v_max;
        v = -v_delta*fabs(alpha)/limiar_theta + v_max;
        w = kp*alpha/180 + kd*(alpha - last_phi);
        limiar_theta = 90 - delta_limiar;
        ////cout << "Frente" << endl;
    }
    else{
        alpha = ajusta_angulo(alpha+180);
        //v = - v_max;
        v = v_delta*fabs(alpha)/limiar_theta - v_max;
        w = kp*alpha/180 + kd*(alpha - last_phi);
        limiar_theta = 90 + delta_limiar;
        ////cout << "Trás" << endl;
    }

    last_phi = alpha;


    //Cinemática
    //    if (fabs(alpha) <= limiar_theta){
    //        w = k*v_max*alpha/180;
    //        v = -v_max*fabs(alpha)/limiar_theta + v_max;
    //    }
    //    else{
    //        alpha = ajusta_angulo(alpha+180);
    //        w = k*v_max*alpha/180;
    //        v = v_max*fabs(alpha)/limiar_theta - v_max;
    //    }
    //Desvio obstáculos
    if (fabs(alpha) > 70 && fabs(alpha) < 110){
        v = 0;
    }
    vels->first = v-w*l;
    vels->second = v+w*l;
    ////cout << "Robo " << robo->get_pos() << endl;

    if (euclidean_dist(robo->get_pos(),ball_pos) > 20 && euclidean_dist(robo->get_pos(), pot_fields->get_meta()) < 10){
        goalkeeper_orientation(robo,vels);
    }

    // Volante gira quando está perto da bola
    if(euclidean_dist(robo->get_pos(),ball_pos) < dist_giro){
        if ((robo->get_pos().y > ball_pos.y) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro_gol)){
            //cout << "3" << endl;
            vels->first = -vel_giro_lado;
            vels->second = vel_giro_lado;
        }
        else if ((robo->get_pos().y < ball_pos.y) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro_gol)){
            //cout << "4" << endl;
            vels->first = vel_giro_lado;
            vels->second = -vel_giro_lado;
        }
    }

    atk_orientation(robo, pot_fields, vels);
    rotate(robo, vels);
    atk_situation(robo,pot_fields,vels);
}

void Mover::velocity_ofensive_midfielder(Robot *robo, Game_functions *pot_fields, pair<float, float> *vels){
    Point2d ball_v;

    double kp = robo->get_kp();
    double kd = robo->get_kd();
    double l = robo->get_l_size();

    ball_v.x = ball_vel.first / 100;
    ball_v.y = -ball_vel.second / 100;

    // Calcula velocidades
    Point robot_grid = convert_C_to_G(robo->get_pos());
    Point2d eixo_x(1.0,0.0);
    Point2d robo_pos = robo->get_pos();

    double v,w,theta,alpha;
    pair<float, float> vel;

    //    if(euclidean_dist(robo_pos, pot_fields->get_meta()) > 30){
    //        v_max = 1;
    //        k = w_max/v_max;
    //    }
    //    else{
    //        v_max = 0.5;
    //        k = w_max/v_max;
    //    }

    theta = pot_fields->get_direction(robot_grid);
    alpha = theta - robo->get_angle();
    alpha = ajusta_angulo(alpha);

    //PID
    if (fabs(alpha) <= limiar_theta ){
        //v = v_max;
        v = -v_delta*fabs(alpha)/limiar_theta + v_max;
        w = kp*alpha/180 + kd*(alpha - last_phi);
        limiar_theta = 90 - delta_limiar;
        ////cout << "Frente" << endl;
    }
    else{
        alpha = ajusta_angulo(alpha+180);
        //v = - v_max;
        v = v_delta*fabs(alpha)/limiar_theta - v_max;
        w = kp*alpha/180 + kd*(alpha - last_phi);
        limiar_theta = 90 + delta_limiar;
        ////cout << "Trás" << endl;
    }

    last_phi = alpha;


    //Cinemática
    //    if (fabs(alpha) <= limiar_theta){
    //        w = k*v_max*alpha/180;
    //        v = -v_max*fabs(alpha)/limiar_theta + v_max;
    //    }
    //    else{
    //        alpha = ajusta_angulo(alpha+180);
    //        w = k*v_max*alpha/180;
    //        v = v_max*fabs(alpha)/limiar_theta - v_max;
    //    }
    //Desvio obstáculos
    if (fabs(alpha) > 70 && fabs(alpha) < 110){
        v = 0;
    }
    vels->first = v - w*l;
    vels->second = v + w*l;

    //    if (euclidean_dist(robo->get_pos(),ball_pos) > 20 && euclidean_dist(robo->get_pos(), pot_fields->get_meta()) < 10){
    //        robot_orientation(robo, pot_fields, vels); // Se o robo estiver na meta, ele aponta para a bola
    //    }

    atk_orientation(robo, pot_fields, vels);
    rotate(robo, vels);
    atk_situation(robo,pot_fields,vels);

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

    /*  if (euclidean_dist(ball_pos,robo->get_pos()) < 10 && fabs(ang_ball_robot) < 15 && fabs(ang_atk_robot) < 15){
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

void Mover::velocity_striker(Robot *robo, Game_functions *pot_fields, pair<float, float> *vels){

    Point2d ball_v;
    ball_v.x = ball_vel.first / 100;
    ball_v.y = -ball_vel.second / 100;

    double kp = robo->get_kp();
    double kd = robo->get_kd();
    double l = robo->get_l_size();

    // Calcula velocidades
    Point robot_grid = convert_C_to_G(robo->get_pos());
    Point2d eixo_x(1.0,0.0);
    Point2d robo_pos = robo->get_pos();

    double v,w,theta,alpha;
    pair<float, float> vel;

    //    if(euclidean_dist(robo_pos, pot_fields->get_meta()) > 30){
    //        v_max = 1;
    //        k = w_max/v_max;
    //    }
    //    else{
    //        v_max = 0.5;
    //        k = w_max/v_max;
    //    }

    theta = pot_fields->get_direction(robot_grid);
    alpha = theta - robo->get_angle();
    alpha = ajusta_angulo(alpha);


    //PID
    if (fabs(alpha) <= limiar_theta ){
        //v = v_max;
        v = -v_delta*fabs(alpha)/limiar_theta + v_max;
        w = kp*alpha/180 + kd*(alpha - last_phi);
        limiar_theta = 90 - delta_limiar;
        ////cout << "Frente" << endl;
    }
    else{
        alpha = ajusta_angulo(alpha+180);
        //v = - v_max;
        v = v_delta*fabs(alpha)/limiar_theta - v_max;
        w = kp*alpha/180 + kd*(alpha - last_phi);
        limiar_theta = 90 + delta_limiar;
        ////cout << "Trás" << endl;
    }

    last_phi = alpha;


    //Cinemática
    //    if (fabs(alpha) <= limiar_theta){
    //        w = k*v_max*alpha/180;
    //        v = -v_max*fabs(alpha)/limiar_theta + v_max;
    //    }
    //    else{
    //        alpha = ajusta_angulo(alpha+180);
    //        w = k*v_max*alpha/180;
    //        v = v_max*fabs(alpha)/limiar_theta - v_max;
    //    }
    //Desvio obstáculos
    if (fabs(alpha) > 70 && fabs(alpha) < 110){
        v = 0;
    }
    vels->first = v-w*l;
    vels->second = v+w*l;

    atk_orientation(robo, pot_fields, vels);
    rotate(robo, vels);
    atk_situation(robo,pot_fields,vels);

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
    /*   if (euclidean_dist(ball_pos,robo->get_pos()) < 10 && fabs(ang_ball_robot) < 15 && fabs(ang_atk_robot) < 15){
        ////cout << 123 << endl;
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

    double kp = robo->get_kp();
    double kd = robo->get_kd();
    double l = robo->get_l_size();

    // Calcula velocidades
    Point robot_grid = convert_C_to_G(robo->get_pos());
    Point2d eixo_x(1.0,0.0);
    Point2d robo_pos = robo->get_pos();

    double v,w,theta,alpha;
    pair<float, float> vel;

    //    if(euclidean_dist(robo_pos, pot_fields->get_meta()) > 30){
    //        v_max = 1;
    //        k = w_max/v_max;
    //    }
    //    else{
    //        v_max = 0.75;
    //        k = w_max/v_max;
    //    }

    theta = pot_fields->get_direction(robot_grid);
    alpha = theta - robo->get_angle();
    alpha = ajusta_angulo(alpha);




    //PID
    if (fabs(alpha) <= limiar_theta ){
        //v = v_max;
        v = -v_delta*fabs(alpha)/limiar_theta + v_max;
        w = kp*alpha/180 + kd*(alpha - last_phi);
        limiar_theta = 90 - delta_limiar;
        ////cout << "Frente" << endl;
    }
    else{
        alpha = ajusta_angulo(alpha+180);
        //v = - v_max;
        v = v_delta*fabs(alpha)/limiar_theta - v_max;
        w = kp*alpha/180 + kd*(alpha - last_phi);
        limiar_theta = 90 + delta_limiar;
        ////cout << "Trás" << endl;
    }

    last_phi = alpha;


    //Cinemática

    //    if (fabs(alpha) <= limiar_theta){
    //        w = (k*v_max*alpha/180);
    //        v = -v_max*fabs(alpha)/limiar_theta + v_max;
    //    }
    //    else{
    //        alpha = ajusta_angulo(alpha+180);
    //        w = k*v_max*alpha/180;
    //        v = v_max*fabs(alpha)/limiar_theta - v_max;
    //    }

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

    double kp = robo->get_kp();
    double kd = robo->get_kd();
    double l = robo->get_l_size();

    for (int cont_vel = 0; cont_vel < 4; cont_vel ++){
        media_ball_v[cont_vel] = media_ball_v[cont_vel+1];
    }
    media_ball_v[4] = ball_v;
    ball_v = 0.35*media_ball_v[4]+0.25*media_ball_v[3]+0.2*media_ball_v[2]+0.15*media_ball_v[1]+0.05*media_ball_v[0];

    ball_v = ball_v*100;
    ////cout << "x " << ball_v.x << "    y " << ball_v.y << endl;

    // Calcula velocidades
    Point robot_grid = convert_C_to_G(robo->get_pos());
    Point2d eixo_x(1.0,0.0);
    Point2d robo_pos = robo->get_pos();

    double v,w,theta,alpha;
    pair<float, float> vel;

    if(euclidean_dist(robo_pos, pot_fields->get_meta()) > 30){
        v_max = 1;
        k = w_max/v_max;
        ////cout << "Aumentou " << endl;
    }
    else{
        v_max = 0.5;
        k = w_max/v_max;
    }

    //atk_situation(robo,pot_fields,vels);

    theta = pot_fields->get_direction(robot_grid);
    alpha = theta - robo->get_angle();
    alpha = ajusta_angulo(alpha);


    //PID
    if (fabs(alpha) <= limiar_theta ){
        //v = v_max;
        v = -v_delta*fabs(alpha)/limiar_theta + v_max;
        w = kp*alpha/180 + kd*(alpha - last_phi);
        limiar_theta = 90 - delta_limiar;
        ////cout << "Frente" << endl;
    }
    else{
        alpha = ajusta_angulo(alpha+180);
        //v = - v_max;
        v = v_delta*fabs(alpha)/limiar_theta - v_max;
        w = kp*alpha/180 + kd*(alpha - last_phi);
        limiar_theta = 90 + delta_limiar;
        ////cout << "Trás" << endl;
    }

    last_phi = alpha;


    //Cinemática

    //    if (fabs(alpha) <= limiar_theta){
    //        w = (k*v_max*alpha/180);
    //        //w = k*v_max*pow(alpha/180,2)*(alpha/fabs(alpha));
    //        v = -v_max*fabs(alpha)/limiar_theta + v_max;
    //    }
    //    else{
    //        alpha = ajusta_angulo(alpha+180);
    //        w = k*v_max*alpha/180;
    //        //w = k*v_max*pow(alpha/180,2)*(alpha/fabs(alpha));
    //        v = v_max*fabs(alpha)/limiar_theta - v_max;
    //    }

    //Desvio obstáculos
    if (fabs(alpha) > 70 && fabs(alpha) < 110){
        v = 0;
    }


    vels->first = v-w*l;
    vels->second = v+w*l;

    atk_orientation(robo, pot_fields, vels);
    rotate(robo, vels);
    atk_situation(robo,pot_fields,vels);


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

    //cout << "ang " << ang_ball_robot << endl;

    //ajusta angulos para menores que 180 e maiores que -180
    if (ang_ball_robot > 180) ang_ball_robot = ang_ball_robot - 360;
    else if (ang_ball_robot < -180) ang_ball_robot = ang_ball_robot + 360;
    ////cout << "Angulo bola atk: " << ang_ball_atk << endl;

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
        ////cout << "bola x " << ball_pos.
    aux.y = 0;x << "   y " << ball_pos.y << endl;
        ////cout << "meta x " << pot_fields->get_meta().x << "   y " << pot_fields->get_meta().y << endl;
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
    //cout << "Angular Calculada:" << w << endl;
    //cout << "Linear Calculada:" << v << endl;
    //cout << "Linear:" << mod_vel/100 << endl << endl << endl;
    //cout << "Angular:" << ang_vel << endl;*/



}

void Mover::velocity_test(Robot *robo, Game_functions *pot_fields, pair<float, float> *vels){
    Point2d ball_v;
    pair <double,double> vel;
    double ang_vel;
    ball_v.x = ball_vel.first / 100;
    ball_v.y = -ball_vel.second / 100;

    double kp = robo->get_kp();
    double kd = robo->get_kd();
    double l = robo->get_l_size();

    // Calcula velocidades
    Point robot_grid = convert_C_to_G(robo->get_pos());
    Point2d eixo_x(1.0,0.0);
    //Point2d robo_pos = robo->get_pos();

    double v,w,theta,alpha;
    theta = pot_fields->get_direction(robot_grid);
    alpha = theta - robo->get_angle();
    alpha = ajusta_angulo(alpha);

    v_max = 0.5;
    kp = 15.75;
    kd = 0.002;

    //    if(fabs(alpha) > 30){
    //        v_max = 0.5;
    //        kp = 15;
    //        kd = 0.002;
    //    }
    //    else{
    //        v_max = 0.6;
    //        kp = 15;
    //        kd = 0.001;
    //    }
    //    v_max = 0.6;
    //    kp = 7;
    //    kd = 0;
    ////cout << "valor de alpha" << alpha << endl;

    //        if (fabs(alpha) <= limiar_theta){
    //            w = (k*v_max*alpha/180);
    //            //w = k*v_max*pow(alpha/180,2)*(alpha/fabs(alpha));
    //            v = -v_max*fabs(alpha)/limiar_theta + v_max;
    //        }
    //        else{
    //            alpha = ajusta_angulo(alpha+180);
    //            w = k*v_max*alpha/180;
    //            //w = k*v_max*pow(alpha/180,2)*(alpha/fabs(alpha));
    //            v = v_max*fabs(alpha)/limiar_theta - v_max;
    //        }




    //     Navegação PID / Derivativo na entrada

    //    v = v_max;
    //    w = kp*alpha/180 + kd*(alpha - last_phi);

    alpha = ajusta_angulo(alpha+180);
    v = - v_max;
    w = kp*alpha/180 + kd*(alpha - last_phi);

    if (fabs(alpha) <= limiar_theta ){
        //v = v_max;
        v = -v_delta*fabs(alpha)/limiar_theta + v_max;
        w = kp*alpha/180 + kd*(alpha - last_phi);
        limiar_theta = 90 - delta_limiar;
        ////cout << "Frente" << endl;
    }
    else{
        alpha = ajusta_angulo(alpha+180);
        //v = - v_max;
        v = v_delta*fabs(alpha)/limiar_theta - v_max;
        w = kp*alpha/180 + kd*(alpha - last_phi) ;
        limiar_theta = 90 + delta_limiar;
        ////cout << "Trás" << endl;
    }

    last_phi = alpha;

    //    v = v_max;
    //    w = kp*alpha/180 - kd*(alpha - last_phi);
    //    limiar_theta = 90 + delta_limiar;


    // Controlador
    //    v = v_max;
    //    w = kp*alpha/180 + kd*(last_phi - robo->get_angle());

    //    //cout <<alpha<< endl;
    //        //cout <<selec_robot.r1.get_angle()<< endl;

    //    v = v_max;
    //    w = kp*alpha/180 + 0*(last_phi - robo->get_angle());

    //    last_phi = alpha;





    //Desvio obstáculosim
    if (fabs(alpha) > 80 && fabs(alpha) < 100){
        //w = w*3;
        v = 0;
    }

    vels->first = v-w*l;
    vels->second = v+w*l;


    //    //cout << "Vel Esquerda:" << vels->first << endl;
    //    //cout << "Vel Direita:" << vels->second << endl;

    ang_vel = robo->get_ang_vel();
    cout << "w(°): " << ang_vel << endl;
    ang_vel = ang_vel*3.141592/180;

    vel = robo->get_velocities();

    vel.first = vel.first*X_CONV_CONST;
    vel.second = vel.second*Y_CONV_CONST;

    //cout << "Angular:" << ang_vel << endl;

    double mod_vel = sqrt(pow(vel.first,2) + pow(vel.second,2));

    ////cout << "Linear Calculada:" << v << endl;
    //    //cout << "Linear:" << mod_vel/100 << endl << endl << endl;

    rotate(robo, vels);


}

void Mover::goalkeeper_orientation(Robot *r, pair<float, float> *vels){
    double alpha,w;
    double kp = r->get_kp();
    double kd = r->get_kd();
    kd = 0.005;
    kp = 20;
    double l = r->get_l_size();

    alpha = 90 - r->get_angle();
    alpha = ajusta_angulo(alpha);
    if (fabs(alpha) <= limiar_theta){
        //w = k*v_max*alpha/180;
        w = kp*alpha/180 + kd*(alpha - last_phi);
    }
    else{
        alpha = ajusta_angulo(alpha+180);
        //w = k*v_max*alpha/180;
        w = kp*alpha/180 + kd*(alpha - last_phi);
    }
    vels->first = -w*l;
    vels->second = w*l;
}

void Mover::robot_orientation(Robot *robo, Game_functions *pot_fields, pair<float, float> *vels){
    double alpha,w;
    double kp = robo->get_kp();
    double kd = robo->get_kd();
    double l = robo->get_l_size();

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
    ////cout << ball_pos.x << endl;
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
            ////cout << "aaaaaa" << endl;
        }
        else{
            alpha = ang_atk_robot;
            ////cout << "bbbbbb" << endl;
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

void Mover::atk_orientation(Robot *robo, Game_functions *pot_fields, pair<float, float> *vels){
    Point2d robo_pos = robo->get_pos();
    Point2d ball_v;
    Point2d eixo_x(1.0,0.0);
    double alpha,w;

    double kp = robo->get_kp();
    double kd = robo->get_kd();
    double l = robo->get_l_size();

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
    ////cout << ball_pos.x << endl;
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


    // Orienta o robo se tiver mal posicionado
    if((euclidean_dist(ball_pos,robo->get_pos()) < dist_giro) && fabs(ang_ball_robot) > 80 && euclidean_dist(ball_v,aux) < 0.1){
        //Funciona a partir do meio de campo para o ataque
        if(centroid_atk.x > centroid_def.x && ball_pos.x > 90){
            alpha = ang_ball_robot;
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
        else if (centroid_atk.x < centroid_def.x && ball_pos.x < 90){
            alpha = ang_ball_robot;
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
        else{
            //Tratar aqui
        }
    }

    /*
    // Função para fazer o robô girar no ataque
    if (centroid_atk.x > ball_pos.x){
        //if ((ball_pos.y > centroid_atk.y) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro) && fabs(prediction_robot) >= 30 && euclidean_dist(ball_v,aux) < 0.1 && fabs(ang_ball_robot) > 50){
        if ((ball_pos.y > centroid_atk.y) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro) && fabs(ang_ball_robot) > 50){
            vels->first = -vel_giro_atk;
            vels->second = vel_giro_atk;
        }
        //else if ((ball_pos.y < centroid_atk.y) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro) && fabs(prediction_robot) >= 30 && euclidean_dist(ball_v,aux) < 0.1 && fabs(ang_ball_robot) > 50){
        else if ((ball_pos.y < centroid_atk.y) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro) && fabs(ang_ball_robot) > 50){
            vels->first = vel_giro_atk;
            vels->second = -vel_giro_atk;
        }
    }
    else{
        //if ((ball_pos.y > centroid_atk.y) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro) && fabs(prediction_robot) >= 30 && euclidean_dist(ball_v,aux) < 0.1 && fabs(ang_ball_robot) > 50){
        if ((ball_pos.y > centroid_atk.y) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro) && fabs(ang_ball_robot) > 50){
            vels->first = vel_giro_atk;
            vels->second = -vel_giro_atk;
        }
        //else if ((ball_pos.y < centroid_atk.y) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro) && fabs(prediction_robot) >= 30 && euclidean_dist(ball_v,aux) < 0.1 && fabs(ang_ball_robot) > 50){
        else if ((ball_pos.y < centroid_atk.y) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro) && fabs(ang_ball_robot) > 50){
            vels->first = -vel_giro_atk;
            vels->second = vel_giro_atk;
        }
    }*/
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
    ////cout << ball_pos.x << endl;
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
    /*if (euclidean_dist(ball_pos,robo->get_pos()) < 10 && fabs(ang_ball_robot) < 30 && fabs(ang_atk_robot) < 30){
        v_max = 1.6;
        k = (w_max/v_max);
        //cout << "Atk-situation " << endl;
    }
    else{
        v_max = 0.6;
        k = (w_max/v_max);
        ////cout << "saiu mover-striker " << endl;
        ////cout << "Angulo bola robo: " << ang_ball_robot << " - Angulo ataque robo: " << ang_atk_robot << endl;
    }*/
    if (centroid_def.x < centroid_atk.x) {
        if (robo_pos.x <= ball_pos.x && fabs(ang_ball_robot) < 20 && fabs(ang_atk_robot) < 20 && euclidean_dist(ball_pos,robo->get_pos()) < 10 && (ball_pos.y > (centroid_def.y - 40)) && (ball_pos.y < (centroid_def.y + 40))){
            if (fabs(robo->get_angle()) < 90){
                vels->first = v_atk;
                vels->second = v_atk;
            }
            else{
                vels->first = -v_atk;
                vels->second = -v_atk;
            }
            //            //cout << "Ataque Situation 1" << endl;
        }
        else{

        }
    }
    else if(centroid_atk.x < centroid_def.x){
        if (robo_pos.x >= ball_pos.x && fabs(ang_ball_robot) < 20 && fabs(ang_atk_robot) < 20 && euclidean_dist(ball_pos,robo->get_pos()) < 10 && (ball_pos.y > (centroid_def.y - 40)) && (ball_pos.y < (centroid_def.y + 40))){
            if (fabs(robo->get_angle()) < 90){
                vels->first = -v_atk;
                vels->second = -v_atk;
            }
            else{
                vels->first = v_atk;
                vels->second = v_atk;
            }
            //            //cout << "Ataque Situation 2" << endl;
        }
        else{

        }
    }


}

void Mover::atk_situation_inv(Robot *robo, Game_functions *pot_fields, pair<float, float> *vels){
    Point2d virtual_atk = centroid_def;
    Point2d virtual_def = centroid_atk;
    Point2d robo_pos = robo->get_pos();
    Point2d eixo_x(1.0,0.0);

    //Cálculo das variáveis utilizadas para aumentar a velocidade do robô

    //Corrige Posicionamento
    ball_pos.y = -ball_pos.y;
    robo_pos.y = -robo_pos.y;
    virtual_atk.y=-virtual_atk.y;

    //Calcula angulo entre robo e bola
    Point2d vec_ball_robot = ball_pos-robo_pos;
    double ang_vec_ball_eixox = angle_two_points(vec_ball_robot,eixo_x);
    ////cout << ball_pos.x << endl;
    //Corrige o angulo
    if (vec_ball_robot.y < 0)
        ang_vec_ball_eixox = -ang_vec_ball_eixox;

    double ang_ball_robot = ang_vec_ball_eixox - robo->get_angle();


    //Calcula angulo entre robo e gol adversario
    Point2d vec_atk_robot = virtual_atk-robo_pos;
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
    virtual_atk.y=-virtual_atk.y;



    //Aumenta a velocidade do robô em situações claras de gol
    /*if (euclidean_dist(ball_pos,robo->get_pos()) < 10 && fabs(ang_ball_robot) < 30 && fabs(ang_atk_robot) < 30){
        v_max = 1.6;
        k = (w_max/v_max);
        //cout << "Atk-situation " << endl;
    }
    else{
        v_max = 0.6;
        k = (w_max/v_max);
        ////cout << "saiu mover-striker " << endl;
        ////cout << "Angulo bola robo: " << ang_ball_robot << " - Angulo ataque robo: " << ang_atk_robot << endl;
    }*/
    if (virtual_def.x < virtual_atk.x) {
        if (robo_pos.x <= ball_pos.x && fabs(ang_ball_robot) < 30 && fabs(ang_atk_robot) < 30 && euclidean_dist(ball_pos,robo->get_pos()) < 10 && (ball_pos.y > (virtual_def.y - 40)) && (ball_pos.y < (virtual_def.y + 40))){
            if (fabs(robo->get_angle()) < 90){
                vels->first = v_atk;
                vels->second = v_atk;
            }
            else{
                vels->first = -v_atk;
                vels->second = -v_atk;
            }
            //cout << "Ataque Situation 3" << endl;
        }
        else{

        }
    }
    else if(virtual_atk.x < virtual_def.x){
        if (robo_pos.x >= ball_pos.x && fabs(ang_ball_robot) < 30 && fabs(ang_atk_robot) < 30 && euclidean_dist(ball_pos,robo->get_pos()) < 10 && (ball_pos.y > (virtual_def.y - 40)) && (ball_pos.y < (virtual_def.y + 40))){
            if (fabs(robo->get_angle()) < 90){
                vels->first = -v_atk;
                vels->second = -v_atk;
            }
            else{
                vels->first = v_atk;
                vels->second = v_atk;
            }
            //cout << "Ataque Situation 4" << endl;
        }
        else{

        }
    }

}

void Mover::atk_situation_any_point(Robot *robo, Game_functions *pot_fields, pair<float, float> *vels){
    Point2d robo_pos = robo->get_pos();
    Point2d eixo_x(1.0,0.0);
    double ang_ball_robot = robo->get_angle()-vector_angle(robo->get_pos(),ball_pos);
    ang_ball_robot = ajusta_angulo(ang_ball_robot);

    if (centroid_def.x < centroid_atk.x) {
        if (euclidean_dist(ball_pos,robo->get_pos()) < 10){
            if (fabs(robo->get_angle()) < 90 &&  fabs(ang_ball_robot) < 30){
                vels->first = v_atk;
                vels->second = v_atk;
            }
            else if(fabs(ang_ball_robot) > 150){
                vels->first = -v_atk;
                vels->second = -v_atk;
            }
            //cout << "Ataque Situation any point" << endl;
        }
    }
    else if(centroid_atk.x < centroid_def.x){
        if (euclidean_dist(ball_pos,robo->get_pos()) < 10){
            if (fabs(robo->get_angle()) < 90 && fabs(ang_ball_robot) > 150){
                vels->first = -v_atk;
                vels->second = -v_atk;
            }
            else if(fabs(ang_ball_robot) < 30){
                vels->first = v_atk;
                vels->second = v_atk;
            }
            //cout << "Ataque Situation any point" << endl;
        }
    }
}

void Mover::rotate(Robot *robo, pair<float, float> *vels){
    // Função para fazer o robô girar nos cantos
    if (centroid_atk.x > ball_pos.x){
        if ((ball_pos.y > centroid_atk.y+60) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro) ){
            ////cout << "3" << endl;
            vels->first = -vel_giro_lado;
            vels->second = vel_giro_lado;
        }
        else if ((ball_pos.y < centroid_atk.y-60) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro)){
            ////cout << "4" << endl;
            vels->first = vel_giro_lado;
            vels->second = -vel_giro_lado;
        }
    }
    else{
        if ((ball_pos.y > centroid_atk.y+60) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro)){
            vels->first = vel_giro_lado;
            vels->second = -vel_giro_lado;
        }
        else if ((ball_pos.y < centroid_atk.y-60) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro)){
            vels->first = -vel_giro_lado;
            vels->second = vel_giro_lado;
        }
    }

    // Função para fazer o robô girar na linha de fundo de ataque
    if (centroid_atk.x > ball_pos.x){
        if ((ball_pos.y > centroid_atk.y+40) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro) && fabs(ball_pos.x - centroid_atk.x) < 15){
            ////cout << "3" << endl;
            vels->first = -vel_giro_lado;
            vels->second = vel_giro_lado;
            ////cout << "foi" << endl;
        }
        else if ((ball_pos.y < centroid_atk.y-40) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro && fabs(ball_pos.x - centroid_atk.x) < 15)){
            ////cout << "4" << endl;
            vels->first = vel_giro_lado;
            vels->second = -vel_giro_lado;
            ////cout << "foi" << endl;
        }
    }
    else{
        if ((ball_pos.y > centroid_atk.y+40) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro && fabs(ball_pos.x - centroid_atk.x) < 15)){
            vels->first = vel_giro_lado;
            vels->second = -vel_giro_lado;
            ////cout << "foi" << endl;
        }
        else if ((ball_pos.y < centroid_atk.y-40) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro && fabs(ball_pos.x - centroid_atk.x) < 15)){
            vels->first = -vel_giro_lado;
            vels->second = vel_giro_lado;
            ////cout << "foi" << endl;
        }
    }
    // Função para fazer o robô girar na linha de fundo de defesa
    if (centroid_atk.x > ball_pos.x){
        if ((ball_pos.y > centroid_def.y+35) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro) && fabs(ball_pos.x - centroid_def.x) < 15){
            ////cout << "3" << endl;
            vels->first = -vel_giro_lado;
            vels->second = vel_giro_lado;
            ////cout << "foi" << endl;
        }
        else if ((ball_pos.y < centroid_def.y-35) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro && fabs(ball_pos.x - centroid_def.x) < 15)){
            ////cout << "4" << endl;
            vels->first = vel_giro_lado;
            vels->second = -vel_giro_lado;
            ////cout << "foi" << endl;
        }
    }
    else{
        if ((ball_pos.y > centroid_def.y+35) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro && fabs(ball_pos.x - centroid_def.x) < 15)){
            vels->first = vel_giro_lado;
            vels->second = -vel_giro_lado;
            ////cout << "foi" << endl;
        }
        else if ((ball_pos.y < centroid_def.y-35) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro && fabs(ball_pos.x - centroid_def.x) < 15)){
            vels->first = -vel_giro_lado;
            vels->second = vel_giro_lado;
            ////cout << "foi" << endl;
        }
    }
}

void Mover::rotate_inv(Robot *robo, pair<float, float> *vels){
    // Função para fazer o robô girar nos cantos
    Point2d virtual_atk = centroid_def;
    Point2d virtual_def = centroid_atk;

    if (virtual_atk.x > ball_pos.x){
        if ((ball_pos.y > virtual_atk.y+60) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro) ){
            ////cout << "3" << endl;
            vels->first = -vel_giro_lado;
            vels->second = vel_giro_lado;
        }
        else if ((ball_pos.y < virtual_atk.y-60) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro)){
            ////cout << "4" << endl;
            vels->first = vel_giro_lado;
            vels->second = -vel_giro_lado;
        }
    }
    else{
        if ((ball_pos.y > virtual_atk.y+60) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro)){
            vels->first = vel_giro_lado;
            vels->second = -vel_giro_lado;
        }
        else if ((ball_pos.y < virtual_atk.y-60) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro)){
            vels->first = -vel_giro_lado;
            vels->second = vel_giro_lado;
        }
    }

    // Função para fazer o robô girar na linha de fundo de ataque
    if (virtual_atk.x > ball_pos.x){
        if ((ball_pos.y > virtual_atk.y+40) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro) && fabs(ball_pos.x - virtual_atk.x) < 15){
            ////cout << "3" << endl;
            vels->first = -vel_giro_lado;
            vels->second = vel_giro_lado;
            ////cout << "foi" << endl;
        }
        else if ((ball_pos.y < virtual_atk.y-40) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro && fabs(ball_pos.x - virtual_atk.x) < 15)){
            ////cout << "4" << endl;
            vels->first = vel_giro_lado;
            vels->second = -vel_giro_lado;
            ////cout << "foi" << endl;
        }
    }
    else{
        if ((ball_pos.y > virtual_atk.y+40) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro && fabs(ball_pos.x - virtual_atk.x) < 15)){
            vels->first = vel_giro_lado;
            vels->second = -vel_giro_lado;
            ////cout << "foi" << endl;
        }
        else if ((ball_pos.y < virtual_atk.y-40) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro && fabs(ball_pos.x - virtual_atk.x) < 15)){
            vels->first = -vel_giro_lado;
            vels->second = vel_giro_lado;
            ////cout << "foi" << endl;
        }
    }
    // Função para fazer o robô girar na linha de fundo de defesa
    if (virtual_atk.x > ball_pos.x){
        if ((ball_pos.y > virtual_def.y+35) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro) && fabs(ball_pos.x - virtual_def.x) < 15){
            ////cout << "3" << endl;
            vels->first = -vel_giro_lado;
            vels->second = vel_giro_lado;
            ////cout << "foi" << endl;
        }
        else if ((ball_pos.y < virtual_def.y-35) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro && fabs(ball_pos.x - virtual_def.x) < 15)){
            ////cout << "4" << endl;
            vels->first = vel_giro_lado;
            vels->second = -vel_giro_lado;
            ////cout << "foi" << endl;
        }
    }
    else{
        if ((ball_pos.y > virtual_def.y+35) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro && fabs(ball_pos.x - virtual_def.x) < 15)){
            vels->first = vel_giro_lado;
            vels->second = -vel_giro_lado;
            ////cout << "foi" << endl;
        }
        else if ((ball_pos.y < virtual_def.y-35) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro && fabs(ball_pos.x - virtual_def.x) < 15)){
            vels->first = -vel_giro_lado;
            vels->second = vel_giro_lado;
            ////cout << "foi" << endl;
        }
    }

}

void Mover:: kick_rotate(Robot *robo, pair<float, float> *vels){
    // Função para fazer o robô girar nos cantos
    Point2d robo_pos = robo->get_pos();

    if (centroid_atk.x > ball_pos.x){
        if ((ball_pos.y > robo_pos.y) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro) ){
            ////cout << "3" << endl;
            vels->first = -vel_giro_lado;
            vels->second = vel_giro_lado;
        }
        else if ((ball_pos.y < robo_pos.y) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro)){
            ////cout << "4" << endl;
            vels->first = vel_giro_lado;
            vels->second = -vel_giro_lado;
        }
    }
    else{
        if ((ball_pos.y > robo_pos.y) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro)){
            vels->first = vel_giro_lado;
            vels->second = -vel_giro_lado;
        }
        else if ((ball_pos.y < robo_pos.y) && (euclidean_dist(ball_pos,robo->get_pos()) < dist_giro)){
            vels->first = -vel_giro_lado;
            vels->second = vel_giro_lado;
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
    ////cout << "atual " << "x " << ball_pos.x << "   y " << ball_pos.y << endl;
    ////cout << "proxima " << "x " << next_ball_pos.x << "   y " << next_ball_pos.y << endl;
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
    ////cout << "i.x = " << i.x << " i.y = " << i.y << endl;
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

void Mover::velocity_killer_cpu(Robot *robo, Game_functions *pot_fields, pair<float, float> *vels)
{
    Point2d ball_v;
    pair <double,double> vel;
    double ang_vel;
    Point robot_grid = convert_C_to_G(robo->get_pos());
    ball_v.x = ball_vel.first / 100;
    ball_v.y = -ball_vel.second / 100;

//    cout << "Ball_pos X: " << ball_pos.x << endl;
 //   cout << "Ball_pos Y: " << ball_pos.y << endl;

    double kp = robo->get_kp();
    double kd = robo->get_kd();
    double l = robo->get_l_size();

    //Troca de direcoes
    Point2d obst_prox;
    Point2d wall_1 = robo->get_pos();
    Point2d wall_2 = robo->get_pos();
    Point2d wall_3 = robo->get_pos();
    Point2d wall_4 = robo->get_pos();

    wall_1.x = 160;
    wall_2.x = 10;
    wall_3.y = 0;
    wall_4.y = 130;

    double d0 = euclidean_dist(robo->get_pos(), enemy_pos[0]);
    double d1 = euclidean_dist(robo->get_pos(), enemy_pos[1]);
    double d2 = euclidean_dist(robo->get_pos(), enemy_pos[2]);
    double d3 = euclidean_dist(robo->get_pos(), selec_robot.r1.get_pos()); //Gandalf
    double d4 = euclidean_dist(robo->get_pos(), selec_robot.r2.get_pos()); // Presto
    double d5 = euclidean_dist(robo->get_pos(), selec_robot.r3.get_pos()); //Leona
    double d6 = euclidean_dist(robo->get_pos(), wall_1);
    double d7 = euclidean_dist(robo->get_pos(), wall_2);
    double d8 = euclidean_dist(robo->get_pos(), wall_3);
    double d9 = euclidean_dist(robo->get_pos(), wall_4);
    double distancia_permitida = 15;
    double distancia_obst;

    // Distancia com o mesmo time
    if (robo->get_pos().x == selec_robot.r1.get_pos().x && robo->get_pos().y == selec_robot.r1.get_pos().y ){
        d3 = 1000;
    }

    if (robo->get_pos().x == selec_robot.r2.get_pos().x && robo->get_pos().y == selec_robot.r2.get_pos().y ){
        d4 = 1000;
    }

    if (robo->get_pos().x == selec_robot.r3.get_pos().x && robo->get_pos().y == selec_robot.r3.get_pos().y ){
        d5 = 1000;
    }


    // Distancia com os adversarios
    if (d0 <= d1 && d0 <= d2 && d0 <= d3 && d0 <= d4 && d0 <= d5 && d0 <= d6 && d0 <= d7 && d0 <= d8 && d0 <= d9 && d0 > 0){
        obst_prox = enemy_pos[0];
    }
    if (d1 <= d0 && d1 <= d2 && d1 <= d3 && d1 <= d4 && d1 <= d5 && d1 <= d6 && d1 <= d7 && d1 <= d8 && d1 <= d9 && d1 > 0){
        obst_prox = enemy_pos[1];
    }
    if (d2 <= d0 && d2 <= d1 && d2 <= d3 && d2 <= d4 && d2 <= d5 && d2 <= d6 && d2 <= d7 && d2 <= d8 && d2 <= d9 && d2 > 0){
        obst_prox = enemy_pos[2];
    }

    if (d3 <= d0 && d3 <= d1 && d3 <= d2 && d3 <= d4 && d3 <= d5 && d3 <= d6 && d3 <= d7 && d3 <= d8 && d3 <= d9 && d3 > 0){
        obst_prox = selec_robot.r1.get_pos();
    }
    if (d4 <= d0 && d4 <= d1 && d4 <= d2 && d4 <= d3 && d4 <= d5 && d4 <= d6 && d4 <= d7 && d4 <= d8 && d4 <= d9 && d4 > 0){
        obst_prox = selec_robot.r2.get_pos();
    }
    if (d5 <= d0 && d5 <= d1 && d5 <= d2 && d5 <= d3 && d5 <= d4 && d5 <= d6 && d5 <= d7 && d5 <= d8 && d5 <= d9 && d5 > 0){
        obst_prox = selec_robot.r3.get_pos();
    }

    // Distancia com as barreiras
    if (d6 <= d0 && d6 <= d1 && d6 <= d2 && d6 <= d3 && d6 <= d4 && d6 <= d5 && d6 <= d7 && d6 <= d8 && d6 <= d9 && d6 > 0){
        obst_prox = wall_1;
    }
    if (d7 <= d0 && d7 <= d1 && d7 <= d2 && d7 <= d3 && d7 <= d4 && d7 <= d5 && d7 <= d6 && d7 <= d8 && d7 <= d9 && d7 > 0){
        obst_prox = wall_2;
    }
    if (d8 <= d0 && d8 <= d1 && d8 <= d2 && d8 <= d3 && d8 <= d4 && d8 <= d5 && d8 <= d6 && d8 <= d7 && d8 <= d9 && d8 > 0){
        obst_prox = wall_3;
    }
    if (d9 <= d0 && d9 <= d1 && d9 <= d2 && d9 <= d3 && d9 <= d4 && d9 <= d5 && d9 <= d6 && d9 <= d7 && d9 <= d8 && d9 > 0){
        obst_prox = wall_4;
    }
    distancia_obst = euclidean_dist(robo->get_pos(), obst_prox);

    //cout << "robo x " << robo->get_pos().x << " robo y " << robo->get_pos().y << endl;
    //cout << "obj x " << obst_prox.x << " obj y " << obst_prox.y << endl;

    double angle = vector_angle(robo->get_pos(),obst_prox);
    double another_ang = fabs(robo->get_angle() - angle);
    if(another_ang > 180){
        another_ang -= 360;
    }
    if(another_ang < -180)
    {
        another_ang += 360;
    }

    //Restricao de posicao
    if (distancia_obst < distancia_permitida){
        if(killer_direction && distancia_obst < distancia_permitida && fabs(another_ang) < 40){
            if (cont_killer_obst > 5){
                killer_direction = false;
                cont_killer_obst = 0;
                cont_killer_tempo = 0;
            }
            else{
                cont_killer_obst = cont_killer_obst + 1;
            }
        }
        else if(!killer_direction && distancia_obst < distancia_permitida && fabs(another_ang) > 180 - 40){
            if (cont_killer_obst > 5){
                killer_direction = true;
                cont_killer_obst = 0;
                cont_killer_tempo = 0;
            }
            else{
                cont_killer_obst = cont_killer_obst + 1;
            }
        }
    }
    else{
        cont_killer_obst = cont_killer_obst - 1;
        if (cont_killer_obst < 0){
            cont_killer_obst = 0;
        }
    }

    //Restricao de tempo
    if(fabs(robo->get_pos().x - last_killer.x) < 0.05 && fabs(robo->get_pos().y - last_killer.y) < 0.05){
        cont_killer_tempo = cont_killer_tempo + 1;
        if (cont_killer_tempo > 15){
            if(killer_direction){
                killer_direction = false;
            }
            else if(!killer_direction){
                killer_direction = true;
            }

            cont_killer_tempo = 0;
            cont_killer_obst = 0;
            //cout << "Trocou direcao" << endl;
        }
    }
    else{
        cont_killer_tempo = cont_killer_tempo - 1;
        if (cont_killer_tempo < 0){
            cont_killer_tempo = 0;
        }
    }
    //    cout << "COntador tempo " << cont_killer_tempo << endl;
    last_killer = robo->get_pos();

    /*if(killer_direction && distancia_obst < distancia_permitida && fabs(another_ang) < 40)
    {
        killer_direction = false;
    }
    else if(!killer_direction && distancia_obst < distancia_permitida && fabs(another_ang) > 180 - 40)
    {
        killer_direction = true;
    } */


    //    cout << "direc: " << killer_direction << endl;
    //    cout << "distancia obstaculo: " << distancia_obst << endl;
    //    cout << "Angulo obstaculo " << another_ang << endl;

    // Fim da troca


    // Calcula velocidades

    double v,w,theta,alpha;
    theta = pot_fields->get_direction_CPU() * 180 / M_PI;  // Angulo do CPU
    Point2d robo_pos;
    robo_pos = robo->get_pos();

        if(pot_fields->Get_atk_situation_state() == true){
            theta = vector_angle(robo_pos,ball_pos);
       //     cout << "Entrou" << endl;
        }else{
                //cout << "Nao entrou" << endl;
        }

    //    cout << endl << "tetinhaa: "<< theta << endl;
    //    if (((ball_pos.x < 25 || ball_pos.x > 145) && (ball_pos.y < 35 || ball_pos.y > 100)) || ball_pos.y < 15  || ball_pos.y > 115){ // Angulo do CPH
    //        theta = pot_fields->get_direction(robot_grid);
    //    }
    //    else{
    //    }

    double def_area_x = def_area[0].x*X_CONV_CONST;
    double def_area_y1 = def_area[1].y*Y_CONV_CONST;
    double def_area_y2 = def_area[6].y*Y_CONV_CONST;

    //CPH
    if (centroid_atk.x > ball_pos.x){ //Comentar tudo para ATK vs DEF
        if(ball_pos.x < def_area_x && ball_pos.y < def_area_y1 && ball_pos.y > def_area_y2)
        cout << "Avoid" << endl;
            //theta = pot_fields->get_direction(robot_grid);
        //        else
        //            if (ball_pos.x < 45 || (ball_pos.x > 145 && (ball_pos.y < 35 || ball_pos.y > 100)) || ball_pos.y < 15  || ball_pos.y > 115)
        //                theta = pot_fields->get_direction(robot_grid);
    }
    else{
        if(ball_pos.x > def_area_x && ball_pos.y < def_area_y1 && ball_pos.y > def_area_y2)
        //    theta = pot_fields->get_direction(robot_grid);
        cout << "Avoid" << endl;
        //        else{
        //            if (ball_pos.x > 125 || (ball_pos.x < 25  && (ball_pos.y < 35 || ball_pos.y > 100)) || ball_pos.y < 15  || ball_pos.y > 115)
        //                theta = pot_fields->get_direction(robot_grid);
        //        }
    }

    //Teste ataque

//    if (centroid_atk.x > centroid_def.x){
//        if(abs(ball_pos.y-centroid_def.y) < 20 && ((centroid_atk.x - ball_pos.x) < 26) && robo_pos.x < ball_pos.x - 7)
//            theta = pot_fields->get_direction(robot_grid);
//    }
//    else{
//        if(abs(ball_pos.y-centroid_def.y) < 20 && ((ball_pos.x - centroid_atk.x) < 26) && robo_pos.x > ball_pos.x + 7)
//            theta = pot_fields->get_direction(robot_grid);
//    }


    theta = ajusta_angulo((theta));
    alpha = theta - robo->get_angle();
    alpha = ajusta_angulo(alpha);



    //cout << "alp " << alpha << endl;



    // Navegação com cinemática

    //    if (fabs(alpha) <= limiar_theta){
    //        w = (k*v_max*alpha/180);
    //        //w = k*v_max*pow(alpha/180,2)*(alpha/fabs(alpha));
    //        v = -v_max*fabs(alpha)/limiar_theta + v_max;
    //        limiar_theta = 90 + delta_limiar;
    //        //cout << "Tras" << endl;
    //    }
    //    else{
    //        alpha = ajusta_angulo(alpha+180);
    //        w = k*v_max*alpha/180;
    //        //w = k*v_max*pow(alpha/180,2)*(alpha/fabs(alpha));
    //        v = v_max*fabs(alpha)/limiar_theta - v_max;
    //        limiar_theta = 90 - delta_limiar;
    //        //cout << "Frente" << endl;
    //    }


    //PID
    /*if (fabs(alpha) <= limiar_theta ){
        v = -v_delta*fabs(alpha)/limiar_theta + v_max;
        w = kp*alpha/180  + kd*(alpha-last_phi);
        limiar_theta = 90 - delta_limiar;
    }
    else{
        alpha = ajusta_angulo(alpha+180);
        v = v_delta*fabs(alpha)/limiar_theta - v_max;
        w = kp*alpha/180 + kd*(alpha-last_phi);
        limiar_theta = 90 + delta_limiar;
    }*/

    /*if(killer_direction && fabs(alpha) > 180 - 25){
            killer_direction = false;
        }
        else if(!killer_direction && fabs(alpha) < 25)
        {
            killer_direction = true;
        }*/
    double diff_angle;
    //PID Unidirection
    //alpha = ajusta_angulo(vector_angle(robo_pos, ball_pos) - robo->get_angle());

    if (euclidean_dist(robo_pos, ball_pos) >= 25){
        if (killer_direction){
            v = -v_delta*fabs(alpha)/limiar_theta + v_max;
            //w = kp*alpha/180 + kd*(robo->get_angle() - last_angle);
            //w = kp*alpha/180 + kd*(alpha-last_phi);
            w = kp*alpha/180 + kd*(alpha-last_phi);
            //            w = 7*alpha/180  + 0.0015*(theta-last_theta_control) + 0*(alpha - last_phi);
            limiar_theta = 90 - delta_limiar;
            //cout << "1" << endl;
        }
        else{
            alpha = ajusta_angulo(alpha+180);
            v = v_delta*fabs(alpha)/limiar_theta - v_max;
            w = kp*alpha/180 + kd*(alpha-last_phi);
            //            w = 7*alpha/180 + 0.0015*(theta-last_theta_control) + 0*(alpha - last_phi);
            limiar_theta = 90 + delta_limiar;
            // cout << "2" << endl;
        }
    }
    else if (euclidean_dist(robo_pos, ball_pos) < 25){
        /*diff_angle = robo->get_angle() - vector_angle(ball_pos,robo_pos);
        diff_angle = ajusta_angulo(diff_angle);
        if((fabs(diff_angle < 60) || fabs(diff_angle > 120)) && ((centroid_def.x < centroid_atk.x && robo_pos.x < ball_pos.x) || (centroid_def.x > centroid_atk.x && robo_pos.x > ball_pos.x)))
        {
            if (fabs(alpha) <= limiar_theta ){
                v = -v_delta*fabs(alpha)/limiar_theta + v_max;
                w = 4*alpha/180 + kd*(alpha-last_phi) + 2.5*diff_angle/180;;
                //            w = 7*alpha/180  + 0.0015*(theta-last_theta_control) + 0*(alpha - last_phi);
                limiar_theta = 90 - delta_limiar;
                //cout << "3" << endl;
            }
            else{
                alpha = ajusta_angulo(alpha+180);
                v = v_delta*fabs(alpha)/limiar_theta - v_max;
                w = 4*alpha/180 + kd*(alpha-last_phi) + 2.5*diff_angle/180;;
                //            w = 7*alpha/180  + 0.0015*(theta-last_theta_control) + 0*(alpha - last_phi);
                limiar_theta = 90 + delta_limiar;
                //cout << "4" << endl;
            }
        }
        else
        {*/
            //alpha = ajusta_angulo(robo->get_angle() - vector_angle(ball_pos, robo_pos));
            if (fabs(alpha) <= limiar_theta ){
                v = -v_delta*fabs(alpha)/limiar_theta + v_max;
                w = kp*alpha/180 + kd*(alpha-last_phi);
                //            w = 7*alpha/180  + 0.0015*(theta-last_theta_control) + 0*(alpha - last_phi);
                limiar_theta = 90 - delta_limiar;
                //cout << "3" << endl;
            }
            else{
                alpha = ajusta_angulo(alpha+180);
                v = v_delta*fabs(alpha)/limiar_theta - v_max;
                w = kp*alpha/180 + kd*(alpha-last_phi);
                //            w = 7*alpha/180  + 0.0015*(theta-last_theta_control) + 0*(alpha - last_phi);
                limiar_theta = 90 + delta_limiar;
                //cout << "4" << endl;
            }
        //}
    }




    //    v = -v_delta*fabs(alpha)/limiar_theta + v_max;
    //    w = kp*alpha/180 + kd*(alpha-last_phi);


    // //cout << "V: " << v << endl;

    //Desvio obstáculos
    /*if (fabs(alpha) > 75 && fabs(alpha) < 105 && euclidean_dist(robo->get_pos(), ball_pos)<40){
        v = 0;
    }*/


    //    // Novo Controlador

    //    double robo_pos_dx = robo_pos.x - last_robo_pos_x;
    //    double robo_pos_dy = robo_pos.y - last_robo_pos_y;
    //    if (robo_pos_dx < 0.001 || robo_pos_dx > -0.001)
    //        robo_pos_dx = 0.001;
    //    if (robo_pos_dy < 0.001 || robo_pos_dy > -0.001)
    //        robo_pos_dy = 0.001;
    //    double dtheta = theta - last_theta;
    //    double fi_v = (dtheta)*cos(robo->get_angle()) + (dtheta)*sin(robo->get_angle());
    //    //cout << "Robo_pos_dx: " << robo_pos_dx << endl;
    //    //cout << "Robo_pos_dy: " << robo_pos_dy << endl;
    //    //cout << "dtheta: " << dtheta << endl;
    //    //cout << "fi_v : " << fi_v << endl;

    //    double v1 = fabs((2*v_max - l*Kw*sqrt(fabs(alpha)))/ (2 + l*fabs(fi_v)));
    //    double v2 = fabs((sqrt((Kw*Kw) + 4*Rm*fabs(fi_v)) - Kw*sqrt(fabs(alpha))) / (2*fabs(fi_v)));
    //    double v3 = abs(k_distance*euclidean_dist(robo_pos, ball_pos));

    //    if (v1 <= v2 && v1 <= v3){
    //        v = v1;
    //        //cout << "V1: " << v << endl;
    //    }
    //    else if (v2 < v1 && v2 < v3){
    //        v = v2;
    //        //cout << "V2: " << v << endl;
    //    }
    //    else if (v3 < v1 && v3 < v2){
    //        v = v3;
    //        //cout << "V3: " << v << endl;
    //    }

    //    if (v < v_min){
    //        v = v_min;
    //        //cout << "Vmin: " << v << endl;
    //    }



    //    v = 0.5;
    //    //cout << "V: " << v << endl;
    //    w = fi_v + Kw*sign(alpha)*sqrt(fabs(alpha));
    //    //cout << "W: " << w << endl;
    //    last_theta = theta;
    //    last_robo_pos_x = robo_pos.x;
    //    last_robo_pos_y = robo_pos.y;

    last_theta_control = theta;
    last_phi = alpha;

    //    // Limitando o Matador
    //    if(centroid_atk.x > centroid_def.x){
    //        if(ball_pos.x < centroid_def.x + 60 && robo->get_pos().x > ball_pos.x)
    //            v = 0;
    //    }
    //    else{
    //        if(ball_pos.x > centroid_def.x - 60 && robo->get_pos().x < ball_pos.x)
    //            v = 0;
    //    }

//    cout << "v: " << v << endl;
//    if(fabs(w) > 20){
//        if(w > 0)
//            w = 20;
//        else
//            w = -20;
//    }

    // Teste V = 0, situação de defesa atacante

//    if(centroid_atk.x < centroid_def.x){
//        if(ball_pos.x > centroid_def.x - 35 && ball_pos.x > robo_pos.x)
//            v = 0;
//    }
//    else if(centroid_def.x < centroid_atk.x){
//        if(ball_pos.x < centroid_def.x + 35 && ball_pos.x < robo_pos.x)
//            v = 0;
//    }

    vels->first = v-w*l;
    vels->second = v+w*l;

    if(centroid_atk.x < centroid_def.x){
        if(ball_pos.x > 45){
            rotate(robo, vels); //Colocar a inv para ATK vs DEF
        }
    }
    else if(centroid_def.x < centroid_atk.x){
        if(ball_pos.x < 135){
            rotate(robo, vels); //Colocar a inv para ATK vs DEF
        }
    }

    //rotate(robo, vels);
    //kick_rotate(robo, vels);
    atk_situation(robo,pot_fields,vels); //Colocar a inv para ATK vs DEF
    //atk_situation_inv(robo,pot_fields,vels);

   // cout << " Velocidade esquerda: " << vels->first << endl;
   // cout << " Velocidade direita: " << vels->second << endl;

    if(pot_fields->Get_atk_situation_state() == true){ // Atk_situation for any point of goal
        atk_situation_any_point(robo,pot_fields,vels);
    }
    //cout << "Esquerda: " << vels->first << endl; //Cout ativo
    //cout << "Direita: " << vels->second << endl; //Cout ativo

    //    ang_vel = robo->get_ang_vel();
    //    ang_vel = ang_vel*3.141592/180;

    //    vel = robo->get_velocities();

    //    vel.first = vel.first*X_CONV_CONST;
    //    vel.second = vel.second*Y_CONV_CONST;

    ////cout << "Angular:" << ang_vel << endl;

    //    double mod_vel = sqrt(pow(vel.first,2) + pow(vel.second,2));

    ////cout << "Linear Calculada:" << v << endl;
    ////cout << "Linear:" << mod_vel/100 << endl << endl << endl;
    //    //cout << "Esquerda: " << vels->first << endl;
    //    //cout << "Direita: " << vels->second << endl;


}

void Mover::velocity_defender_root(Robot *robo, Game_functions *pot_fields, pair<float, float> *vels){

    Point2d meta = pot_fields->get_meta_defender_root();
    Point2d robot_pos = robo->get_pos();
    Point robot_grid = convert_C_to_G(robot_pos);
    double robot_angle = ajusta_angulo(robo->get_angle());

    double kp = robo->get_kp();
    double kd = robo->get_kd();
    double l = robo->get_l_size();

    Point2d ball_v;

    double v,w,theta,alpha;
    pair<float, float> vel;

    ball_v.x = ball_vel.first / 100;
    ball_v.y = -ball_vel.second / 100;


    //Troca de direcoes
    Point2d obst_prox;
    Point2d wall_1 = robo->get_pos();
    Point2d wall_2 = robo->get_pos();
    Point2d wall_3 = robo->get_pos();
    Point2d wall_4 = robo->get_pos();

    wall_1.x = 160;
    wall_2.x = 10;
    wall_3.y = 0;
    wall_4.y = 130;

    double d0 = euclidean_dist(robo->get_pos(), enemy_pos[0]);
    double d1 = euclidean_dist(robo->get_pos(), enemy_pos[1]);
    double d2 = euclidean_dist(robo->get_pos(), enemy_pos[2]);
    double d3 = euclidean_dist(robo->get_pos(), selec_robot.r1.get_pos()); //Gandalf
    double d4 = euclidean_dist(robo->get_pos(), selec_robot.r2.get_pos()); // Presto
    double d5 = euclidean_dist(robo->get_pos(), selec_robot.r3.get_pos()); //Leona
    double d6 = euclidean_dist(robo->get_pos(), wall_1);
    double d7 = euclidean_dist(robo->get_pos(), wall_2);
    double d8 = euclidean_dist(robo->get_pos(), wall_3);
    double d9 = euclidean_dist(robo->get_pos(), wall_4);
    double distancia_permitida = 15;
    double distancia_obst;

    // Distancia com o mesmo time
    if (robo->get_pos().x == selec_robot.r1.get_pos().x && robo->get_pos().y == selec_robot.r1.get_pos().y ){
        d3 = 1000;
    }

    if (robo->get_pos().x == selec_robot.r2.get_pos().x && robo->get_pos().y == selec_robot.r2.get_pos().y ){
        d4 = 1000;
    }

    if (robo->get_pos().x == selec_robot.r3.get_pos().x && robo->get_pos().y == selec_robot.r3.get_pos().y ){
        d5 = 1000;
    }


    // Distancia com os amigos

    if (d3 <= d4 && d3 <= d5){
        obst_prox = selec_robot.r1.get_pos();
    }
    if (d4 <= d3 && d4 <= d5){
        obst_prox = selec_robot.r2.get_pos();
    }
    if (d5 <= d3 && d5 <= d4){
        obst_prox = selec_robot.r3.get_pos();
    }

    distancia_obst = euclidean_dist(robo->get_pos(), obst_prox);

    //cout << "robo x " << robo->get_pos().x << " robo y " << robo->get_pos().y << endl;
    //cout << "obj x " << obst_prox.x << " obj y " << obst_prox.y << endl;

    double angle = vector_angle(robo->get_pos(),obst_prox);
    double another_ang = fabs(robo->get_angle() - angle);
    if(another_ang > 180){
        another_ang -= 360;
    }
    if(another_ang < -180)
    {
        another_ang += 360;
    }

    //Restricao de posicao
    if (distancia_obst < distancia_permitida){
        if(defender_direction && distancia_obst < distancia_permitida && fabs(another_ang) < 40){
            if (cont_defender_obst > 5){
                defender_direction = false;
                cont_defender_obst = 0;
                cont_defender_tempo = 0;
            }
            else{
                cont_defender_obst = cont_defender_obst + 1;
            }
        }
        else if(!defender_direction && distancia_obst < distancia_permitida && fabs(another_ang) > 180 - 40){
            if (cont_defender_obst > 5){
                defender_direction = true;
                cont_defender_obst = 0;
                cont_defender_tempo = 0;
            }
            else{
                cont_defender_obst = cont_defender_obst + 1;
            }
        }
    }
    else{
        cont_defender_obst = cont_defender_obst - 1;
        if (cont_defender_obst < 0){
            cont_defender_obst = 0;
        }
    }



    for (int cont_vel = 0; cont_vel < 4; cont_vel ++){
        media_ball_v[cont_vel] = media_ball_v[cont_vel+1];
    }
    media_ball_v[4] = ball_v;
    ball_v = 0.35*media_ball_v[4]+0.25*media_ball_v[3]+0.2*media_ball_v[2]+0.15*media_ball_v[1]+0.05*media_ball_v[0];
    ////cout << ball_v.x << endl;

    ////cout << "x " << ball_pos.x << "   y " << ball_pos.y << endl;

    //vels->first = 0;
    //vels->second = 0;

    alpha = 90 - robo->get_angle();
    alpha = ajusta_angulo(alpha);


    //PID
    if (fabs(alpha) <= limiar_theta ){
        w = kp*alpha/180 + kd*(alpha - last_phi);
        limiar_theta = 90 - delta_limiar;
    }
    else{
        alpha = ajusta_angulo(alpha+180);
        w = kp*alpha/180 + kd*(alpha - last_phi);
        limiar_theta = 90 + delta_limiar;
    }

    if (centroid_def.x < centroid_atk.x){
        alpha = 90 - robot_angle;
        alpha = ajusta_angulo(alpha);
        //PID
        if (fabs(alpha) <= limiar_theta ){
            w = 17*alpha/180 + kd*(alpha - last_phi);
            limiar_theta = 90 - delta_limiar;
        }
        else{
            alpha = ajusta_angulo(alpha+180);
            w = 17*alpha/180 + kd*(alpha - last_phi);
            limiar_theta = 90 + delta_limiar;
        }
        double tempo;
        double aux_position_y;
        tempo = (robot_pos.x + 4.5 - ball_pos.x)/ball_v.x;
        aux_position_y = ball_pos.y - tempo*ball_v.y;
        if(aux_position_y < 0){
            aux_position_y = 0;
        }
        if(aux_position_y > 130){
            aux_position_y = 130;
        }
        //previsao de bola
        if (ball_v.x < 0 && ball_pos.x > centroid_def.x + line_root_defender){
            if (robot_angle > 0){
                v = -0.8*(aux_position_y-robot_pos.y)/tempo;
                if(v > 0.6){
                    v = 0.6;
                }
                else if (v < -0.6){
                    v = -0.6;
                }
                vels->first = v - w*l;
                vels->second = v + w*l;
            }
            else if (robot_angle < 0){
                v = 0.8*(aux_position_y-robot_pos.y)/tempo;
                if(v > 0.6){
                    v = 0.6;
                }
                else if(v < -0.6){
                    v = -0.6;
                }

                vels->first = v - w*l;
                vels->second = v + w*l;
            }
        }
        else if (ball_pos.x > centroid_def.x + line_root_defender && robo->get_pos().x < centroid_def.x + line_root_defender + 10 && robo->get_pos().x > centroid_def.x + line_root_defender - 10){
            //FollowBall
                alpha = 90 - robot_angle;
                alpha = ajusta_angulo(alpha);
                //PID
                if (fabs(alpha) <= limiar_theta ){
                    w = 17*alpha/180 + kd*(alpha - last_phi);
                    limiar_theta = 90 - delta_limiar;
                }
                else{
                    alpha = ajusta_angulo(alpha+180);
                    w = 17*alpha/180 + kd*(alpha - last_phi);
                    limiar_theta = 90 + delta_limiar;
                }
                //cout << "angle " << robot_angle << endl;
                //ball_v.y = (ball_v.y / fabs(ball_v.y)) * 0.4;
                if(fabs(robo->get_pos().y-ball_pos.y) < 3){
                    v = 0;
                }
                else if (robot_angle > 0 && ball_pos.y < robot_pos.y ){
                    v = 0.33; // Cinemática 0.005
                    //  cout << "1" << endl;
                }
                else if (robot_angle > 0 && ball_pos.y > robot_pos.y){
                    v = -0.33; //PID 0.03
                    // cout << "2" << endl;
                }
                else if (robot_angle < 0 && ball_pos.y < robot_pos.y ){
                    v = -0.33;
                    //cout << "3" << endl;
                }
                else if (robot_angle < 0 && ball_pos.y > robot_pos.y ){
                    v = 0.33;
                    //cout << "4" << endl;
                }
                if(v > v_max_gol_ef){
                    v = v_max_gol_ef;
                }
                else if(v < -v_max_gol_ef){
                    v = -v_max_gol_ef;
                }
                vels->first = v - w*l;
                vels->second = v + w*l;
        }
        else{
            //Return2Goal
            theta = vector_angle(robo->get_pos(),meta);
            alpha = theta - robo->get_angle();
            alpha = ajusta_angulo(alpha);

            //PID
            if (fabs(alpha) <= limiar_theta ){
                //v = v_max;
                v = -v_delta*fabs(alpha)/limiar_theta + v_max;
                w = kp*alpha/180 + kd*(alpha - last_phi);
                limiar_theta = 90 - delta_limiar;
                ////cout << "Frente" << endl;
            }
            else{
                alpha = ajusta_angulo(alpha+180);
                //v = - v_max;
                v = v_delta*fabs(alpha)/limiar_theta - v_max;
                w = kp*alpha/180 + kd*(alpha - last_phi);
                limiar_theta = 90 + delta_limiar;
                ////cout << "Trás" << endl;
            }


            //Defender Direction

//                if (defender_direction){
//                    v = -v_delta*fabs(alpha)/limiar_theta + v_max;
//                    //w = kp*alpha/180 + kd*(robo->get_angle() - last_angle);
//                    //w = kp*alpha/180 + kd*(alpha-last_phi);
//                    w = kp*alpha/180 + kd*(alpha-last_phi);
//                    //            w = 7*alpha/180  + 0.0015*(theta-last_theta_control) + 0*(alpha - last_phi);
//                    limiar_theta = 90 - delta_limiar;
//                    //cout << "1" << endl;
//                }
//                else{
//                    alpha = ajusta_angulo(alpha+180);
//                    v = v_delta*fabs(alpha)/limiar_theta - v_max;
//                    w = kp*alpha/180 + kd*(alpha-last_phi);
//                    //            w = 7*alpha/180 + 0.0015*(theta-last_theta_control) + 0*(alpha - last_phi);
//                    limiar_theta = 90 + delta_limiar;
//                    // cout << "2" << endl;
//                }


            //                if (fabs(alpha) <= limiar_theta){
            //                    w = kgol*v_max_gol*alpha/180;
            //                    v = -v_max_gol*fabs(alpha)/limiar_theta + v_max_gol;
            //                }
            //                else{
            //                    alpha = ajusta_angulo(alpha+180);
            //                    w = kgol*v_max_gol*alpha/180;
            //                    v = v_max_gol*fabs(alpha)/limiar_theta - v_max_gol;
            //                }
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
            if((euclidean_dist(robot_pos, pot_fields->get_meta_defender_root()) < 7.5) && (fabs(robo->get_angle()) > 85) && (fabs(robo->get_angle()) < 95)){
                vels->first = 0;
                vels->second = 0;
            }
            else if (euclidean_dist(robot_pos, pot_fields->get_meta_defender_root()) < 7.5){
                goalkeeper_orientation(robo,vels);

                ////cout << "AdjustRobo" << endl;
            }
        }
    }else{
        alpha = 90 - robot_angle;
        alpha = ajusta_angulo(alpha);
        //PID
        if (fabs(alpha) <= limiar_theta ){
            w = 17*alpha/180 + kd*(alpha - last_phi);
            limiar_theta = 90 - delta_limiar;
        }
        else{
            alpha = ajusta_angulo(alpha+180);
            w = 17*alpha/180 + kd*(alpha - last_phi);
            limiar_theta = 90 + delta_limiar;
        }
        double tempo;
        double aux_position_y;
        tempo = (robot_pos.x - 4.5 - ball_pos.x)/ball_v.x;
        aux_position_y = ball_pos.y - tempo*ball_v.y;
        if(aux_position_y < 0){
            aux_position_y = 0;
        }
        if(aux_position_y > 130){
            aux_position_y = 130;
        }
        //previsao de bola

        if (ball_v.x > 0 && ball_pos.x < centroid_def.x - line_root_defender){

            if (robot_angle > 0){
                v = -(aux_position_y-robot_pos.y)/tempo;
                if(v > v_max_gol_ef){
                    v = v_max_gol_ef;
                }
                else if(v < -v_max_gol_ef){
                    v = -v_max_gol_ef;
                }
                vels->first = v - w*l;
                vels->second = v + w*l;
            }
            else if (robot_angle < 0){
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
            // //cout << "prevision" << endl;
        }
        else if (ball_pos.x < centroid_def.x - line_root_defender && robo->get_pos().x < centroid_def.x - line_root_defender + 10 && robo->get_pos().x > centroid_def.x - line_root_defender - 10){
            //FollowBall
            alpha = 90 - robot_angle;
            alpha = ajusta_angulo(alpha);
            //PID
            if (fabs(alpha) <= limiar_theta ){
                w = 17*alpha/180 + kd*(alpha - last_phi);
                limiar_theta = 90 - delta_limiar;
            }
            else{
                alpha = ajusta_angulo(alpha+180);
                w = 17*alpha/180 + kd*(alpha - last_phi);
                limiar_theta = 90 + delta_limiar;
            }

            //cout << "angle " << robot_angle << endl;
            //ball_v.y = (ball_v.y / fabs(ball_v.y)) * 0.4;
            if(fabs(robo->get_pos().y-ball_pos.y) < 3){
                v = 0;
            }
            else if (robot_angle > 0 && ball_pos.y < robot_pos.y ){
                v = 0.33; // Cinemática 0.005
                //  cout << "1" << endl;
            }
            else if (robot_angle > 0 && ball_pos.y > robot_pos.y){
                v = -0.33; //PID 0.03
                // cout << "2" << endl;
            }
            else if (robot_angle < 0 && ball_pos.y < robot_pos.y ){
                v = -0.33;
                //cout << "3" << endl;
            }
            else if (robot_angle < 0 && ball_pos.y > robot_pos.y ){
                v = 0.33;
                //cout << "4" << endl;
            }
            if(v > v_max_gol_ef){
                v = v_max_gol_ef;
            }
            else if(v < -v_max_gol_ef){
                v = -v_max_gol_ef;
            }
            vels->first = v - w*l;
            vels->second = v + w*l;


        }
        else{
            // //cout << "return to meta" << endl;
            //Return2Goal
            theta = vector_angle(robo->get_pos(),meta);
            alpha = theta - robo->get_angle();
            alpha = ajusta_angulo(alpha);

            //PID
            if (fabs(alpha) <= limiar_theta ){
                //v = v_max;
                v = -v_delta*fabs(alpha)/limiar_theta + v_max;
                w = kp*alpha/180 + kd*(alpha - last_phi);
                limiar_theta = 90 - delta_limiar;
                ////cout << "Frente" << endl;
            }
            else{
                alpha = ajusta_angulo(alpha+180);
                //v = - v_max;
                v = v_delta*fabs(alpha)/limiar_theta - v_max;
                w = kp*alpha/180 + kd*(alpha - last_phi);
                limiar_theta = 90 + delta_limiar;
                ////cout << "Trás" << endl;
            }

            //Defender Direction

//                if (defender_direction){
//                    v = -v_delta*fabs(alpha)/limiar_theta + v_max;
//                    //w = kp*alpha/180 + kd*(robo->get_angle() - last_angle);
//                    //w = kp*alpha/180 + kd*(alpha-last_phi);
//                    w = kp*alpha/180 + kd*(alpha-last_phi);
//                    //            w = 7*alpha/180  + 0.0015*(theta-last_theta_control) + 0*(alpha - last_phi);
//                    limiar_theta = 90 - delta_limiar;
//                    //cout << "1" << endl;
//                }
//                else{
//                    alpha = ajusta_angulo(alpha+180);
//                    v = v_delta*fabs(alpha)/limiar_theta - v_max;
//                    w = kp*alpha/180 + kd*(alpha-last_phi);
//                    //            w = 7*alpha/180 + 0.0015*(theta-last_theta_control) + 0*(alpha - last_phi);
//                    limiar_theta = 90 + delta_limiar;
//                    // cout << "2" << endl;
//                }

            //                if (fabs(alpha) <= limiar_theta){
            //                    w = kgol*v_max_gol*alpha/180;
            //                    v = -v_max_gol*fabs(alpha)/limiar_theta + v_max_gol;
            //                }
            //                else{
            //                    alpha = ajusta_angulo(alpha+180);
            //                    w = kgol*v_max_gol*alpha/180;
            //                    v = v_max_gol*fabs(alpha)/limiar_theta - v_max_gol;
            //                }

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
            if((euclidean_dist(robot_pos, pot_fields->get_meta_defender_root()) < 7.5) && (fabs(robo->get_angle()) > 85) && (fabs(robo->get_angle()) < 95)){
                vels->first = 0;
                vels->second = 0;
            }
            else if (euclidean_dist(robot_pos, pot_fields->get_meta_defender_root()) < 7.5){
                goalkeeper_orientation(robo,vels);

                ////cout << "AdjustRobo" << endl;
            }
        }
    }

    last_phi = alpha;
    rotate(robo, vels);
    kick_rotate(robo, vels);

//    if (test < 5 ){
//        test = test + 1;
//        vels->first = 0;
//        vels->second = 0;
//    }
//    else if (test == 5 ){
//        test = 0;
//        vels->first = 1;
//        vels->second = 1;
//    }


    //Point robot_grid = convert_C_to_G(robo->get_pos());
    //Point2d eixo_x(1.0,0.0);



    /*Point2d robo_pos = robo->get_pos();
    Point2d meta_defender_root = pot_fields->get_meta_defender_root();
    double robo_angle = ajusta_angulo(robo->get_angle());

    double v,w,theta,alpha;
    pair<float, float> vel;

    double kp = robo->get_kp();
    double kd = robo->get_kd();
    double l = robo->get_l_size();

    //velocidade da bola
    Point2d ball_v;

    ball_v.x = ball_vel.first / 100;
    ball_v.y = -ball_vel.second / 100;


    for (int cont_vel = 0; cont_vel < 4; cont_vel ++){
        media_ball_v[cont_vel] = media_ball_v[cont_vel+1];
    }
    media_ball_v[4] = ball_v;
    ball_v = 0.35*media_ball_v[4]+0.25*media_ball_v[3]+0.2*media_ball_v[2]+0.15*media_ball_v[1]+0.05*media_ball_v[0];

    //Angulo do campos potenciais

    alpha = 90 - robo_angle; //90 (para alinhar o robo, o angulo do robo com o CPU e tratado depois)
    alpha = ajusta_angulo(alpha);

    //PID
    if (fabs(alpha) <= limiar_theta ){
        w = 11*alpha/180 + 0.0*(alpha - last_phi);
        limiar_theta = 90 - delta_limiar;
    }
    else{
        alpha = ajusta_angulo(alpha+180);
        w = 11*alpha/180 + 0.0*(alpha - last_phi);
        limiar_theta = 90 + delta_limiar;
    }


    if (centroid_atk.x > centroid_def.x){ //conferir lado

        double v_follow = 0;
        if (pot_fields->flag_return==0){
            //cout << " ball v " << ball_v.y << endl;

            if(ball_v.y > 0){
                v_follow = 0.040*fabs((ball_pos.y - robo_pos.y - 6));
            }else{
                v_follow = 0.040*fabs((ball_pos.y - robo_pos.y + 6));
            }

            //condicoes iguais para diferentes centroides
            if (fabs(robo_pos.y - ball_pos.y) < 3){
                v_follow = 0;
                goalkeeper_orientation(robo,vels);
            }
            else if (robo_angle > 0 && ball_pos.y < robo_pos.y ){
                v = v_follow;
            }
            else if (robo_angle > 0 && ball_pos.y > robo_pos.y){
                v = -v_follow;
            }
            else if (robo_angle < 0 && ball_pos.y < robo_pos.y ){
                v = -v_follow;
            }
            else if (robo_angle < 0 && ball_pos.y > robo_pos.y ){
                v = v_follow;
            }
            //  cout << "Defender New FollowBall 1" << endl;
            //}
            if(v > 0.65){
                v = 0.65;
            }
            else if(v < -0.65){
                v = -0.65;
            }
            vels->first = v-w*l;
            vels->second = v+w*l;
            if(fabs(vels->first) < 0.15 && v != 0){
                if(vels->first < 0)
                    vels->first = -0.15;
                else
                    vels->first = 0.15;
            }
            if(fabs(vels->second) < 0.15 && v != 0){
                if(vels->second < 0)
                    vels->second = -0.15;
                else
                    vels->second = 0.15;
            }

        }
        else if (pot_fields->flag_return==1 || pot_fields->flag_return==2){

            //Return2Goal
            theta = vector_angle(robo_pos,meta_defender_root);
            alpha = theta - robo_angle;
            alpha = ajusta_angulo(alpha);

            // PID
            if (fabs(alpha) <= limiar_theta ){
                v = -v_delta*fabs(alpha)/limiar_theta + v_max;
                w = kp*alpha/180 + kd*(alpha - last_phi);
                limiar_theta = 90 - delta_limiar;
            }
            else{
                alpha = ajusta_angulo(alpha+180);
                v = v_delta*fabs(alpha)/limiar_theta - v_max;
                w = kp*alpha/180 + kd*(alpha - last_phi);
                limiar_theta = 90 + delta_limiar;
            }

            if(v > v_max_gol_ef){
                v = v_max_gol_ef;
            }
            else if(v < -v_max_gol_ef){
                v = -v_max_gol_ef;
            }

            vels->first = v-w*l;
            vels->second = v+w*l;

            if(fabs(vels->first) < 0.15 && v != 0){
                if(vels->first < 0)
                    vels->first = -0.15;
                else
                    vels->first = 0.15;
            }
            if(fabs(vels->second) < 0.15 && v != 0){
                if(vels->second < 0)
                    vels->second = -0.15;
                else
                    vels->second = 0.15;
            }

            //cout << "Defender Old ReturnToGoal 1" << endl;

            //AdjustRobo
            if((fabs(robo_pos.x - meta_defender_root.x) < 5) && (fabs(robo_pos.y - meta_defender_root.y) < 4) &&(fabs(robo_angle) > 85) && (fabs(robo_angle) < 95)){
                vels->first = 0;
                vels->second = 0;
            }else if((fabs(robo_pos.x - meta_defender_root.x) < 5) && (fabs(robo_pos.y - meta_defender_root.y) < 4)){
                goalkeeper_orientation(robo,vels);
            }
        }
    }

    else if (centroid_atk.x <= centroid_def.x){ //conferir lado
        //if (robo_pos.x < 140){ //Navigation.centroid_def.x - defender_line
        //if (fabs(ball_v.x) < 2) // conferir se a bola ta indo pro gol
        //{
        //FollowBall

        //cout << "Flag " << pot_fields->flag_return << endl;
            double v_follow = 0;
        if (pot_fields->flag_return==0){
            //cout << " ball v " << ball_v.y << endl;

            if(ball_v.y > 0){
                v_follow = 0.040*fabs((ball_pos.y - robo_pos.y - 6));
            }else{
                v_follow = 0.040*fabs((ball_pos.y - robo_pos.y + 6));
            }
            //condicoes iguais para diferentes centroides
            if (fabs(robo_pos.y - ball_pos.y) < 3){
                v_follow = 0;
                goalkeeper_orientation(robo,vels);
            }
            else if (robo_angle > 0 && ball_pos.y < robo_pos.y ){
                v = v_follow;
            }
            else if (robo_angle > 0 && ball_pos.y > robo_pos.y){
                v = -v_follow;
            }
            else if (robo_angle < 0 && ball_pos.y < robo_pos.y ){
                v = -v_follow;
            }
            else if (robo_angle < 0 && ball_pos.y > robo_pos.y ){
                v = v_follow;
            }
            //      cout << "Defender New FollowBall 2" << endl;
            //                cout << "Entrou" << endl;
            //}
            if(v > 0.65){
                v = 0.65;
            }
            else if(v < -0.65){
                v = -0.65;
            }
            vels->first = v-w*l;
            vels->second = v+w*l;
        }
        if(fabs(vels->first) < 0.15 && v != 0){
            if(vels->first < 0)
                vels->first = -0.15;
            else
                vels->first = 0.15;
        }
        if(fabs(vels->second) < 0.15 && v != 0){
            if(vels->second < 0)
                vels->second = -0.15;
            else
                vels->second = 0.15;
        }

        //}
        else if (pot_fields->flag_return==1 || pot_fields->flag_return==2){

            //Return2Goal

            //            cout << "mx " << meta_defender_root.x << endl;
            //            cout << "my " << meta_defender_root.y << endl;
            //            cout << "rx " << robo_pos.x << endl;
            //            cout << "ry " << robo_pos.y << endl;

            theta = vector_angle(robo_pos,meta_defender_root);
            alpha = theta - robo_angle;
            alpha = ajusta_angulo(alpha);

            // PID
            if (fabs(alpha) <= limiar_theta ){
                v = -v_delta*fabs(alpha)/limiar_theta + v_max;
                w = kp*alpha/180 + kd*(alpha - last_phi);
                limiar_theta = 90 - delta_limiar;
            }
            else{
                alpha = ajusta_angulo(alpha+180);
                v = v_delta*fabs(alpha)/limiar_theta - v_max;
                w = kp*alpha/180 + kd*(alpha - last_phi);
                limiar_theta = 90 + delta_limiar;
            }

            if(v > v_max_gol_ef){
                v = v_max_gol_ef;
            }
            else if(v < -v_max_gol_ef){
                v = -v_max_gol_ef;
            }

            vels->first = v-w*l;
            vels->second = v+w*l;
            if(fabs(vels->first) < 0.15 && v != 0){
                if(vels->first < 0)
                    vels->first = -0.15;
                else
                    vels->first = 0.15;
            }
            if(fabs(vels->second) < 0.15 && v != 0){
                if(vels->second < 0)
                    vels->second = -0.15;
                else
                    vels->second = 0.15;
            }
            //    cout << "Defender Old ReturnToGoal 2" << endl;

            //AdjustRobo
            if((fabs(robo_pos.x - meta_defender_root.x) < 5) && (fabs(robo_pos.y - meta_defender_root.y) < 4) &&(fabs(robo_angle) > 85) && (fabs(robo_angle) < 95)){
                vels->first = 0;
                vels->second = 0;
            }else if((fabs(robo_pos.x - meta_defender_root.x) < 5) && (fabs(robo_pos.y - meta_defender_root.y) < 4)){
                goalkeeper_orientation(robo,vels);
            }
            //            pot_fields->flag_return = 2;
        }
        //        else if(pot_fields->flag_return == 2){
        //             vels->first = 0;
        //              vels->first = 0;
        //                          cout << "Stop 2" << endl;

        //        }
    }

    // alpha = 90 - robo_angle;
    //                alpha = ajusta_angulo(alpha);


    //                //PID
    //                if (fabs(alpha) <= limiar_theta ){
    //                    w = 13*alpha/180 + kd*(alpha - last_phi);
    //                    limiar_theta = 90 - delta_limiar;
    //                }
    //                else{
    //                    alpha = ajusta_angulo(alpha+180);
    //                    w = 13*alpha/180 + kd*(alpha - last_phi);
    //                    limiar_theta = 90 + delta_limiar;
    //                }


    //                if (fabs(ball_v.y < 2))
    //                {
    //                    //ball_v.y = (ball_v.y / fabs(ball_v.y)) * 0.4;
    //                    if(fabs(robo_pos.y-ball_pos.y) < 3){
    //                        v = 0;
    //                        goalkeeper_orientation(robo,vels);

    //                    }
    //                    else if (robo_angle > 0 && ball_pos.y < robo_pos.y ){
    //                        v = 0.33; // Cinemática 0.005
    //                    }
    //                    else if (robo_angle > 0 && ball_pos.y > robo_pos.y){
    //                        v = -0.33; //PID 0.03
    //                    }
    //                    else if (robo_angle < 0 && ball_pos.y < robo_pos.y ){
    //                        v = -0.33;
    //                    }
    //                    else if (robo_angle < 0 && ball_pos.y > robo_pos.y ){
    //                        v = 0.33;
    //                    }
    //                    ////cout << "FollowBall" << endl;

    //                }
    //                if(v > 0.6){
    //                    v = 0.6;
    //                }
    //                else if(v < -0.6){
    //                    v = -0.6;
    //                }
    //                vels->first = v - w*l;
    //                vels->second = v + w*l;

    //cout << "vr" <<vels->first << endl;
    //cout << "ve" <<vels->second << endl;
    last_phi = alpha;


    //rotate(robo, vels);
    if(pot_fields->flag_return!=2)
        kick_rotate(robo, vels);
    // cout << "Distancia " << euclidean_dist(centroid_def, robo_pos) << endl;

    //cout << "Meta x " << pot_fields->get_meta_defender_root().x << endl;
    //cout << "Meta y " << pot_fields->get_meta_defender_root().y << endl;
    //cout << "Ball x " << ball_pos.x << endl;
    //cout << "Ball y " << ball_pos.y << endl;*/



}

void Mover::set_killer_direction(bool a)
{
    killer_direction = a;
}

// Novas Funções
void Mover::velocity_fake9(Robot *robo, Game_functions *pot_fields, pair<float, float> *vels)
{
    Point2d ball_v;
    pair <double,double> vel;
    double ang_vel;
    double theta;
    double alpha;
    double last_phi=0;
    double w,v;
    Point2d meta;
    ball_v.x = ball_vel.first / 100;
    ball_v.y = -ball_vel.second / 100;


    double kp = robo->get_kp();
    double kd = robo->get_kd();
    double l = robo->get_l_size();

    meta = pot_fields->meta_fake9;
    theta = vector_angle(robo->get_pos(), meta);
    alpha = theta - robo->get_angle();
    alpha = ajusta_angulo(alpha);

    //PID
    if (fabs(alpha) <= limiar_theta ){
         v = -v_delta*fabs(alpha)/limiar_theta + v_max;
         w = kp*alpha/180 + kd*(alpha-last_phi);
         //            w = 7*alpha/180  + 0.0015*(theta-last_theta_control) + 0*(alpha - last_phi);
         limiar_theta = 90 - delta_limiar;
         //cout << "3" << endl;
    }
    else{
        alpha = ajusta_angulo(alpha+180);
        v = v_delta*fabs(alpha)/limiar_theta - v_max;
        w = kp*alpha/180 + kd*(alpha-last_phi);
        //            w = 7*alpha/180  + 0.0015*(theta-last_theta_control) + 0*(alpha - last_phi);
        limiar_theta = 90 + delta_limiar;
        //cout << "4" << endl;
    }
    //Fim PID
    last_phi = alpha;
    vels->first = v-w*l;
    vels->second = v+w*l;
    cout << "Velocidade 1: " << v-w*l << endl;
    cout << "Velocidade 2: " << v+w*l << endl;
}
//Fim Novas Funções

void Mover::set_params(Robot * robo){
    switch(robo->get_channel())
    {
    case 1: //roda travando
        robo->set_kp(15);
        robo->set_kd(0.003);
        robo->set_l_size(0.030);
        break;
    case 2: //ok
        robo->set_kp(13);
        robo->set_kd(0.003);
        robo->set_l_size(0.030);
        break;
    case 3: //ok
        robo->set_kp(16);
        robo->set_kd(0.0035);
        robo->set_l_size(0.030);
        break;
    case 4: //ok
        robo->set_kp(12);
        robo->set_kd(0.003);
        robo->set_l_size(0.030);
        break;
    case 8: //trocar roda
        robo->set_kp(10);
        robo->set_kd(0.005);
        robo->set_l_size(0.033);
        break;
    case 9: //trocar roda
        robo->set_kp(6.85);
        robo->set_kd(0.0000);
        robo->set_l_size(0.034);
        break;
    case 10:
        robo->set_kp(7.5);
        robo->set_kd(0.00000);
        robo->set_l_size(0.034);
        break;
    case 11:
        robo->set_kp(7.3); //8.3
        robo->set_kd(0.000);
        robo->set_l_size(0.034);
        break;
    case 12: //Ganhos não ajustados ainda
        robo->set_kp(8.5);
        robo->set_kd(0.000);
        robo->set_l_size(0.034);
        break;
    }
}
