#ifndef CPH_H
#define CPH_H

#include <QThread>
#include "robot.h" //Robot class
#include "utils.h" //Utils library


class CPH : QThread
{
    Q_OBJECT
private:
    bool stop;
protected:
    void run();
    void msleep(int ms);
signals:

public:
    CPH();
    void Play();
    void Stop();
    bool isStopped() const;
//    ~CPH();
};

#endif // CPH_H
