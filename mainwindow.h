#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QMainWindow>
#include <setparameters.h>
#include <unistd.h>
#include "settingsdialog.h"
#include "settingsdialog.h"
#include "vision.h"
#include "fuzzy.h"
#include "game_functions.h"
#include "navigation.h"
#include "drawobjects.h"
#include "mover.h"
#include "informationwindow.h"

#define GANDALF    0
#define LEONA      1
#define PRESTO     2

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void openSetParameters();

    void on_InfoWindow_closed();
public:
    explicit MainWindow(QWidget *parent = 0);
    void load_serial_cfg();
    void prepare_game_scene(int w, int h);
    ~MainWindow();

private slots:
    void updateMoverRobots(Selector);

    void updateFuzzyRobots(Selector);

    void updatePerceptionInfo(Vision::Perception);

    void updateSerialSettings(SettingsDialog::Settings);

    void receiveSerialSettings(SettingsDialog::Settings);

    void updateFPS(double);

    void on_actionOpen_Camera_triggered(bool checked);

    void on_btn_startGame_clicked();

    void on_btn_changeStrategy_clicked();

    void on_actionSwap_Teams_triggered();

    void on_actionShow_VisionLog_triggered(bool checked);

    void on_actionRead_Parameters_triggered();

    void on_actionSet_Parameters_triggered();

    void on_actionSwap_ATK_DEF_triggered();

    void on_actionShow_Areas_triggered(bool checked);

    void on_actionOpen_InfoWindow_triggered();

    void on_actionSwap_Roles_triggered(bool checked);

signals:
    void updateVisionInfo(std::vector<Robot>);

    void updateInformationWindow(InfoParameters data);

private:
    SetParameters *setparam;
    InformationWindow *iWindow;
    InfoParameters iWindowData;
    bool iWindowOpen;
    Ui::MainWindow *ui;
    Fuzzy *fuzzy;
    Game_functions *leona;
    Game_functions *presto;
    Game_functions *gandalf;
    Mover *mover;
    Vision *eye;
    Vision::Perception percep;
    SettingsDialog::Settings serial_config;
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
    bool started, area_read, run_fuzzy, run_leona, run_presto, run_gandalf, run_mover, game_started, team_changed;
    std::vector<bool> vel_computed;

    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
