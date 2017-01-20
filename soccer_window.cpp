#include "soccer_window.h"
#include "ui_soccer_window.h"
#include "serial.h"
#include <iostream>
#include <QDebug>

using namespace std;

soccer_window::soccer_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::soccer_window)
{
    ui->setupUi(this);
    serial_sett = new SettingsDialog;
    serial = new Serial;

    connect(serial_sett, SIGNAL(serial_settings(SettingsDialog::Settings)), this, SLOT(updateSerialSettings(SettingsDialog::Settings)));
}

soccer_window::~soccer_window()
{
    delete ui;
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
