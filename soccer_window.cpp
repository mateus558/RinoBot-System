#include <iostream>
#include <fstream>
#include <QMessageBox>
#include <QDebug>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "soccer_window.h"
#include "ui_soccer_window.h"
#include "fuzzy.h"
#include "utils.h"
#include "game_functions.h"
#include "navigation.h"

using namespace std;

soccer_window::soccer_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::soccer_window)
{
    qRegisterMetaType<Vision::Perception>("Vision::Perception");
    qRegisterMetaType<Selector>("Selector");
    qRegisterMetaType<rVector>("rVector");


    ui->setupUi(this);
    ui->cam_id_spinBox->setValue(0);
    area_read = false;
    eye = new Vision;
    fuzzy = new Fuzzy; //instancia o objeto fuzzy na rotina do sistema
    leona = new Game_functions; //instancia o objeto leona na rotina do sistema
    presto = new Game_functions; //instancia o objeto presto na rotina do sistema
    gandalf = new Game_functions; //instancia o objeto gandalf na rotina do sistema
    run_fuzzy = false; //flag da thread do fuzzy
    run_leona = false; //frlag da thread da leona
    run_presto = false; //flag da thread da presto
    run_gandalf = false; //flag da thread da gandalf

    game_started = false;
    team_robots.resize(3);

    eye->set_mode(0);
    load_serial_cfg();
    Robot::config_serial(serial_config);

    connect(eye, SIGNAL(processedImage(QImage)), this, SLOT(updateVisionUI(QImage)));
    connect(eye, SIGNAL(framesPerSecond(double)), this, SLOT(updateFPS(double)));
    connect(eye, SIGNAL(infoPercepted(Vision::Perception)), this, SLOT(updatePerceptionInfo(Vision::Perception)), Qt::QueuedConnection);  
    connect(fuzzy, SIGNAL(emitRobots(Selector)), this, SLOT(updateFuzzyRobots(Selector)), Qt::QueuedConnection);
    connect(leona, SIGNAL(emitRobots(Selector)), this, SLOT(updateGameFunctionsRobots(Selector)), Qt::QueuedConnection);
    connect(presto, SIGNAL(emitRobots(Selector)), this, SLOT(updateGameFunctionsRobots(Selector)), Qt::QueuedConnection);
    connect(gandalf, SIGNAL(emitRobots(Selector)), this, SLOT(updateGameFunctionsRobots(Selector)), Qt::QueuedConnection);
    connect(this, SIGNAL(rupdateVisionInfo(rVector)), eye, SLOT(updateFuzzyRobots(rVector)), Qt::QueuedConnection);
    connect(this, SIGNAL(updateVisionInfo(rVector)), eye, SLOT(updateGameFunctionsRobots(rVector)), Qt::QueuedConnection);
}

void soccer_window::load_serial_cfg(){
    fstream in;
    string name;
    int flowControl, parity, stopBits, dataBits;

    in.open("Config/serial.cfg", fstream::in);

    in >> name;
    in >> serial_config.baudRate;
    in >> flowControl;
    in >> parity;
    in >> stopBits;
    in >> dataBits;

    in.close();

    serial_config.name = QString::fromStdString(name);
    serial_config.flowControl = QSerialPort::FlowControl(flowControl);
    serial_config.parity = QSerialPort::Parity(parity);
    serial_config.stopBits = QSerialPort::StopBits(stopBits);
    serial_config.dataBits = QSerialPort::DataBits(dataBits);
}

void soccer_window::closeEvent(QCloseEvent *event){
    QWidget::closeEvent(event);
    Robot::close_serial();
    eye->Stop();
    eye->wait();
    eye->release_cam();
}

void soccer_window::receiveSerialSettings(SettingsDialog::Settings serial_config){
    Robot::config_serial(serial_config);
}

void soccer_window::updateVisionUI(QImage img){
    if(!img.isNull()){
        ui->game_view->setAlignment(Qt::AlignCenter);
        ui->game_view->setPixmap(QPixmap::fromImage(img).scaled(ui->game_view->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

void soccer_window::updateFuzzyRobots(Selector selec_robot){
    team_robots[0].set_flag_fuzzy(selec_robot.r3.get_flag_fuzzy());
    team_robots[1].set_flag_fuzzy(selec_robot.r1.get_flag_fuzzy());
    team_robots[2].set_flag_fuzzy(selec_robot.r2.get_flag_fuzzy());

    emit updateVisionInfo(team_robots);
}

void soccer_window::updateGameFunctionsRobots(Selector selec_robot){
    team_robots[0].set_lin_vel(make_pair(selec_robot.r3.get_l_vel(), selec_robot.r3.get_r_vel()));
    team_robots[1].set_lin_vel(make_pair(selec_robot.r1.get_l_vel(), selec_robot.r1.get_r_vel()));
    team_robots[2].set_lin_vel(make_pair(selec_robot.r2.get_l_vel(), selec_robot.r2.get_r_vel()));
    if(game_started){
        Robot::send_velocities(team_robots[1].get_channel(),make_pair(team_robots[1].get_r_vel(), team_robots[1].get_l_vel()));
        Robot::send_velocities(team_robots[2].get_channel(),make_pair(team_robots[2].get_r_vel(), team_robots[2].get_l_vel()));
        Robot::send_velocities(team_robots[0].get_channel(),make_pair(team_robots[0].get_r_vel(), team_robots[0].get_l_vel()));
    }else{
        Robot::send_velocities(team_robots[1].get_channel(), make_pair(0, 0));
        Robot::send_velocities(team_robots[2].get_channel(), make_pair(0, 0));
        Robot::send_velocities(team_robots[0].get_channel(), make_pair(0, 0));
    }
    emit updateVisionInfo(team_robots);
}

void soccer_window::updatePerceptionInfo(Vision::Perception percep_info){
    p2dVector enemy_pos(3), team_pos(3);

    percep = percep_info;

    if(!area_read){
        map_area = percep.map_area;
        atk_area = percep.atk_area;
        def_area = percep.def_area;
        area_read = true;
        centroid_atk = (atk_area[2] + atk_area[3] + atk_area[4] + atk_area[5])/4;
        centroid_def = (def_area[2] + def_area[3] + def_area[4] + def_area[5])/4;

        centroid_atk.x = centroid_atk.x * X_CONV_CONST;
        centroid_atk.y = centroid_atk.y * Y_CONV_CONST;

        centroid_def.x = centroid_def.x * X_CONV_CONST;
        centroid_def.y = centroid_def.y * Y_CONV_CONST;

        fuzzy->set_centroid_atk(centroid_atk); //salva a area de atk para o fuzzy
        fuzzy->set_centroid_def(centroid_def); //salva a area de def para o fuzzy

        leona->set_centroid_atk(centroid_atk); //salva a area de atk para a leona
        leona->set_centroid_def(centroid_def); //salva a area de def para a leona
        leona->set_def_area(def_area);

        presto->set_centroid_atk(centroid_atk); //salva a area de atk para o presto
        presto->set_centroid_def(centroid_def); //salva a area de def para o presto
        presto->set_def_area(def_area);

        gandalf->set_centroid_atk(centroid_atk); //salva a area de atk para o gandalf
        gandalf->set_centroid_def(centroid_def); //salva a area de def para o gandalf
        gandalf->set_def_area(def_area);
    }

    leona->set_ball_vel(percep.ball_vel); //salva a velocidade da bola para a leona
    presto->set_ball_vel(percep.ball_vel); //salva a velocidade da bola para o presto
    gandalf->set_ball_vel(percep.ball_vel); //salva a velocidade da bola para o gandalf

    if(percep.ball_found){
        ui->ball_detec_col_label->setStyleSheet("QLabel { background-color : green; }");
        ui->ball_detec_label->setText("Ball found");
        ball_pos = percep.ball_pos_cm;
    }else{
        ui->ball_detec_col_label->setStyleSheet("QLabel { background-color : red; }");
        ui->ball_detec_label->setText("Ball not found");
    }

    enemy_pos[0] = percep.enemy_robots[0].get_pos();
    enemy_pos[1] = percep.enemy_robots[1].get_pos();
    enemy_pos[2] = percep.enemy_robots[2].get_pos();

    team_pos[0] = percep.team_robots[0].get_pos(); //Leona
    team_pos[1] = percep.team_robots[1].get_pos(); //Gandalf
    team_pos[2] = percep.team_robots[2].get_pos(); //Presto
    team_robots = percep.team_robots;

    leona->set_ball_pos(ball_pos); //Salva a posicao da bola para a leona
    leona->set_enemy_pos(enemy_pos); //Salva a posicao dos inimigos para a leona
    leona->set_team_pos(team_pos); //Salva a posicao do time para a leona

    presto->set_ball_pos(ball_pos); //Salva a posicao da bola para o presto
    presto->set_enemy_pos(enemy_pos); //Salva a posicao dos inimigos para o presto
    presto->set_team_pos(team_pos); //Salva a posicao do time para o presto

    gandalf->set_ball_pos(ball_pos); //Salva a posicao da bola para o gandalf
    gandalf->set_enemy_pos(enemy_pos); //Salva a posicao dos inimigos para o gandalf
    gandalf->set_team_pos(team_pos); //Salva a posicao do time para o gandalf

    fuzzy->set_to_select(percep.team_robots[1], percep.team_robots[2], percep.team_robots[0]); //Gandalf, Presto e Leona nesta ordem
    fuzzy->set_ball_pos(ball_pos); //Salva a posicao da bola para o fuzzy
    fuzzy->set_enemy_pos(enemy_pos); //Salva a posicao dos inimigos para o fuzzy

    leona->set_to_select(percep.team_robots[1], percep.team_robots[2], percep.team_robots[0]);
    leona->set_enemy_pos(enemy_pos);
    leona->set_ball_pos(ball_pos);
    leona->set_def_area(def_area);
    leona->set_calc_Gandalf(false);
    leona->set_calc_Presto(false);
    leona->set_calc_Leona(true);

    presto->set_to_select(percep.team_robots[1], percep.team_robots[2], percep.team_robots[0]);
    presto->set_enemy_pos(enemy_pos);
    presto->set_ball_pos(ball_pos);
    presto->set_def_area(def_area);
    presto->set_calc_Gandalf(false);
    presto->set_calc_Presto(true);
    presto->set_calc_Leona(false);

    gandalf->set_to_select(percep.team_robots[1], percep.team_robots[2], percep.team_robots[0]);
    gandalf->set_enemy_pos(enemy_pos);
    gandalf->set_ball_pos(ball_pos);
    gandalf->set_def_area(def_area);
    gandalf->set_calc_Gandalf(true);
    gandalf->set_calc_Presto(false);
    gandalf->set_calc_Leona(false);

    if(percep.team_robots[1].is_detected()){
        ui->gandalf_detec_col_label->setStyleSheet("QLabel { background-color : green; }");
        ui->gandalf_detec_label->setText("Detected");
    }else{
        ui->gandalf_detec_col_label->setStyleSheet("QLabel { background-color : red; }");
        ui->gandalf_detec_label->setText("Not Detected");
    }
    if(percep.team_robots[0].is_detected()){
        ui->leona_detec_col_label->setStyleSheet("QLabel { background-color : green; }");
        ui->leona_detec_label->setText("Detected");
    }else{
        ui->leona_detec_col_label->setStyleSheet("QLabel { background-color : red; }");
        ui->leona_detec_label->setText("Not Detected");
    }
    if(percep.team_robots[2].is_detected()){
        ui->presto_detec_col_label->setStyleSheet("QLabel { background-color : green; }");
        ui->presto_detec_label->setText("Detected");
    }else{
        ui->presto_detec_col_label->setStyleSheet("QLabel { background-color : red; }");
        ui->presto_detec_label->setText("Not Detected");
    }

    fuzzy->zera_flag_finish();

    //inicia a thread do fuzzy caso ela nao esteja em execucao
    if(run_fuzzy){
        if(fuzzy->is_running()){
            fuzzy->wait();
        }
        fuzzy->Play();
     }

    if(!run_leona || !run_presto || !run_gandalf){
        fuzzy->wait();

        if (fuzzy->get_flag_finish() && !run_leona && !run_presto && !run_gandalf){
            run_leona = true;
            run_presto = true;
            run_gandalf = true;
        }else{
            run_leona = false;
            run_presto = false;
            run_gandalf = false;
        }
    }

    //inicia a thread da leona caso ela nao esteja em execucao
    if(run_leona){
        if(leona->is_running()){
            leona->wait();
        }
        leona->Play();
     }

    //inicia a thread do presto caso ela nao esteja em execucao
    if(run_presto){
        if(presto->is_running()){
            presto->wait();
        }
        presto->Play();
    }

    //inicia a thread do gandalf caso ela nao esteja em execucao
    if(run_gandalf){
        if(gandalf->is_running()){
            gandalf->wait();
        }
        gandalf->Play();
     }
}

void soccer_window::updateFPS(double fps){
    ui->fps_lcd->display(fps);
}

void soccer_window::updateSerialSettings(SettingsDialog::Settings settings){
    Robot::config_serial(settings);
}

void soccer_window::on_start_game_2_clicked()
{
    if(!game_started){
        game_started = true;
        Point convert_C_to_G(Point2d);

        run_fuzzy = true;

        if(!Robot::is_serial_open()){
            Robot::open_serial();
        }

        ui->start_game_2->setText("Stop Game");
    }else{
        game_started = false;
        run_fuzzy = false;
        run_leona = false;
        run_presto = false;
        run_gandalf = false;

        Robot::send_velocities(team_robots[1].get_channel(), make_pair(0, 0));
        Robot::send_velocities(team_robots[2].get_channel(), make_pair(0, 0));
        Robot::send_velocities(team_robots[0].get_channel(), make_pair(0, 0));

        ui->start_game_2->setText("Start Game");
    }
}

void soccer_window::on_start_game_clicked()
{
    cam_id = ui->cam_id_spinBox->value();

    if(eye->isStopped()){
        if(!eye->open_camera(cam_id)){
            QMessageBox msgBox;
            msgBox.setText("The camera could not be opened!");
            msgBox.exec();
            return;
        }

        eye->Play();
        ui->start_game->setText("Stop Capture");
    }else{
        eye->Stop();
        eye->wait();
        eye->release_cam();

        ui->start_game->setText("Start Capture");
    }
}

void soccer_window::on_switch_fields_clicked()
{
    pVector aux;

    aux = atk_area;
    atk_area = def_area;
    def_area = aux;

    eye->switch_teams_areas();
    eye->set_atk_area(atk_area);
    eye->set_def_area(def_area);

    centroid_atk = (atk_area[2] + atk_area[3] + atk_area[4] + atk_area[5])/4;
    centroid_def = (def_area[2] + def_area[3] + def_area[4] + def_area[5])/4;

    centroid_atk.x = centroid_atk.x * X_CONV_CONST;
    centroid_atk.y = centroid_atk.y * Y_CONV_CONST;

    centroid_def.x = centroid_def.x * X_CONV_CONST;
    centroid_def.y = centroid_def.y * Y_CONV_CONST;

    fuzzy->set_centroid_atk(centroid_atk); //salva a area de atk para o fuzzy
    fuzzy->set_centroid_def(centroid_def); //salva a area de def para o fuzzy

    leona->set_centroid_atk(centroid_atk); //salva a area de atk para a leona
    leona->set_centroid_def(centroid_def); //salva a area de def para a leona
    leona->set_def_area(def_area);
    leona->team_changed();

    presto->set_centroid_atk(centroid_atk); //salva a area de atk para o presto
    presto->set_centroid_def(centroid_def); //salva a area de def para o presto
    presto->set_def_area(def_area);
    presto->team_changed();

    gandalf->set_centroid_atk(centroid_atk); //salva a area de atk para o gandalf
    gandalf->set_centroid_def(centroid_def); //salva a area de def para o gandalf
    gandalf->set_def_area(def_area);
    gandalf->team_changed();
}

void soccer_window::on_read_parameters_clicked()
{
    int ch;
    char cwd[1024];
    vector<Robot> robots = eye->get_robots();
    vector<int> low_color(3);
    vector<int> upper_color(3);
    Point convert_C_to_G(Point2d);
    vector<int> low_team_color(3);
    vector<int> upper_team_color(3);
    pair<vector<int>, vector<int> > ball_range;
    string path, role, ID;
    ifstream file, t1_file, t2_file, ball;

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        fprintf(stdout, "Current working dir: %s\n", cwd);
    else
        perror("getcwd() error");

    ball_range.first.resize(3);
    ball_range.second.resize(3);

    t1_file.open("Config/T1", fstream::in);

    if(!t1_file){
        cerr << "Team 1 config could not be opened!" << endl;
    }

    t1_file >> low_team_color[0] >> low_team_color[1] >> low_team_color[2];
    t1_file >> upper_team_color[0] >> upper_team_color[1] >> upper_team_color[2];

    t1_file.close();
    t1_file.clear();

    for(auto itr = robots.begin(); itr != robots.end(); ++itr){
        path = "Config/" + (*itr).get_nick();
        file.open(path.c_str());

        if(!file){
            cerr << (*itr).get_nick() << " config could not be opened!" << endl;
        }

        file >> low_color[0] >> low_color[1] >> low_color[2];
        file >> upper_color[0] >> upper_color[1] >> upper_color[2];
        file >> ch;
        file >> role;
        file >> ID;

        (*itr).set_team_low_color(low_team_color);
        (*itr).set_team_upper_color(upper_team_color);
        (*itr).set_low_color(low_color);
        (*itr).set_upper_color(upper_color);
        (*itr).set_ID(ID);
        (*itr).set_channel(ch);
        (*itr).set_role(role);

        file.close();
        file.clear();
    }

    t2_file.open("Config/T2", fstream::in);

    if(!t2_file){
        cerr << "Team 2 config could not be opened!" << endl;
    }

    t2_file >> low_team_color[0] >> low_team_color[1] >> low_team_color[2];
    t2_file >> upper_team_color[0] >> upper_team_color[1] >> upper_team_color[2];
    t2_file.close();
    t2_file.clear();

    for(auto itr = robots.begin() + 3; itr != robots.end(); ++itr){
        (*itr).set_team_low_color(low_team_color);
        (*itr).set_team_upper_color(upper_team_color);
    }

    eye->set_robots(robots);
    ui->gandalf_role_label->setText(QString::fromStdString(robots[1].get_role()));
    ui->leona_role_label->setText(QString::fromStdString(robots[0].get_role()));
    ui->presto_role_label->setText(QString::fromStdString(robots[2].get_role()));
    ball.open("Config/ball", fstream::in);

    if(!ball){
        cout << "Ball config could not be opened!" << endl;
    }

    ball >> ball_range.first[0] >> ball_range.first[1] >> ball_range.first[2];
    ball >> ball_range.second[0] >> ball_range.second[1] >> ball_range.second[2];
    ball.close();
    ball.clear();

    eye->set_ball(ball_range);
}

void soccer_window::on_show_field_areas_checkbox_toggled(bool checked)
{
    eye->show_area(checked);
}

void soccer_window::on_show_rnames_checkBox_toggled(bool checked)
{
    eye->show_names(checked);
}

void soccer_window::on_show_rcentroids_checkbox_toggled(bool checked)
{
    eye->show_centers(checked);
}

void soccer_window::on_show_visionlogs_checkbox_toggled(bool checked)
{
    eye->show_errors(checked);
}

soccer_window::~soccer_window()
{
    delete eye;
    delete ui;
}
