#ifndef SOCCER_WINDOW_H
#define SOCCER_WINDOW_H
#include <QMainWindow>
#include <QWidget>
#include "settingsdialog.h"
#include "vision.h"
#include "cph.h"
#include "cpo.h"
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
    void updateBallPos(const Point2d &ball_pos);
    void updateVisionUI(QImage img);
    void isBallFound(bool ball_found);
    void updateFPS(double fps);
    void updateMapPoints(const pVector &map_area);
    void updateAtkPoints(const pVector &atk_area);
    void updateDefPoints(const pVector &def_area);
    void updateRobotsInfo(const rVector &robots);
private slots:

    void on_start_game_clicked();

    void on_switch_fields_clicked();

    void on_read_parameters_clicked();

    void on_checkBox_toggled(bool checked);

    void on_checkBox_2_toggled(bool checked);

    void on_checkBox_3_toggled(bool checked);

    void on_CPH_clicked();

private:
    QThread* thread;
    CPH *cph;
    CPO *cpo;
    Vision *eye;
    Serial *serial;
    SettingsDialog *serial_sett;
    Ui::soccer_window *ui;
    SettingsDialog::Settings settings;
    std::vector<Robot> robots;
    Point2d ball_pos;
    std::vector<cv::Point> map_area;
    std::vector<cv::Point> def_area;
    std::vector<cv::Point> atk_area;
    void closeEvent(QCloseEvent *event);

    bool started;
};

#endif // SOCCER_WINDOW_H
