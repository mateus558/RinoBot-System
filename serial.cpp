#include <iostream>
#include <QMessageBox>
#include "robot.h"

using namespace std;

Serial::Serial(){
    serial = new QSerialPort;
    delay = 10;

    connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &Serial::handle_error);

    timer.start(delay);
}

bool Serial::open(){
    if(!serial->isOpen() || !serial->isWritable()){
        cerr << "WARNING: Serial port " << serial->portName().toUtf8().constData() << " could not be opened!" << endl;
        return false;
    }

    if(serial->open(QIODevice::ReadWrite)){
        cout << serial->portName().toUtf8().constData() << " is open." << endl;
    }else{
        cerr << "WARNING: Serial port " << serial->portName().toUtf8().constData() << " could not be opened!" << endl;
        return false;
    }

    if(!timer.isActive())
        timer.start(delay);

    return true;
}

void Serial::close(){
    if(serial->isOpen()){
        serial->close();
        clog << serial->portName().toUtf8().constData() << " closed." << endl;
    }
}

qint64 Serial::bytes_available(){
    return serial->bytesAvailable();
}

void Serial::write(QByteArray data){
    serial->write(data);

    timer.start(delay);
}

void Serial::read(char *b, int i){
    serial->read(&(*b), i);

    timer.start(delay);
}

bool Serial::flush(){
    return serial->flush();
}

void Serial::handle_error(QSerialPort::SerialPortError error){
    if (error == QSerialPort::ResourceError) {
        cerr << serial->errorString().toUtf8().constData() << endl;
        close();
    }
}

bool Serial::is_open(){
    return serial->isOpen();
}

void Serial::set_serial_settings(SettingsDialog::Settings settings){
    this->settings = settings;

    serial->setPortName(settings.name);
    serial->setBaudRate(settings.baudRate);
    serial->setDataBits(settings.dataBits);
    serial->setParity(settings.parity);
    serial->setStopBits(settings.stopBits);
}

Serial::~Serial(){
    if(is_open()){
        close();
    }

    delete serial;
}
