#include <iostream>
#include <iomanip>
#include <cmath>
#include "cph.h"

using namespace std;


CPH::CPH(int a, int b){
    dx = a;
    dy = b;
    pGrid = dMatrix(20, vector<double>(20, 0.0));
    tGrid = iMatrix(20, vector<int>(20, 0));
    cout<<"\n\nAMBIENTE CRIADO!\n";
}

double CPH::iterator(){
    double erro = 0;
    double top, botton, left, right;
    double newPotencial, oldPotencial;
    int i,j;
    for(i=0;i<20;i++)
    {
        for(j=0;j<20;j++)
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

double CPH::get_neighborhood(int i, int j, int k){
   double top,botton,left,right;
   if(i==0)
   {
       top=1;
       botton=get_potential(i+1,j);
   }
   else
   {
       if(i==19)
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
       if(j==19)
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

int CPH::get_occupancy(int i, int j){
    if(get_potential(i,j)==1 || get_potential(i,j)==0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

double CPH::get_potential(int i, int j){
    return pGrid[i][j];
}

void CPH::set_direction(){
    int i,j;

    for(i=0;i<20;i++)
    {
        for(j=0;j<20;j++)
        {
            //cout << "i = " << i << " j = " << j << endl;
            if(get_occupancy(i,j)==1)
                tGrid[i][j] = -atan2(get_neighborhood(i,j,0)-get_neighborhood(i,j,1),get_neighborhood(i,j,2)-get_neighborhood(i,j,3))*180/PI;
            else
                tGrid[i][j] = get_potential(i,j)*1000;
        }
    }
}

void CPH::set_potential(int i, int j, double aux){
    pGrid[i][j]= aux;
}

void CPH::init_grid(){
    int i,j;
    for(i=0;i<20;i++)
    {
        for(j=0;j<20;j++)
        {
            if (i==0 || i == 19)
                pGrid[i][j]=1;
            else if (j==0 || j == 19)
                pGrid[i][j]=1;
            else
                pGrid[i][j]=0.5;
        }
    }
}

void CPH::print_grid(){
    cout<<"\n\n\nGrid:\n\n";;
    int i,j;
    for(i=0;i<20;i++)
    {
        for(j=0;j<20;j++)
        {
            cout.precision(4);
            cout<<fixed;
            cout<<pGrid[i][j]<<setw(7);
        }
        cout<<"\n\n";
    }
    cout<<"\n\n\nGrid de direcoes:\n\n";
    for(i=0;i<20;i++)
    {
        for(j=0;j<20;j++)
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

Point CPH::convert_C_to_G(Point2d coord){
    Point i;

    coord.x = int(coord.x);
    coord.y = int(coord.y);

    if(coord.x / dx != 20){
        i.x = coord.x / dx;
    }else{
        i.x = coord.x / dx - 1;
    }

    if(coord.y / dy != 20){
        i.y = coord.y / dy;
    }else{
        i.y = coord.y / dy - 1;
    }
    cout << "i.x = " << i.x << " i.y = " << i.y << endl;
    return i;
}

void CPH::run(){

}

bool CPH::isStopped() const
{
    return this->stop;
}

void CPH::Play(){
    if(!isRunning()){
        if(isStopped())
            stop = false;
        start(LowPriority);
    }
}

void CPH::Stop(){

}

void CPH::msleep(int ms){
    struct timespec ts = {ms / 1000, (ms % 1000) * 1000 * 1000};
    nanosleep(&ts, NULL);
}
