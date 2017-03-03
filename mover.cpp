#include <iostream>
#include <iomanip>
#include <cmath>
#include "mover.h"
#include "robot.h"
#include "utils.h"

using namespace std;
double limiar_theta = 90;
double v_max = 0.6;
double w_max = 8;
double k = (w_max/v_max);
double l = 0.0275;

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


    //Pro primeiro robô - Gandalf
    calcula_velocidades(&selec_robot.r1,selec_iterador.cph,selec_iterador.cpo);
    selec_robot.r1.set_lin_vel(make_pair(vl,vr));
    //cout << "Vel left: " << vl << endl;
    //cout << "Vel right: " << vr << endl;

    /*float velocidade = selec_robot.r1->get_l_vel();
    float veld = selec_robot.r1->get_r_vel();
    cout << "Vel: "<<velocidade << endl;
    cout << "Ver: "<<veld << endl;*/

    //selec_robot.r1.open_serial();

    /*cout<<selec_robot.r1.get_channel()<<endl;
    cout<<selec_robot.r2.get_channel()<<endl;
    cout<<selec_robot.r3.get_channel()<<endl;*/

    //Robot::send_velocities(selec_robot.r1.get_channel(), make_pair(selec_robot.r1.get_r_vel(), selec_robot.r1.get_l_vel()));


    //Pro segundo robô - Presto
    //calcula_velocidades(selec_robot.r2,selec_iterador.cph,selec_iterador.cpo);
    //selec_robot.r2->send_velocities(selec_robot.r2->get_channel(), selec_robot.r2->get_lin_vel());

    emit emitRobots(selec_robot);
}

void Mover::set_to_select(Robot r1, Robot r2, Robot r3){
    selec_robot.r1 = r1;
    selec_robot.r2 = r2;
    selec_robot.r3 = r3;
}

void Mover::set_to_select_iterador(CPH *cph, CPO *cpo){
    selec_iterador.cph = cph;
    selec_iterador.cpo = cpo;
}

void Mover::calcula_velocidades(Robot *r, CPH *cph, CPO *cpo){

    double v,w,theta,alpha;
    Point2d robot_pos = r->get_pos();
    Point robot_grid = convert_C_to_G(robot_pos);
    //cout << " Posicao do robo " << endl;
    //cout << " x: " << robot_pos.x << " y: " << robot_pos.y << endl;

    if(r->get_flag_fuzzy() == 4){
        cout<<"Sou Goleiro!"<<endl;
    }
    else{

        /*if(r->get_flag_fuzzy() == 0){
             //theta = cph->get_direction(robot_grid);
            cout << "Rodrigay!" << endl;
        }
        else if(r->get_flag_fuzzy() == 1){
             //theta = cph2->get_direction(robot_grid);
            cout << "gabigay!" << endl;
        }
        else if(r->get_flag_fuzzy() == 2){
             //theta = cpo2->get_direction(robot_grid);
            cout << "JoaoTraveco!" << endl;
        }
        else if(r->get_flag_fuzzy() == 3){
             //theta = cpo->get_direction(robot_grid);
            cout << "Fredtransex!" << endl;
        }*/


        theta = cph->get_direction(robot_grid);
        cout << "angulo do grid: " << theta << endl;

        alpha = theta - r->get_angle();
        alpha = ajusta_angulo(alpha);

        cout << "angulo do robo: "<<r->get_angle()<<endl;

        if (fabs(alpha) <= limiar_theta){
            w = k*v_max*alpha/180;
            v = -v_max*fabs(alpha)/limiar_theta + v_max;
        }
        else{
            alpha = ajusta_angulo(alpha+180);
            w = k*v_max*alpha/180;
            v = v_max*fabs(alpha)/limiar_theta - v_max;
        }

        /*if(w < 45){
            w *= 2;
        }
        if(w < 22.5){
            w *= 2;
        }*/

        //cout << "velocidade linear: " << v << endl;
        //cout << "velocidade angular: " << w << endl;

        vl = v-w*l;
        vr = v+w*l;

        //r->set_lin_vel(make_pair(vl,vr));
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
