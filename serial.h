#ifndef SERIAL_H
#define SERIAL_H
#include <QtCore>
#include <QtSerialPort/QSerialPort>
#include "settingsdialog.h"

class Serial : public QThread
{
    Q_OBJECT
private:
    int mode;
    bool open;
    QSerialPort *serial;
    QString port_name;
    qint32 baud_rate;
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopBits;
    QSerialPort::FlowControl flowControl;
    SettingsDialog::Settings settings;
    QMutex mutex;

    void listen_port();
    void run();

public:
    Serial();
    void open_serial_port();
    void close_serial_port();
    void write_data(const QByteArray &data);
    QByteArray read_data();
    void set_serial_settings(SettingsDialog::Settings);
    void set_mode(int);
    void set_baud_rate(qint32);
    void set_parity(QSerialPort::Parity);
    void set_stopbits(QSerialPort::StopBits);
    void set_flowcontrol(QSerialPort::FlowControl);
    void set_portname(QString);
    bool is_open();
};

#endif // SERIAL_H
