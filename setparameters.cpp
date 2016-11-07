#include "setparameters.h"
#include "ui_setparameters.h"
#include <iostream>
#include <fstream>

using namespace std;

SetParameters::SetParameters(QWidget *parent) : QMainWindow(parent),    ui(new Ui::SetParameters){
    eye = new Vision;
    conf = new ConfigRobots;

    ui->setupUi(this);
    connect(ui->configRobots, SIGNAL(clicked(bool)), this, SLOT(on_configRobots_clicked()));
    connect(eye, SIGNAL(processedImage(QImage)), this, SLOT(updateVisionUI(QImage)));
    connect(eye, SIGNAL(framesPerSecond(double)), this, SLOT(updateFPS(double)));
}

SetParameters::~SetParameters(){
    delete eye;
    delete ui;
}

void SetParameters::updateVisionUI(QImage img){
    if(!img.isNull()){
        ui->camera_video->setAlignment(Qt::AlignCenter);
        ui->camera_video->setPixmap(QPixmap::fromImage(img).scaled(ui->camera_video->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

void SetParameters::updateFPS(double val){
    ui->fps_number->display(val);
}

void SetParameters::on_initCapture_clicked(){
    if(eye == NULL){
        eye = new Vision;
    }

    if(!eye->open_camera()){
        QMessageBox msgBox;
        msgBox.setText("The camera could not be opened!");
        msgBox.exec();
    }
    eye->Play();
}

void SetParameters::on_configRobots_clicked(){
    eye->Stop();
    eye->release_cam();
    conf->show();
}

void SetParameters::on_readParameters_clicked()
{
    vector<Robot> robots = eye->get_robots();
    vector<int> low_color(3, 0);
    vector<int> upper_color(3, 0);
    int ch;
    string path, role, ID;
    ifstream file;

    for(auto itr = robots.begin(); itr != robots.end(); ++itr){
        path = "Config/" + (*itr).get_nick();
        file.open(path.c_str());

        file >> low_color[0] >> low_color[1] >> low_color[2];
        file >> upper_color[0] >> upper_color[1] >> upper_color[2];
        file >> ch;
        file >> role;
        file >> ID;

        (*itr).set_low_color(low_color);
        (*itr).set_upper_color(upper_color);
        (*itr).set_ID(ID);
        (*itr).set_channel(ch);
        (*itr).set_role(role);

        file.close();
        file.clear();
    }

    eye->set_robots(robots);
}
