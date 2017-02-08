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
    void updatePerceptionInfo(Vision::Perception);
    void updateSerialSettings(SettingsDialog::Settings);
    void updateVisionUI(QImage);
    void updateFPS(double);
private slots:

    void on_start_game_clicked();

    void on_switch_fields_clicked();

    void on_read_parameters_clicked();

    void on_CPH_clicked();

    void on_show_field_areas_checkbox_toggled(bool checked);

    void on_show_rnames_checkBox_toggled(bool checked);

    void on_show_rcentroids_checkbox_toggled(bool checked);

    void on_show_visionlogs_checkbox_toggled(bool checked);

private:
    CPH *cph;
    CPO *cpo;
    Vision *eye;
    Vision::Perception percep;
    Serial *serial;
    Ui::soccer_window *ui;
    SettingsDialog::Settings settings;
    std::vector<Robot> robots;
    Point2d ball_pos;
    std::vector<cv::Point> map_area;
    std::vector<cv::Point> def_area;
    std::vector<cv::Point> atk_area;
    void closeEvent(QCloseEvent *event);

    bool started, area_read, run_cph;
};

#endif // SOCCER_WINDOW_H
