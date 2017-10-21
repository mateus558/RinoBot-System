#include <iostream>
#include <fstream>
#include <QMessageBox>
#include <QDebug>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <QPainterPath>
#include <errno.h>
#include "soccer_window.h"
#include "ui_soccer_window.h"
#include "utils.h"
#include "fuzzy.h"
#include "game_functions.h"
#include "navigation.h"
#include "mover.h"

using namespace std;

soccer_window::soccer_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::soccer_window)
{
    int i;
    qRegisterMetaType<Vision::Perception>("Vision::Perception");
    qRegisterMetaType<Selector>("Selector");
    //qRegisterMetaType<rVector>("rVector");


    ui->setupUi(this);

    ui->strategy_options->addItem("Strategy 1");
    ui->strategy_options->addItem("Strategy 2");
    ui->strategy_options->addItem("Test");

    area_read = false;
    eye = new Vision;
    fuzzy = new Fuzzy; //instancia o objeto fuzzy na rotina do sistema
    leona = new Game_functions; //instancia o objeto leona na rotina do sistema
    presto = new Game_functions; //instancia o objeto presto na rotina do sistema
    gandalf = new Game_functions; //instancia o objeto gandalf na rotina do sistema
    mover = new Mover; //instancia o objeto mover na rotina do sistema
    run_fuzzy = false; //flag da thread do fuzzy
    run_gandalf = false; //flag da thread da gandalf
    run_leona = false; //flag da thread da leona
    run_presto = false; //flag da thread da presto
    run_mover = false; //flag da thread da mover
    game_started = false;
    game_scene = new QGraphicsScene;
    field = new FieldDraw;
    ball = new BallDraw;

    field->setZValue(-1000);
    team_robots.resize(3);
    team_shapes.resize(3);
    enemy.resize(3);

    for(i = 0; i < 3; i++){
        team_shapes[i] = new RobotDraw;
        enemy[i] = new Enemy;
    }
    eye->set_mode(0);
    eye->togglePlay(true);

    load_serial_cfg();
    Robot::config_serial(serial_config);

    connect(eye, SIGNAL(framesPerSecond(double)), this, SLOT(updateFPS(double)));
    connect(eye, SIGNAL(infoPercepted(Vision::Perception)), this, SLOT(updatePerceptionInfo(Vision::Perception)), Qt::QueuedConnection);  
    connect(fuzzy, SIGNAL(emitRobots(Selector)), this, SLOT(updateFuzzyRobots(Selector)), Qt::QueuedConnection);
    connect(mover, SIGNAL(emitRobots(Selector)), this, SLOT(updateMoverRobots(Selector)), Qt::QueuedConnection);
    //connect(leona, SIGNAL(emitRobots(Selector)), this, SLOT(updateGameFunctionsRobots(Selector)), Qt::QueuedConnection);
    //connect(presto, SIGNAL(emitRobots(Selector)), this, SLOT(updateGameFunctionsRobots(Selector)), Qt::QueuedConnection);
    //connect(gandalf, SIGNAL(emitRobots(Selector)), this, SLOT(updateGameFunctionsRobots(Selector)), Qt::QueuedConnection);
    connect(this, SIGNAL(updateVisionInfo(std::vector<Robot>)), eye, SLOT(updateFuzzyRobots(std::vector<Robot>)));
    connect(this, SIGNAL(updateVisionInfo(std::vector<Robot>)), eye, SLOT(updateMoverRobots(std::vector<Robot>)));


}

soccer_window::~soccer_window()
{
    int i = 0;

    delete eye;
    delete ball;
    delete field;

    for(i = 0; i < team_shapes.size(); i++){
        delete team_shapes[i];
    }
    for(i = 0; i < enemy.size(); i++){
        delete enemy[i];
    }

    delete game_scene;
    delete ui;
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

void soccer_window::prepare_game_scene(int w, int h)
{
    int i;

    game_scene->setBackgroundBrush(Qt::black);
    game_scene->setSceneRect(0, 0, w, h);
    ui->game_view->setScene(game_scene);

    for(i = 0; i < 3; i++){
        team_shapes[i]->pos = team_robots[i].get_centroid();
        game_scene->addItem(team_shapes[i]);
        game_scene->addItem(enemy[i]);
    }
    game_scene->addItem(field);
    game_scene->addItem(ball);
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

void soccer_window::updateFuzzyRobots(Selector selec_robot){
    team_robots[0].set_flag_fuzzy(selec_robot.r3.get_flag_fuzzy());
    team_robots[1].set_flag_fuzzy(selec_robot.r1.get_flag_fuzzy());
    team_robots[2].set_flag_fuzzy(selec_robot.r2.get_flag_fuzzy());

    team_robots[0].set_output_fuzzy(selec_robot.r3.get_output_fuzzy());
    team_robots[1].set_output_fuzzy(selec_robot.r1.get_output_fuzzy());
    team_robots[2].set_output_fuzzy(selec_robot.r2.get_output_fuzzy());

    emit updateVisionInfo(team_robots);
}

void soccer_window::updateMoverRobots(Selector selec_robot){

    team_robots[0].set_lin_vel(make_pair(selec_robot.r3.get_l_vel(), selec_robot.r3.get_r_vel()));
    team_robots[1].set_lin_vel(make_pair(selec_robot.r1.get_l_vel(), selec_robot.r1.get_r_vel()));
    team_robots[2].set_lin_vel(make_pair(selec_robot.r2.get_l_vel(), selec_robot.r2.get_r_vel()));


    if(game_started){
        Robot::send_velocities(team_robots[1].get_channel(),make_pair(team_robots[1].get_r_vel(), team_robots[1].get_l_vel()));
        Robot::send_velocities(team_robots[2].get_channel(),make_pair(team_robots[2].get_r_vel(), team_robots[2].get_l_vel()));
        Robot::send_velocities(team_robots[0].get_channel(),make_pair(team_robots[0].get_r_vel(), team_robots[0].get_l_vel()));

        /*cout << "Presto: " << team_robots[1].get_r_vel() << " " << team_robots[1].get_r_vel() << endl;
        cout << "Gandalf: " << team_robots[2].get_r_vel() << " " << team_robots[2].get_r_vel() << endl;
        cout << "Leona: " << team_robots[0].get_r_vel() << " " << team_robots[0].get_r_vel() << endl;*/
    }else{
        Robot::send_velocities(team_robots[1].get_channel(), make_pair(0, 0));
        Robot::send_velocities(team_robots[2].get_channel(), make_pair(0, 0));
        Robot::send_velocities(team_robots[0].get_channel(), make_pair(0, 0));
    }

    emit updateVisionInfo(team_robots);
}

void soccer_window::updatePerceptionInfo(Vision::Perception percep_info){
    p2dVector enemy_pos(3), team_pos(3);
    pair<vector<Point>, vector<Point> > cont;
    int i,j;

    percep = percep_info;

    if(!area_read){
        map_area = percep.map_area;
        atk_area = percep.atk_area;
        def_area = percep.def_area;
        field->fieldPoints = map_area;
        field->atkPoints = atk_area;
        field->defPoints = def_area;
        prepare_game_scene(percep.img_size.x, percep.img_size.y);
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

        mover->set_centroid_atk(centroid_atk); //salva a area de atk para o gandalf
        mover->set_centroid_def(centroid_def); //salva a area de def para o gandalf
        mover->set_def_area(def_area);
    }
    for(i = 0; i < team_robots.size(); i++){
        cont = team_robots[i].get_contour();
        Point c = team_robots[i].get_centroid();
        team_shapes[i]->angle = team_robots[i].get_angle();
        team_shapes[i]->team_contour = cont.first;
        team_shapes[i]->role_contour = cont.second;
        enemy[i]->pos = percep.enemy_robots[i].get_centroid();
        for(j = 0; j < 3; j++){
            vector<int> lower, upper;

            lower = team_robots[i].get_team_low_color();
            upper = team_robots[i].get_team_upper_color();

            team_shapes[i]->team_color[j] = (lower[j]+upper[j])/2;

            lower = team_robots[i].get_low_color();
            upper = team_robots[i].get_upper_color();

            team_shapes[i]->role_color[j] = (lower[j]+upper[j])/2;
        }
        team_shapes[i]->pos = c;
    }

    leona->set_ball_vel(percep.ball_vel); //salva a velocidade da bola para a leona
    presto->set_ball_vel(percep.ball_vel); //salva a velocidade da bola para o presto
    gandalf->set_ball_vel(percep.ball_vel); //salva a velocidade da bola para o gandalf
    mover->set_ball_vel(percep.ball_vel); //salva a velocidade da bola para a mover

    if(percep.ball_found){
        ui->ball_detec_col_label->setStyleSheet("QLabel { background-color : green; }");
        ui->ball_detec_label->setText("Ball found");
        ball_pos = percep.ball_pos_cm;
        ball->pos = percep.ball_pos;
        ball->contour = percep.ball_contour;
        for(i = 0; i < ball->color.size(); i++){
            ball->color[i] = percep_info.ball_color.second[i] + percep.ball_color.first[i];
            ball->color[i] /= 2;
        }
    }else{
        ui->ball_detec_col_label->setStyleSheet("QLabel { background-color : red; }");
        ui->ball_detec_label->setText("Ball not found");
    }
    game_scene->update();

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
    leona->set_def_area(def_area);
    leona->set_calc_Gandalf(false);
    leona->set_calc_Presto(false);
    leona->set_calc_Leona(true);

    presto->set_to_select(percep.team_robots[1], percep.team_robots[2], percep.team_robots[0]);
    presto->set_def_area(def_area);
    presto->set_calc_Gandalf(false);
    presto->set_calc_Presto(true);
    presto->set_calc_Leona(false);

    gandalf->set_to_select(percep.team_robots[1], percep.team_robots[2], percep.team_robots[0]);
    gandalf->set_def_area(def_area);
    gandalf->set_calc_Gandalf(true);
    gandalf->set_calc_Presto(false);
    gandalf->set_calc_Leona(false);

    mover->set_to_select(percep.team_robots[1], percep.team_robots[2], percep.team_robots[0]);
    mover->set_to_select_iterador(gandalf, presto, leona);
    mover->set_enemy_pos(enemy_pos);
    mover->set_ball_pos(ball_pos);
    mover->set_def_area(def_area);

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
    gandalf->zera_flag_finish();
    presto->zera_flag_finish();
    leona->zera_flag_finish();

    //inicia a thread do fuzzy caso ela nao esteja em execucao
    if(run_fuzzy){
        if(fuzzy->is_running()){
            fuzzy->wait();
        }
        fuzzy->Play();
     }

    if(!run_leona || !run_presto || !run_gandalf){
        fuzzy->wait();

        if (fuzzy->get_flag_finish() && !run_mover){
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

    //inicia a thread da mover caso ela nao esteja em execucao
    if(run_mover){
        if(mover->is_running()){
            mover->wait();
        }
        mover->Play();
    }

    if(!run_mover){
        gandalf->wait();
        presto->wait();
        leona->wait();
        fuzzy->wait();

        if(gandalf->get_flag_finish() && presto->get_flag_finish() && leona->get_flag_finish() && !run_mover){
            run_mover = true;
        }
        else{
            run_mover = false;
        }
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
        //Point convert_C_to_G(Point2d);

        run_fuzzy = true;

        if(!Robot::is_serial_open()){
            Robot::open_serial();
            ui->serial_status_col_label->setStyleSheet("QLabel { background-color : green; }");
            ui->serial_status_label->setText("Serial Open");
        }

        ui->start_game_2->setText("Stop Game");
    }else{
        game_started = false;
        run_fuzzy = false;
        run_leona = false;
        run_presto = false;
        run_gandalf = false;
        run_mover = false;

        Robot::send_velocities(team_robots[1].get_channel(), make_pair(0, 0));
        Robot::send_velocities(team_robots[2].get_channel(), make_pair(0, 0));
        Robot::send_velocities(team_robots[0].get_channel(), make_pair(0, 0));

        ui->start_game_2->setText("Start Game");
        ui->serial_status_col_label->setStyleSheet("QLabel { background-color : red; }");
        ui->serial_status_label->setText("Serial Closed");
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

    mover->set_centroid_atk(centroid_atk); //salva a area de atk para o gandalf
    mover->set_centroid_def(centroid_def); //salva a area de def para o gandalf
    mover->set_def_area(def_area);
    mover->team_changed();

    field->atkPoints = atk_area;
    field->defPoints = def_area;
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


    //caso não seja selecionado nada na change strategy é forçada a nova estrategia
    fuzzy->set_strategy(2);
}

void soccer_window::on_change_strategy_clicked(){
    string strategy = ui->strategy_options->currentText().toUtf8().constData();

    cout << strategy << endl;

    char num_strategy;

    if(strategy == "Test")
        num_strategy = 0;
    else if (strategy == "Strategy 1")
        num_strategy = 1;
    else if (strategy == "Strategy 2")
        num_strategy = 2;

    fuzzy->set_strategy(num_strategy);
}

void soccer_window::on_show_field_areas_checkbox_toggled(bool checked)
{
    eye->show_area(checked);
    field->showFields = checked;

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


