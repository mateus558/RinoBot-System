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

void Navigation::univector_field(Robot *robo, Point2d enemy, Point2d meta)
{
    float k0 = 0.12;
    float d_min = 2;
    float norma_s,fih_AUF,fih_TUF;
    float d = sqrt(pow(robo->get_pos().x - enemy.x, 2)+ pow(robo->get_pos().y - enemy.y, 2));  //distancia entre o robo e o obstaculo
    Point2d s, enemy_vel, robo_vel, virtual_obj;
    enemy_vel.x = 0;
    enemy_vel.y = 0;
    robo_vel.x = robo->get_velocities().first*X_CONV_CONST;
    robo_vel.y = robo->get_velocities().second*Y_CONV_CONST;
    s.x = k0 * ( enemy_vel.x - robo_vel.x); // Velocidade
    s.y = k0*(enemy_vel.y - robo_vel.y);
    norma_s = sqrt(pow(s.x,2)+ pow(s.y,2));

    if (d >= norma_s)
    {
        virtual_obj.x = enemy.x + s.x;
        virtual_obj.y = enemy.y + s.y;
    }
    else
    {
        virtual_obj.x = enemy.x + (d*s.x/norma_s);
        virtual_obj.y = enemy.y + (d*s.y/norma_s);
    }

    fih_AUF = repulsive_angle(robo->get_pos().x, robo->get_pos().y, virtual_obj);
    fih_TUF = hyperbolic_spiral(robo->get_pos().y, robo->get_pos().x, meta);

    if (d <= d_min)
        the_fih = fih_AUF;
    else
        the_fih = fih_AUF*Gaussian_Func(d-d_min) + fih_TUF*(1-Gaussian_Func(d-d_min));
    //        cout << "the_fih: " << the_fih << endl; //TESTE DELETAR

}

float Navigation::hyperbolic_spiral(float yi, float xi, Point2d meta)
{
    float Kr = 20;
    float theta_up,theta_down,rho_up,rho_down;
    float de = 7;
    Vector3d p(xi,yi,1),ph(0,0,0);

    //cout << "g_size " << g_size << endl;
    MatrixXd m_trans(3,3),m_rot(3,3);
    m_trans  << 1, 0, -meta.x, 0, 1, -meta.y, 0, 0, 1;
    m_rot << cos(-theta_dir),-sin(-theta_dir),0,sin(-theta_dir),cos(-theta_dir),0,0,0,1;

    ph = m_rot*m_trans*p;
    //std::cout << ph << std::endl << std::endl;
    theta_up = atan2((ph(1)-de-g_size),ph(0)) + theta_dir;
    theta_down = atan2((ph(1)+de+g_size),ph(0)) + theta_dir;
    rho_up = sqrt(pow(ph(0),2) + pow((ph(1)-de-g_size),2));
    rho_down = sqrt(pow(ph(0),2) + pow((ph(1)+de+g_size),2));

    if (ph(1)>g_size)
        phi = theta_up + pi*(2-(de+Kr)/(rho_up+Kr))/2;
    else if (ph(1)< -g_size)
        phi = theta_down - pi*(2-(de+Kr)/(rho_down+Kr))/2;
    else
        phi = theta_dir;

    //cout << "phi: " << phi << endl; //TESTE DELETAR

    return phi;

}

void Navigation::set_thetaDir(float theta)
{
    theta_dir = theta;
}

float Navigation::get_direction_CPU()
{
    return -phi;
}

float Navigation::repulsive_angle(float x, float y, Point2d pos)
{
    float alpha;
    if(x - pos.x < 0)
        alpha = atan((y-pos.y)/(x-pos.x))+pi;
    else
        alpha = atan((y-pos.y)/(x-pos.x));

    return alpha;
}

float Navigation::Gaussian_Func(float r){
    float delta = (4.57/2),G;
    G = pow(M_E,(-pow(r,2)/(2*pow(delta,2))));
    return G;
}
