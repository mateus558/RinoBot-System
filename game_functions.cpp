#include <iostream>
#include <iomanip>
#include <cmath>
#include "game_functions.h"
#include "robot.h"
#include "utils.h"

using namespace std;


Serial Game_functions::serial;

Game_functions::Game_functions()
{
    stop = true;
    game_functions_initialized = false;
    enemy_pos_grid = pVector(3);
    team_pos_grid = pVector(3);
    team_chang = false;
    vels.assign(3, make_pair(0, 0));

    i = 0;
    stop = true;
    grid_initialized = vel_Computed = false;
    enemy_pos_grid = pVector(3);
    team_pos_grid = pVector(3);
    pGrid = dMatrix(28, vector<double>(36, 0.0));
    tGrid = dMatrix(28, vector<double>(36, 0.0));
}

Game_functions::~Game_functions(){

}

bool Game_functions::isStopped() const
{
    return this->stop;
}

void Game_functions::Play(){
    if(isStopped())
        stop = false;
   start();
}

void Game_functions::Stop(){
    stop = true;
}

bool Game_functions::is_running(){
    return isRunning();
}

void Game_functions::msleep(int ms){
    struct timespec ts = {ms / 1000, (ms % 1000) * 1000 * 1000};
    nanosleep(&ts, NULL);
}

void Game_functions::run(){
    if(!game_functions_initialized){
        //init_game_functions();
        game_functions_initialized = true;
    }
    //Pro terceiro robô - Leona
     if (calc_Leona){
        int r3_flag = selec_robot.r3.get_flag_fuzzy();
        //cout << "Leona: " << r3_flag << endl;
        switch (r3_flag){
            case 0:
                defender(&selec_robot.r3, 2, &vels[2]);
                break;
            case 1:
                defensive_midfielder(&selec_robot.r3, 2, &vels[2]);
                break;
            case 2:
                ofensive_midfielder(&selec_robot.r3, 2, &vels[2]);
                break;
            case 3:
                striker(&selec_robot.r3, 2, &vels[2]);
                break;
            case 4:
                goalkeeper(&selec_robot.r3, 2, &vels[2]);
                break;
        }
        /*selec_robot.r3.set_lin_vel(vels[2]);
        selec_robot.flags[2] = true;*/
    }

    //Pro primeiro robô - Gandalf    
    if(calc_Gandalf)
    {
        int r1_flag = selec_robot.r1.get_flag_fuzzy();
        //cout << "Gandalf: " << r1_flag << endl;
        switch (r1_flag){
            case 0:
                defender(&selec_robot.r1, 0, &vels[0]);
                break;
            case 1:
                defensive_midfielder(&selec_robot.r1, 0, &vels[0]);
                break;
            case 2:
                ofensive_midfielder(&selec_robot.r1, 0, &vels[0]);
                break;
            case 3:
                striker(&selec_robot.r1, 0, &vels[0]);
                break;
            case 4:
                goalkeeper(&selec_robot.r1, 0, &vels[0]);
                break;
        }
        //cout << "Gandalf metax: " << meta.x << " y: " << meta.y << endl;
        /*selec_robot.r1.set_lin_vel(vels[0]);
        selec_robot.flags[0] = true;*/
    }

    //Pro segundo robô - Presto
    if(calc_Presto)
    {
        int r2_flag = selec_robot.r2.get_flag_fuzzy();
        //cout << "Presto: " << r2_flag << endl;
        switch (r2_flag){
            case 0:
                defender(&selec_robot.r2, 1, &vels[1]);
                break;
            case 1:
                defensive_midfielder(&selec_robot.r2, 1, &vels[1]);
                break;
            case 2:
                ofensive_midfielder(&selec_robot.r2, 1, &vels[1]);
                break;
            case 3:
                striker(&selec_robot.r2, 1, &vels[1]);
                break;
            case 4:
                goalkeeper(&selec_robot.r2, 1, &vels[1]);
            break;
        }
        //print_grid();
        //cout << "Presto metax: " << meta.x << " y: " << meta.y << endl;
        /*selec_robot.r2.set_lin_vel(vels[1]);
        selec_robot.flags[1] = true;*/
    }

    flag_finish_functions = true;

    //emit emitRobots(selec_robot);
}

void Game_functions::set_to_select(Robot r1, Robot r2, Robot r3){
    selec_robot.r1 = r1;
    selec_robot.r2 = r2;
    selec_robot.r3 = r3;
}

void Game_functions::team_changed(){
    if(!team_chang){
        team_chang = true;
    }else{
        team_chang = false;
    }
}

void Game_functions::return2goal(){
    Point2d meta;
    Point meta_grid;
    if(ball_pos.x > 0 && ball_pos.y > 0){
                if (ball_pos.x < centroid_atk.x){
                    if (ball_pos.x < 90){
                        if(ball_pos.y < 45){
                            meta.x = centroid_def.x + 8;
                            meta.y = centroid_def.y - 20;
                        }
                        else if(ball_pos.y > 95){
                            meta.x = centroid_def.x + 8;
                            meta.y = centroid_def.y + 20;
                        }
                        else{
                            meta.x = centroid_def.x + 8;
                            meta.y = centroid_def.y;
                        }
                    }
                    else{
                        meta.x = centroid_def.x + 8;
                        meta.y = centroid_def.y;
                    }
                }
                if (ball_pos.x >= centroid_atk.x){
                    if (ball_pos.x > 90){
                        if(ball_pos.y < 45){
                            meta.x = centroid_def.x - 8;
                            meta.y = centroid_def.y - 20;
                        }
                        else if(ball_pos.y > 95){
                            meta.x = centroid_def.x - 8;
                            meta.y = centroid_def.y + 20;
                        }
                        else{
                            meta.x = centroid_def.x - 8;
                            meta.y = centroid_def.y;
                        }
                    }
                    else{
                        meta.x = centroid_def.x - 8;
                        meta.y = centroid_def.y;
                    }
                }
                meta_goalkeeper = meta;

                meta_grid = convert_C_to_G(meta); //cm to grid
                if (meta_grid.x > 0 && meta_grid.y > 0){
                    set_potential(meta_grid.y, meta_grid.x, 0);
                }

                while(iterator_cph()>1E-6);
                set_direction();
                set_grid_orientation(meta_grid);
    }
}

void Game_functions::goalkeeper(Robot *robo, int num_Robo, pair<float, float> *vels){
    // Gera o grid
    init_grid();

    return2goal();

}

void Game_functions::defender(Robot *robo, int num_Robo, pair<float, float> *vels){
    // Gera o grid
    //if(!grid_initialized){
        init_grid();
    //}

        for(i = 0; i < 3; ++i){
            if(enemy_pos[i].x > 0 && enemy_pos[i].y > 0){
                enemy_pos_grid[i] = convert_C_to_G(enemy_pos[i]);
                //cout<<"Inimigo "<<enemy_pos_grid[i].x<<" "<<enemy_pos_grid[i].y<<endl;
                if(enemy_pos_grid[i].x>0 && enemy_pos_grid[i].y>0)
                    set_potential(enemy_pos_grid[i].y, enemy_pos_grid[i].x, 1);
            }else{
                //tratar posição dos inimigos aqui
            }

            if(team_pos[i].x > 0 && team_pos[i].y > 0)//Encherga os amigos como obstáculos
            {
                if(team_pos[i] == robo->get_pos())//Verifica o robo usado
                {
                }
                else//Seta como 1 o potencial dos robos restantes
                {
                    team_pos_grid[i] = convert_C_to_G(team_pos[i]);
                    if(team_pos_grid[i].x > 0 && team_pos_grid[i].y > 0){
                        set_potential(team_pos_grid[i].y, team_pos_grid[i].x, 1);
                    }
                    else{
                        //Tratar Aqui
                    }
                }
            }
            else{
                //tratar posição dos miguxos aqui
            }
        }

    double def_area_x = def_area[0].x*X_CONV_CONST;
    double def_area_y1 = def_area[1].y*Y_CONV_CONST;
    double def_area_y2 = def_area[6].y*Y_CONV_CONST;

    Point meta_grid;

    if (centroid_atk.x > ball_pos.x){
        if(ball_pos.x < def_area_x && ball_pos.y < def_area_y1 && ball_pos.y > def_area_y2){
            //cout << "Reconheceu a area de defesa" << endl;
            if(ball_pos.x > 0 && ball_pos.y > 0){
                meta.x = centroid_def.x + 35;
                meta.y = centroid_def.y;
                meta_grid = convert_C_to_G(meta);
                //cout<<"Bola "<<ball_pos_grid.x<<" "<<ball_pos_grid.y<<endl;
                if (meta_grid.x > 0 && meta_grid.y > 0)
                    set_potential(meta_grid.y, meta_grid.x, 0);
            }else{
                //tratar a meta aqui
            }

        }else{
            if(ball_pos.x > 0 && ball_pos.y > 0){
                ball_pos_grid = convert_C_to_G(ball_pos);
                //cout<<"Bola "<<ball_pos_grid.x<<" "<<ball_pos_grid.y<<endl;
                if (ball_pos_grid.x > 0 && ball_pos_grid.y > 0)
                    set_potential(ball_pos_grid.y, ball_pos_grid.x, 0);
            }else{
                //tratar a bola aqui
            }

            if(ball_pos.x > 0 && ball_pos.y > 0){
                ball_pos_grid = convert_C_to_G(ball_pos);
                //cout<<"Bola "<<ball_pos_grid.x<<" "<<ball_pos_grid.y<<endl;
                if(ball_pos_grid.x+1 < 28 && ball_pos_grid.y+1 < 28){
                    set_potential(ball_pos_grid.y, ball_pos_grid.x+1, 1);
                    set_potential(ball_pos_grid.y+1, ball_pos_grid.x+1, 1);
                    set_potential(ball_pos_grid.y-1, ball_pos_grid.x+1, 1);
                }
            }else{
                //tratar a barreira aqui
            }
        }
    }else{
        if(ball_pos.x > def_area_x && ball_pos.y < def_area_y1 && ball_pos.y > def_area_y2){
            if(ball_pos.x > 0 && ball_pos.y > 0){
                meta.x = centroid_def.x - 35;
                meta.y = centroid_def.y;
                meta_grid = convert_C_to_G(meta);
                //cout<<"Bola "<<ball_pos_grid.x<<" "<<ball_pos_grid.y<<endl;
                if (meta_grid.x > 0 && meta_grid.y > 0)
                    set_potential(meta_grid.y, meta_grid.x, 0);
            }else{
                //tratar a meta aqui
            }
        }else{
            if(ball_pos.x > 0 && ball_pos.y > 0){
                ball_pos_grid = convert_C_to_G(ball_pos);
                //cout<<"Bola "<<ball_pos_grid.x<<" "<<ball_pos_grid.y<<endl;
                if (ball_pos_grid.x > 0 && ball_pos_grid.y > 0)
                    set_potential(ball_pos_grid.y, ball_pos_grid.x, 0);
            }else{
                //tratar a bola aqui
            }

            if(ball_pos.x > 0 && ball_pos.y > 0){
                ball_pos_grid = convert_C_to_G(ball_pos);
                //cout<<"Bola "<<ball_pos_grid.x<<" "<<ball_pos_grid.y<<endl;
                if(ball_pos_grid.y+1 < 28){
                    set_potential(ball_pos_grid.y, ball_pos_grid.x-1, 1);
                    set_potential(ball_pos_grid.y+1, ball_pos_grid.x-1, 1);
                    set_potential(ball_pos_grid.y-1, ball_pos_grid.x-1, 1);
                }
            }else{
                //tratar a barreira aqui
            }
        }
    }
    while(iterator_cph()>1E-6);
    set_direction();
}

void Game_functions::defensive_midfielder(Robot *robo, int num_Robo, pair<float, float> *vels){
    //if(!grid_initialized){
        init_grid();
    //}
    Point meta_grid;

    for(i = 0; i < 3; ++i){
        if(enemy_pos[i].x > 0 && enemy_pos[i].y > 0){
            enemy_pos_grid[i] = convert_C_to_G(enemy_pos[i]);
            //cout<<"Inimigo "<<enemy_pos_grid[i].x<<" "<<enemy_pos_grid[i].y<<endl;
            if(enemy_pos_grid[i].x>0 && enemy_pos_grid[i].y>0)
                set_potential(enemy_pos_grid[i].y, enemy_pos_grid[i].x, 1);
        }else{
            //tratar posição dos inimigos aqui
        }

        if(team_pos[i].x > 0 && team_pos[i].y > 0)//Encherga os amigos como obstáculos
        {
            if(team_pos[i] == robo->get_pos())//Verifica o robo usado
            {
            }
            else//Seta como 1 o potencial dos robos restantes
            {
                team_pos_grid[i] = convert_C_to_G(team_pos[i]);
                if(team_pos_grid[i].x > 0 && team_pos_grid[i].y > 0){
                    set_potential(team_pos_grid[i].y, team_pos_grid[i].x, 1);
                }
                else{
                    //Tratar Aqui
                }
            }
        }
        else{
            //tratar posição dos miguxos aqui
        }
    }

    //cout<<"Bola "<<ball_pos_grid.x<<" "<<ball_pos_grid.y<<endl;

    if(ball_pos.x > 0 && ball_pos.y > 0){
        if ((ball_pos.y > centroid_def.y+55 || ball_pos.y < centroid_def.y-55) && fabs(ball_pos.x - centroid_def.x) < 70){
            //cout << 1 << endl;
            ball_pos_grid = convert_C_to_G(ball_pos);
            if (ball_pos_grid.x > 0 && ball_pos_grid.y > 0){
                //cout << 2 << endl;
                //cout<<"Meta: "<<ball_pos_grid.x<<" "<<ball_pos_grid.y<<endl;
                set_potential(ball_pos_grid.y, ball_pos_grid.x, 0);
                meta = ball_pos;
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
            //cout << "Meta x: " << meta.x << " y: " << meta.y << endl;
            if(meta.x > 0 && meta.y > 0){
                 meta_grid = convert_C_to_G(meta);
                 //cout<<"Bola "<<ball_pos_grid.x<<" "<<ball_pos_grid.y<<endl;
                 if (meta_grid.x > 0 && meta_grid.y > 0)
                     set_potential(meta_grid.y, meta_grid.x, 0);
            }else{
                //tratar a meta aqui
            }
        }
    }else{
        //tratar a bola aqui
    }

    /*if(ball_pos.x > 0 && ball_pos.y > 0){
        ball_pos_grid = convert_C_to_G(ball_pos);2d meta;
        //cout<<"Bola "<<ball_pos_grid.x<<" "<<ball_pos_grid.y<<endl;
        set_potential(ball_pos_grid.y, ball_pos_grid.x, 0);
    }else{
        //tratar a bola aqui
    }*/
    while(iterator_cph()>1E-6);
    set_direction();
}

void Game_functions::ofensive_midfielder(Robot *robo, int num_Robo, pair<float, float> *vels){
    Point2d eixo_x(1.0,0.0);
    Point meta_grid;
    //if(!grid_initialized){
        init_grid();
    //}

        for(i = 0; i < 3; ++i){
            if(enemy_pos[i].x > 0 && enemy_pos[i].y > 0){
                enemy_pos_grid[i] = convert_C_to_G(enemy_pos[i]);
                //cout<<"Inimigo "<<enemy_pos_grid[i].x<<" "<<enemy_pos_grid[i].y<<endl;
                if(enemy_pos_grid[i].x>0 && enemy_pos_grid[i].y>0)
                    set_potential(enemy_pos_grid[i].y, enemy_pos_grid[i].x, 1);
            }else{
                //tratar posição dos inimigos aqui
            }

            if(team_pos[i].x > 0 && team_pos[i].y > 0)//Encherga os amigos como obstáculos
            {
                if(team_pos[i] == robo->get_pos())//Verifica o robo usado
                {
                }
                else//Seta como 1 o potencial dos robos restantes
                {
                    team_pos_grid[i] = convert_C_to_G(team_pos[i]);
                    if(team_pos_grid[i].x > 0 && team_pos_grid[i].y > 0){
                        set_potential(team_pos_grid[i].y, team_pos_grid[i].x, 1);
                    }
                    else{
                        //Tratar Aqui
                    }
                }
            }
            else{
                //tratar posição dos miguxos aqui
            }
        }

    if(ball_pos.x > 0 && ball_pos.y > 0){
        if (fabs(ball_pos.x - centroid_def.x) < 40){
            set_epsilon(0);
            set_orientation(0);
            if (ball_pos.x < centroid_atk.x){
                meta.x = centroid_def.x + 75;
                meta.y  = centroid_def.y;
                meta_grid = convert_C_to_G(meta);
                if(meta_grid.x > 0 && meta_grid.y > 0){
                         set_potential(meta_grid.y, meta_grid.x, 0);
                }else{
                    //tratar a meta aqui
                }
            }
            else{
                meta.x = centroid_def.x - 75;
                meta.y  = centroid_def.y;
                meta_grid = convert_C_to_G(meta);
                if(meta_grid.x > 0 && meta_grid.y > 0){
                         set_potential(meta_grid.y, meta_grid.x, 0);
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

            set_epsilon(0.3 + euclidean_dist(team_prox,ball_pos)/200);
           // cout << " epsilon: " << e << endl;

            ball_pos_grid = convert_C_to_G(ball_pos);
             //cout<<"Bola "<<ball_pos_grid.x<<" "<<ball_pos_grid.y<<endl;
            if (ball_pos_grid.x > 0 && ball_pos_grid.y > 0)
                set_potential(ball_pos_grid.y, ball_pos_grid.x, 0);

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
            set_orientation(ang_ball_atk);
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

    while(iterator_cpo()>1E-6);
    set_direction();
}

void Game_functions::striker(Robot *robo, int num_Robo, pair<float, float> *vels){
    Point meta_grid;
    Point2d eixo_x(1.0,0.0);
    //if(!grid_initialized){
        init_grid();
    //}
        for(i = 0; i < 3; ++i){
            if(enemy_pos[i].x > 0 && enemy_pos[i].y > 0){
                enemy_pos_grid[i] = convert_C_to_G(enemy_pos[i]);
                //cout<<"Inimigo "<<enemy_pos_grid[i].x<<" "<<enemy_pos_grid[i].y<<endl;
                if(enemy_pos_grid[i].x>0 && enemy_pos_grid[i].y>0)
                    set_potential(enemy_pos_grid[i].y, enemy_pos_grid[i].x, 1);
            }else{
                //tratar posição dos inimigos aqui
            }

            if(team_pos[i].x > 0 && team_pos[i].y > 0)//Encherga os amigos como obstáculos
            {
                if(team_pos[i] == robo->get_pos())//Verifica o robo usado
                {
                }
                else//Seta como 1 o potencial dos robos restantes
                {
                    team_pos_grid[i] = convert_C_to_G(team_pos[i]);
                    if(team_pos_grid[i].x > 0 && team_pos_grid[i].y > 0){
                        set_potential(team_pos_grid[i].y, team_pos_grid[i].x, 1);
                    }
                    else{
                        //Tratar Aqui
                    }
                }
            }
            else{
                //tratar posição dos miguxos aqui
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

        set_epsilon(0.3 + euclidean_dist(team_prox,ball_pos)/250);
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
        set_orientation(ang_ball_atk);
        //orientation = 45;
        //Corrige Posicionamento novamente
        ball_pos.y = -ball_pos.y;
        centroid_atk.y=-centroid_atk.y;

        // temos que mudar urgente
        if (euclidean_dist(ball_pos,team_prox) < 5){
            if (centroid_atk.x > 0 && centroid_atk.y > 0){
                meta_grid = convert_C_to_G(centroid_atk);
                set_epsilon(0);
                //cout<<"Bola "<<ball_pos_grid.x<<" "<<ball_pos_grid.y<<endl;
                if (meta_grid.x > 0 && meta_grid.y > 0)
                    set_potential(meta_grid.y, meta_grid.x, 0);
            }else{
                //tratar o gol aqui
            }

        }else{
            ball_pos_grid = convert_C_to_G(ball_pos);
             //cout<<"Bola "<<ball_pos_grid.x<<" "<<ball_pos_grid.y<<endl;
            if (ball_pos_grid.x > 0 && ball_pos_grid.y > 0)
                set_potential(ball_pos_grid.y, ball_pos_grid.x, 0);
        }
    }else{
        //tratar a bola aqui
    }
    while(iterator_cpo()>1E-6);
    set_direction();
}

double Game_functions::ajusta_angulo(double angle){
    while (angle < -180)
        angle = angle + 360;
    while (angle > 180)
        angle = angle - 360;
    return angle;
}

bool Game_functions::get_flag_finish(){
    return this->flag_finish_functions;
}

void Game_functions::zera_flag_finish(){
    flag_finish_functions = false;
}

Point Game_functions::convert_C_to_G(Point2d coord){
    /*Point i;

    coord.x = int(coord.x) + 5;
    coord.y = int(coord.y) + 5;

    if(coord.x / 5 != 35){
        i.x = coord.x / 5;
    }
    else if(coord.x / 5 < 3){
        i.x = 3;
    }
    else{
        i.x = 35;
    }

    if(coord.y / 5 != 27){
        i.y = coord.y / 5;
    }
    else if(coord.y / 5 < 1){
        i.y = 1;
    }
    else{
        i.y = 27;
    }
    return i;*/

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

void Game_functions::set_calc_Gandalf(bool var){
    this->calc_Gandalf = var;
}

void Game_functions::set_calc_Presto(bool var){
    this->calc_Presto = var;
}

void Game_functions::set_calc_Leona(bool var){
    this->calc_Leona = var;
}

void Game_functions::set_enemy_pos(p2dVector enemy_pos){
    this->enemy_pos = enemy_pos;
}

void Game_functions::set_ball_pos(Point2d ball_pos){
    this->ball_pos = ball_pos;
}

void Game_functions::set_centroid_atk(Point2d centroid_atk){
    this->centroid_atk = centroid_atk;
}

void Game_functions::set_centroid_def(Point2d centroid_def){
    this->centroid_def = centroid_def;
}

void Game_functions::set_team_pos(p2dVector team_pos){
    this->team_pos = team_pos;
}

void Game_functions::set_def_area(pVector def_area){
    this->def_area = def_area;
}

void Game_functions::set_ball_vel(pair<double, double> ball_vel){
    this->ball_vel = ball_vel;
}

Point2d Game_functions::get_meta_goalkeeper(){
    return meta_goalkeeper;
}

Point2d Game_functions::get_meta(){
    return meta;
}


