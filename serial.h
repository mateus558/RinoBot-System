#ifndef SERIAL_H
#define SERIAL_H

#include <QTimer>
#include <QObject>
#include <QtSerialPort/QSerialPort>
#include "settingsdialog.h"

class Serial: public QObject
{
    Q_OBJECT
private:
    QSerialPort *serial;
    SettingsDialog::Settings settings;
    QTimer *timer;
    int delay;

private slots:
    void handleTimeout();
    void handle_error(QSerialPort::SerialPortError);
public:
    explicit Serial(QObject *parent = nullptr);
    bool open();
    void close();
    void read(char*, int);
    void write(QByteArray);
    bool flush();
    bool is_open();
    qint64 bytes_available();
    void set_serial_settings(SettingsDialog::Settings);
    ~Serial();
};


#endif // SERIAL_H
