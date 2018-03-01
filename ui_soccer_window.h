/********************************************************************************
** Form generated from reading UI file 'soccer_window.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOCCER_WINDOW_H
#define UI_SOCCER_WINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_soccer_window
{
public:
    QPushButton *start_game;
    QCheckBox *switch_fields;
    QGroupBox *battery_level_group;
    QProgressBar *gandalf_battery_level;
    QProgressBar *leona_battery_level;
    QProgressBar *presto_baterry_level;
    QGroupBox *robots_roles_group;
    QLabel *gandalf_role_label;
    QLabel *leona_role_label;
    QLabel *presto_role_label;
    QLabel *gandalf_label;
    QLabel *leona_label;
    QLabel *presto_label;
    QGroupBox *optionsGroupBox;
    QCheckBox *show_field_areas_checkbox;
    QCheckBox *show_rnames_checkBox;
    QCheckBox *show_rcentroids_checkbox;
    QCheckBox *show_visionlogs_checkbox;
    QCheckBox *checkBox;
    QPushButton *read_parameters;
    QGroupBox *detection_status_group;
    QLabel *gandalf_detec_label;
    QLabel *leona_detec_label;
    QLabel *presto_detec_label;
    QLabel *gandalf_detec_col_label;
    QLabel *leona_detec_col_label;
    QLabel *presto_detec_col_label;
    QLabel *gandalf_loss_rate;
    QLabel *leona_loss_rate;
    QLabel *presto_loss_rate;
    QLabel *cam_id_label;
    QSpinBox *cam_id_spinBox;
    QPushButton *start_game_2;
    QGraphicsView *game_view;
    QGroupBox *groupBox;
    QLabel *ball_detec_label;
    QLabel *ball_detec_col_label;
    QLabel *serial_status_col_label;
    QLabel *serial_status_label;
    QLCDNumber *fps_lcd;
    QLabel *fps_label;
    QPushButton *change_strategy;
    QComboBox *strategy_options;
    QLabel *gamelbl;
    QLabel *strategylbl;
    QLabel *currentStrategylbl;
    QLabel *cameralbl;
    QCheckBox *swapteamscbk;
    QLabel *cutoffFrequencylbl;
    QSlider *horizontalSlider;
    QLCDNumber *chopFrequencylcd;
    QPushButton *startFilterbtn;
    QCheckBox *swap_roles;

    void setupUi(QWidget *soccer_window)
    {
        if (soccer_window->objectName().isEmpty())
            soccer_window->setObjectName(QStringLiteral("soccer_window"));
        soccer_window->setWindowModality(Qt::ApplicationModal);
        soccer_window->resize(916, 592);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(soccer_window->sizePolicy().hasHeightForWidth());
        soccer_window->setSizePolicy(sizePolicy);
        soccer_window->setMaximumSize(QSize(916, 592));
        QIcon icon;
        icon.addFile(QStringLiteral("Untitled1.png"), QSize(), QIcon::Normal, QIcon::Off);
        soccer_window->setWindowIcon(icon);
        soccer_window->setLayoutDirection(Qt::LeftToRight);
        start_game = new QPushButton(soccer_window);
        start_game->setObjectName(QStringLiteral("start_game"));
        start_game->setGeometry(QRect(140, 410, 41, 31));
        start_game->setMaximumSize(QSize(171, 41));
        switch_fields = new QCheckBox(soccer_window);
        switch_fields->setObjectName(QStringLiteral("switch_fields"));
        switch_fields->setGeometry(QRect(20, 320, 171, 41));
        battery_level_group = new QGroupBox(soccer_window);
        battery_level_group->setObjectName(QStringLiteral("battery_level_group"));
        battery_level_group->setGeometry(QRect(270, 480, 181, 101));
        gandalf_battery_level = new QProgressBar(battery_level_group);
        gandalf_battery_level->setObjectName(QStringLiteral("gandalf_battery_level"));
        gandalf_battery_level->setGeometry(QRect(10, 30, 161, 16));
        gandalf_battery_level->setValue(100);
        leona_battery_level = new QProgressBar(battery_level_group);
        leona_battery_level->setObjectName(QStringLiteral("leona_battery_level"));
        leona_battery_level->setGeometry(QRect(10, 50, 161, 16));
        leona_battery_level->setValue(100);
        presto_baterry_level = new QProgressBar(battery_level_group);
        presto_baterry_level->setObjectName(QStringLiteral("presto_baterry_level"));
        presto_baterry_level->setGeometry(QRect(10, 70, 161, 16));
        presto_baterry_level->setAutoFillBackground(false);
        presto_baterry_level->setStyleSheet(QStringLiteral(""));
        presto_baterry_level->setValue(100);
        robots_roles_group = new QGroupBox(soccer_window);
        robots_roles_group->setObjectName(QStringLiteral("robots_roles_group"));
        robots_roles_group->setGeometry(QRect(460, 480, 120, 101));
        gandalf_role_label = new QLabel(robots_roles_group);
        gandalf_role_label->setObjectName(QStringLiteral("gandalf_role_label"));
        gandalf_role_label->setGeometry(QRect(8, 30, 101, 20));
        leona_role_label = new QLabel(robots_roles_group);
        leona_role_label->setObjectName(QStringLiteral("leona_role_label"));
        leona_role_label->setGeometry(QRect(8, 50, 91, 20));
        presto_role_label = new QLabel(robots_roles_group);
        presto_role_label->setObjectName(QStringLiteral("presto_role_label"));
        presto_role_label->setGeometry(QRect(10, 70, 101, 20));
        gandalf_label = new QLabel(soccer_window);
        gandalf_label->setObjectName(QStringLiteral("gandalf_label"));
        gandalf_label->setGeometry(QRect(200, 500, 59, 14));
        leona_label = new QLabel(soccer_window);
        leona_label->setObjectName(QStringLiteral("leona_label"));
        leona_label->setGeometry(QRect(210, 530, 59, 14));
        presto_label = new QLabel(soccer_window);
        presto_label->setObjectName(QStringLiteral("presto_label"));
        presto_label->setGeometry(QRect(210, 560, 59, 14));
        optionsGroupBox = new QGroupBox(soccer_window);
        optionsGroupBox->setObjectName(QStringLiteral("optionsGroupBox"));
        optionsGroupBox->setGeometry(QRect(10, 220, 191, 181));
        show_field_areas_checkbox = new QCheckBox(optionsGroupBox);
        show_field_areas_checkbox->setObjectName(QStringLiteral("show_field_areas_checkbox"));
        show_field_areas_checkbox->setGeometry(QRect(10, 30, 101, 20));
        show_rnames_checkBox = new QCheckBox(optionsGroupBox);
        show_rnames_checkBox->setObjectName(QStringLiteral("show_rnames_checkBox"));
        show_rnames_checkBox->setGeometry(QRect(10, 50, 111, 20));
        show_rcentroids_checkbox = new QCheckBox(optionsGroupBox);
        show_rcentroids_checkbox->setObjectName(QStringLiteral("show_rcentroids_checkbox"));
        show_rcentroids_checkbox->setGeometry(QRect(10, 70, 131, 20));
        show_visionlogs_checkbox = new QCheckBox(optionsGroupBox);
        show_visionlogs_checkbox->setObjectName(QStringLiteral("show_visionlogs_checkbox"));
        show_visionlogs_checkbox->setGeometry(QRect(10, 89, 141, 21));
        checkBox = new QCheckBox(optionsGroupBox);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(10, 130, 171, 20));
        read_parameters = new QPushButton(soccer_window);
        read_parameters->setObjectName(QStringLiteral("read_parameters"));
        read_parameters->setGeometry(QRect(90, 50, 141, 31));
        detection_status_group = new QGroupBox(soccer_window);
        detection_status_group->setObjectName(QStringLiteral("detection_status_group"));
        detection_status_group->setGeometry(QRect(590, 480, 141, 101));
        gandalf_detec_label = new QLabel(detection_status_group);
        gandalf_detec_label->setObjectName(QStringLiteral("gandalf_detec_label"));
        gandalf_detec_label->setGeometry(QRect(40, 30, 91, 20));
        leona_detec_label = new QLabel(detection_status_group);
        leona_detec_label->setObjectName(QStringLiteral("leona_detec_label"));
        leona_detec_label->setGeometry(QRect(40, 50, 91, 20));
        presto_detec_label = new QLabel(detection_status_group);
        presto_detec_label->setObjectName(QStringLiteral("presto_detec_label"));
        presto_detec_label->setGeometry(QRect(40, 70, 91, 20));
        gandalf_detec_col_label = new QLabel(detection_status_group);
        gandalf_detec_col_label->setObjectName(QStringLiteral("gandalf_detec_col_label"));
        gandalf_detec_col_label->setGeometry(QRect(10, 30, 21, 16));
        gandalf_detec_col_label->setStyleSheet(QStringLiteral("background-color : red"));
        leona_detec_col_label = new QLabel(detection_status_group);
        leona_detec_col_label->setObjectName(QStringLiteral("leona_detec_col_label"));
        leona_detec_col_label->setGeometry(QRect(10, 50, 21, 16));
        leona_detec_col_label->setStyleSheet(QStringLiteral("background-color : red"));
        presto_detec_col_label = new QLabel(detection_status_group);
        presto_detec_col_label->setObjectName(QStringLiteral("presto_detec_col_label"));
        presto_detec_col_label->setGeometry(QRect(10, 70, 21, 16));
        presto_detec_col_label->setStyleSheet(QStringLiteral("background-color : red"));
        gandalf_loss_rate = new QLabel(detection_status_group);
        gandalf_loss_rate->setObjectName(QStringLiteral("gandalf_loss_rate"));
        gandalf_loss_rate->setGeometry(QRect(130, 30, 31, 16));
        leona_loss_rate = new QLabel(detection_status_group);
        leona_loss_rate->setObjectName(QStringLiteral("leona_loss_rate"));
        leona_loss_rate->setGeometry(QRect(130, 50, 31, 16));
        presto_loss_rate = new QLabel(detection_status_group);
        presto_loss_rate->setObjectName(QStringLiteral("presto_loss_rate"));
        presto_loss_rate->setGeometry(QRect(130, 70, 31, 16));
        cam_id_label = new QLabel(soccer_window);
        cam_id_label->setObjectName(QStringLiteral("cam_id_label"));
        cam_id_label->setGeometry(QRect(10, 450, 91, 21));
        cam_id_spinBox = new QSpinBox(soccer_window);
        cam_id_spinBox->setObjectName(QStringLiteral("cam_id_spinBox"));
        cam_id_spinBox->setGeometry(QRect(130, 450, 47, 23));
        cam_id_spinBox->setMaximum(999);
        cam_id_spinBox->setValue(0);
        start_game_2 = new QPushButton(soccer_window);
        start_game_2->setObjectName(QStringLiteral("start_game_2"));
        start_game_2->setGeometry(QRect(10, 50, 71, 31));
        game_view = new QGraphicsView(soccer_window);
        game_view->setObjectName(QStringLiteral("game_view"));
        game_view->setGeometry(QRect(240, 10, 671, 461));
        game_view->setMaximumSize(QSize(721, 471));
        groupBox = new QGroupBox(soccer_window);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(740, 480, 161, 91));
        ball_detec_label = new QLabel(groupBox);
        ball_detec_label->setObjectName(QStringLiteral("ball_detec_label"));
        ball_detec_label->setGeometry(QRect(40, 30, 111, 20));
        ball_detec_col_label = new QLabel(groupBox);
        ball_detec_col_label->setObjectName(QStringLiteral("ball_detec_col_label"));
        ball_detec_col_label->setGeometry(QRect(10, 30, 21, 16));
        ball_detec_col_label->setStyleSheet(QStringLiteral("background-color : red"));
        serial_status_col_label = new QLabel(groupBox);
        serial_status_col_label->setObjectName(QStringLiteral("serial_status_col_label"));
        serial_status_col_label->setGeometry(QRect(10, 60, 21, 16));
        serial_status_col_label->setStyleSheet(QStringLiteral("background-color : red"));
        serial_status_label = new QLabel(groupBox);
        serial_status_label->setObjectName(QStringLiteral("serial_status_label"));
        serial_status_label->setGeometry(QRect(40, 60, 91, 20));
        fps_lcd = new QLCDNumber(soccer_window);
        fps_lcd->setObjectName(QStringLiteral("fps_lcd"));
        fps_lcd->setGeometry(QRect(100, 480, 81, 23));
        fps_lcd->setStyleSheet(QStringLiteral("Background-color: #000;"));
        fps_label = new QLabel(soccer_window);
        fps_label->setObjectName(QStringLiteral("fps_label"));
        fps_label->setGeometry(QRect(10, 480, 31, 20));
        change_strategy = new QPushButton(soccer_window);
        change_strategy->setObjectName(QStringLiteral("change_strategy"));
        change_strategy->setGeometry(QRect(140, 150, 81, 31));
        strategy_options = new QComboBox(soccer_window);
        strategy_options->setObjectName(QStringLiteral("strategy_options"));
        strategy_options->setGeometry(QRect(10, 150, 121, 31));
        strategy_options->setCursor(QCursor(Qt::ArrowCursor));
        strategy_options->setLocale(QLocale(QLocale::English, QLocale::UnitedStatesVirginIslands));
        gamelbl = new QLabel(soccer_window);
        gamelbl->setObjectName(QStringLiteral("gamelbl"));
        gamelbl->setGeometry(QRect(10, 20, 67, 17));
        strategylbl = new QLabel(soccer_window);
        strategylbl->setObjectName(QStringLiteral("strategylbl"));
        strategylbl->setGeometry(QRect(10, 100, 81, 17));
        currentStrategylbl = new QLabel(soccer_window);
        currentStrategylbl->setObjectName(QStringLiteral("currentStrategylbl"));
        currentStrategylbl->setGeometry(QRect(10, 120, 91, 17));
        cameralbl = new QLabel(soccer_window);
        cameralbl->setObjectName(QStringLiteral("cameralbl"));
        cameralbl->setGeometry(QRect(10, 410, 101, 31));
        swapteamscbk = new QCheckBox(soccer_window);
        swapteamscbk->setObjectName(QStringLiteral("swapteamscbk"));
        swapteamscbk->setGeometry(QRect(20, 370, 111, 23));
        cutoffFrequencylbl = new QLabel(soccer_window);
        cutoffFrequencylbl->setObjectName(QStringLiteral("cutoffFrequencylbl"));
        cutoffFrequencylbl->setGeometry(QRect(10, 520, 121, 17));
        horizontalSlider = new QSlider(soccer_window);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(10, 540, 171, 20));
        horizontalSlider->setMaximum(99);
        horizontalSlider->setSingleStep(1);
        horizontalSlider->setOrientation(Qt::Horizontal);
        chopFrequencylcd = new QLCDNumber(soccer_window);
        chopFrequencylcd->setObjectName(QStringLiteral("chopFrequencylcd"));
        chopFrequencylcd->setGeometry(QRect(100, 560, 81, 23));
        chopFrequencylcd->setStyleSheet(QStringLiteral("Background-color: #000;"));
        chopFrequencylcd->setFrameShadow(QFrame::Sunken);
        startFilterbtn = new QPushButton(soccer_window);
        startFilterbtn->setObjectName(QStringLiteral("startFilterbtn"));
        startFilterbtn->setGeometry(QRect(140, 510, 41, 31));
        swap_roles = new QCheckBox(soccer_window);
        swap_roles->setObjectName(QStringLiteral("swap_roles"));
        swap_roles->setGeometry(QRect(20, 194, 107, 29));
        optionsGroupBox->raise();
        start_game->raise();
        switch_fields->raise();
        battery_level_group->raise();
        robots_roles_group->raise();
        gandalf_label->raise();
        leona_label->raise();
        presto_label->raise();
        read_parameters->raise();
        detection_status_group->raise();
        cam_id_label->raise();
        cam_id_spinBox->raise();
        start_game_2->raise();
        game_view->raise();
        groupBox->raise();
        fps_lcd->raise();
        fps_label->raise();
        change_strategy->raise();
        strategy_options->raise();
        gamelbl->raise();
        strategylbl->raise();
        currentStrategylbl->raise();
        cameralbl->raise();
        swapteamscbk->raise();
        cutoffFrequencylbl->raise();
        horizontalSlider->raise();
        chopFrequencylcd->raise();
        startFilterbtn->raise();
        swap_roles->raise();

        retranslateUi(soccer_window);

        QMetaObject::connectSlotsByName(soccer_window);
    } // setupUi

    void retranslateUi(QWidget *soccer_window)
    {
        soccer_window->setWindowTitle(QApplication::translate("soccer_window", "Play Soccer", Q_NULLPTR));
        start_game->setText(QApplication::translate("soccer_window", "Off", Q_NULLPTR));
        switch_fields->setText(QApplication::translate("soccer_window", "Switch ATK/DEF Area", Q_NULLPTR));
        battery_level_group->setTitle(QApplication::translate("soccer_window", "Battery Levels:", Q_NULLPTR));
        robots_roles_group->setTitle(QApplication::translate("soccer_window", "Robots Roles:", Q_NULLPTR));
        gandalf_role_label->setText(QApplication::translate("soccer_window", "     -- None --", Q_NULLPTR));
        leona_role_label->setText(QApplication::translate("soccer_window", "     -- None --", Q_NULLPTR));
        presto_role_label->setText(QApplication::translate("soccer_window", "    -- None --", Q_NULLPTR));
        gandalf_label->setText(QApplication::translate("soccer_window", "Gandalf:", Q_NULLPTR));
        leona_label->setText(QApplication::translate("soccer_window", "Leona:", Q_NULLPTR));
        presto_label->setText(QApplication::translate("soccer_window", "Presto:", Q_NULLPTR));
        optionsGroupBox->setTitle(QApplication::translate("soccer_window", "Options:", Q_NULLPTR));
        show_field_areas_checkbox->setText(QApplication::translate("soccer_window", "Show Areas", Q_NULLPTR));
        show_rnames_checkBox->setText(QApplication::translate("soccer_window", "Show Names", Q_NULLPTR));
        show_rcentroids_checkbox->setText(QApplication::translate("soccer_window", "Show Centroids", Q_NULLPTR));
        show_visionlogs_checkbox->setText(QApplication::translate("soccer_window", "Show Vision Logs", Q_NULLPTR));
        checkBox->setText(QApplication::translate("soccer_window", "CheckBox", Q_NULLPTR));
        read_parameters->setText(QApplication::translate("soccer_window", "Read Parameters", Q_NULLPTR));
        detection_status_group->setTitle(QApplication::translate("soccer_window", "Detection:", Q_NULLPTR));
        gandalf_detec_label->setText(QApplication::translate("soccer_window", "Not Detected", Q_NULLPTR));
        leona_detec_label->setText(QApplication::translate("soccer_window", "Not Detected", Q_NULLPTR));
        presto_detec_label->setText(QApplication::translate("soccer_window", "Not Detected", Q_NULLPTR));
        gandalf_detec_col_label->setText(QString());
        leona_detec_col_label->setText(QString());
        presto_detec_col_label->setText(QString());
        gandalf_loss_rate->setText(QString());
        leona_loss_rate->setText(QString());
        presto_loss_rate->setText(QString());
        cam_id_label->setText(QApplication::translate("soccer_window", "Cam ID:", Q_NULLPTR));
        start_game_2->setText(QApplication::translate("soccer_window", "Game", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("soccer_window", "Other Info:", Q_NULLPTR));
        ball_detec_label->setText(QApplication::translate("soccer_window", "Ball not found", Q_NULLPTR));
        ball_detec_col_label->setText(QString());
        serial_status_col_label->setText(QString());
        serial_status_label->setText(QApplication::translate("soccer_window", "Serial Closed", Q_NULLPTR));
        fps_label->setText(QApplication::translate("soccer_window", "FPS:", Q_NULLPTR));
        change_strategy->setText(QApplication::translate("soccer_window", "Change", Q_NULLPTR));
        gamelbl->setText(QApplication::translate("soccer_window", "Game:", Q_NULLPTR));
        strategylbl->setText(QApplication::translate("soccer_window", "Strategy:", Q_NULLPTR));
        currentStrategylbl->setText(QApplication::translate("soccer_window", "Current: ", Q_NULLPTR));
        cameralbl->setText(QApplication::translate("soccer_window", "Set Camera: ", Q_NULLPTR));
        swapteamscbk->setText(QApplication::translate("soccer_window", "Swap Teams", Q_NULLPTR));
        cutoffFrequencylbl->setText(QApplication::translate("soccer_window", "Cutoff Frequency:", Q_NULLPTR));
        startFilterbtn->setText(QApplication::translate("soccer_window", "Off", Q_NULLPTR));
        swap_roles->setText(QApplication::translate("soccer_window", "Swap Roles", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class soccer_window: public Ui_soccer_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOCCER_WINDOW_H
