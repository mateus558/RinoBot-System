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
    ui->comboBox->addItem("Gandalf");
    ui->comboBox->addItem("Presto");
    ui->comboBox->addItem("Leona");
    ui->comboBox_2->addItem("Goalkeeper");
    ui->comboBox_2->addItem("Attacker");
    ui->comboBox_2->addItem("Defender");

    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_clicked()));
}

ConfigRobots::~ConfigRobots()
{
    delete ui;
}

void ConfigRobots::set_vision(Vision *eye, int cam_id){
    if(!eye->is_open()){
        eye->open_camera(cam_id);
    }
    this->eye = eye;
}

void ConfigRobots::on_pushButton_clicked()
{
    string robot = ui->comboBox->currentText().toUtf8().constData();
    set_color->set_robot(robot);
    set_color->show();
}

void ConfigRobots::on_pushButton_2_clicked()
{
    string robot_nick = ui->comboBox->currentText().toUtf8().constData();
    string path = "Config/" + robot_nick;
    int channel = ui->spinBox->value();
    string role = ui->comboBox_2->currentText().toUtf8().constData();
    string ID = ui->lineEdit->text().toUtf8().constData();

    ofstream out;
    out.open(path.c_str(), ofstream::out | ofstream::app);

    if(!out){
        cout << "File could not be opened!" << endl;
    }
    cout << "ok" << endl;
    out << channel << endl;
    out << role << endl;
    out << ID << endl;

    out.close();
}
