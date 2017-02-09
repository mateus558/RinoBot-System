#ifndef SERIAL_H
#define SERIAL_H

#include <QtCore>
#include <QTimer>
#include <QtSerialPort/QSerialPort>
#include "settingsdialog.h"
#include "robot.h"

class Robot;
struct Encoder;

//union usado para converter float em byte e vice versa
typedef union{
    float  Float;
    unsigned char Bytes[4];
}Float2Char;

//union usado para converter short em byte e vice versa
typedef union{
    unsigned short Short;
    unsigned char Bytes[2];
}Short2Char;

class Serial: public QObject {
    Q_OBJECT
private:
    int mode, timer_delay;
    bool open;
    QTimer timer;
    QSerialPort *serial;
    QTextStream standardOutput;
    QByteArray data;
    QString port_name;
    qint32 baud_rate;
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopBits;
    QSerialPort::FlowControl flowControl;
    SettingsDialog::Settings settings;
    QMutex mutex;
signals:
    void encoderReading(Encoder);
private slots:
    void handle_readyRead();
    void handle_timeOut();
public:
    Serial();
    void listen_robots();
    void open_serial_port();
    void close_serial_port();
    void write_data(std::string data_str);
    void write_data(QByteArray data);
    void read(char *b, int i);
    QByteArray read_data();
    qint64 read_line(char *data, qint64 maxSize);
    qint64 bytes_available();
    bool flush();
    void set_serial_settings(SettingsDialog::Settings);
    void set_mode(int);
    void set_baud_rate(qint32);
    void set_parity(QSerialPort::Parity);
    void set_stopbits(QSerialPort::StopBits);
    void set_flowcontrol(QSerialPort::FlowControl);
    void set_portname(QString);
    bool is_open();
    bool can_read_line();
    void handle_error(QSerialPort::SerialPortError error);
};

#endif // SERIAL_H
