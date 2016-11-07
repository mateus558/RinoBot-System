#include "setcolorrange.h"
#include "ui_setcolorrange.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <iostream>
#include <fstream>

using namespace std;

SetColorRange::SetColorRange(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetColorRange)
{
    eye = new Vision;
    ui->setupUi(this);
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(on_horizontalSlider_sliderMoved(int)));
    connect(ui->horizontalSlider_2, SIGNAL(valueChanged(int)), this, SLOT(on_horizontalSlider_2_sliderMoved(int)));
    connect(ui->horizontalSlider_3, SIGNAL(valueChanged(int)), this, SLOT(on_horizontalSlider_3_sliderMoved(int)));
    connect(ui->horizontalSlider_4, SIGNAL(valueChanged(int)), this, SLOT(on_horizontalSlider_4_sliderMoved(int)));
    connect(ui->horizontalSlider_5, SIGNAL(valueChanged(int)), this, SLOT(on_horizontalSlider_5_sliderMoved(int)));
    connect(ui->horizontalSlider_6, SIGNAL(valueChanged(int)), this, SLOT(on_horizontalSlider_6_sliderMoved(int)));
    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_2_clicked()));
    connect(eye, SIGNAL(processedImage(QImage)), this, SLOT(updateVisionUI(QImage)));
    eye->set_mode(1);
}

void SetColorRange::closeEvent(QCloseEvent *event){
    eye->Stop();
    eye->release_cam();
    eye->terminate();
    eye->wait();
}

void SetColorRange::updateVisionUI(QImage img){
    if(!img.isNull()){
        ui->label_7->setAlignment(Qt::AlignCenter);
        ui->label_7->setPixmap(QPixmap::fromImage(img).scaled(ui->label_7->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

void SetColorRange::set_vision(Vision *eye, int cam_id){
    if(!eye->is_open()){
        eye->open_camera(cam_id);
    }
    this->eye = eye;
}

void SetColorRange::on_horizontalSlider_sliderMoved(int position)
{
    eye->low[0] = position;
    ui->lcdNumber->display(position);
}

void SetColorRange::on_horizontalSlider_2_sliderMoved(int position)
{
    eye->low[1] = position;
    ui->lcdNumber_2->display(position);
}

void SetColorRange::on_horizontalSlider_3_sliderMoved(int position)
{
    eye->low[2] = position;
    ui->lcdNumber_3->display(position);
}

void SetColorRange::on_horizontalSlider_4_sliderMoved(int position)
{
    eye->upper[0] = position;
    ui->lcdNumber_4->display(position);
}

void SetColorRange::on_horizontalSlider_5_sliderMoved(int position)
{
    eye->upper[1] = position;
    ui->lcdNumber_5->display(position);
}

void SetColorRange::on_horizontalSlider_6_sliderMoved(int position)
{
    eye->upper[2] = position;
    ui->lcdNumber_6->display(position);
}

void SetColorRange::on_pushButton_2_clicked()
{
    if(!eye->open_camera()){
        QMessageBox msgBox;
        msgBox.setText("The camera could not be opened!");
        msgBox.exec();
    }
    eye->Play();
}

void SetColorRange::set_robot(string robot)
{
    this->robot = robot;
}

SetColorRange::~SetColorRange()
{
    delete ui;
}

void SetColorRange::on_pushButton_clicked()
{
    string path = "Config/" + robot;
    ofstream out;

    out.open(path.c_str(), ofstream::out | ofstream::trunc);
    if(!out){
        cout << "File not open" << endl;
    }

    for(int i = 0; i < 3; ++i){
        out << eye->low[i] << " ";
    }

    out << endl;

    for(int i = 0; i < 3; ++i){
        out << eye->upper[i] << " ";
    }
    out << endl;

    out.close();
}
