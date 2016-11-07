#include "configrobots.h"
#include "ui_configrobots.h"
#include <iostream>
#include <fstream>

using namespace std;

ConfigRobots::ConfigRobots(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigRobots)
{
    set_color = new SetColorRange;

    ui->setupUi(this);
    ui->select_robot->addItem("Gandalf");
    ui->select_robot->addItem("Presto");
    ui->select_robot->addItem("Leona");
    ui->robot_role->addItem("Goalkeeper");
    ui->robot_role->addItem("Attacker");
    ui->robot_role->addItem("Defender");

    connect(ui->configColorRange, SIGNAL(clicked(bool)), this, SLOT(on_configColorRange_clicked()));
}

ConfigRobots::~ConfigRobots()
{
    delete ui;
}

void ConfigRobots::set_vision(Vision *eye, int cam_id)
{
    if(!eye->is_open()){
        eye->open_camera(cam_id);
    }
    this->eye = eye;
}

void ConfigRobots::on_configColorRange_clicked()
{
    string robot = ui->select_robot->currentText().toUtf8().constData();
    set_color->set_robot(robot);
    set_color->show();
}

void ConfigRobots::on_save_clicked()
{
    string robot_nick = ui->select_robot->currentText().toUtf8().constData();
    string path = "Config/" + robot_nick;
    int channel = ui->robot_channel->value();
    string role = ui->robot_role->currentText().toUtf8().constData();
    string ID = ui->robot_ID->text().toUtf8().constData();

    ofstream out;
    out.open(path.c_str(), ofstream::out | ofstream::app);

    if(!out){
        cout << "File could not be opened!" << endl;
    }

    out << channel << endl;
    out << role << endl;
    out << ID << endl;

    out.close();
}
