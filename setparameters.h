#ifndef SETPARAMETERS_H
#define SETPARAMETERS_H

#include <QMainWindow>
#include <QMessageBox>
#include <vision.h>
#include <configrobots.h>

namespace Ui {
class SetParameters;
}

class SetParameters : public QMainWindow
{
    Q_OBJECT

private:
    void set_points(string fname, string area, int n_points);
public slots:
    void updateVisionUI(QImage img);
    void updateFPS(double val);

public:
    explicit SetParameters(QWidget *parent = 0);
    ~SetParameters();

private slots:
    void on_initCapture_clicked();
    void on_configRobots_clicked();
    void on_readParameters_clicked();

    void on_T1_color_clicked();

    void on_T2_color_clicked();

    void on_mapPoints_clicked();

    void on_attackArrea_btn_clicked();

    void on_defenseArrea_btn_clicked();

    void on_ball_color_clicked();

private:
    Ui::SetParameters *ui;
    ConfigRobots *conf;
    Vision *eye;
    SetColorRange *set_team_color;
};

#endif // SETPARAMETERS_H
