#ifndef SOCCER_WINDOW_H
#define SOCCER_WINDOW_H
#include <QMainWindow>
#include <QWidget>
#include "settingsdialog.h"
#include "vision.h"
#include "cph.h"
#include "cpo.h"
#include "cph2.h"
#include "cpo2.h"
#include "cpo3.h"
#include "fuzzy.h"
#include "mover.h"
#include "navegation.h"
#include "game_functions.h"

namespace Ui {
class soccer_window;
}

class soccer_window : public QWidget
{
    Q_OBJECT

public:
    explicit soccer_window(QWidget *parent = 0);
    void load_serial_cfg();
    ~soccer_window();
public slots:
    void updateMoverRobots(Selector);
    void updateFuzzyRobots(Selector);
    void updatePerceptionInfo(Vision::Perception);
    void updateSerialSettings(SettingsDialog::Settings);
    void updateVisionUI(QImage);
    void receiveSerialSettings(SettingsDialog::Settings);
    void updateFPS(double);
signals:
    void updateVisionInfo(rVector);
private slots:

    void on_start_game_clicked();

    void on_switch_fields_clicked();

    void on_read_parameters_clicked();

    void on_show_field_areas_checkbox_toggled(bool checked);

    void on_show_rnames_checkBox_toggled(bool checked);

    void on_show_rcentroids_checkbox_toggled(bool checked);

    void on_show_visionlogs_checkbox_toggled(bool checked);

    void on_start_game_2_clicked();

private:
    NAVEGATION *calc_Gandalf, *calc_Presto, *calc_Leona;
    GAME_FUNCTIONS gandalf, presto, leona;
    CPH *cph;
    CPH2 *cph2;
    CPO *cpo;
    CPO2 *cpo2;
    CPO3 *cpo3;
    Fuzzy *fuzzy;
    Mover *mover;
    Vision *eye;
    Vision::Perception percep;
    SettingsDialog::Settings serial_config;
    Ui::soccer_window *ui;
    std::vector<Robot> team_robots;
    Point2d ball_pos;
    std::vector<cv::Point> map_area;
    std::vector<cv::Point> def_area;
    std::vector<cv::Point> atk_area;
    Point centroid_atk;
    Point centroid_def;
    Selector selec_robot; //estrutura de selecao dos robos que vao entrar no fuzzy
    int cam_id;
    bool started, area_read, run_cph, run_cpo, run_fuzzy, run_mover, run_cph2, run_cpo2, run_cpo3, game_started, team_changed;
    bool run_Gandalf, run_Presto, run_Leona;


    void closeEvent(QCloseEvent *event);
};

#endif // SOCCER_WINDOW_H
