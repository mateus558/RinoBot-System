#include "video4linuxconfig.h"
#include "ui_video4linuxconfig.h"

#include <iostream>
#include <utility>
#include <string>
#include <fstream>

using namespace std;

using namespace std;

video4linuxConfig::video4linuxConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::video4linuxConfig)
{
    ui->setupUi(this);
    eye = new Vision;

    eye->set_mode(1);


    connect(ui->bright_slider, SIGNAL(valueChanged(int)), this, SLOT(on_bright_slider_sliderMoved(int)));
    connect(ui->contrast_slider, SIGNAL(valueChanged(int)), this, SLOT(on_contrast_slider_sliderMoved(int)));
    connect(ui->saturation_slider, SIGNAL(valueChanged(int)), this, SLOT(on_saturation_slider_sliderMoved(int)));
    connect(ui->white_bal_slider, SIGNAL(valueChanged(int)), this, SLOT(on_white_bal_slider_sliderMoved(int)));
    connect(ui->sharpness_slider, SIGNAL(valueChanged(int)), this, SLOT(on_sharpness_slider_sliderMoved(int)));
    connect(ui->exposure_slider, SIGNAL(valueChanged(int)), this, SLOT(on_exposure_slider_sliderMoved(int)));
    connect(ui->focus_slider, SIGNAL(valueChanged(int)), this, SLOT(on_focus_slider_sliderMoved(int)));
}

video4linuxConfig::~video4linuxConfig()
{
    delete ui;
}

void video4linuxConfig::showEvent(QShowEvent *event){
    QWidget::showEvent(event);

    int value;
    string atrib;
    vector<int> values;
    ifstream file("Config/default_cam_calib.conf");

    system("./Config/camera_calib.sh");

    if(!file){
        clog << "File could not be opened! (Camera calibration)" << endl;

        ui->bright_slider->setValue(0);
        ui->contrast_slider->setValue(0);
        ui->saturation_slider->setValue(0);
        ui->white_bal_slider->setValue(2000);
        ui->sharpness_slider->setValue(0);
        ui->exposure_slider->setValue(3);
        ui->focus_slider->setValue(0);

        return ;
    }

    while(file >> atrib >> value){
        values.push_back(value);
    }

    ui->bright_slider->setValue(values[0]);
    ui->contrast_slider->setValue(values[1]);
    ui->saturation_slider->setValue(values[2]);
    ui->white_bal_slider->setValue(values[3]);
    ui->sharpness_slider->setValue(values[4]);
    ui->exposure_slider->setValue(values[5]);
    ui->focus_slider->setValue(values[6]);
    ui->focus_lcd->display(values[6]);
}

void video4linuxConfig::on_bright_slider_sliderMoved(int position)
{
    std::string command("v4l2-ctl --set-ctrl brightness=");

    command = command + std::to_string(position);
    system(command.c_str());
    ui->bright_lcd->display(position);
}

pair<vector<string>, vector<int> > video4linuxConfig::read_default_calib(){
    int value;
    string atrib;
    vector<int> values;
    vector<string> atribs;
    pair<vector<string>, vector<int> > r;
   /* ifstream file("Config/default_cam_calib.conf");

    if(!file){
        cerr << "File could not be opened! (Camera calibration)" << endl;
        r = make_pair(atrib, values);
        return r;
    }

    while(file >> atrib >> value){
        values.push_back(value);
        atribs.push_back(atrib);
    }
    r = make_pair(atrib, values);*/

    return r;
}

void video4linuxConfig::on_contrast_slider_sliderMoved(int position)
{
    std::string command("v4l2-ctl --set-ctrl contrast=");

    command = command + std::to_string(position);
    system(command.c_str());
    ui->contrast_lcd->display(position);
}



void video4linuxConfig::on_saturation_slider_sliderMoved(int position)
{
    std::string command("v4l2-ctl --set-ctrl saturation=");

    command = command + std::to_string(position);
    system(command.c_str());
    ui->saturation_lcd->display(position);
}

void video4linuxConfig::on_white_bal_slider_sliderMoved(int position)
{
    std::string command("v4l2-ctl --set-ctrl white_balance_temperature=");

    command = command + std::to_string(position);
    system(command.c_str());
    ui->white_bal_lcd->display(position);
}

void video4linuxConfig::on_sharpness_slider_sliderMoved(int position)
{
    std::string command("v4l2-ctl --set-ctrl sharpness=");

    command = command + std::to_string(position);
    system(command.c_str());
    ui->sharpness_lcd->display(position);
}

void video4linuxConfig::on_exposure_slider_sliderMoved(int position)
{
    std::string command("v4l2-ctl --set-ctrl exposure_absolute=");

    command = command + std::to_string(position);
    system(command.c_str());
    ui->exposure_lcd->display(position);
}

void video4linuxConfig::on_focus_slider_sliderMoved(int position)
{
    std::string command("v4l2-ctl --set-ctrl focus_absolute=");

    command = command + std::to_string(position);
    system(command.c_str());
    ui->focus_lcd->display(position);
}

void video4linuxConfig::on_pushButton_2_clicked()
{

}
