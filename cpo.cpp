#include <iostream>
#include <iomanip>
#include <cmath>
#include "cpo.h"

using namespace std;


CPO::CPO(){
    dx = 5;
    dy = 5;
    pGrid = dMatrix(28, vector<double>(36, 0.0));
    tGrid = iMatrix(28, vector<int>(36, 0));
    cout<<"\n\nAMBIENTE CRIADO!\n";
}

double CPO::iterator(){
    double erro = 0;
    double top, botton, left, right;
    double newPotencial, oldPotencial;
    double vec[2], e, h, lambda;
    int i,j,orientation;

    orientation = -45;
    vec[0] = cos(orientation*PI/180);
    vec[1] = sin(orientation*PI/180);

    h = dx/dy;
    e = 1;
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

double CPO::get_neighborhood(int i, int j, int k){
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


int CPO::get_occupancy(int i, int j){
    if(get_potential(i,j)==1 || get_potential(i,j)==0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

double CPO::get_potential(int i, int j){
    return pGrid[i][j];
}

void CPO::set_direction(){
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

void CPO::set_potential(int i, int j, double aux){
    pGrid[i][j]= aux;
}

void CPO::init_grid(){
    int i,j;
    for(i=0;i<28;i++)
    {
        for(j=0;j<36;j++)
        {
            if (i==0 || i == 27)
                pGrid[i][j]=1;
            else if (j==0 || j == 35)
                pGrid[i][j]=1;
            else
                pGrid[i][j]=0.9;
        }
    }
}

void CPO::print_grid(){
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
            while (tGrid[i][j]>180)
                tGrid[i][j] = tGrid[i][j] - 360;
            while (tGrid[i][j]<-180)
                tGrid[i][j] = tGrid[i][j] + 360;
            cout<<tGrid[i][j]<<setw(7);
        }
        cout<<"\n\n";
    }
    cout<<"\n\n\n";
}

Point CPO::convert_C_to_G(Point2d coord){
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
    cout << "i.x = " << i.x << " i.y = " << i.y << endl;
    return i;
}

void CPO::run(){

}

bool CPO::isStopped() const
{
    return this->stop;
}

void CPO::Play(){
    if(!isRunning()){
        if(isStopped())
            stop = false;
        start(LowPriority);
    }
}

void CPO::Stop(){

}

void CPO::msleep(int ms){
    struct timespec ts = {ms / 1000, (ms % 1000) * 1000 * 1000};
    nanosleep(&ts, NULL);
}
