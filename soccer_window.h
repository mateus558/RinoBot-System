#ifndef SOCCER_WINDOW_H
#define SOCCER_WINDOW_H
#include <QMainWindow>
#include <QWidget>
#include "settingsdialog.h"
#include "vision.h"
#include "serial.h"

namespace Ui {
class soccer_window;
}

class soccer_window : public QWidget
{
    Q_OBJECT

public:
    explicit soccer_window(QWidget *parent = 0);
    ~soccer_window();
public slots:
    void updateSerialSettings(SettingsDialog::Settings settings);
    void updateVisionUI(QImage img);
    void updateFPS(double fps);
    void updateMapPoints(const pVector &map_area);
    void updateAtkPoints(const pVector &atk_area);
    void updateDefPoints(const pVector &def_area);
    void updateRobotsInfo(const rVector &robots);

private slots:

    void on_start_game_clicked();

    void on_switch_fields_clicked();

    void on_showAreasRadioButton_toggled(bool checked);

    void on_read_parameters_clicked();

private:
    Ui::soccer_window *ui;
    Vision *eye;
    SettingsDialog *serial_sett;
    Serial *serial;
    SettingsDialog::Settings settings;
    std::vector<Robot> robots;
    std::vector<cv::Point> map_area;
    std::vector<cv::Point> def_area;
    std::vector<cv::Point> atk_area;
    bool started;
};

#endif // SOCCER_WINDOW_H
