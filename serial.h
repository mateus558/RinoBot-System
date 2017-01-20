#ifndef SERIAL_H
#define SERIAL_H
#include <QtCore>
#include <QTimer>
#include <QtSerialPort/QSerialPort>
#include "settingsdialog.h"

class Serial : public QThread
{
    Q_OBJECT
private:
    int mode;
    bool open;
    QTimer timer;
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
    void write_data(string data_str);
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
