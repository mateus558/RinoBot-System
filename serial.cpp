#include <iostream>
#include "serial.h"

using namespace std;

Serial::Serial(){
    open = false;
    serial = new QSerialPort(this);

}

void Serial::run(){

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
    }
}

void Serial::write_data(const QByteArray &data){
    serial->write(data);
}

QByteArray Serial::read_data(){
    return serial->readAll();
}

void Serial::listen_port(){

}

bool Serial::is_open(){
    return this->open;
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
