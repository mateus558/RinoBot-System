#include <iostream>
#include <fstream>
#include <QMessageBox>
#include <QDebug>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "soccer_window.h"
#include "ui_soccer_window.h"
#include "serial.h"
#include "utils.h"

using namespace std;

soccer_window::soccer_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::soccer_window)
{
    ui->setupUi(this);
    serial_sett = new SettingsDialog;
    serial = new Serial;
    eye = new Vision;
    eye->set_mode(0);

    qRegisterMetaType<pVector>("pVector");
    qRegisterMetaType<rVector>("rVector");
    qRegisterMetaType<Point2d>("Point2d");


    connect(serial_sett, SIGNAL(serial_settings(SettingsDialog::Settings)), this, SLOT(updateSerialSettings(SettingsDialog::Settings)));
    connect(eye, SIGNAL(processedImage(QImage)), this, SLOT(updateVisionUI(QImage)));
    connect(eye, SIGNAL(framesPerSecond(double)), this, SLOT(updateFPS(double)));
    connect(eye, SIGNAL(ballPos(Point2d)), this, SLOT(updateBallPos(Point2d)), Qt::QueuedConnection);
    connect(eye, SIGNAL(mapPoints(pVector)), this, SLOT(updateMapPoints(pVector)), Qt::QueuedConnection);
    connect(eye, SIGNAL(atkPoints(pVector)), this, SLOT(updateAtkPoints(pVector)), Qt::QueuedConnection);
    connect(eye, SIGNAL(defPoints(pVector)), this, SLOT(updateDefPoints(pVector)), Qt::QueuedConnection);
    connect(eye, SIGNAL(robotsInfo(rVector)), this, SLOT(updateRobotsInfo(rVector)), Qt::QueuedConnection);
}

void soccer_window::closeEvent(QCloseEvent *event){
    QWidget::closeEvent(event);

    eye->Stop();
    eye->wait();
    eye->release_cam();
}

void soccer_window::updateVisionUI(QImage img){
    if(!img.isNull()){
        ui->game_view->setAlignment(Qt::AlignCenter);
        ui->game_view->setPixmap(QPixmap::fromImage(img).scaled(ui->game_view->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

void soccer_window::updateRobotsInfo(const rVector &robots){
    this->robots = robots;
}

void soccer_window::updateBallPos(const Point2d &ball_pos){
    this->ball_pos = ball_pos;
}

void soccer_window::updateFPS(double fps){
    ui->fps_lcd->display(fps);
}

void soccer_window::updateMapPoints(const pVector &map_area){
    this->map_area = map_area;
}

void soccer_window::updateAtkPoints(const pVector &atk_area){
    this->atk_area = atk_area;
}

void soccer_window::updateDefPoints(const pVector &def_area){
    this->def_area = def_area;
}

void soccer_window::updateSerialSettings(SettingsDialog::Settings settings){
    this->settings = settings;
    serial->set_serial_settings(settings);
}

void soccer_window::on_start_game_clicked()
{
    int cam_id = CV_CAP_FIREWIRE;

    if(eye->isStopped()){
        if(!eye->open_camera(cam_id)){
            QMessageBox msgBox;
            msgBox.setText("The camera could not be opened!");
            msgBox.exec();
        }

        eye->Play();
        ui->start_game->setText("Stop Game");
    }else{
        eye->Stop();
        eye->wait();
        eye->release_cam();
        ui->start_game->setText("Start Game");
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
}

void soccer_window::on_showAreasRadioButton_toggled(bool checked)
{
    if(checked){
        eye->show_area(true);
    }else{
        eye->show_area(false);
    }
}

soccer_window::~soccer_window()
{
    delete eye;
    delete serial;
    delete serial_sett;
   // delete ui;
}

void soccer_window::on_read_parameters_clicked()
{
    int ch;
    char cwd[1024];
    vector<Robot> robots = eye->get_robots();
    vector<int> low_color(3);
    vector<int> upper_color(3);
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
        cout << "Team 1 config could not be opened!" << endl;
    }

    t1_file >> low_team_color[0] >> low_team_color[1] >> low_team_color[2];
    t1_file >> upper_team_color[0] >> upper_team_color[1] >> upper_team_color[2];
    cout << low_team_color[0] << " " << upper_team_color[0] << endl;
    t1_file.close();
    t1_file.clear();

    for(auto itr = robots.begin(); itr != robots.end(); ++itr){
        path = "Config/" + (*itr).get_nick();
        file.open(path.c_str());

        if(!file){
            cout << (*itr).get_nick() << " config could not be opened!" << endl;
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
        cout << "Team 2 config could not be opened!" << endl;
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
    ui->label->setText(QString::fromStdString(robots[0].get_role()));
    ui->label_2->setText(QString::fromStdString(robots[1].get_role()));
    ui->label_3->setText(QString::fromStdString(robots[2].get_role()));
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

void soccer_window::on_iterate_clicked()
{
    vector<Point2d> enemy_pos(3);
    pVector enemy_pos_grid(3);
    Point  ball_pos_grid;
    int i = 0;
    cph = new CPH(5, 5);

    enemy_pos[0] = robots[3].get_pos();
    enemy_pos[1] = robots[4].get_pos();
    enemy_pos[2] = robots[5].get_pos();
    cph->init_grid();

    for(i = 0; i < 3; ++i){
        enemy_pos_grid[i] = cph->convert_C_to_G(enemy_pos[i]);
        cph->set_potential(enemy_pos_grid[i].y, enemy_pos_grid[i].x, 1);
    }

    ball_pos_grid = cph->convert_C_to_G(ball_pos);
    cph->set_potential(ball_pos_grid.y, ball_pos_grid.x, 0);

    while(cph->iterator() > 1E-6);

    cph->set_direction();
    cph->print_grid();
}
