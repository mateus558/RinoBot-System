#include <iostream>
#include <QMessageBox>
#include "serial.h"

using namespace std;

Serial::Serial(){
    open = false;
    serial = new QSerialPort(this);

    connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &Serial::handle_error);

    timer.start(10);
}

void Serial::open_serial_port(){
    if(serial->open(QSerialPort::ReadWrite)){
        open = true;
        cout << serial->portName().toUtf8().constData() << " is open." << endl;
    }else{
        open = false;
        cerr << "WARNING: Serial port " << serial->portName().toUtf8().constData() << " could not be opened!" << endl;
    }
}

void Serial::close_serial_port(){
    if(serial->isOpen()){
        serial->close();
        clog << serial->portName().toUtf8().constData() << " closed." << endl;
    }
}

qint64 Serial::bytes_available(){
    return serial->bytesAvailable();
}

void Serial::write_data(string data_str){
    QByteArray data(data_str.c_str(), data_str.length());

    serial->write(data);
    timer.start(10);
}

void Serial::write_data(QByteArray data){
    serial->write(data);
    timer.start(10);
}

void Serial::read(char *b, int i){
    serial->read(&(*b), i);
}

QByteArray Serial::read_data(){
    QByteArray ret;

    ret.append(serial->readAll());
    if(!timer.isActive()){
        timer.start(10);
    }

    if(ret.isEmpty()){
        cout << "No data available." << endl;
    }else{
        cout << "Data received." << endl;
    }

    return ret;
}

qint64 Serial::read_line(char *data, qint64 maxSize){
    qint64 ret;

    ret = serial->readLine(data, maxSize);
    if(!timer.isActive()){
        timer.start(10);
    }

    return ret;
}

bool Serial::flush(){
    return serial->flush();
}

void Serial::handle_error(QSerialPort::SerialPortError error){
    if (error == QSerialPort::ResourceError) {
        cerr << serial->errorString().toUtf8().constData() << endl;
        close_serial_port();
    }
}

bool Serial::is_open(){
    return this->open;
}

bool Serial::can_read_line(){
    return serial->canReadLine();
}

void Serial::set_serial_settings(SettingsDialog::Settings settings){
    this->settings = settings;

    serial->setPortName(settings.name);
    serial->setBaudRate(settings.baudRate);
    serial->setDataBits(settings.dataBits);
    serial->setParity(settings.parity);
    serial->setFlowControl(settings.flowControl);
    serial->setStopBits(settings.stopBits);
}

void Serial::set_mode(int mode){
    this->mode = mode;
}

void Serial::set_baud_rate(qint32 baud_rate){
    this->baud_rate = baud_rate;
    serial->setBaudRate(baud_rate);
}

void Serial::set_flowcontrol(QSerialPort::FlowControl flowControl){
    this->flowControl = flowControl;
    serial->setFlowControl(flowControl);
}

void Serial::set_parity(QSerialPort::Parity parity){
    this->parity = parity;
    serial->setParity(parity);
}

void Serial::set_stopbits(QSerialPort::StopBits stopBits){
    this->stopBits = stopBits;
    serial->setStopBits(stopBits);
}

void Serial::set_portname(QString port_name){
    this->port_name = port_name;
    serial->setPortName(port_name);
}
