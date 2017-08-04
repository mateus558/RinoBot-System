#ifndef SETPARAMETERS_H
#define SETPARAMETERS_H
#include <QMainWindow>
#include <QMessageBox>
#include <vision.h>
#include <configrobots.h>
#include "settingsdialog.h"
#include "video4linuxconfig.h"

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
    void updateSerialSettings(SettingsDialog::Settings settings);

signals:
    void serialSettings(SettingsDialog::Settings);

public:
    explicit SetParameters(QWidget *parent = 0);
    ~SetParameters();

private slots:
    void closeEvent(QCloseEvent *event);
    void on_initCapture_clicked();
    void on_configRobots_clicked();
    void on_readParameters_clicked();

    void on_T1_color_clicked();

    void on_T2_color_clicked();

    void on_mapPoints_clicked();

    void on_attackArrea_btn_clicked();

    void on_defenseArrea_btn_clicked();

    void on_ball_color_clicked();

    void on_config_serial_clicked();

    void on_calibrate_camera_clicked();

    void on_save_image_clicked();

private:
    int cam_id;
    Ui::SetParameters *ui;
    ConfigRobots *conf;
    Vision *eye;
    SettingsDialog *serial_settings_dialog;
    SettingsDialog::Settings serial_settings;
    SetColorRange *set_team_color;
    video4linuxConfig *calib_camera;
};

#endif // SETPARAMETERS_H
