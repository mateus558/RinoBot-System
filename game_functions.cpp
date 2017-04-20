#include "game_functions.h"
#include <QThread>
#include <QMutex>
#include <vector>
#include "robot.h" //Robot class
#include "utils.h" //Utils library
#include "fuzzy.h"
#include "mover.h"
#include "navegation.h"
#include "iostream"

using namespace std;

GAME_FUNCTIONS::GAME_FUNCTIONS()
{
    stop = true;
    game_functions_initialized = false;

}

void GAME_FUNCTIONS::run(){
    if (calc_Gandalf){
        set_game_function(&selec_robot.r1);
    }
    else if (calc_Presto){
        set_game_function(&selec_robot.r2);
    }
    else if (calc_Leona){
        set_game_function(&selec_robot.r3);
    }
    flag_finish_functions = true;
}

void GAME_FUNCTIONS::set_to_select(Robot r1, Robot r2, Robot r3){
    selec_robot.r1 = r1;
    selec_robot.r2 = r2;
    selec_robot.r3 = r3;
}void goalkeeper(NAVEGATION *);
void defender(NAVEGATION *);
void defensive_midfielder(NAVEGATION *);
void ofensive_midfielder(NAVEGATION *);
void striker(NAVEGATION *);

void GAME_FUNCTIONS::set_to_select_iterador(NAVEGATION *Gandalf, NAVEGATION *Presto, NAVEGATION *Leona){
    selec_iterador.Gandalf = Gandalf;
    selec_iterador.Presto = Presto;
    selec_iterador.Leona = Leona;
}

void GAME_FUNCTIONS::set_enemy_pos(p2dVector enemy_pos){
    this->enemy_pos = enemy_pos;
}

void GAME_FUNCTIONS::set_team_pos(p2dVector team_pos){
    this->team_pos = team_pos;
}

void GAME_FUNCTIONS::set_ball_pos(Point2d ball_pos){
    this->ball_pos = ball_pos;
}

void GAME_FUNCTIONS::set_ball_vel(pair<double, double> ball_vel){
    this->ball_vel = ball_vel;
}

void GAME_FUNCTIONS::set_def_area(pVector def_area){
    this->def_area = def_area;
}

void GAME_FUNCTIONS::set_centroid_atk(Point2d centroid_atk){
    this->centroid_atk = centroid_atk;
}

void GAME_FUNCTIONS::set_centroid_def(Point2d centroid_def){
    this->centroid_def = centroid_def;
}

Point GAME_FUNCTIONS::convert_C_to_G(Point2d coord){
    Point i;

    coord.x = int(coord.x) + 5;
    coord.y = int(coord.y) + 5;

    if(coord.x / dx < 35 && coord.x > 0){
        i.x = coord.x / dx;
    }else if(coord.x / dx >= 35){
        i.x = 34;
    }else if(coord.x / dx <= 0){
        i.x = 1;
    }

    if(coord.y / dy < 27 && coord.y > 0){
        i.y = coord.y / dy;
    }else if(coord.y / dy >= 27){
        i.y = 26;
    }else if(coord.y / dy <= 0){
        i.y = 1;
    }

    return i;
}

void GAME_FUNCTIONS::set_game_function(Robot *r){
    NAVEGATION *robo;
    /*cout << 4 << endl;
    if (r->get_channel() == selec_robot.r1.get_channel()){
        cout << 5 << endl;
        robo = selec_iterador.Gandalf;
    }
    else if (r->get_channel() == selec_robot.r2.get_channel()){
        robo = selec_iterador.Presto;
    }
    else if (r->get_channel() == selec_robot.r3.get_channel()){
        robo = selec_iterador.Leona;
    }*/
    if (calc_Gandalf){
        robo = selec_iterador.Gandalf;
    }
    else if (calc_Presto){
        robo = selec_iterador.Presto;
    }
    else if (calc_Leona){
        robo = selec_iterador.Leona;
    }

    if (r->get_flag_fuzzy() == 0){
        robo->print_grid();
        //defender(robo);
    }
    else if (r->get_flag_fuzzy() == 1){
        //defensive_midfielder(robo);
    }
    else if (r->get_flag_fuzzy() == 2){
        //ofensive_midfielder(robo);
    }
    else if (r->get_flag_fuzzy() == 3){
        //striker(robo);
    }
    else if (r->get_flag_fuzzy() == 4){
        //goalkeeper(robo);
    }

}

void GAME_FUNCTIONS::set_calc_Gandalf(bool var){
    this->calc_Gandalf = var;
}

void GAME_FUNCTIONS::set_calc_Presto(bool var){
    this->calc_Presto = var;
}

void GAME_FUNCTIONS::set_calc_Leona(bool var){
    this->calc_Leona = var;
}

void GAME_FUNCTIONS::goalkeeper(NAVEGATION *robo){
    //fazer depois
}

void GAME_FUNCTIONS::defender(NAVEGATION *robo){
    //if(!grid_initialized){
        robo->init_grid();
    //}

    for(i = 0; i < 3; ++i){
        if(enemy_pos[i].x > 0 && enemy_pos[i].y > 0){
            enemy_pos_grid[i] = convert_C_to_G(enemy_pos[i]);
            //cout<<"Inimigo "<<enemy_pos_grid[i].x<<" "<<enemy_pos_grid[i].y<<endl;
            if(enemy_pos_grid[i].x>0 && enemy_pos_grid[i].y>0)
                robo->set_potential(enemy_pos_grid[i].y, enemy_pos_grid[i].x, 1);
        }else{
            //tratar posição dos inimigos aqui
        }

        if(team_pos[i].x > 0 && team_pos[i].y > 0){
            team_pos_grid[i] = convert_C_to_G(team_pos[i]);
            //cout<<"Amigo "<<team_pos_grid[i].x<<" "<<team_pos_grid[i].y<<endl;
        }else{
            //tratar posição dos miguxos aqui
        }
    }

    double def_area_x = def_area[0].x*X_CONV_CONST;
    double def_area_y1 = def_area[1].y*Y_CONV_CONST;
    double def_area_y2 = def_area[6].y*Y_CONV_CONST;
    Point meta;
    Point2d meta2d;
    meta2d.y = centroid_def.y;



    if (centroid_atk.x > ball_pos.x){
        if(ball_pos.x < def_area_x && ball_pos.y < def_area_y1 && ball_pos.y > def_area_y2){
            //cout << "Reconheceu a area de defesa" << endl;


            if(ball_pos.x > 0 && ball_pos.y > 0){
                meta2d.x = centroid_def.x + 35;
                meta = convert_C_to_G(meta2d);
                //cout<<"Bola "<<ball_pos_grid.x<<" "<<ball_pos_grid.y<<endl;
                if (meta.x > 0 && meta.y > 0)
                    robo->set_potential(meta.y, meta.x, 0);
            }else{
                //tratar a meta aqui
            }

        }else{
            if(ball_pos.x > 0 && ball_pos.y > 0){
                ball_pos_grid = convert_C_to_G(ball_pos);
                //cout<<"Bola "<<ball_pos_grid.x<<" "<<ball_pos_grid.y<<endl;
                if (ball_pos_grid.x > 0 && ball_pos_grid.y > 0)
                    robo->set_potential(ball_pos_grid.y, ball_pos_grid.x, 0);
            }else{
                //tratar a bola aqui
            }

            if(ball_pos.x > 0 && ball_pos.y > 0){
                ball_pos_grid = convert_C_to_G(ball_pos);
                //cout<<"Bola "<<ball_pos_grid.x<<" "<<ball_pos_grid.y<<endl;
                if(ball_pos_grid.x+1 < 28 && ball_pos_grid.y+1 < 28){
                    robo->set_potential(ball_pos_grid.y, ball_pos_grid.x+1, 1);
                    robo->set_potential(ball_pos_grid.y+1, ball_pos_grid.x+1, 1);
                    robo->set_potential(ball_pos_grid.y-1, ball_pos_grid.x+1, 1);
                }
            }else{
                //tratar a barreira aqui
            }
        }
    }else{
        if(ball_pos.x > def_area_x && ball_pos.y < def_area_y1 && ball_pos.y > def_area_y2){
            if(ball_pos.x > 0 && ball_pos.y > 0){
                meta2d.x = centroid_def.x - 35;
                meta = convert_C_to_G(meta2d);
                //cout<<"Bola "<<ball_pos_grid.x<<" "<<ball_pos_grid.y<<endl;
                if (meta.x > 0 && meta.y > 0)
                    robo->set_potential(meta.y, meta.x, 0);
            }else{
                //tratar a meta aqui
            }
        }else{
            if(ball_pos.x > 0 && ball_pos.y > 0){
                ball_pos_grid = convert_C_to_G(ball_pos);
                //cout<<"Bola "<<ball_pos_grid.x<<" "<<ball_pos_grid.y<<endl;
                if (ball_pos_grid.x > 0 && ball_pos_grid.y > 0)
                    robo->set_potential(ball_pos_grid.y, ball_pos_grid.x, 0);
            }else{
                //tratar a bola aqui
            }

            if(ball_pos.x > 0 && ball_pos.y > 0){
                ball_pos_grid = convert_C_to_G(ball_pos);
                //cout<<"Bola "<<ball_pos_grid.x<<" "<<ball_pos_grid.y<<endl;
                if(ball_pos_grid.y+1 < 28){
                    robo->set_potential(ball_pos_grid.y, ball_pos_grid.x-1, 1);
                    robo->set_potential(ball_pos_grid.y+1, ball_pos_grid.x-1, 1);
                    robo->set_potential(ball_pos_grid.y-1, ball_pos_grid.x-1, 1);
                }
            }else{
                //tratar a barreira aqui
            }
        }
    }
    while(robo->iterator_cph()>1E-6);
    robo->set_direction();

}

void GAME_FUNCTIONS::defensive_midfielder(NAVEGATION *robo){
    //if(!grid_initialized){
        robo->init_grid();
    //}
    Point2d meta_aux;

    for(i = 0; i < 3; ++i){
        if(enemy_pos[i].x > 0 && enemy_pos[i].y > 0){
            enemy_pos_grid[i] = convert_C_to_G(enemy_pos[i]);
            //cout<<"Inimigo "<<enemy_pos_grid[i].x<<" "<<enemy_pos_grid[i].y<<endl;
            robo->set_potential(enemy_pos_grid[i].y, enemy_pos_grid[i].x, 1);
        }else{
            //tratar posição dos inimigos aqui
        }

        if(team_pos[i].x > 0 && team_pos[i].y > 0){
            team_pos_grid[i] = convert_C_to_G(team_pos[i]);
            //cout<<"Amigo "<<team_pos_grid[i].x<<" "<<team_pos_grid[i].y<<endl;
        }else{
            //tratar posição dos miguxos aqui
        }
    }

    //cout<<"Bola "<<ball_pos_grid.x<<" "<<ball_pos_grid.y<<endl;
    Point2d meta;

    if(ball_pos.x > 0 && ball_pos.y > 0){
        if ((ball_pos.y > centroid_def.y+55 || ball_pos.y < centroid_def.y-55) && fabs(ball_pos.x - centroid_def.x) < 70){
            //cout << 1 << endl;
            ball_pos_grid = convert_C_to_G(ball_pos);
            if (ball_pos_grid.x > 0 && ball_pos_grid.y > 0){
                //cout << 2 << endl;
                //cout<<"Meta: "<<ball_pos_grid.x<<" "<<ball_pos_grid.y<<endl;
                robo->set_potential(ball_pos_grid.y, ball_pos_grid.x, 0);
                meta_aux = ball_pos;
                /*if(ball_pos.x < centroid_atk.x){
                    set_potential(ball_pos_grid.y, ball_pos_grid.x+1, 1);
                    set_potential(ball_pos_grid.y+1, ball_pos_grid.x+1, 1);
                    set_potential(ball_pos_grid.y-1, ball_pos_grid.x+1, 1);
                }else{
                    set_potential(ball_pos_grid.y, ball_pos_grid.x-1, 1);
                    set_potential(ball_pos_grid.y+1, ball_pos_grid.x-1, 1);
                    set_potential(ball_pos_grid.y-1, ball_pos_grid.x-1, 1);
                }*/
            }
        }else{
            Point2d vec_ball_def = centroid_def - ball_pos;
            double aux = (0.45/150)*euclidean_dist(centroid_def,ball_pos);

            meta = ball_pos + vec_ball_def*aux;
            //cout << "Meta: " << endl;
            //cout << " x: " << meta.x << " y: " << meta.y << endl;
            if(meta.x > 0 && meta.y > 0){
                 Point meta_pos_grid = convert_C_to_G(meta);
                 //cout<<"Bola "<<ball_pos_grid.x<<" "<<ball_pos_grid.y<<endl;
                 if (meta_pos_grid.x > 0 && meta_pos_grid.y > 0)
                     robo->set_potential(meta_pos_grid.y, meta_pos_grid.x, 0);
            }else{
                //tratar a meta aqui
            }
            meta_aux = meta;
        }
    }else{
        //tratar a bola aqui
    }

    /*if(ball_pos.x > 0 && ball_pos.y > 0){
        ball_pos_grid = convert_C_to_G(ball_pos);
        //cout<<"Bola "<<ball_pos_grid.x<<" "<<ball_pos_grid.y<<endl;
        set_potential(ball_pos_grid.y, ball_pos_grid.x, 0);
    }else{
        //tratar a bola aqui
    }*/
    while(robo->iterator_cph()>1E-6);
    robo->set_direction();
}

void GAME_FUNCTIONS::ofensive_midfielder(NAVEGATION *robo){
    Point2d eixo_x(1.0,0.0);
    Point2d meta2d;
    Point meta;
    //if(!grid_initialized){
        robo->init_grid();
    //}

    for(i = 0; i < 3; ++i){
        if(enemy_pos[i].x > 0 && enemy_pos[i].y > 0){
            enemy_pos_grid[i] = convert_C_to_G(enemy_pos[i]);
            //cout<<"Inimigo "<<enemy_pos_grid[i].x<<" "<<enemy_pos_grid[i].y<<endl;
            if(enemy_pos_grid[i].x>0 && enemy_pos_grid[i].y>0)
                robo->set_potential(enemy_pos_grid[i].y, enemy_pos_grid[i].x, 1);
        }else{
            //tratar posição dos inimigos aqui
        }

        if(team_pos[i].x > 0 && team_pos[i].y > 0){
            team_pos_grid[i] = convert_C_to_G(team_pos[i]);
            //cout<<"Amigo "<<team_pos_grid[i].x<<" "<<team_pos_grid[i].y<<endl;
        }else{
            //tratar posição dos miguxos aquieuclidean_dist(ball_pos,enemy_prox
        }
    }

    if(ball_pos.x > 0 && ball_pos.y > 0){
        if (fabs(ball_pos.x - centroid_def.x) < 40){
            robo->set_epsilon(0);
            robo->set_orientation(0);
            if (ball_pos.x < centroid_atk.x){
                meta2d.x = centroid_def.x + 75;
                meta2d.y  = centroid_def.y;
                meta = convert_C_to_G(meta2d);
                if(meta.x > 0 && meta.y > 0){
                         robo->set_potential(meta.y, meta.x, 0);
                }else{
                    //tratar a meta aqui
                }
            }
            else{
                meta2d.x = centroid_def.x - 75;
                meta2d.y  = centroid_def.y;
                meta = convert_C_to_G(meta2d);
                if(meta.x > 0 && meta.y > 0){
                         robo->set_potential(meta.y, meta.x, 0);
                }else{
                    //tratar a meta aqui
                }
            }
        }
        else{
            //Utiliza o robo amigo mais próximo para definição do epsilon
            Point2d team_prox;
            if ((euclidean_dist(ball_pos,team_pos[0]) <= euclidean_dist(ball_pos,team_pos[1])) && (euclidean_dist(ball_pos,team_pos[0]) <= euclidean_dist(ball_pos,team_pos[2])))
                team_prox = team_pos[0];
            else if (euclidean_dist(ball_pos,team_pos[1]) <= euclidean_dist(ball_pos,team_pos[2]))
                team_prox = team_pos[1];
            else
                team_prox = team_pos[2];

            robo->set_epsilon(0.3 + euclidean_dist(team_prox,ball_pos)/200);
           // cout << " epsilon: " << e << endl;

            ball_pos_grid = convert_C_to_G(ball_pos);
             //cout<<"Bola "<<ball_pos_grid.x<<" "<<ball_pos_grid.y<<endl;
            if (ball_pos_grid.x > 0 && ball_pos_grid.y > 0)
                robo->set_potential(ball_pos_grid.y, ball_pos_grid.x, 0);

            // Calculo do angulo de orientacao usar no ataque leve para dribles
            //Corrige Posicionamento
            ball_pos.y = -ball_pos.y;
            centroid_atk.y = -centroid_atk.y;

            //Calcula angulo entre a bola e o gol de ataque
            Point2d vec_ball_atk = centroid_atk-ball_pos;
            double ang_ball_atk = angle_two_points(vec_ball_atk,eixo_x);
            if (vec_ball_atk.y < 0)
                    ang_ball_atk = -ang_ball_atk;
            //ajusta angulos para menores que 180 e maiores que -180
            if (ang_ball_atk > 180) ang_ball_atk = ang_ball_atk - 360;
            else if (ang_ball_atk < -180) ang_ball_atk = ang_ball_atk + 360;
            //cout << "Angulo bola atk: " << ang_ball_atk << endl;
            robo->set_orientation(ang_ball_atk);
            //orientation = 45;
            //Corrige Posicionamento novamente
            ball_pos.y = -ball_pos.y;
            centroid_atk.y=-centroid_atk.y;
        }

    }else{
        //tratar a bola aqui
    }

    /*if (drible)
    {
    //Define o enimigo mais proximo
    Point2d enemy_prox;
    enemy_prox.y = -enemy_prox.y;
    if ((euclidean_dist(ball_pos,enemy_pos[0]) <= euclidean_dist(ball_pos,enemy_pos[1])) && (euclidean_dist(ball_pos,enemy_pos[0]) <= euclidean_dist(ball_pos,enemy_pos[2])))
        enemy_prox = enemy_pos[0];
    else if (euclidean_dist(ball_pos,enemy_pos[1]) <= euclidean_dist(ball_pos,enemy_pos[2]))
        enemy_prox = enemy_pos[1];
    else
        enemy_prox = enemy_pos[2];
    //Calcula o angulo entre a bola e o inimigo mais proximo
    Point2d vec_ball_enemy = enemy_prox-ball_pos;
    double ang_ball_enemy = angle_two_points(vec_ball_enemy,eixo_x);
    //Corrige o angulo
    if (vec_ball_enemy.y < 0)
            ang_ball_enemy = -ang_ball_enemy;
    //ajusta angulos para menores que 180 e maiores que -180
    if (ang_ball_enemy > 180) ang_ball_enemy = ang_ball_enemy - 360;
    else if (ang_ball_enemy < -180) ang_ball_enemy = ang_ball_enemy + 360;
    //cout << "Angulo bola enemy: " << ang_ball_enemy << endl;

    //Calcula a orientacao como base na bola, inimigo mais proximo e gol adversario
    if ((ang_ball_enemy-ang_ball_atk) > 0)
        orientation = ang_ball_atk - 90*cos((3.1415/180)*(ang_ball_enemy-ang_ball_atk))*pow(2.7183,-0.04620*euclidean_dist(ball_pos,enemy_prox));
    else
        orientation = ang_ball_atk + 90*cos((3.1415/180)*(ang_ball_enemy-ang_ball_atk))*pow(2.7183,-0.04620*euclidean_dist(ball_pos,enemy_prox));
    }*/

   // cout<<"Orientação: "<<orientation<<endl;
    while(robo->iterator_cpo()>1E-6);
    robo->set_direction();
}

void GAME_FUNCTIONS::striker(NAVEGATION *robo){
    Point2d eixo_x(1.0,0.0);
    //if(!grid_initialized){
        robo->init_grid();
    //}
    for(i = 0; i < 3; ++i){
        if(enemy_pos[i].x > 0 && enemy_pos[i].y > 0){
            enemy_pos_grid[i] = convert_C_to_G(enemy_pos[i]);
            //cout<<"Inimigo "<<enemy_pos_grid[i].x<<" "<<enemy_pos_grid[i].y<<endl;
            if(enemy_pos_grid[i].x>0 && enemy_pos_grid[i].y>0)
                robo->set_potential(enemy_pos_grid[i].y, enemy_pos_grid[i].x, 1);
        }else{
            //tratar posição dos inimigos aqui
        }

        if(team_pos[i].x > 0 && team_pos[i].y > 0){
            team_pos_grid[i] = convert_C_to_G(team_pos[i]);
            //cout<<"Amigo "<<team_pos_grid[i].x<<" "<<team_pos_grid[i].y<<endl;
        }else{
            //tratar posição dos miguxos aquieuclidean_dist(ball_pos,enemy_prox
        }
    }

    if(ball_pos.x > 0 && ball_pos.y > 0){
        //Utiliza o robo amigo mais próximo para definição do epsilon
        Point2d team_prox;
        if ((euclidean_dist(ball_pos,team_pos[0]) <= euclidean_dist(ball_pos,team_pos[1])) && (euclidean_dist(ball_pos,team_pos[0]) <= euclidean_dist(ball_pos,team_pos[2])))
            team_prox = team_pos[0];
        else if (euclidean_dist(ball_pos,team_pos[1]) <= euclidean_dist(ball_pos,team_pos[2]))
            team_prox = team_pos[1];
        else
            team_prox = team_pos[2];

        robo->set_epsilon(0.3 + euclidean_dist(team_prox,ball_pos)/250);
       // cout << " epsilon: " << e << endl;

        // Calculo do angulo de orientacao usar no ataque leve para dribles
        //Corrige Posicionamento
        ball_pos.y = -ball_pos.y;
        centroid_atk.y = -centroid_atk.y;

        //Calcula angulo entre a bola e o gol de ataque
        Point2d vec_ball_atk = centroid_atk-ball_pos;
        double ang_ball_atk = angle_two_points(vec_ball_atk,eixo_x);
        if (vec_ball_atk.y < 0)
                ang_ball_atk = -ang_ball_atk;
        //ajusta angulos para menores que 180 e maiores que -180
        if (ang_ball_atk > 180) ang_ball_atk = ang_ball_atk - 360;
        else if (ang_ball_atk < -180) ang_ball_atk = ang_ball_atk + 360;
        //cout << "Angulo bola atk: " << ang_ball_atk << endl;
        robo->set_orientation(ang_ball_atk);
        //orientation = 45;
        //Corrige Posicionamento novamente
        ball_pos.y = -ball_pos.y;
        centroid_atk.y=-centroid_atk.y;

        Point meta;
        if (euclidean_dist(ball_pos,team_prox) < 5){
            if (centroid_atk.x > 0 && centroid_atk.y > 0){
                meta = convert_C_to_G(centroid_atk);
                robo->set_epsilon(0);
                //cout<<"Bola "<<ball_pos_grid.x<<" "<<ball_pos_grid.y<<endl;
                if (meta.x > 0 && meta.y > 0)
                    robo->set_potential(meta.y, meta.x, 0);
            }else{
                //tratar o gol aqui
            }

        }else{
            ball_pos_grid = convert_C_to_G(ball_pos);
             //cout<<"Bola "<<ball_pos_grid.x<<" "<<ball_pos_grid.y<<endl;
            if (ball_pos_grid.x > 0 && ball_pos_grid.y > 0)
                robo->set_potential(ball_pos_grid.y, ball_pos_grid.x, 0);
        }
    }else{
        //tratar a bola aqui
    }
    while(robo->iterator_cpo()>1E-6);
    robo->set_direction();
}

bool GAME_FUNCTIONS::get_flag_finish(){
    return this->flag_finish_functions;
}

void GAME_FUNCTIONS::zera_flag_finish(){
    flag_finish_functions = false;
}

void GAME_FUNCTIONS::Play(){
    if(isStopped())
        stop = false;
   start();
}

bool GAME_FUNCTIONS::is_running(){
    return isRunning();
}

void GAME_FUNCTIONS::Stop(){
    stop = true;
}

bool GAME_FUNCTIONS::isStopped() const
{
    return this->stop;
}

void GAME_FUNCTIONS::msleep(int ms){
    /*struct timespec ts = {ms / 1000, (ms % 1000) * 1000 * 1000};
    nanosleep(&ts, NULL);*/
}

GAME_FUNCTIONS::~GAME_FUNCTIONS(){

}
