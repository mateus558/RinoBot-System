#include "navegation.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include "utils.h"

using namespace std;

NAVEGATION::NAVEGATION(){
    i = 0;
    stop = true;
    grid_initialized = false;
    enemy_pos_grid = pVector(3);
    team_pos_grid = pVector(3);
    pGrid = dMatrix(28, vector<double>(36, 0.0));
    tGrid = dMatrix(28, vector<double>(36, 0.0));
    //cout << "\n\nAMBIENTE CRIADO! \n";
}

void NAVEGATION::run(){

        //A ser editada - classe função de jogo
        //if(!grid_initialized){
        //init_grid();
        //}

        /*for(i = 0; i < 3; ++i){
            if(enemy_pos[i].x > 0 && enemy_pos[i].y > 0){
                enemy_pos_grid[i] = convert_C_to_G(enemy_pos[i]);
                //cout<<"Inimigo "<<enemy_pos_grid[i].x<<" "<<enemy_pos_grid[i].y<<endl;
                if(enemy_pos_grid[i].x>0 && enemy_pos_grid[i].y>0)
                    set_potential(enemy_pos_grid[i].y, enemy_pos_grid[i].x, 1);
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
                        set_potential(meta.y, meta.x, 0);
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
                    meta2d.x = centroid_def.x - 35;
                    meta = convert_C_to_G(meta2d);
                    //cout<<"Bola "<<ball_pos_grid.x<<" "<<ball_pos_grid.y<<endl;
                    if (meta.x > 0 && meta.y > 0)
                        set_potential(meta.y, meta.x, 0);
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
        } */


    //while(iterator_cph()>1E-6);
    //set_direction();

    //print_grid();
}




double NAVEGATION::iterator_cph(){
    double erro = 0;
    double top, botton, left, right;
    double newPotencial, oldPotencial;
    int i,j;
    for(i=0;i<28;i++)
    {
        for(j=0;j<36;j++)
        {
            if(get_occupancy(i,j))
            {
                oldPotencial = get_potential(i,j);
                top = get_neighborhood(i,j,0);
                botton = get_neighborhood(i,j,1);
                left = get_neighborhood(i,j,2);
                right = get_neighborhood(i,j,3);
                newPotencial = (top+botton+left+right)/4;
                newPotencial = newPotencial + 0.8*(newPotencial-oldPotencial);
                erro = erro + pow((newPotencial - oldPotencial),2);
                set_potential(i,j,newPotencial);
            }
        }
    }
    return erro;
}

double NAVEGATION::iterator_cpo(){
    double erro = 0;
    double top, botton, left, right;
    double newPotencial, oldPotencial;
    double vec[2], h, lambda;
    int i,j;

    vec[0] = cos(orientation*PI/180);
    vec[1] = sin(orientation*PI/180);

    h = dx/dy;
    lambda = e*h/2;

     for(i=0;i<28;i++)
     {
         for(j=0;j<36;j++)
         {
             if(get_occupancy(i,j)==1)
             {
                oldPotencial = get_potential(i,j);
                top = get_neighborhood(i,j,0);
                 botton = get_neighborhood(i,j,1);
                 left = get_neighborhood(i,j,2);
                 right = get_neighborhood(i,j,3);
                 newPotencial = ((1+lambda*vec[0])*right+(1-lambda*vec[0])*left+(1+lambda*vec[1])*top+(1-lambda*vec[1])*botton)/4;
                 //newPotencial = newPotencial + 0.8*(newPotencial-oldPotencial);
                 erro = erro + pow((newPotencial - oldPotencial),2);
                 set_potential(i,j,newPotencial);
             }
         }
     }
     return erro;
}

double NAVEGATION::get_neighborhood(int i, int j, int k){
   double top,botton,left,right;
   if(i==0)
   {
       top=1;
       botton=get_potential(i+1,j);
   }
   else
   {
       if(i==27)
       {
           botton=1;
           top=get_potential(i-1,j);
       }
       else
       {
           top=get_potential(i-1,j);
           botton=get_potential(i+1,j);
       }
   }
   if(j==0)
   {
       left=1;
       right=get_potential(i,j+1);
   }
   else
   {
       if(j==35)
       {
           right=1;
           left=get_potential(i,j-1);
       }
       else
       {
           left=get_potential(i,j-1);
           right=get_potential(i,j+1);
       }
   }
   switch (k) {
   case 0:
       return top;
       break;
   case 1:
       return botton;
       break;
   case 2:
       return left;
       break;
   case 3:
       return right;
       break;
   default:
       break;
   }
}

void NAVEGATION::set_potential(int i, int j, double aux){
    pGrid[i][j]= aux;
}

double NAVEGATION::get_potential(int i, int j){
    return pGrid[i][j];
}

int NAVEGATION::get_occupancy(int i, int j){
    if(get_potential(i,j)==1 || get_potential(i,j)==0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void NAVEGATION::set_direction(){
    int i,j;

    for(i=0;i<28;i++)
    {
        for(j=0;j<36;j++)
        {
            //cout << "i = " << i << " j = " << j << endl;
            if(get_occupancy(i,j)==1)
                tGrid[i][j] = -atan2(get_neighborhood(i,j,0)-get_neighborhood(i,j,1),get_neighborhood(i,j,2)-get_neighborhood(i,j,3))*180/PI;
            else
                tGrid[i][j] = get_potential(i,j)*1000;
        }
    }
}

double NAVEGATION::get_direction(Point grid){
    return this->tGrid[grid.y][grid.x];
}

void NAVEGATION::init_grid(){
    int i,j;

    for(i=0;i<28;i++)
    {
        for(j=0;j<36;j++)
        {
            if ( i == 0 || i == 27 || j == 0 || j == 1 || j == 2 || j == 33 || j == 34 || j == 35 )
            {
                if ( j == 1 || j == 2 || j == 33 || j == 34 )
                {
                    if (i > 9 && i < 18)
                        pGrid[i][j] = 0.9;
                    else
                        pGrid[i][j] = 1.0;
                }
                else
                    pGrid[i][j] = 1.0;
            }
            else
                pGrid[i][j] = 0.9;
        }
    }
    grid_initialized = true;
}

void NAVEGATION::print_grid(){
    cout<<"\n\n\nGrid:\n\n";;
    int i,j;
    for(i=0;i<28;i++)
    {
        for(j=0;j<36;j++)
        {
            cout.precision(4);
            cout<<fixed;
            cout<<pGrid[i][j]<<setw(7);
        }
        cout<<"\n\n";
    }
    cout<<"\n\n\nGrid de direcoes:\n\n";
    for(i=0;i<28;i++)
    {
        for(j=0;j<36;j++)
        {
            cout<<tGrid[i][j]<<"\t";
        }
        cout<<"\n\n";
    }
    cout<<"\n\n\n";
}

Point2d NAVEGATION::get_meta_aux(){
    return this->meta;
}

void NAVEGATION::set_meta_aux(Point2d meta){
    this->meta = meta;
}

/*void NAVEGATION::set_enemy_pos(p2dVector enemy_pos){
    this->enemy_pos = enemy_pos;
}

void NAVEGATION::set_team_pos(p2dVector team_pos){
    this->team_pos = team_pos;
}

void NAVEGATION::set_ball_pos(Point2d ball_pos){
    this->ball_pos = ball_pos;
}

void NAVEGATION::set_def_area(pVector def_area){
    this->def_area = def_area;
}

void NAVEGATION::set_centroid_atk(Point2d centroid_atk){
    this->centroid_atk = centroid_atk;
}

void NAVEGATION::set_centroid_def(Point2d centroid_def){
    this->centroid_def = centroid_def;
}*/

void NAVEGATION::set_epsilon(double e){
    this->e = e;
}

void NAVEGATION::set_orientation(double orientation){
    this->orientation = orientation;
}


bool NAVEGATION::get_flag_finish(){
    return this->flag_finish_navegation;
}

void NAVEGATION::zera_flag_finish(){
    flag_finish_navegation = false;
}

void NAVEGATION::Play(){
    if(isStopped())
        stop = false;
   start();
}

bool NAVEGATION::is_running(){
    return isRunning();
}

void NAVEGATION::Stop(){
    stop = true;
}

bool NAVEGATION::isStopped() const
{
    return this->stop;
}

void NAVEGATION::msleep(int ms){
    /*struct timespec ts = {ms / 1000, (ms % 1000) * 1000 * 1000};
    nanosleep(&ts, NULL);*/
}

NAVEGATION::~NAVEGATION(){

}
