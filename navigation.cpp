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
            if (i > 7 && i < 20 && (j == 3 || j == 4 || j == 33 || j == 32)){
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
        //cout  << "Entrou" << the_fih*180/pi << endl;
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
    Point2d robo_pos;
    robo_pos = robo->get_pos();
    float k0 = 12;
    float r = 15;        // Raio de Influencia do repulsivo
    float d_min = 10;   // Raio de Influencia do repulsivo
    float norma_s,fih_AUF,fih_TUF;
    float d = euclidean_dist(robo_pos, enemy);  //distancia entre o robo e o obstaculo
    float d_ball = euclidean_dist(robo_pos, meta);
    Point2d s, enemy_vel, robo_vel, virtual_obj;
    enemy_vel.x = 0;
    enemy_vel.y = 0;
    Point2d p1,p2;
    float ang_p1, ang_p2, ang_ball_robot;
    MatrixXd vec_obj(2,1), vec_p1(2,1), vec_p2(2,1), rot_matrix(2,2);
    avoid_state = false;

    fih_TUF = -hyperbolic_spiral(robo->get_pos().y, robo->get_pos().x, meta);

    // ------------ Repulsive Arquivo ------------------------------------------\\

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

   //  std::cout << "X:" << virtual_obj.x << std::endl;
   //  std::cout << "Y:" << virtual_obj.y << std::endl;

        fih_AUF = repulsive_angle(robo->get_pos().x, robo->get_pos().y, enemy);

        if((d <= d_min)){
            the_fih = fih_AUF;
            //cout << "End: "  << endl;
        }
        else{
            the_fih = fih_AUF*Gaussian_Func(d-d_min) + fih_TUF*(1-Gaussian_Func(d-d_min));
        }
            the_fih = fih_TUF;
    // ----------------------------------------------------------------------\\


    // ------------ Repulsive Otario ------------------------------------------\\

//    fih_AUF = tangencial_repulsive(robo,meta,enemy,r);

//    if (d <= r){
//        the_fih = fih_AUF ;
//        }
//    else{
//        the_fih = fih_AUF*Gaussian_Func(d - r) + fih_TUF*(1-Gaussian_Func(d - r));
//     }

    // Fim do Repulsive otario

    // --------------- Repulsive whirlpool ----------------------------------\\

    //    fih_AUF = repulsive_angle(robo->get_pos().x, robo->get_pos().y, enemy);
    //    float r_aux = d_min;
    //    float dist_o_m = euclidean_dist( meta, enemy);

    //    if (dist_o_m <= r_aux)
    //        r_aux -= dist_o_m;

    //    Point2d robo_aux = robo->get_pos();
    //    float dist_r_o = euclidean_dist( enemy, robo_aux);
    //    if(dist_r_o < r_aux)
    //    {
    //        the_fih = whirlpool_repulsive( robo, meta, enemy, fih_AUF);
    //    }
    //    else
    //    {
    //        the_fih = fih_TUF;
    //    }

    // Fim do repulsive whirlpool

    // ----------------------- Repulsive_Math ----------------------------\\

//    fih_AUF = repulsive_Math(robo,enemy,meta);

//    vec_obj << meta.x - enemy.x, meta.y - enemy.y;
//    rot_matrix <<  cos(pi/2),sin(pi/2),-sin(pi/2),cos(pi/2);
//    vec_p1 = d_min*rot_matrix*vec_obj/sqrt(pow(vec_obj(0),2)+pow(vec_obj(1),2));
//    rot_matrix <<  cos(-pi/2),sin(-pi/2),-sin(-pi/2),cos(-pi/2);
//    vec_p2 = d_min*rot_matrix*vec_obj/sqrt(pow(vec_obj(0),2)+pow(vec_obj(1),2));

//    p1.x = enemy.x + vec_p1(0);
//    p1.y = enemy.y + vec_p1(1);

//    p2.x = enemy.x + vec_p2(0);
//    p2.y = enemy.y + vec_p2(1);

//    ang_p1 = vector_angle(meta,p1);
//    ang_p2 = vector_angle(meta,p2);
//    ang_ball_robot = vector_angle(meta,robo_pos);

//    if(meta.x > enemy.x)
//    {
//        ang_p1 += 360;
//        ang_p2 += 360;
//        ang_ball_robot += 360;
//    }

////    cout << "ang_p1: " << ang_p1 << endl;
////    cout << "ang_p2: " << ang_p2 << endl;
////    cout << "ang_ball_robot: " << ang_ball_robot << endl;
//    if(ang_p1 > ang_p2)
//    {
//        if(ang_ball_robot < ang_p1 && ang_ball_robot > ang_p2 && euclidean_dist(meta,robo_pos) > euclidean_dist(meta,enemy))
//        {
//            the_fih = fih_AUF;
//            cout << "obstaculo" << endl;
//        }
//        else
//        {
//            the_fih = fih_TUF;
//            cout << "nao obstaculo" << endl;
//        }
//    }
//    else
//    {
//        if(ang_ball_robot > ang_p1 && ang_ball_robot < ang_p2 && euclidean_dist(meta,robo_pos) > euclidean_dist(meta,enemy))
//        {
//            the_fih = fih_AUF;
////            cout << "obstaculo" << endl;
//        }
//        else
//        {
//            the_fih = fih_TUF;
//            the_fih = fih_AUF*Gaussian_Func(d - d_min) + fih_TUF*(1-Gaussian_Func(d - d_min));
////            cout << "nao obstaculo" << endl;
//        }
//    }


//    if(/*(d <= d_min) &&*/ (d <= d_ball)){
//        the_fih = fih_AUF;
//    }
//    else{
//        the_fih = fih_TUF;
//    }

//      the_fih = fih_AUF*Gaussian_Func(d) + fih_TUF*(1-Gaussian_Func(d));
    //the_fih = fih_AUF;
    // ----------------------- --------------- ----------------------------\\

    //        cout << "the_fih: " << the_fih << endl; //TESTE DELETAR
    //cout << d <<endl;
}

float Navigation::hyperbolic_spiral(float yi, float xi, Point2d meta)
{

// ----- CPU ANTIGO - ROTACIONADO COM G_SIZE--------

    float theta_up,theta_down,rho_up,rho_down;
    Vector3d p(xi,yi,1),ph(0,0,0);

    //cout << "kr " << Kr << endl;
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


// ------- CPU NOVO - ROTACIONADO -----------


//    float Kr = 5;
//    float theta, rho, y_aux, yl, yr , phi_cw, phi_ccw;
//    float pl[2], pr[2], vec[2];
//    float de = 13;
//    Vector3d p(xi,yi,1),ph(0,0,0);

//    Matrix3d m_trans1(3,3),m_trans2(3,3),m_rot(3,3);
//    // Matriz para transladar a bola pra origem
//    m_trans1 << 1, 0, -meta.x, 0, 1, -meta.y, 0, 0, 1;
//    // Matriz para transladar a bola da origem pra posição original
//    m_trans2 << 1 ,0 ,meta.x, 0, 1, meta.y, 0, 0, 1;

//    m_rot << cos(-theta_dir),-sin(-theta_dir),0,sin(-theta_dir),cos(-theta_dir),0,0,0,1;

//    ph = m_trans2*m_rot*m_trans1*p;

//    pl[0] = ph(0);
//    pl[1] = ph(1) - de;
//    pr[0] = ph(0);
//    pr[1] = ph(1) + de;

//    y_aux = ph(1) - meta.y;

//    yl = y_aux + de;
//    yr = y_aux - de;


//    rho = sqrt(pow(pl[0]-meta.x,2)+pow(pl[1]-meta.y,2));
//    theta = atan2(pl[1]-meta.y,pl[0]-meta.x);

//    if (rho > de){
//        phi_ccw = theta + pi*(2-((de+Kr)/(rho+Kr)))/2;
//    }else{
//        phi_ccw = theta + pi*sqrt(rho/de)/2;
//    }

//    rho = sqrt(pow(pr[0]-meta.x,2)+pow(pr[1]-meta.y,2));
//    theta = atan2(pr[1]-meta.y,pr[0]-meta.x);

//    if (rho > de){
//        phi_cw = theta - pi*(2-((de+Kr)/(rho+Kr)))/2;
//    }else{
//        phi_cw = theta - pi*sqrt(rho/de)/2;
//    }

//    vec[0] = (yl*cos(phi_ccw) - yr*cos(phi_cw))/(2*de);
//    vec[1] = (yl*sin(phi_ccw) - yr*sin(phi_cw))/(2*de);

//    phi = atan2(vec[1],vec[0]) + theta_dir;

//    //cout<<"Este é o phi: "<<phi<<endl; //DELETAR

//    return phi;

}

void Navigation::set_thetaDir(float theta)
{
    theta_dir = theta;
}

float Navigation::get_direction_CPU()
{
    return the_fih;   // Angulo hiperbole+repulsive
//        return -phi;      //Angulo da hiperbole
}

float Navigation::repulsive_angle(float y, float x, Point2d pos)
{
    float alpha;
    if(x - pos.x < 0)
        alpha = atan((y-pos.y)/(x-pos.x))+pi;
    else
        alpha = atan((y-pos.y)/(x-pos.x));

    return alpha;
}

float Navigation::Gaussian_Func(float r){
    float delta = 30.25;
    float G;
    G = pow(M_E,(-pow(r,2)/(2*pow(delta,2))));
    return G;
}

float Navigation::tangencial_repulsive(Robot *robot, Point2d meta, Point2d obstaculo, float r){
    float alpha,omega,zeta,dist_robo_obst;
    int rot;
/*    omega = repulsive_angle(robot->get_pos().x,robot->get_pos().y,meta);  // Angulo entre o robo e a bola
    zeta = repulsive_angle(obstaculo.x,obstaculo.y,meta);*/                  // Angulo entre o obstaculo e a bola

//    if(omega < 0 && zeta < 0){
//        if(zeta <= omega){
//            rot = -1;
//        }
//        else{
//            rot = 1;
//        }
//    }
//    else{usado
//        if(zeta <= omega){
//            rot = 1;
//        }
//        else{
//            rot = -1;
//        }
//    }

    Point2d robo_pos;
    robo_pos = robot->get_pos();
    //    robo_pos.y = robot->get_pos().y;
    dist_robo_obst = euclidean_dist(robo_pos,obstaculo);

    alpha = atan(r/dist_robo_obst);
  //  cout << endl << "repulsive otario: " << alpha*180/pi << endl;
    return alpha;
}

float Navigation::whirlpool_repulsive(Robot *robot, Point2d meta, Point2d obstaculo, float angle_rep){
    float alpha,omega,zeta,dist_robo_obst;
    int rot;
    omega = repulsive_angle(robot->get_pos().x,robot->get_pos().y,meta);  // Angulo entre o robo e a bola
    zeta = repulsive_angle(obstaculo.x,obstaculo.y,meta);                  // Angulo entre o obstaculo e a bola

    rot = -pi/4;

    if(omega < 0 && zeta < 0){
        if(zeta <= omega){
            alpha = angle_rep - rot;
        }
        else{
            alpha = angle_rep + rot;
        }
    }
    else{
        if(zeta <= omega){
            alpha = angle_rep + rot;
        }
        else{
            alpha = angle_rep - rot;
        }
    }
    cout << endl << endl << "rep: " << angle_rep*180/pi << endl << endl;
    return alpha;
}

void Navigation::set_kr(float aux){
    Kr = aux;
}

float Navigation::get_kr(){
    return Kr;
}

void Navigation::set_de(float aux){
    de = aux;
}

float Navigation::get_de(){
    return de;
}

float Navigation::repulsive_Math(Robot *robo, Point2d obj, Point2d ball){
    float rot_angle = pi/2;
    float k_const = 1 , k_larg = 0.05;
    float m = (ball.y-obj.y)/(ball.x-obj.x);
    float norm, psi;
    int a;
    Point2d vec_out, vec_tan, vec, robo_pos;
    MatrixXd rot(2,2);
    MatrixXd vec_tan_aux(2,1), vec_aux(2,1);

    robo_pos = robo->get_pos();
    norm = sqrt(pow(obj.x - robo_pos.x,2) + pow(obj.y - robo_pos.y,2));
    k_const = k_larg*norm;

    if(obj.x <= ball.x){
        if(robo_pos.y-obj.y > m*(robo_pos.x-obj.x))
            a = -1;
        else
            a = 1;
    }
    else {
        if(robo_pos.y-obj.y > m*(robo_pos.x-obj.x))
            a = 1;
        else
            a = -1;
    }

    vec_out.x = ball.x - robo_pos.x;
    vec_out.y = ball.y - robo_pos.y;

    rot << cos(a*rot_angle), sin(a*rot_angle), -sin(a*rot_angle), cos(a*rot_angle);
    vec_aux << vec_out.x, vec_out.y;
    vec_tan_aux = rot*vec_aux;
    vec_tan.x = vec_tan_aux(0);
    vec_tan.y = vec_tan_aux(1);

    vec.x = vec_tan.x + k_const*vec_out.x;
    vec.y = vec_tan.y + k_const*vec_out.y;

    psi = atan2(vec.y,vec.x);
    return -psi;
}
