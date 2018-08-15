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
    connect(eye, SIGNAL(processedImage(QImage)), this, SLOT(updateVisionUI(QImage)));
}

void video4linuxConfig::set_camid(int cam_id)
{
    this->cam_id = cam_id;
}

video4linuxConfig::~video4linuxConfig()
{
    delete ui;
}

void video4linuxConfig::showEvent(QShowEvent *event){
    QWidget::showEvent(event);

    read_params("Config/cam_calib.conf");

    system("v4l2-ctl --set-ctrl white_balance_temperature_auto=0");
    system("v4l2-ctl --set-ctrl power_line_frequency=2");
    system("v4l2-ctl --set-ctrl exposure_auto=1");
    system("v4l2-ctl --set-ctrl exposure_auto_priority=1");
    system("v4l2-ctl --set-ctrl pan_absolute=0");
    system("v4l2-ctl --set-ctrl tilt_absolute=0");
    system("v4l2-ctl --set-ctrl focus_auto=0");
    system("v4l2-ctl --set-ctrl focus_absolute=0");
    system("v4l2-ctl --set-ctrl zoom_absolute=100");
    system("v4l2-ctl --set-ctrl backlight_compensation=1");

    update_sliders();

    if(eye == NULL)
    {
        eye = new Vision;
        eye->set_mode(1);
    }

}

void video4linuxConfig::on_bright_slider_sliderMoved(int position)
{
    std::string command("v4l2-ctl --set-ctrl brightness=");
    values[0] = position;
    command = command + std::to_string(position);
    system(command.c_str());
    ui->bright_lcd->display(position);
}

void video4linuxConfig::on_contrast_slider_sliderMoved(int position)
{
    std::string command("v4l2-ctl --set-ctrl contrast=");
    values[1] = position;
    command = command + std::to_string(position);
    system(command.c_str());
    ui->contrast_lcd->display(position);
}



void video4linuxConfig::on_saturation_slider_sliderMoved(int position)
{
    std::string command("v4l2-ctl --set-ctrl saturation=");
    values[2] = position;
    command = command + std::to_string(position);
    system(command.c_str());
    ui->saturation_lcd->display(position);
}

void video4linuxConfig::on_white_bal_slider_sliderMoved(int position)
{
    std::string command("v4l2-ctl --set-ctrl white_balance_temperature=");
    values[4] = position;
    command = command + std::to_string(position);
    system(command.c_str());
    ui->white_bal_lcd->display(position);
}

void video4linuxConfig::on_sharpness_slider_sliderMoved(int position)
{
    std::string command("v4l2-ctl --set-ctrl sharpness=");
    values[5] = position;
    command = command + std::to_string(position);
    system(command.c_str());
    ui->sharpness_lcd->display(position);
}

void video4linuxConfig::on_exposure_slider_sliderMoved(int position)
{
    std::string command("v4l2-ctl --set-ctrl exposure_absolute=");
    values[6] = position;
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

void video4linuxConfig::on_gain_slider_sliderMoved(int position)
{
    std::string command("v4l2-ctl --set-ctrl gain=");
    values[3] = position;
    command = command + std::to_string(position);
    system(command.c_str());
    ui->gain_lcd->display(position);
}

void video4linuxConfig::updateVisionUI(QImage img)
{
    if(!img.isNull())
    {
        ui->camera_view->setAlignment(Qt::AlignCenter);
        ui->camera_view->setPixmap(QPixmap::fromImage(img).scaled(ui->camera_view->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}



void video4linuxConfig::on_pushButton_2_clicked(){}

void video4linuxConfig::on_setToDefault_clicked()
{
    read_default();
    update_sliders();
    update_v4l();
}



void video4linuxConfig::on_Init_Capture_btn_clicked()
{
    if(!eye->open_camera(cam_id)){
        QMessageBox msgBox;
        msgBox.setText("The camera could not be opened!");
        msgBox.exec();
    }
    eye->Play();

}

void video4linuxConfig::closeEvent(QCloseEvent *event){
    QWidget::closeEvent(event);
    std::string atrib;
    ofstream file("Config/cam_calib.conf", std::ofstream::out | std::ofstream::trunc);

    file << "brightness " << values[0] << endl;
    file << "contrast " << values[1] << endl;
    file << "saturation " << values[2] << endl;
    file << "gain " << values[3] << endl;
    file << "white_balance_temperature " << values[4] << endl;
    file << "sharpness " << values[5] << endl;
    file << "exposure_absolute " << values[6] << endl;

    update_v4l();

    if(!eye->isStopped()){
        eye->Stop();
        eye->wait();
        eye->release_cam();
    }
}

void video4linuxConfig::update_v4l(){
    std::string atrib;

    atrib = "v4l2-ctl --set-ctrl brightness=" + std::to_string(values[0]);
    system(atrib.c_str());
    atrib = "v4l2-ctl --set-ctrl contrast=" + std::to_string(values[1]);
    system(atrib.c_str());
    atrib = "v4l2-ctl --set-ctrl saturation=" + std::to_string(values[2]);
    system(atrib.c_str());
    atrib = "v4l2-ctl --set-ctrl gain=" + std::to_string(values[3]);
    system(atrib.c_str());
    atrib = "v4l2-ctl --set-ctrl white_balance_temperatur=" + std::to_string(values[4]);
    system(atrib.c_str());
    atrib = "v4l2-ctl --set-ctrl sharpness=" + std::to_string(values[5]);
    system(atrib.c_str());
    atrib = "v4l2-ctl --set-ctrl exposure_absolute=" + std::to_string(values[6]);
    system(atrib.c_str());
}

void video4linuxConfig::update_sliders(){
    ui->bright_slider->setValue(values[0]);
    ui->bright_lcd->display(values[0]);

    ui->contrast_slider->setValue(values[1]);
    ui->contrast_lcd->display(values[1]);

    ui->saturation_slider->setValue(values[2]);
    ui->saturation_lcd->display(values[2]);

    ui->gain_slider->setValue(values[3]);
    ui->gain_lcd->display(values[3]);

    ui->white_bal_slider->setValue(values[4]);
    ui->white_bal_lcd->display(values[4]);

    ui->sharpness_slider->setValue(values[5]);
    ui->sharpness_lcd->display(values[5]);

    ui->exposure_slider->setValue(values[6]);
    ui->exposure_lcd->display(values[6]);
}

void video4linuxConfig::read_default(){
    read_params("Config/default_cam_calib.conf");
}

void video4linuxConfig::read_params(std::string fileName){
    int value;
    string atrib;
    ifstream file(fileName);

    if(!file.is_open()){
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

    if(values.size() == 0){
        while(file >> atrib >> value)
            values.push_back(value);
    } else {
        int i = 0;
        while(file >> atrib >> value){
            values[i] = value;
            i++;
        }
    }
}
