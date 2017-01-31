#include <iostream>
#include <QMessageBox>
#include <QDebug>
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
    setAttribute(Qt::WA_DeleteOnClose);
    serial_sett = new SettingsDialog;
    serial = new Serial;
    eye = new Vision;
    eye->set_mode(1);

    if(!read_points("Config/map", map_area)){
        cerr << "The map points could not be read!" << endl;
    }

    if(!read_points("Config/defense_area", def_area)){
        cerr << "The defense area points could not be read!" << endl;
    }

    if(!read_points("Config/attack_area", atk_area)){
        cerr << "The attack area points could not be read!" << endl;
    }

    connect(serial_sett, SIGNAL(serial_settings(SettingsDialog::Settings)), this, SLOT(updateSerialSettings(SettingsDialog::Settings)));
    connect(eye, SIGNAL(processedImage(QImage)), this, SLOT(updateVisionUI(QImage)));
    connect(eye, SIGNAL(framesPerSecond(double)), this, SLOT(updateFPS(double)));
}

void soccer_window::updateVisionUI(QImage img){
    if(!img.isNull()){
        ui->game_view->setAlignment(Qt::AlignCenter);
        ui->game_view->setPixmap(QPixmap::fromImage(img).scaled(ui->game_view->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

void soccer_window::updateFPS(double fps){
    ui->fps_lcd->display(fps);
}

void soccer_window::updateSerialSettings(SettingsDialog::Settings settings){
    this->settings = settings;
    serial->set_serial_settings(settings);
}

void soccer_window::on_pushButton_clicked()
{
    serial_sett->show();
}

void soccer_window::on_pushButton_2_clicked()
{
    serial->open_serial_port();
}

void soccer_window::on_pushButton_3_clicked()
{
    string com("l");
    serial->write_data(com);
}

void soccer_window::on_pushButton_4_clicked()
{
    string com("d");
    serial->write_data(com);
}

void soccer_window::on_pushButton_5_clicked()
{
    QByteArray data;
    string com("f"), out;
    serial->write_data(com);
    if(serial->bytes_available() > 0){
        data = serial->read_data();
        out = string(data.constData(), data.length());
        cout << out << endl;
        serial->flush();
    }
    //read = serial->read_data();
    //str.append(read);
    /*for(int i = 0; i < sizeof(data)/sizeof(char); ++i){
        cout << data[i] << endl;
    }*/
    //cout << str;
}

void soccer_window::on_pushButton_6_clicked()
{
    serial->close_serial_port();
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
        ui->start_game->setText("Start Game");
    }
}

void soccer_window::on_switch_fields_clicked()
{
    vector<Point> aux;

    aux = atk_area;
    atk_area = def_area;
    def_area = aux;

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
    delete ui;
}
