#include <iostream>
#include <string>
#include <sstream>
#include "utils.h"
#include "robot.h"


using namespace std;

Serial Robot::serial;

Robot::Robot(){
    channel = -1;
    centroid = Point(-1, -1);
    last_centroid = centroid;
    centroid_cm = Point2d(0.0, 0.0);
    team_cent = Point(-1, -1);
    color_cent = Point(-1, -1);
    nick = "NULL";
    role = "NULL";
    ID = "NULL";
    low_color_team.assign(3, 0);
    upper_color_team.assign(3, 255);
    low_color.assign(3, 0);
    upper_color.assign(3, 255);
    pos_hist.push_back(Point(-1, -1));
    last_angle = loss_rate = 0.0;
    detected = false;
    pos_tolerance = 2.0; //2cm
    ang_tolerance = 3;
    flag_fuzzy = 0;
}

void Robot::config_serial(SettingsDialog::Settings settings){
    serial.set_serial_settings(settings);
}

void Robot::open_serial(){
    serial.open();
}

void Robot::close_serial(){
    serial.close();
}

bool Robot::is_serial_open(){
    return serial.is_open();
}

bool Robot::send_velocities(int channel, pair<float, float> vels){
    float left_vel = vels.first, right_vel = vels.second;

    if(serial.is_open()){
        //Inicializamos o vetor de bytes a ser transferido
        QByteArray bytes(13, 0x0);
        bytes[0] = 18;
        //Setamos o byte 1 como o número do robô selecionado
        bytes[1] = (char)channel;
        bytes[12] = 19;

        //Criamos uma variável para converter a soma dos bytes de velocidade
        Short2Char cont;
        cont.Short = 0;
        cont.Short += bytes[0] + bytes[1];

        //Criamos uma variável para converter as velocidades em bytes
        Float2Char valor1, valor2;
        //Fazemos com que o valor float da nossa variável Union seja a velocidade informada
        valor1.Float = left_vel;
        // Como o valor da variável Union ocupa a mesma posição de memória dos valores em byte dessa variável, setamos os bytes correspondentes da velocidade no vetor de saída como os bytes da variável Union
        bytes[2] = valor1.Bytes[0];
        bytes[3] = valor1.Bytes[1];
        bytes[4] = valor1.Bytes[2];
        bytes[5] = valor1.Bytes[3];
        // Adicionamos a soma dos bytes da velocidade a variável de contagem de bytes
        cont.Short += valor1.Bytes[0] + valor1.Bytes[1] + valor1.Bytes[2] + valor1.Bytes[3];

        valor2.Float = right_vel;
        bytes[6] = valor2.Bytes[0];
        bytes[7] = valor2.Bytes[1];
        bytes[8] = valor2.Bytes[2];
        bytes[9] = valor2.Bytes[3];
        cont.Short += valor2.Bytes[0] + valor2.Bytes[1] + valor2.Bytes[2] + valor2.Bytes[3];

        //Setamos os bytes de contagemno vetor de saída como os bytes da variável de contagem
        bytes[10] = cont.Bytes[0];
        bytes[11] = cont.Bytes[1];

        //Escrevemos os bytes na porta serial
        serial.write(bytes);
        //Finalizamos a transferência dos dados a serial
        serial.flush();
    }else{
        cerr << "(Serial closed) Couldn't write wheels velocities at serial port." << endl;

        return false;
    }
    return true;
}

bool Robot::encoders_reading(int &robot, pair<float, float> &vels, float &battery){
    //Array de bytes lidos da serial
    QByteArray *dados;
    //Armazena a quantidade de bytes lidos da serial
    unsigned char PosDados;
    char b;

    dados = new QByteArray(17, 0x0);
    PosDados = 0;

    if(!serial.is_open()){
        cerr << "Couldn't read information from serial. (Serial closed)" << endl;
        return false;
    }

    // Executamos a leitura de bytes enquanto houver um byte disponível na serial
    while (serial.bytes_available() > 0){
        //Lemos um byte da serial para a variável b
        serial.read(&b, 1);
        //Adicionamos b ao array de entrada de bytes
        dados->data()[PosDados] = b;
        //Incrementamos a quantidade de bytes recebidos
        PosDados++;

        //Obtemos o número do robô
        int NumRobo = (int)dados->at(1);
        robot = NumRobo;

        if (PosDados == 9){
            //Se 9 bytes forem recebidos e o primeiro e o último byte são respectivamente 20 e 21. então esta é uma mensagem leitura da bateria
            if (dados->at(0) ==20 && dados->at(8)==21){
                unsigned short cont = 0;
                unsigned char i = 0;

                //Somamos os bytes do valor da bateria
                for (i=0x2; i <= 0x5; i+=0x1 ){
                    cont += (unsigned char)dados->at(i);
                }
                Short2Char conversor;
                //Obtemos a contagem de bytes enviada pelo robô
                conversor.Bytes[0] = dados->at(6);
                conversor.Bytes[1] = dados->at(7);
                //Se a contagem enviada pelo robô for igual a contagem feita acima, então os bytes chegaram corretamente
                if (cont == conversor.Short){
                    //Convertemos os bytes recebidos da bateria em um float
                    Float2Char bateria;
                    bateria.Bytes[0] = dados->at(2);
                    bateria.Bytes[1] = dados->at(3);
                    bateria.Bytes[2] = dados->at(4);
                    bateria.Bytes[3] = dados->at(5);
                    //Processamos o valor de bateria recebido
                    battery = bateria.Float;
                }
                //Informamos que a contagem atual de bytes recebidos é igual a zero
                PosDados = 0;
            }

        }else if (PosDados == 13){
            //Se 13 bytes forem recebidos e o primeiro e o último são respectivamente 18 e 19 então esta é uma mensagem de leitura das velocidades das rodas
             if (dados->at(0) ==18 && dados->at(12)==19){
                unsigned short cont =0;
                unsigned char i = 0;
                for (i=0x2; i <= 0x9; i+=0x1 )
                {
                  cont += (unsigned char)dados->at(i);
                }
                Short2Char conversor;
                conversor.Bytes[0] = dados->at(10);
                conversor.Bytes[1] = dados->at(11);
                if (cont == conversor.Short){
                    //Convertemos os bytes das velocidades em float
                    Float2Char velEsquerda, velDireita;
                    velEsquerda.Bytes[0] = dados->at(2);
                    velEsquerda.Bytes[1] = dados->at(3);
                    velEsquerda.Bytes[2] = dados->at(4);
                    velEsquerda.Bytes[3] = dados->at(5);
                    velDireita.Bytes[0] = dados->at(6);
                    velDireita.Bytes[1] = dados->at(7);
                    velDireita.Bytes[2] = dados->at(8);
                    velDireita.Bytes[3] = dados->at(9);

                    //Processamos os valores de velocidade recebidos
                    vels.first  = (double) velEsquerda.Float;
                    vels.second = (double) velDireita.Float;
                }
                PosDados = 0;
            }
        }
    }

    return true;
}

void Robot::set_angle(double angle)
{
    last_angle = this->angle;
    this->angle = angle;
}

double Robot::get_angle()
{
    return this->angle;
}

double Robot::get_ang_vel(){
    return this->w;
}

double Robot::get_predic_angle()
{
    return this->ang_predict;
}

/**
 * @brief Robot::compute_velocity
 * Computa a velocidade linear e angular do robo em px/s e graus/s, respectivamente
 * @param deltaT - intervalo de tempo entre os frames
 *
 */
void Robot::compute_velocity(double deltaT){
    _vel.first = (centroid.x - last_centroid.x) / deltaT;
    _vel.second = (centroid.y - last_centroid.y) / deltaT;

    w = (angle - last_angle) / deltaT;
}

/**
 * @brief Robot::predict_info - Preve a posicao o angulo do robo no proximo frame.
 * @param deltaT - intervalo de tempo entre os frames
 */
void Robot::predict_info(double deltaT){

   centroid_predict.x = centroid.x + (_vel.first)*deltaT;
   centroid_predict.y = centroid.y + (_vel.second)*deltaT;
   ang_predict = angle + w*deltaT;

}


pair<float, float> Robot::get_velocities(){
    return this->_vel;
}

double Robot::get_last_angle()
{
    return this->last_angle;
}

void Robot::set_centroid(Point p)
{
    last_centroid = centroid;
    this->centroid = p;
    centroid_cm.x = centroid.x * X_CONV_CONST;
    centroid_cm.y = centroid.y * Y_CONV_CONST;

    add_pos_hist(p);
}

Point Robot::get_centroid()
{   if(centroid == Point(-1, -1)) return last_centroid;
    return this->centroid;
}

Point Robot::get_last_centroid(){
    return last_centroid;
}

Point Robot::get_predic_centroid()
{
    return this->centroid_predict;
}

pair<vector<Point>, vector<Point> > Robot::get_contour()
{
    pair<pVector, pVector> p;

    p.first = team_contour;
    p.second = role_contour;

    return p;
}


Point2d Robot::get_pos(){
    return centroid_cm;
}

void Robot::set_line_slope(Point p){
    this->line_slope = p;
}

Point Robot::get_line_slope(){
    return line_slope;
}

void Robot::add_pos_hist(Point p){
    if(pos_hist.size() == 5){
        pos_hist.pop_back();
    }
    pos_hist.push_back(p);
}

Point Robot::get_from_pos_hist(int rank){
    return pos_hist[pos_hist.size() - (rank + 1)];
}

void Robot::was_detected(bool detected){
    this->detected = detected;

    if((n_loss + n_detected)%500 == 0){
        loss_rate = n_loss / 500;
    }

    if(!detected){
        n_loss++;
    }else n_detected++;
}

bool Robot::is_detected(){
    return this->detected;
}

double Robot::get_loss_rate(){
    return loss_rate;
}

void Robot::set_color_cent(Point p)
{
    this->color_cent = p;
}

Point Robot::get_color_cent()
{
    return this->color_cent;
}

void Robot::set_team_cent(Point p)
{
    this->team_cent = p;
}

void Robot::set_team_contour(vector<Point> team_contour)
{
    this->team_contour = team_contour;
}

void Robot::set_role_contour(vector<Point> role_contour)
{
    this->role_contour = role_contour;
}

Point Robot::get_team_cent()
{
    return this->team_cent;
}

void Robot::set_channel(int channel)
{
    this->channel = channel;
}

void Robot::set_role(string role)
{
    this->role = role;
}

void Robot::set_nick(string nick)
{
    this->nick = nick;
}

void Robot::set_ID(string ID)
{
    this->ID = ID;
}

void Robot::set_team_low_color(vector<int> low_color){
    this->low_color_team = low_color;
}

void Robot::set_team_upper_color(vector<int> upper_color){
    this->upper_color_team = upper_color;
}

vector<int> Robot::get_team_low_color(){
    return this->low_color_team;
}

vector<int> Robot::get_team_upper_color(){
    return this->upper_color_team;
}

void Robot::set_low_color(vector<int> low_color)
{
    this->low_color = low_color;
}

void Robot::set_upper_color(vector<int> upper_color)
{
    this->upper_color = upper_color;
}

vector<int> Robot::get_low_color()
{
    return this->low_color;
}

vector<int> Robot::get_upper_color()
{
    return this->upper_color;
}

string Robot::get_nick()
{
    return this->nick;
}

string Robot::get_role()
{
    return this->role;
}

string Robot::get_ID()
{
    return this->ID;
}

int Robot::get_channel()
{
    return this->channel;
}

void Robot::set_flag_fuzzy(int output, Point centroid_atk, Point centroid_def, Point2d ball){
    if(output == 0)
    {
        this->flag_fuzzy = output;
       // cout << "Robo deve Defender Arduamente!"<< endl;
    }
    else if(output == 1)
    {
        if (ball.x < centroid_atk.x){
            if (ball.x < centroid_def.x + 75 && ball.y < centroid_def.y + 47 && ball.y > centroid_def.y - 47){
                this->flag_fuzzy = 0;
                //cout << nick <<" deve Defender Arduamente!"<< endl;
            }
            else{
                this->flag_fuzzy = output;
                //cout << nick <<" deve ser Um bom Volante!"<< endl;
            }
        }
        else{
            if (ball.x > centroid_def.x - 75 && ball.y < centroid_def.y + 47 && ball.y > centroid_def.y - 47){
                this->flag_fuzzy = 0;
                //cout << nick <<" deve Defender Arduamente2!"<< endl;
            }
            else{
                this->flag_fuzzy = output;
                //cout << nick <<" deve ser Um bom Volante2!"<< endl;
            }
        }
        /*if(centroid_cm.x < centroid_def.x){
            if((ball.x > centroid_def.x - 75 && ball.x < centroid_def.x + 15) && (ball.y < centroid_def.y + 35 && ball.y > centroid_def.y - 35)){
                if(centroid_cm.x > ball.x){
                    cout << nick <<" deve Defender Arduamente!"<< endl;
                    this->flag_fuzzy = 0;
                }else{
                    this->flag_fuzzy = output;
                    cout << nick <<" deve ser Um bom Volante!3"<< endl;
                }
            }

        }else if(centroid_cm.x > centroid_def.x){
            if((ball.x < centroid_def.x + 75 && ball.x > centroid_def.x - 15) && (ball.y < centroid_def.y + 35 && ball.y > centroid_def.y - 35)){
                if(centroid_cm.x < ball.x){
                    this->flag_fuzzy = 0;
                    cout << nick <<"Robo deve Defender Arduamente!"<< endl;
                }else{
                    this->flag_fuzzy = output;
                    cout << nick << " deve ser Um bom Volante!2"<< endl;
                }
            }else{
                this->flag_fuzzy = output;
                cout << nick <<" deve ser Um bom Volante!1"<< endl;
            }
        }else{
            this->flag_fuzzy = output;
            cout << nick <<" deve ser Um bom Volante!1"<< endl;
        }
        cout << nick <<" deve ser Um bom Volante!"<< endl;*/
    }
    else if(output == 2)
    {
        this->flag_fuzzy = 2;
        //cout << nick <<" deve ser Um bom Meia!"<< endl;
    }
    else if(output == 3)
    {
         if(centroid_cm.x < centroid_atk.x){
            if((ball.x > centroid_atk.x - 75) && (ball.y < centroid_atk.y + 45 && ball.y > centroid_atk.y - 45)){
                if(centroid_cm.x < ball.x){
                    this->flag_fuzzy = 3;
                    //cout << nick <<" deve Atacar Ferozmente!" << endl;
                }else{
                    this->flag_fuzzy = 2;
                   // cout << nick <<" deve ser Um bom Meia!4"<< endl;
                }
            }else{
                this->flag_fuzzy = 2;
                //cout << nick <<" deve ser Um bom Meia!5"<< endl;
            }
         }else if(centroid_cm.x > centroid_atk.x){
            if(ball.x < centroid_atk.x + 75 && (ball.y < centroid_atk.y + 45 && ball.y > centroid_atk.y - 45)){
                if(centroid_cm.x > ball.x){
                    this->flag_fuzzy = 3;
                    //cout << nick <<" deve Atacar Ferozmente!" << endl;
                }else{
                    this->flag_fuzzy = 2;
                    //cout << nick <<" deve ser Um bom Meia!1"<< endl;

                }
            }else{
                this->flag_fuzzy = 2;
                //cout << nick <<" deve ser Um bom Meia!2"<< endl;

            }
         }else{
             this->flag_fuzzy = 2;
            //cout << nick <<" deve ser Um bom Meia!3"<< endl;

         }
        //cout << "Robo deve Atacar Ferozmente!" << endl;
    }
    else if(output == 4)
    {
        this->flag_fuzzy = 4;
        //cout << nick <<" deve Catar Ferozmente!" << endl;
    }
    else{
    this->flag_fuzzy = output;
    }
}

void Robot::set_flag_fuzzy(int output){
    this->flag_fuzzy = output;
}

int Robot::get_flag_fuzzy(){
    return flag_fuzzy;
}

void Robot::set_output_fuzzy(Point2d output){
    this->output_fuzzy = output;
}

Point2d Robot::get_output_fuzzy(){
    return this->output_fuzzy;
}

double Robot::min_function(double p, double q){
    if(p <= q)
    {
        return p;
    }
    else
        return q;
}

double Robot::max_function(double p, double q){
    if(p >= q)
    {
        return p;
    }
    else
        return q;
}

void Robot::set_lin_vel(pair<float, float> vels){
    this->vel = vels;
}

float Robot::get_l_vel(){
    return vel.first;
}
float Robot::get_r_vel(){
    return vel.second;
}
