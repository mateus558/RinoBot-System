#ifndef INFORMATIONWINDOW_H
#define INFORMATIONWINDOW_H

#include <vector>
#include "vision.h"
#include <QMessageBox>
#include <QDialog>

using namespace std;

#define NUM_ROBOTS 3
#define GANDALF    0
#define LEONA      1
#define PRESTO     2

struct BallInfo{
    double x;
    double y;
    double vel_vision;
};

struct RobotInfo{
    double channel;
    double x;
    double y;
    double vel_strategy;
    double vel_vision;
    double vel_max;
};
/**************ROBOT INFO********************
 * robots array:
 *
 *   -0
 *      Gandalf
 *
 *   -1
 *      Leona
 *
 *   -2
 *      Presto
 * ******************************************/
struct InfoParameters{
    RobotInfo robots[NUM_ROBOTS];
    BallInfo ball;
    Vision* eye;
};

namespace Ui {
class InformationWindow;
}

class InformationWindow : public QDialog
{
    Q_OBJECT

public slots:
    void updateData(InfoParameters data);

public:
    explicit InformationWindow(QWidget *parent = 0);
    ~InformationWindow();

private slots:
    void on_valueFilterchangebtn_clicked();

    void on_startFilterbtn_clicked();

    void on_velocityMaxGandalfbtn_clicked();

    void on_velocityMaxLeonabtn_clicked();

    void on_velocityMaxPrestobtn_clicked();

    void on_pidbtn_clicked();

    void on_strategybtn_clicked();

signals:
    void close();

private:
    Ui::InformationWindow *ui;

    InfoParameters data;

    void updateData();

    void closeEvent(QCloseEvent *event);
};

#endif // INFORMATIONWINDOW_H
