#include "navigation.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include "utils.h"

using namespace std;

Navigation::Navigation(){
    //cout << "\n\nAMBIENTE CRIADO! \n";
}

void Navigation::run(){

}

double Navigation::iterator_cph(){
    double erro = 0;
    double top, botton, left, right;
    double newPotencial, oldPotencial;
    int i,j;
    for(i=0;i<28;i++)
    {
        for(j=0;j<36;j++)
        {
            if(get_occupancy(i,j))
            {newPotencial = newPotencial + 0.8*(newPotencial-oldPotencial);
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

double Navigation::iterator_cpo(){
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
                 //if (e < 0.5){
                     newPotencial = newPotencial + 0.8*(newPotencial-oldPotencial);
                 //}
                 erro = erro + pow((newPotencial - oldPotencial),2);
                 set_potential(i,j,newPotencial);
             }
         }
     }
     return erro;
}

double Navigation::get_neighborhood(int i, int j, int k){
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

void Navigation::set_potential(int i, int j, double aux){
    pGrid[i][j]= aux;
}

double Navigation::get_potential(int i, int j){
    return pGrid[i][j];
}

int Navigation::get_occupancy(int i, int j){
    if(get_potential(i,j)==1 || get_potential(i,j)==0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void Navigation::set_grid_orientation(Point meta){
    int i, j;
    for (i = 0; i < 28; i++){
        for (j = 0; j < 36; j++){
            if (i > 7 && i < 20 && (j == 3 || j == 33)){
                if (meta.y < i){
                    tGrid[i][j] = 90;
                }
                else if (meta.y > i){
                    tGrid[i][j] = -90;
                }
            }
        }
    }
}

void Navigation::set_direction(Point2d centroid_atk, Point2d centroid_def){
    int i,j;
    for(i=0;i<28;i++)
    {
        for(j=0;j<36;j++)
        {
            if(get_occupancy(i,j)==1)
                tGrid[i][j] = -atan2(get_neighborhood(i,j,0)-get_neighborhood(i,j,1),get_neighborhood(i,j,2)-get_neighborhood(i,j,3))*180/PI;
            else{
                if(centroid_atk.x > centroid_def.x)
                    tGrid[i][j] = 0;
                if(centroid_atk.x < centroid_def.x)
                    tGrid[i][j] = 180;
            }
        }
    }
}

double Navigation::get_direction(Point grid){
    return this->tGrid[grid.y][grid.x];
}

void Navigation::init_grid(){
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

void Navigation::print_grid(){
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


void Navigation::set_epsilon(double e){
    this->e = e;
}

void Navigation::set_orientation(double orientation){
    this->orientation = orientation;
}


bool Navigation::get_flag_finish(){
    return this->flag_finish_navegation;
}

void Navigation::zera_flag_finish(){
    flag_finish_navegation = false;
}

void Navigation::Play(){
    if(isStopped())
        stop = false;
   start();
}

bool Navigation::is_running(){
    return isRunning();
}

void Navigation::Stop(){
    stop = true;
}

bool Navigation::isStopped() const
{
    return this->stop;
}

void Navigation::msleep(int ms){
    struct timespec ts = {ms / 1000, (ms % 1000) * 1000 * 1000};
    nanosleep(&ts, NULL);
}

Navigation::~Navigation(){

}
