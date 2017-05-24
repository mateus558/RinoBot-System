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
    /*calcula_velocidades(&selec_robot.r1,selec_iterador.Gandalf, &vels[0]);
    selec_robot.r1.set_lin_vel(vels[0]);

    calcula_velocidades(&selec_robot.r2,selec_iterador.Presto, &vels[1]);
    selec_robot.r2.set_lin_vel(vels[1]);

    calcula_velocidades(&selec_robot.r3,selec_iterador.Leona, &vels[2]);
    selec_robot.r3.set_lin_vel(vels[2]);*/


    //Pro terceiro robô - Leona
    calcula_velocidades(&selec_robot.r3,selec_iterador.cph,selec_iterador.cpo,selec_iterador.cph2,selec_iterador.cpo2, selec_iterador.cpo3, &vels[2]);
    selec_robot.r3.set_lin_vel(vels[2]);

    //Pro primeiro robô - Gandalf
    calcula_velocidades(&selec_robot.r1,selec_iterador.cph,selec_iterador.cpo,selec_iterador.cph2,selec_iterador.cpo2, selec_iterador.cpo3, &vels[0]);
    selec_robot.r1.set_lin_vel(vels[0]);

    //Pro segundo robô - Presto
    calcula_velocidades(&selec_robot.r2,selec_iterador.cph,selec_iterador.cpo,selec_iterador.cph2,selec_iterador.cpo2, selec_iterador.cpo3, &vels[1]);
    selec_robot.r2.set_lin_vel(vels[1]);


    //cout << vels[2].first << endl;


    emit emitRobots(selec_robot);
}

void Mover::set_to_select(Robot r1, Robot r2, Robot r3){
    selec_robot.r1 = r1;
    selec_robot.r2 = r2;
    selec_robot.r3 = r3;
}

void Mover::set_to_select_iterador(CPH *cph, CPO *cpo, CPH2 *cph2, CPO2 *cpo2, CPO3 *cpo3){
    /*selec_iterador.Gandalf = Gandalf;
    selec_iterador.Presto = Presto;
    selec_iterador.Leona = Leona;*/
    selec_iterador.cph = cph;
    selec_iterador.cpo = cpo;
    selec_iterador.cph2 = cph2;
    selec_iterador.cpo2 = cpo2;
    selec_iterador.cpo3 = cpo3;
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

pair<double, double> Mover::defenderGK(Robot r){
    double limiar = 0.04, bb = 0, rho, rho1, rho2, angulation,kw = 1;
    int ksi = 100, xtraRange = 50;
    Point2d goal, ball, b_pos, lx, ly, goaler, r_pos;
    Point def_centroid;
    pVector limits = def_area;
    pair<double, double> b_vel, vels;

    r_pos = r.get_pos()*10;
    b_pos = ball_pos * 10;
    def_centroid = (def_area[0] + def_area[1] + def_area[6] + def_area[7]) / 4;
    cout << def_centroid.x << " " << def_centroid.y << endl;
    def_centroid.x *= X_CONV_CONST * 10;
    def_centroid.y *= Y_CONV_CONST * 10;
    goal = def_centroid;
    ball = Point2d(def_centroid.x + limiar * 3, b_pos.y);
    lx = Point2d(limits[0].x * X_CONV_CONST * 10, limits[7].x * X_CONV_CONST * 10);
    ly = Point2d(limits[0].y * Y_CONV_CONST * 10, limits[7].y * Y_CONV_CONST * 10);

    if(b_pos.y < ly.y){
        cout << "oi" << endl;
        ball = Point2d(def_centroid.x + limiar * 3, def_area[7].y* Y_CONV_CONST * 10);
    }else if(b_pos.y < ly.x){
        cout << "oi1" << endl;
        ball = Point2d(def_centroid.x + limiar * 3, def_area[0].y* Y_CONV_CONST * 10);
    }
    cout << ly << endl;
    cout << def_area[7]* Y_CONV_CONST * 10 << " " << def_area[0]* Y_CONV_CONST * 10 << endl;

    //if(!team_changed){
    goaler = Point2d(goal.x , goal.y);
    cout << goaler << endl;
    cout << r_pos << endl;
    cout << "ly=" << ly << endl;
    cout << "lx=" << lx << endl;

    rho = euclidean_dist(goaler, r_pos);
    rho1 = euclidean_dist(goaler, b_pos);
    rho2 = euclidean_dist(ball, r_pos);
    cout << team_chang << endl;
   //if(team_chang){
        //b_vel.first = -ball_vel.first / 100;
    //}else{
        b_vel.first = ball_vel.first / 100;
    //}
    cout << "rho=" << rho << endl;

    b_vel.second = ball_vel.second / 100;
    angulation = (r.get_angle() < 0)?-90:90;

    if(rho1 < 750){
        cout << 1 << endl;
        if(b_vel.first < -0.1 || (b_vel.first < 0.05 && (b_pos.y < ly.x || b_pos.y > ly.y))){
            cout << 2 << endl;
            if(rho2 > ksi){
                cout << 7<<endl;
                vels = potDefense(0.0015, kw, r, ball, 0);
            }else{
                cout << 8 << endl;
                vels.first = 0;
                vels.second = set_ang(r.get_angle(), angulation, 1);
            }
        }else if(r_pos.x < lx.y && r_pos.y > ly.x && r_pos.y < ly.y && r_pos.y < ly.y + limiar){
            cout << 3 << endl;
            if(fabs(r.get_angle()) < 115 && fabs(r.get_angle()) > 65){
                vels.first = 0;
                vels.second = set_ang(r.get_angle(), angulation, 1);
            }else{
                vels.first = 0;
                vels.second = set_ang(r.get_angle(), angulation, 1);
            }
        }else{
            cout << 4 << endl;
            if(rho > ksi){
                vels = potDefense(0.0015, kw, r, goaler, 0);
            }else{
                if(fabs(r.get_angle()) < 115 && fabs(r.get_angle()) > 65){
                    vels.first = 0;
                    vels.second = set_ang(r.get_angle(), angulation, 1);
                }else{
                    vels.first = 0;
                    vels.second = set_ang(r.get_angle(), angulation, 1);
                }
            }
        }
    }else if(rho > ksi){
        cout << 5 << endl;
        vels = potDefense(0.0015, kw, r, goaler, 0);
    }else{
        cout << 6 << endl;
        vels.first = 0;
        vels.second = set_ang(r.get_angle(), angulation, 1);
    }

    //}
    return vels;
}

pair<double, double> Mover::potDefense(double katt, double kw, Robot r, Point2d obj, bool correct){
    Point2d pos_robot, b_pos, Fatt;
    pair<double, double> vels = make_pair(0,0), ball_v;
    double  var = 0.7, limiar = 0.04, diff = 16;//katt = 0.0015,,  kw = 0.07
    double erroY, dt, dy, drobo, alpha, r_angle, angle;

    vels.second = 0.0;
    b_pos = ball_pos / 100;
    ball_v.first = ball_vel.first / 100;
    ball_v.second = ball_vel.second / 100;
    pos_robot = r.get_pos() * 10;
    erroY = fabs(pos_robot.y - ball_pos.y)/100;
    /*r_angle = r.get_angle();
    cout << "pos_robot=" << pos_robot << endl;
    cout << "obj=" << obj << endl;NAVEGATION *robo
    Fatt = katt * (obj - pos_robot);
    cout << "Fatt="<<Fatt << endl;
    vels.first = sqrt(Fatt.x * Fatt.x + Fatt.y * Fatt.y);
    cout << "obj - pos_robot = " << (pos_robot-obj) << endl;
    vels.first = (vels.first > 0.6)?0.6:vels.first;
    cout << fabs(obj.y - pos_robot.y) << endl;
    if(fabs(obj.y - pos_robot.y) <= diff){
        vels.first = 0.0;
    }*/

    //if(correct){
        if(pos_robot.y > b_pos.y){
            cout << 1 << endl;
            if(ball_v.first == 0){    //Vx ball = 0
                if(ball_v.second == 0){   //Vy ball = 0
                    /*Fatt = katt * (obj - pos_robot);
                    vels.first = sqrt(Fatt.x * Fatt.x + Fatt.y * Fatt.y);
                    vels.first = (vels.first > 0.6)?0.6:vels.first;*/
                }else if(ball_v.second > 0){  //Vy ball > 0
                    vels.first = fabs(ball_v.second) + fabs(ball_v.first);
                }else{  //Vy ball < 0
                    vels.first = (erroY / var) * abs(ball_v.first);
                }
            }else if(ball_v.first < 0){
                if(ball_v.second == 0){   //Vy ball = 0
                    dt = (fabs(b_pos.x - pos_robot.x) + limiar) / ball_v.first;
                    dy = fabs(ball_v.second * dt);
                    drobo = fabs(b_pos.y - pos_robot.y) - dy;
                    vels.first = drobo / dt;
                }else if(ball_v.second > 0){  //Vy ball > 0
                    vels.first = fabs(ball_v.second) + fabs(ball_v.first);
                }else{  //Vy ball < 0
                    dt = (fabs(b_pos.x - pos_robot.x) + limiar) / ball_v.first;
                    dy = fabs(ball_v.second * dt);

                    if(dy > erroY){
                        vels.first = -(dy - erroY) / dt;
                    }else if(dy == erroY){
                        vels.first = 0;
                    }else{
                        //drobo = fabs(b_pos.y - pos_robot.y) -Point2d meta_aux; dy;
                        vels.first = fabs(drobo / dt);
                    }
                }
            }else{  //Vx > 0
                if(ball_v.second == 0){
                   /* Fatt = katt * (obj - pos_robot);
                    vels.first = sqrt(Fatt.x * Fatt.x + Fatt.y * Fatt.y);*/
                }else if(ball_v.second > 0.6){
                    vels.first = fabs(vels.second) + fabs(vels.first);
                }else{
                    vels.first = (erroY / 0.7) * fabs(vels.first);
                }
            }
        }/*else if(pos_robot.y < b_pos.y){
            if(ball_v.first == 0){    //Vx ball = 0
                if(ball_v.second == 0){   //Vy ball = 0
                    Fatt = katt * (obj - pos_robot);
                    vels.first = sqrt(Fatt.x * Fatt.x + Fatt.y * Fatt.y);
                    vels.first = (vels.first > 0.6)?0.6:vels.first;
                }else if(ball_v.second > 0){  //Vy ball > 0
                    vels.first = (erroY / var) * abs(ball_v.first);
                }else{  //Vy ball < 0
                    vels.first = fabs(ball_v.second) + fabs(ball_v.first);
                }
            }else if(ball_v.first < 0){
                if(ball_v.second == 0){   //Vy ball = 0
                    dt = (fabs(b_pos.x - pos_robot.x) + limiar) / ball_v.first;
                    dy = fabs(ball_v.second * dt);
                    drobo = fabs(b_pos.y - pos_robot.y) - dy;
                    vels.first = drobo / dt;
                }else if(ball_v.second > 0){  //Vy ball > 0
                    dt = (fabs(b_pos.x - pos_robot.x) + limiar) / ball_v.first;
                    dy = fabs(ball_v.second * dt);

                    if(dy > erroY){
                        vels.first = -(dy - erroY) / dt;
                    }else if(dy == erroY){
                        vels.first = 0;
                    }else{
                        drobo = fabs(b_pos.y - pos_robot.y) - dy;
                        vels.first = fabs(drobo) / dt;
                    }
                }else{  //Vy ball < 0
                    vels.first = fabs(ball_v.second) + fabs(ball_v.first);
                }
            }else{  //Vx > 0
                if(ball_v.second == 0){   //Vy ball = 0
                    Fatt = katt * (obj - pos_robot);
                    vels.first = sqrt(Fatt.x * Fatt.x + Fatt.y * Fatt.y);
                    vels.first = (vels.first > 0.6)?0.6:vels.first;
                }else if(ball_v.second > 0){  //Vy ball > 0
                    vels.first = (erroY / 0.7) * fabs(ball_v.first);
                }else{  //Vy ball < 0
                    vels.first = fabs(ball_v.second) + fabs(ball_v.first);
                }
            }
        }else if(pos_robot.y == b_pos.y){
            vels.first = 0;
        }else{
            cerr << "Error at goalkeeper function." << endl;
        }*/

        /*if(vels.first > 0){
            vels.first = (vels.first > 0.6)?0.6:vels.first;
        }else{
            vels.first = (vels.first > -0.6)?-0.6:vels.first;Point2d meta_aux;
        }*/
       // vels.first *= -1;
    //}
    //cout << "r_angle=" << r_angle << endl;

    //r_angle = (r_angle < 0)?r_angle*-1 + 180:r_angle;
    //cout << "r_angle=" << r_angle << endl;
    /*alpha = fmod(atan2(-Fatt.y, Fatt.x) * 180 / PI - r_angle, 360);
    cout << "atan=" << atan2(-Fatt.y, Fatt.x) * 180 / PI<< endl;
    cout << "atan-r_angle = " << atan2(-Fatt.y, Fatt.x) * 180 / PI - r_angle << endl;
    cout << alpha << endl;
    /*if(alpha > 180){
        alpha = alpha - 360;
    }

    if(fabs(alpha) > 90){
        vels.first *= -1;
        alpha = fmod(alpha+180, 360);
        if(alpha > 180){
            alpha = alpha - 360;
        }
    }*/
    //vels.second =(correct)?kw * (alpha*PI)/180:0;
    //vels.second = kw * (alpha*PI)/180;
    vels.second = 0;
    /*cout << "kw=" << kw << endl;
    cout << "w=" << vels.second << " alpha= " << alpha <<  " " << kw*(alpha * PI) / 180 << endl;
    cout << "v = "<<vels.first<<endl;*/
    return vels;
}

void Mover::goleiro(Robot r, pair<float, float> *vels){
    Point2d pos_robot, b_pos, ball_v;
    double erroY, dt, dy, drobo, limiar, var, r_angle;

    *vels = make_pair(0, 0);
    r_angle = r.get_angle();
    ball_v.x = ball_vel.first / 100;
    ball_v.y = ball_vel.second / 100;
    pos_robot = r.get_pos()*10;
    b_pos = ball_pos*10;
    erroY = fabs(pos_robot.y - ball_pos.y)/100;
    cout << b_pos << " " << (def_area[5].y * Y_CONV_CONST * 10) << endl;
    if(pos_robot.y > b_pos.y){
        cout << 8 << endl;
        if(ball_v.x == 0){    //Vx ball = 0
                cout << 2 << endl;
                if(ball_v.y == 0){   //Vy ball = 0
                /*Fatt = katt * (obj - pos_robot);
                vels->first = sqrt(Fatt.x * Fatt.x + Fatt.y * Fatt.y);
                vels->first = (vels->first > 0.6)?0.6:vels->first;*/
            }else if(ball_v.y > 0){  //Vy ball > 0
                cout << 3 << endl;
                vels->first = fabs(ball_v.y) + fabs(ball_v.x);
            }else{  //Vy ball < 0
                cout << 4 << endl;

                vels->first = (erroY / var) * abs(ball_v.x);
            }
        }else if(ball_v.x < 0){
            if(ball_v.y == 0){   //Vy ball = 0
                cout << 5 << endl;
                dt = (fabs(b_pos.x - pos_robot.x) + limiar) / ball_v.x;
                dy = fabs(ball_v.y * dt);
                drobo = fabs(b_pos.y - pos_robot.y) - dy;
                vels->first = drobo / dt;
            }else if(ball_v.y > 0){  //Vy ball > 0
                cout << 6 << endl;

                vels->first = fabs(ball_v.y) + fabs(ball_v.x);
            }else{  //Vy ball < 0
                cout << 7 << endl;

                dt = (fabs(b_pos.x - pos_robot.x) + limiar) / ball_v.x;
                dy = fabs(ball_v.y * dt);

                if(dy > erroY){
                    vels->first = (dy - erroY) / dt;
                }else if(dy == erroY){
                    vels->first = 0;
                }else{
                    drobo = fabs(b_pos.y - pos_robot.y) - dy;
                    vels->first = -fabs(drobo / dt);
                }
            }
        }else{  //Vx > 0

        }
    }else if(pos_robot.y < b_pos.y){
        cout << 1 << endl;
        if(ball_v.x == 0){    //Vx ball = 0
            if(ball_v.y == 0){   //Vy ball = 0
                /*Fatt = katt * (obj - pos_robot);
                vels->first = sqrt(Fatt.x * Fatt.x + Fatt.y * Fatt.y);
                vels->first = (vels->first > 0.6)?0.6:vels->first;*/
            }else if(ball_v.y > 0){  //Vy ball > 0
                vels->first = (erroY / var) * abs(ball_v.x);
            }else{  //Vy ball < 0
                vels->first = fabs(ball_v.y) + fabs(ball_v.x);
            }
        }else if(ball_v.x < 0){
            if(ball_v.y == 0){   //Vy ball = 0
                dt = (fabs(b_pos.x - pos_robot.x) + limiar) / ball_v.x;
                dy = fabs(ball_v.y * dt);
                drobo = fabs(b_pos.y - pos_robot.y) - dy;
                vels->first = drobo / dt;
            }else if(ball_v.y > 0){  //Vy ball > 0
                dt = (fabs(b_pos.x - pos_robot.x) + limiar) / ball_v.x;
                dy = fabs(ball_v.y * dt);

                if(dy > erroY){
                    vels->first = -(dy - erroY) / dt;
                }else if(dy == erroY){
                    vels->first = 0;
                }else{
                    drobo = fabs(b_pos.y - pos_robot.y) - dy;
                    vels->first = fabs(drobo) / dt;
                }
            }else{  //Vy ball < 0
                vels->first = fabs(ball_v.y) + fabs(ball_v.x);
            }
        }
    }else{
        vels->first = 0;
    }

    if(r_angle > 0){
        vels->first *= -1;
    }
    cout << vels->first << " " << vels->second << endl;
}

void Mover::calcula_velocidades(Robot *r, CPH *cph,CPO *cpo, CPH2 *cph2, CPO2 *cpo2, CPO3 *cpo3, pair<float, float> *vels){

    double v,w,theta,alpha;
    pair<float, float> vel;

    Point2d robot_pos = r->get_pos();
    Point robot_grid = convert_C_to_G(robot_pos);
    //cout << " Posicao do robo " << endl;
    //cout << " x: " << robot_pos.x << " y: " << robot_pos.y << endl;
   // cout << r->get_flag_fuzzy() << endl;


   if(r->get_flag_fuzzy() == 4){
        /*goleiro(*r, vels);
        v = vels->first;
        w = vels->second;
        v = 0;

        if(ball_pos.y < r->get_pos().y){
            w = -7;
        }else{
            w = 7;
        }
        theta = cpo3->get_direction(robot_grid);
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
        Point2d meta_aux;

        //cout << "velocidade linear: " << v << endl;
        //cout << "velocidade angular: " << w << endl;



        if((euclidean_dist(robot_pos, cpo3->get_meta_aux()) < 4) && (fabs(r->get_angle())> 80) && (fabs(r->get_angle()< 100))){
            v = 0;
            w = 0;
        }
        else if (euclidean_dist(robot_pos, cpo3->get_meta_aux()) < 4){
            v = 0;
            alpha = theta - 90;
            w = k*v_max*alpha/180;
        }
        vels->first = v - w*l;
        vels->second = v + w*l;*/

       theta = cpo3->get_direction(robot_grid);
       alpha = theta - r->get_angle();
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
       Point2d meta_aux;
       if((euclidean_dist(robot_pos, cpo3->get_meta_aux()) < 4) && (fabs(r->get_angle())> 80) && (fabs(r->get_angle()< 100))){
           v = 0;
           w = 0;
       }
       else if (euclidean_dist(robot_pos, cpo3->get_meta_aux()) < 4){
           v = 0;
           alpha = theta - 90;
           w = k*v_max*alpha/180;
       }
       vels->first = v - w*l;
       vels->second = v + w*l;


    }
    else{
       if (r->get_flag_fuzzy() == 0){
           theta = cph->get_direction(robot_grid);
       }
       else if (r->get_flag_fuzzy() == 1){
           theta = cph2->get_direction(robot_grid);
       }
       else if (r->get_flag_fuzzy() == 2){
           theta = cpo2->get_direction(robot_grid);
       }
       else if (r->get_flag_fuzzy() == 3){
           theta = cpo->get_direction(robot_grid);
       }
    }
    //cout << "decisao: " << r->get_flag_fuzzy();

        if (centroid_atk.x > ball_pos.x){
            if(r->get_flag_fuzzy() != 4){
                if ((ball_pos.y > centroid_atk.y+55) && (euclidean_dist(ball_pos,robot_pos) < 5)){
                    //cout << "1" << endl;
                    vels->first = -0.6;
                    vels->second = 0.6;
                }
                else if ((ball_pos.y < centroid_atk.y-55) && (euclidean_dist(ball_pos,robot_pos) < 5)){
                    //cout << "2" << endl;
                    vels->first = 0.6;
                    vels->second = -0.6;
                }
                else if (euclidean_dist(robot_pos,cph2->get_meta_aux()) < 5 && r->get_flag_fuzzy() == 1){
                    vels->first = 0;
                    vels->second = 0;
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

                    vels->first = v - w*l;
                    vels->second = v + w*l;
                    //r->set_lin_vel(make_pair(vl,vr));
                }
            }
        }else{
            if(r->get_flag_fuzzy() != 4){
                if ((ball_pos.y > centroid_atk.y+55) && (euclidean_dist(ball_pos,robot_pos) < 5)){
                    vels->first = 0.6;
                    vels->second = -0.6;
                }
                else if ((ball_pos.y < centroid_atk.y-55) && (euclidean_dist(ball_pos,robot_pos) < 5)){
                    vels->first = -0.6;
                    vels->second = 0.6;
                }
                else if (euclidean_dist(robot_pos,cph2->get_meta_aux()) < 5 && r->get_flag_fuzzy() == 1){
                    vels->first = 0;
                    vels->second = 0;
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

                    vels->first = v-w*l;
                    vels->second = v+w*l;
                    //cout << vl << " " << vr << endl;
                    //r->set_lin_vel(make_pair(vl,vr));
                }
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
