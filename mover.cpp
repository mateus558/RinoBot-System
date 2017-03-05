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
double k = (w_max/v_max);
double l = 0.028; // caso mudar de robo trocar esse valor (robo antigo 0.0275)

Serial Mover::serial;

Mover::Mover()
{
    stop = true;
    mover_initialized = false;
    enemy_pos_grid = pVector(3);
    team_pos_grid = pVector(3);
    vr = 0;
    vl = 0;
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
    if (selec_robot.r1.get_flag_fuzzy() >= 2 && selec_robot.r2.get_flag_fuzzy() >= 2){
        if (fabs(selec_robot.r1.get_pos().x - centroid_def.x) > fabs(selec_robot.r2.get_pos().x - centroid_def.x)){
            selec_robot.r2.set_flag_fuzzy(1);
        }
        else {
            selec_robot.r1.set_flag_fuzzy(1);
        }
    }
    else{
        //tratar aqui
    }
    if (selec_robot.r1.get_flag_fuzzy() <= 1 && selec_robot.r2.get_flag_fuzzy() <= 1){
        if (fabs(selec_robot.r1.get_pos().x - centroid_def.x) > fabs(selec_robot.r2.get_pos().x - centroid_def.x)){
            selec_robot.r1.set_flag_fuzzy(2);
        }
        else {
            selec_robot.r2.set_flag_fuzzy(2);
        }
    }
    else{
        //tratar aqui
    }

    //Pro primeiro robô - Gandalf
    calcula_velocidades(&selec_robot.r1,selec_iterador.cph,selec_iterador.cpo,selec_iterador.cph2,selec_iterador.cpo2, selec_iterador.cpo3);
    selec_robot.r1.set_lin_vel(make_pair(vl,vr));

    //Pro segundo robô - Presto
    calcula_velocidades(&selec_robot.r2,selec_iterador.cph,selec_iterador.cpo,selec_iterador.cph2,selec_iterador.cpo2, selec_iterador.cpo3);
    selec_robot.r2.set_lin_vel(make_pair(vl,vr));

    //Pro terceiro robô - Leona
    calcula_velocidades(&selec_robot.r3,selec_iterador.cph,selec_iterador.cpo,selec_iterador.cph2,selec_iterador.cpo2, selec_iterador.cpo3);
    selec_robot.r3.set_lin_vel(make_pair(vl,vr));


    emit emitRobots(selec_robot);
}

void Mover::set_to_select(Robot r1, Robot r2, Robot r3){
    selec_robot.r1 = r1;
    selec_robot.r2 = r2;
    selec_robot.r3 = r3;
}

void Mover::set_to_select_iterador(CPH *cph, CPO *cpo , CPH2 *cph2, CPO2 *cpo2, CPO3 *cpo3){
    selec_iterador.cph = cph;
    selec_iterador.cph2 = cph2;
    selec_iterador.cpo = cpo;
    selec_iterador.cpo2 = cpo2;
    selec_iterador.cpo3 = cpo3;

}

void Mover::calcula_velocidades(Robot *r, CPH *cph, CPO *cpo, CPH2 *cph2, CPO2 *cpo2, CPO3 *cpo3){

    double v,w,theta,alpha;
    w_max = 7;
    Point2d robot_pos = r->get_pos();
    Point robot_grid = convert_C_to_G(robot_pos);
    //cout << " Posicao do robo " << endl;
    //cout << " x: " << robot_pos.x << " y: " << robot_pos.y << endl;

    if(r->get_flag_fuzzy() == 4){
        //cout<<"Sou Goleiro!"<<endl;
        w_max = 5;
        theta = cpo3->get_direction(robot_grid);
    }
    else{

        if(r->get_flag_fuzzy() == 0){
            theta = cph->get_direction(robot_grid);
            //cout << "Rodrigay!" << endl;
        }
        else if(r->get_flag_fuzzy() == 1){
            theta = cph2->get_direction(robot_grid);
            //cout << "gabigay!" << endl;
        }
        else if(r->get_flag_fuzzy() == 2){
            theta = cpo2->get_direction(robot_grid);
            //cout << "JoaoTraveco!" << endl;
        }
        else if(r->get_flag_fuzzy() == 3){
            theta = cpo->get_direction(robot_grid);
            //cout << "Fredtransex!" << endl;
        }
    }
    cout << "decisao: " << r->get_flag_fuzzy();

        if (centroid_atk.x > ball_pos.x){
            if ((ball_pos.y > centroid_atk.y+55) && (euclidean_dist(ball_pos,robot_pos) < 5)){
                //cout << "1" << endl;
                vl = -0.6;
                vr = 0.6;
            }
            else if ((ball_pos.y < centroid_atk.y-55) && (euclidean_dist(ball_pos,robot_pos) < 5)){
                //cout << "2" << endl;
                vl = 0.6;
                vr = -0.6;
            }
            else if (euclidean_dist(robot_pos,cph2->get_meta_aux()) < 5 && r->get_flag_fuzzy() == 1){
                cout << "3" << endl;
                vl = 0;
                vr = 0;
            }
            else if (euclidean_dist(robot_pos,cpo3->get_meta_aux()) < 5){// && r->get_flag_fuzzy() == 4){
                cout << "4" << endl;
                alpha = 90 - r->get_angle();
                alpha = ajusta_angulo(alpha);
                if (fabs(alpha) < 10 || fabs(alpha) > 170)
                    w = 0;
                else{
                    w = k*v_max*alpha/180;
                    vl = -w*l;
                    vr = w*l;
                }
            }
            else{
                alpha = theta - r->get_angle();
                alpha = ajusta_angulo(alpha);

                //cout << "angulo do robo: "<<r->get_angle()<<endl;

                if (fabs(alpha) <= limiar_theta){
                    w = k*v_max*alpha/180;
                    v = -v_max*fabs(alpha)/limiar_theta + v_max;
                }
                else{
                    alpha = ajusta_angulo(alpha+180);
                    w = k*v_max*alpha/180;
                    v = v_max*fabs(alpha)/limiar_theta - v_max;
                }


                //cout << "velocidade linear: " << v << endl;
                //cout << "velocidade angular: " << w << endl;

                vl = v - w*l;
                vr = v + w*l;
                //r->set_lin_vel(make_pair(vl,vr));
            }
        }
        else{
            if ((ball_pos.y > centroid_atk.y+55) && (euclidean_dist(ball_pos,robot_pos) < 5)){
                cout << "1" << endl;
                vl = 0.6;
                vr = -0.6;
            }
            else if ((ball_pos.y < centroid_atk.y-55) && (euclidean_dist(ball_pos,robot_pos) < 5)){
                cout << "2" << endl;
                vl = -0.6;
                vr = 0.6;
            }
            else if (euclidean_dist(robot_pos,cph2->get_meta_aux()) < 5 && r->get_flag_fuzzy() == 1){
                cout << "3" << endl;
                vl = 0;
                vr = 0;
            }
            else if (euclidean_dist(robot_pos,cpo3->get_meta_aux()) < 5){// && r->get_flag_fuzzy() == 4){
                cout << "4" << endl;
                alpha = 90 - r->get_angle();
                alpha = ajusta_angulo(alpha);
                if (fabs(alpha) < 10 || fabs(alpha) > 170)
                    w = 0;
                else{
                    w = k*v_max*alpha/180;
                    vl = -w*l;
                    vr = w*l;
                }
            }
            else{
                alpha = theta - r->get_angle();
                alpha = ajusta_angulo(alpha);

                //cout << "angulo do robo: "<<r->get_angle()<<endl;

                if (fabs(alpha) <= limiar_theta){
                    w = k*v_max*alpha/180;
                    v = -v_max*fabs(alpha)/limiar_theta + v_max;
                }
                else{
                    alpha = ajusta_angulo(alpha+180);
                    w = k*v_max*alpha/180;
                    v = v_max*fabs(alpha)/limiar_theta - v_max;
                }

                //cout << "velocidade linear: " << v << endl;
                //cout << "velocidade angular: " << w << endl;

                vl = v-w*l;
                vr = v+w*l;
                //r->set_lin_vel(make_pair(vl,vr));
            }
        }
    }


Point Mover::convert_C_to_G(Point2d coord){
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
