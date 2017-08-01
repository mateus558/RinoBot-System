#include "video4linuxconfig.h"
#include "ui_video4linuxconfig.h"
#include <string>

video4linuxConfig::video4linuxConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::video4linuxConfig)
{
    ui->setupUi(this);

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

void video4linuxConfig::on_bright_slider_sliderMoved(int position)
{
    std::string command("v4l2-ctl --set-ctrl brightness=");

    command = command + to_string(position);
    system(val);
    ui->bright_lcd->display(position);
}

void video4linuxConfig::on_contrast_slider_sliderMoved(int position)
{
    std::string command("v4l2-ctl --set-ctrl contrast=");

    command = command + to_string(position);
    system(command);
    ui->contrast_lcd->display(position);
}



void video4linuxConfig::on_saturation_slider_sliderMoved(int position)
{
    std::string command("v4l2-ctl --set-ctrl saturation=");

    command = command + to_string(position);
    system(command);
    ui->saturation_lcd->display(position);
}

void video4linuxConfig::on_white_bal_slider_sliderMoved(int position)
{
    std::string command("v4l2-ctl --set-ctrl white_balance_temperature=");

    command = command + to_string(position);
    system(command);
    ui->white_bal_lcd->display(position);
}

void video4linuxConfig::on_sharpness_slider_sliderMoved(int position)
{
    std::string command("v4l2-ctl --set-ctrl sharpness=");

    command = command + to_string(position);
    system(command);
    ui->sharpness_lcd->display(position);
}

void video4linuxConfig::on_exposure_slider_sliderMoved(int position)
{
    std::string command("v4l2-ctl --set-ctrl exposure_absolute=");

    command = command + to_string(position);
    system(command);
    ui->exposure_lcd->display(position);
}

void video4linuxConfig::on_focus_slider_sliderMoved(int position)
{
    std::string command("v4l2-ctl --set-ctrl focus_absolute=");

    command = command + to_string(position);
    system(val);
    ui->focus_lcd->display(position);
}
