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
double w_max_gol = 5;
double k = (w_max/v_max);
double l = 0.028; // caso mudar de robo trocar esse valor (robo antigo 0.0275)

Serial Mover::serial;

Mover::Mover()
{
    stop = true;
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
    cout << "Velocidades: " << vels[0].first << " " <<  vels[0].second << endl;

    //Pro segundo robô - Presto
    calcula_velocidades(&selec_robot.r2,selec_iterador.presto, &vels[1]);
    selec_robot.r2.set_lin_vel(vels[1]);

    //Pro terceiro robô - Leona
    calcula_velocidades(&selec_robot.r3,selec_iterador.leona, &vels[2]);
    selec_robot.r3.set_lin_vel(vels[2]);

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

    vels->first = 0;
    vels->second = 0;

    alpha = 90 - robo->get_angle();
    alpha = ajusta_angulo(alpha);
    if (fabs(alpha) <= limiar_theta){
        w = k*v_max*alpha/180;
    }
    else{
        alpha = ajusta_angulo(alpha+180);
        w = k*v_max*alpha/180;
    }
    if (ball_pos.x <= centroid_atk.x){
        double tempo;
        double aux_position_y;
        tempo = (robot_pos.x - 3.75 - ball_pos.x)/ball_v.x;
        aux_position_y = ball_pos.y - tempo*ball_v.y;
        if (ball_v.x < 0 && (aux_position_y > centroid_def.y-25) && (aux_position_y < centroid_def.y+25)){
            if (robo->get_angle() > 0){
                v = -(aux_position_y-robot_pos.y)/tempo;
                vels->first = v - w*l;
                vels->second = v + w*l;
            }
            else if (robo->get_angle() < 0){
                v = (aux_position_y-robot_pos.y)/tempo;
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
                vels->first = v - w*l;
                vels->second = v + w*l;
            }
            else {
                //Return2Goal
                theta = pot_fields->get_direction(robot_grid);
                alpha = theta - robo->get_angle();
                alpha = ajusta_angulo(alpha);
                if (fabs(alpha) <= limiar_theta){
                    w = k*v_max_gol*alpha/180;
                    v = -v_max_gol*fabs(alpha)/limiar_theta + v_max_gol;
                }
                else{
                    alpha = ajusta_angulo(alpha+180);
                    w = k*v_max_gol*alpha/180;
                    v = v_max_gol*fabs(alpha)/limiar_theta - v_max_gol;
                }
                if (fabs(alpha) > 65 && fabs(alpha) < 115){
                    v = 0;
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
                }
            }
        }
    }
    else if (ball_pos.x < centroid_def.x){
        double tempo;
        double aux_position_y;
        tempo = (robot_pos.x - 3.75 - ball_pos.x)/ball_v.x;
        aux_position_y = ball_pos.y - tempo*ball_v.y;
        if (ball_v.x > 0 && (aux_position_y > centroid_def.y-25) && (aux_position_y < centroid_def.y+25)){
            if (robo->get_angle() > 0){
                v = -(aux_position_y-robot_pos.y)/tempo;
                vels->first = v - w*l;
                vels->second = v + w*l;
            }
            else if (robo->get_angle() < 0){
                v = (aux_position_y-robot_pos.y)/tempo;
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
                    w = k*v_max_gol*alpha/180;
                    v = -v_max_gol*fabs(alpha)/limiar_theta + v_max_gol;
                }
                else{
                    alpha = ajusta_angulo(alpha+180);
                    w = k*v_max_gol*alpha/180;
                    v = v_max_gol*fabs(alpha)/limiar_theta - v_max_gol;
                }
                if (fabs(alpha) > 65 && fabs(alpha) < 115){
                    v = 0;
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
                }
            }
        }
    }
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

    if (centroid_atk.x > ball_pos.x){
        if ((ball_pos.y > centroid_atk.y+55) && (euclidean_dist(ball_pos,robo->get_pos()) < 5)){
            //cout << "1" << endl;
            vels->first = -0.6;
            vels->second = 0.6;
        }
        else if ((ball_pos.y < centroid_atk.y-55) && (euclidean_dist(ball_pos,robo->get_pos()) < 5)){
            //cout << "2" << endl;
            vels->first = 0.6;
            vels->second = -0.6;
        }
    }
    else{
        if ((ball_pos.y > centroid_atk.y+55) && (euclidean_dist(ball_pos,robo->get_pos()) < 5)){
            vels->first = 0.6;
            vels->second = -0.6;
        }
        else if ((ball_pos.y < centroid_atk.y-55) && (euclidean_dist(ball_pos,robo->get_pos()) < 5)){
            vels->first = -0.6;
            vels->second = 0.6;
        }
    }
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

    if (centroid_atk.x > ball_pos.x){
        if ((ball_pos.y > centroid_atk.y+55) && (euclidean_dist(ball_pos,robo->get_pos()) < 5)){
            //cout << "1" << endl;
            vels->first = -0.6;
            vels->second = 0.6;
        }
        else if ((ball_pos.y < centroid_atk.y-55) && (euclidean_dist(ball_pos,robo->get_pos()) < 5)){
            //cout << "2" << endl;
            vels->first = 0.6;
            vels->second = -0.6;
        }
        else if (euclidean_dist(robo->get_pos(),pot_fields->get_meta()) < 6){
            vels->first = 0;
            vels->second = 0;
        }
    }
    else{
        if ((ball_pos.y > centroid_atk.y+55) && (euclidean_dist(ball_pos,robo->get_pos()) < 5)){
            vels->first = 0.6;
            vels->second = -0.6;
        }
        else if ((ball_pos.y < centroid_atk.y-55) && (euclidean_dist(ball_pos,robo->get_pos()) < 5)){
            vels->first = -0.6;
            vels->second = 0.6;
        }
        else if (euclidean_dist(robo->get_pos(),pot_fields->get_meta()) < 6){

            vels->first = 0;
            vels->second = 0;
        }
    }
}

void Mover::velocity_ofensive_midfielder(Robot *robo, Game_functions *pot_fields, pair<float, float> *vels){
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
    vels->first = v - w*l;
    vels->second = v + w*l;

    if (centroid_atk.x > ball_pos.x){
        if ((ball_pos.y > centroid_atk.y+55) && (euclidean_dist(ball_pos,robo->get_pos()) < 5)){
            //cout << "1" << endl;
            vels->first = -0.6;
            vels->second = 0.6;
        }
        else if ((ball_pos.y < centroid_atk.y-55) && (euclidean_dist(ball_pos,robo->get_pos()) < 5)){
            //cout << "2" << endl;
            vels->first = 0.6;
            vels->second = -0.6;
        }
    }
    else{
        if ((ball_pos.y > centroid_atk.y+55) && (euclidean_dist(ball_pos,robo->get_pos()) < 5)){
            vels->first = 0.6;
            vels->second = -0.6;
        }
        else if ((ball_pos.y < centroid_atk.y-55) && (euclidean_dist(ball_pos,robo->get_pos()) < 5)){
            vels->first = -0.6;
            vels->second = 0.6;
        }
    }
}

void Mover::velocity_striker(Robot *robo, Game_functions *pot_fields, pair<float, float> *vels){
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

    if (centroid_atk.x > ball_pos.x){
        if ((ball_pos.y > centroid_atk.y+55) && (euclidean_dist(ball_pos,robo->get_pos()) < 5)){
            //cout << "1" << endl;
            vels->first = -0.6;
            vels->second = 0.6;
        }
        else if ((ball_pos.y < centroid_atk.y-55) && (euclidean_dist(ball_pos,robo->get_pos()) < 5)){
            //cout << "2" << endl;
            vels->first = 0.6;
            vels->second = -0.6;
        }
    }
    else{
        if ((ball_pos.y > centroid_atk.y+55) && (euclidean_dist(ball_pos,robo->get_pos()) < 5)){
            vels->first = 0.6;
            vels->second = -0.6;
        }
        else if ((ball_pos.y < centroid_atk.y-55) && (euclidean_dist(ball_pos,robo->get_pos()) < 5)){
            vels->first = -0.6;
            vels->second = 0.6;
        }
    }
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
