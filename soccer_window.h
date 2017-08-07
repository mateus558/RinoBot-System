#ifndef SOCCER_WINDOW_H
#define SOCCER_WINDOW_H
#include <QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include "settingsdialog.h"
#include "vision.h"
#include "fuzzy.h"
#include "game_functions.h"
#include "navigation.h"
#include "drawobjects.h"

namespace Ui {
class soccer_window;
}

class soccer_window : public QWidget
{
    Q_OBJECT

public:
    explicit soccer_window(QWidget *parent = 0);
    void load_serial_cfg();
    void prepare_game_scene(int w, int h);
    ~soccer_window();
public slots:
    void updateGameFunctionsRobots(Selector);
    void updateFuzzyRobots(Selector);
    void updatePerceptionInfo(Vision::Perception);
    void updateSerialSettings(SettingsDialog::Settings);
    void receiveSerialSettings(SettingsDialog::Settings);
    void updateFPS(double);
signals:
    void updateVisionInfo(std::vector<Robot>);
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
    Fuzzy *fuzzy;
    Game_functions *leona;
    Game_functions *presto;
    Game_functions *gandalf;
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
    QGraphicsScene *game_scene;
    FieldDraw *field;
    BallDraw *ball;
    vector<Enemy*> enemy;
    std::vector<RobotDraw*> team_shapes;
    int cam_id;
    bool started, area_read, run_fuzzy, run_leona, run_presto, run_gandalf, game_started, team_changed;


    void closeEvent(QCloseEvent *event);
};

#endif // SOCCER_WINDOW_H
