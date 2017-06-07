#include <iostream>
#include <iomanip>
#include <cmath>
#include "math.h"
#include "cpo3.h"
#include "utils.h"
#include "robot.h"

using namespace std;
Point meta;



CPO3::CPO3(){

    stop = true;
    grid_initialized = false;
    enemy_pos_grid = pVector(3);
    team_pos_grid = pVector(3);
    pGrid = dMatrix(28, vector<double>(36, 0.0));
    tGrid = dMatrix(28, vector<double>(36, 0));
    //cout<<"\n\nAMBIENTE CRIADO!\n";
}



double CPO3::iterator(){

    double erro = 0;
    double top, botton, left, right;
    double newPotencial, oldPotencial;
    double vec[2], h, lambda;
    int i,j;

    vec[0] = cos(orientation*PI/180);
    vec[1] = sin(orientation*PI/180);
    e = 0;
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
                 newPotencial = newPotencial + 0.8*(newPotencial-oldPotencial);
                 erro = erro + pow((newPotencial - oldPotencial),2);
                 set_potential(i,j,newPotencial);
             }
         }
     }
     return erro;
}

double CPO3::get_neighborhood(int i, int j, int k){
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


int CPO3::get_occupancy(int i, int j){
    if(get_potential(i,j)==1 || get_potential(i,j)==0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

double CPO3::get_potential(int i, int j){
    return pGrid[i][j];
}

void CPO3::set_direction(){
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
    // Setar a orientacao das celulas na linha ndo gol
    /*Point meta = convert_C_to_G(meta_aux);
    for(i=0;i<28;i++){
         for(j=0;j<36;j++){
             if(i > 6 && i < 21 && (j == 32 || j == 3)){ //|| j == 4 || j == 31)){ // i>6, i<21, j==3, 32
                 if (meta.y < i)
                     tGrid[i][j] = 90;
                 else
                     tGrid[i][j] = -90;
             }
             if (i > 5 && i < 22 && (j == 31 || j == 2)){
                 if (meta.y < i)
                     tGrid[i][j] = 75;
                 else
                     tGrid[i][j] = -75;

             }

             if (i > 8 && i < 19 && (i == 33 || i == 4 )){
                 if (meta.y < i)
                     tGrid[i][j] = 105;
                 else
                     tGrid[i][j] = -105;
             }*/ 
}

double CPO3::get_direction(Point grid){
    return this->tGrid[grid.y][grid.x];;
}

void CPO3::set_potential(int i, int j, double aux){
    pGrid[i][j]= aux;
}

void CPO3::init_grid(){
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
}

void CPO3::print_grid(){
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
            cout.precision(1);
            cout<<fixed;
            cout<<tGrid[i][j]<<setw(7);
        }
        cout<<"\n\n";
    }
    cout<<"\n\n\n";
}

Point CPO3::convert_C_to_G(Point2d coord){
    Point i;

    coord.x = int(coord.x) + 5;
    coord.y = int(coord.y) + 5;

    if(coord.x / dx != 35){
        i.x = coord.x / dx;
    }else{
        i.x = coord.x / dx - 1;
    }

    if(coord.y / dy != 27){
        i.y = coord.y / dy;
    }else{
        i.y = coord.y / dy - 1;
    }
    //cout << "i.x = " << i.x << " i.y = " << i.y << endl;
    return i;
}


void CPO3::run(){
    Point2d eixo_x(1.0,0.0);
    Point2d meta2d;
    //if(!grid_initialized){
        init_grid();
        grid_initialized = true;
    //}
    e = 0;
    orientation = 0;

    /*if(ball_pos.x > 0 && ball_pos.y > 0){
        if (ball_pos.x < centroid_atk.x){
                if(ball_pos.x > 75){
                    meta2d.x = centroid_def.x + 8;
                    meta2d.y = centroid_def.y;
                    meta = convert_C_to_G(meta2d);
                    if (meta.x > 0 && meta.y > 0){
                        set_potential(meta.y, meta.x, 0);
                    }
                }
                else{
                    meta2d.x = centroid_def.x + 8;
                    if (ball_pos.y > centroid_def.y + 18)
                        meta2d.y = centroid_def.y + 18;
                    else if (ball_pos.y < centroid_def.y - 18)
                        meta2d.y = centroid_def.y - 18;
                    else
                        meta2d.y = ball_pos.y;
                    meta = convert_C_to_G(meta2d);
                    if (meta.x > 0 && meta.y > 0){
                        set_potential(meta.y, meta.x, 0);
                    }
                    else{
                            //tratar meta aqui
                    }
                    meta_aux.x = meta2d.x;
                    meta_aux.y = meta2d.y;
                    if (meta2d.y > team_pos[0].y)
                        orientation = -90;
                    else
                        orientation = 90;
                    //cout << "Bola fora da area" << endl;
                }

        }else{
            if(ball_pos.x < 75){
                meta2d.x = centroid_def.x - 8;
                meta2d.y = centroid_def.y;
                meta = convert_C_to_G(meta2d);
                if (meta.x > 0 && meta.y > 0){
                    set_potential(meta.y, meta.x, 0);
                }
            }
            else{
                meta2d.x = centroid_def.x - 8;
                if (ball_pos.y > centroid_def.y + 18)
                    meta2d.y = centroid_def.y + 18;
                else if (ball_pos.y < centroid_def.y - 18)
                    meta2d.y = centroid_def.y - 18;
                else
                    meta2d.y = ball_pos.y;
                meta = convert_C_to_G(meta2d);
                if (meta.x > 0 && meta.y > 0){
                    set_potential(meta.y, meta.x, 0);
                }
                else{
                        //tratar meta aqui
                    }
                meta_aux.x = meta2d.x;
                meta_aux.y = meta2d.y;
                if (meta2d.y > team_pos[0].y)
                    orientation = -90;
                else
                    orientation = 90;
                //cout << "Bola fora da area" << endl;
            }
        }
    }else{
        //tratar a bola aqui
    };*/



            //print_grid();

    return2goal();
    flag_finish_CPO3 = true;


}

void CPO3::return2goal(){
    if(ball_pos.x > 0 && ball_pos.y > 0){
            if (ball_pos.x < centroid_atk.x){
                if (ball_pos.x < 90){
                    if(ball_pos.y < 45){
                        meta_aux.x = centroid_def.x + 8;
                        meta_aux.y = centroid_def.y - 20;
                    }
                    else if(ball_pos.y > 95){
                        meta_aux.x = centroid_def.x + 8;
                        meta_aux.y = centroid_def.y + 20;
                    }
                    else{
                        meta_aux.x = centroid_def.x + 8;
                        meta_aux.y = centroid_def.y;
                    }
                }
                else{
                    meta_aux.x = centroid_def.x + 8;
                    meta_aux.y = centroid_def.y;
                }
            }
            if (ball_pos.x >= centroid_atk.x){
                if (ball_pos.x > 90){
                    if(ball_pos.y < 45){
                        meta_aux.x = centroid_def.x - 8;
                        meta_aux.y = centroid_def.y - 20;
                    }
                    else if(ball_pos.y > 95){
                        meta_aux.x = centroid_def.x - 8;
                        meta_aux.y = centroid_def.y + 20;
                    }
                    else{
                        meta_aux.x = centroid_def.x - 8;
                        meta_aux.y = centroid_def.y;
                    }
                }
                else{
                    meta_aux.x = centroid_def.x - 8;
                    meta_aux.y = centroid_def.y;
                }
            }

            meta = convert_C_to_G(meta_aux); //cm to grid
            if (meta_aux.x > 0 && meta_aux.y > 0){
                //cout << "ataque: " << centroid_atk << " defesa: " << centroid_def << endl;
                set_potential(meta.y, meta.x, 0);
                //cout << "Metax: " << meta_aux.x << " Metay: " << meta_aux.y << endl;

            }

            while(iterator()>1E-6);
            set_direction();
            set_grid_orientation();

    }
}

void CPO3::set_grid_orientation(){
    // Setar a orientacao das celulas na linha ndo gol
        meta = convert_C_to_G(meta_aux);
        int i, j;
        for(i=0;i<28;i++){
             for(j=0;j<36;j++){
                 if(i > 6 && i < 21 && (j == 32 || j == 3)){ //|| j == 4 || j == 31)){ // i>6, i<21, j==3, 32
                     if (meta.y < i)
                         tGrid[i][j] = 90;
                     else
                         tGrid[i][j] = -90;
                 }
             }
        }
}

bool CPO3::get_flag_finish(){
    return this->flag_finish_CPO3;
}

void CPO3::zera_flag_finish(){
    flag_finish_CPO3 = false;
}

void CPO3::set_ball_vel(pair<double, double> ball_vel){
    this->ball_vel = ball_vel;
}

void CPO3::set_orientation(double angle){
    this->orientation = angle;
}

void CPO3::set_enemy_pos(p2dVector enemy_pos){
    this->enemy_pos = enemy_pos;
}

void CPO3::set_team_pos(p2dVector team_pos){
    this->team_pos = team_pos;
}

void CPO3::set_ball_pos(Point2d ball_pos){
    this->ball_pos = ball_pos;
}

void CPO3::set_centroid_atk(Point2d centroid_atk){
    this->centroid_atk = centroid_atk;
}

void CPO3::set_centroid_def(Point2d centroid_def){
    this->centroid_def = centroid_def;
}

Point2d CPO3::get_meta_aux(){
    return this->meta_aux;
}


bool CPO3::isStopped() const
{
    return this->stop;
}

void CPO3::Play(){
    if(!isRunning()){
        if(isStopped())
            stop = false;
        start(LowPriority);
    }
}

void CPO3::Stop(){
    stop = true;
}

bool CPO3::is_running(){
    return isRunning();
}

void CPO3::msleep(int ms){
    /*struct timespec ts = {ms / 1000, (ms % 1000) * 1000 * 1000};
    nanosleep(&ts, NULL);*/
}

CPO3::~CPO3(){

}
