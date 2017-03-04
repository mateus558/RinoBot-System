/********************************************************************************
** Form generated from reading UI file 'soccer_window.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOCCER_WINDOW_H
#define UI_SOCCER_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_soccer_window
{
public:
    QLabel *game_view;
    QPushButton *start_game;
    QPushButton *switch_fields;
    QPushButton *CPH;
    QLCDNumber *fps_lcd;
    QLabel *fps_label;
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
    QLabel *ball_detec_label;
    QLabel *ball_detec_col_label;
    QLabel *cam_id_label;
    QSpinBox *cam_id_spinBox;
    QGroupBox *serial_status_group;
    QLabel *gandalf_serial_label;
    QLabel *leona_serial_label;
    QLabel *presto_serial_label;
    QLabel *gandalf_serial_col;
    QLabel *leona_detec_col;
    QLabel *presto_detec_col;
    QPushButton *pushButton;

    void setupUi(QWidget *soccer_window)
    {
        if (soccer_window->objectName().isEmpty())
            soccer_window->setObjectName(QStringLiteral("soccer_window"));
        soccer_window->setWindowModality(Qt::ApplicationModal);
        soccer_window->resize(905, 592);
        QIcon icon;
        icon.addFile(QStringLiteral("Untitled1.png"), QSize(), QIcon::Normal, QIcon::Off);
        soccer_window->setWindowIcon(icon);
        soccer_window->setLayoutDirection(Qt::LeftToRight);
        game_view = new QLabel(soccer_window);
        game_view->setObjectName(QStringLiteral("game_view"));
        game_view->setGeometry(QRect(20, 10, 701, 461));
        game_view->setStyleSheet(QStringLiteral("Background-color: #000;"));
        start_game = new QPushButton(soccer_window);
        start_game->setObjectName(QStringLiteral("start_game"));
        start_game->setGeometry(QRect(730, 10, 171, 41));
        switch_fields = new QPushButton(soccer_window);
        switch_fields->setObjectName(QStringLiteral("switch_fields"));
        switch_fields->setGeometry(QRect(730, 70, 171, 41));
        CPH = new QPushButton(soccer_window);
        CPH->setObjectName(QStringLiteral("CPH"));
        CPH->setGeometry(QRect(760, 190, 111, 31));
        fps_lcd = new QLCDNumber(soccer_window);
        fps_lcd->setObjectName(QStringLiteral("fps_lcd"));
        fps_lcd->setGeometry(QRect(820, 550, 64, 23));
        fps_lcd->setStyleSheet(QStringLiteral("Background-color: #000;"));
        fps_label = new QLabel(soccer_window);
        fps_label->setObjectName(QStringLiteral("fps_label"));
        fps_label->setGeometry(QRect(780, 550, 31, 20));
        battery_level_group = new QGroupBox(soccer_window);
        battery_level_group->setObjectName(QStringLiteral("battery_level_group"));
        battery_level_group->setGeometry(QRect(80, 480, 181, 101));
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
        robots_roles_group->setGeometry(QRect(270, 480, 120, 101));
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
        gandalf_label->setGeometry(QRect(20, 510, 59, 14));
        leona_label = new QLabel(soccer_window);
        leona_label->setObjectName(QStringLiteral("leona_label"));
        leona_label->setGeometry(QRect(20, 530, 59, 14));
        presto_label = new QLabel(soccer_window);
        presto_label->setObjectName(QStringLiteral("presto_label"));
        presto_label->setGeometry(QRect(20, 550, 59, 14));
        optionsGroupBox = new QGroupBox(soccer_window);
        optionsGroupBox->setObjectName(QStringLiteral("optionsGroupBox"));
        optionsGroupBox->setGeometry(QRect(740, 290, 141, 121));
        show_field_areas_checkbox = new QCheckBox(optionsGroupBox);
        show_field_areas_checkbox->setObjectName(QStringLiteral("show_field_areas_checkbox"));
        show_field_areas_checkbox->setGeometry(QRect(10, 30, 85, 20));
        show_rnames_checkBox = new QCheckBox(optionsGroupBox);
        show_rnames_checkBox->setObjectName(QStringLiteral("show_rnames_checkBox"));
        show_rnames_checkBox->setGeometry(QRect(10, 50, 101, 20));
        show_rcentroids_checkbox = new QCheckBox(optionsGroupBox);
        show_rcentroids_checkbox->setObjectName(QStringLiteral("show_rcentroids_checkbox"));
        show_rcentroids_checkbox->setGeometry(QRect(10, 70, 121, 20));
        show_visionlogs_checkbox = new QCheckBox(optionsGroupBox);
        show_visionlogs_checkbox->setObjectName(QStringLiteral("show_visionlogs_checkbox"));
        show_visionlogs_checkbox->setGeometry(QRect(10, 90, 131, 20));
        read_parameters = new QPushButton(soccer_window);
        read_parameters->setObjectName(QStringLiteral("read_parameters"));
        read_parameters->setGeometry(QRect(730, 130, 171, 41));
        detection_status_group = new QGroupBox(soccer_window);
        detection_status_group->setObjectName(QStringLiteral("detection_status_group"));
        detection_status_group->setGeometry(QRect(400, 480, 141, 101));
        gandalf_detec_label = new QLabel(detection_status_group);
        gandalf_detec_label->setObjectName(QStringLiteral("gandalf_detec_label"));
        gandalf_detec_label->setGeometry(QRect(40, 30, 81, 20));
        leona_detec_label = new QLabel(detection_status_group);
        leona_detec_label->setObjectName(QStringLiteral("leona_detec_label"));
        leona_detec_label->setGeometry(QRect(40, 50, 91, 20));
        presto_detec_label = new QLabel(detection_status_group);
        presto_detec_label->setObjectName(QStringLiteral("presto_detec_label"));
        presto_detec_label->setGeometry(QRect(40, 70, 81, 20));
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
        ball_detec_label = new QLabel(soccer_window);
        ball_detec_label->setObjectName(QStringLiteral("ball_detec_label"));
        ball_detec_label->setGeometry(QRect(770, 430, 91, 20));
        ball_detec_col_label = new QLabel(soccer_window);
        ball_detec_col_label->setObjectName(QStringLiteral("ball_detec_col_label"));
        ball_detec_col_label->setGeometry(QRect(740, 430, 21, 16));
        ball_detec_col_label->setStyleSheet(QStringLiteral("background-color : red"));
        cam_id_label = new QLabel(soccer_window);
        cam_id_label->setObjectName(QStringLiteral("cam_id_label"));
        cam_id_label->setGeometry(QRect(740, 250, 59, 14));
        cam_id_spinBox = new QSpinBox(soccer_window);
        cam_id_spinBox->setObjectName(QStringLiteral("cam_id_spinBox"));
        cam_id_spinBox->setGeometry(QRect(800, 250, 47, 23));
        cam_id_spinBox->setMaximum(999);
        cam_id_spinBox->setValue(300);
        serial_status_group = new QGroupBox(soccer_window);
        serial_status_group->setObjectName(QStringLiteral("serial_status_group"));
        serial_status_group->setGeometry(QRect(550, 480, 101, 101));
        gandalf_serial_label = new QLabel(serial_status_group);
        gandalf_serial_label->setObjectName(QStringLiteral("gandalf_serial_label"));
        gandalf_serial_label->setGeometry(QRect(40, 30, 51, 20));
        leona_serial_label = new QLabel(serial_status_group);
        leona_serial_label->setObjectName(QStringLiteral("leona_serial_label"));
        leona_serial_label->setGeometry(QRect(40, 50, 51, 20));
        presto_serial_label = new QLabel(serial_status_group);
        presto_serial_label->setObjectName(QStringLiteral("presto_serial_label"));
        presto_serial_label->setGeometry(QRect(40, 70, 51, 20));
        gandalf_serial_col = new QLabel(serial_status_group);
        gandalf_serial_col->setObjectName(QStringLiteral("gandalf_serial_col"));
        gandalf_serial_col->setGeometry(QRect(10, 30, 21, 16));
        gandalf_serial_col->setStyleSheet(QStringLiteral("background-color : red"));
        leona_detec_col = new QLabel(serial_status_group);
        leona_detec_col->setObjectName(QStringLiteral("leona_detec_col"));
        leona_detec_col->setGeometry(QRect(10, 50, 21, 16));
        leona_detec_col->setStyleSheet(QStringLiteral("background-color : red"));
        presto_detec_col = new QLabel(serial_status_group);
        presto_detec_col->setObjectName(QStringLiteral("presto_detec_col"));
        presto_detec_col->setGeometry(QRect(10, 70, 21, 16));
        presto_detec_col->setStyleSheet(QStringLiteral("background-color : red"));
        pushButton = new QPushButton(soccer_window);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(760, 460, 80, 22));
        optionsGroupBox->raise();
        game_view->raise();
        start_game->raise();
        switch_fields->raise();
        CPH->raise();
        fps_lcd->raise();
        fps_label->raise();
        battery_level_group->raise();
        robots_roles_group->raise();
        gandalf_label->raise();
        leona_label->raise();
        presto_label->raise();
        read_parameters->raise();
        detection_status_group->raise();
        ball_detec_label->raise();
        ball_detec_col_label->raise();
        cam_id_label->raise();
        cam_id_spinBox->raise();
        serial_status_group->raise();
        pushButton->raise();

        retranslateUi(soccer_window);

        QMetaObject::connectSlotsByName(soccer_window);
    } // setupUi

    void retranslateUi(QWidget *soccer_window)
    {
        soccer_window->setWindowTitle(QApplication::translate("soccer_window", "Play Soccer", 0));
        game_view->setText(QApplication::translate("soccer_window", "TextLabel", 0));
        start_game->setText(QApplication::translate("soccer_window", "Start Game", 0));
        switch_fields->setText(QApplication::translate("soccer_window", "Switch ATK/DEF Area", 0));
        CPH->setText(QApplication::translate("soccer_window", "CPH", 0));
        fps_label->setText(QApplication::translate("soccer_window", "FPS:", 0));
        battery_level_group->setTitle(QApplication::translate("soccer_window", "Battery Levels:", 0));
        robots_roles_group->setTitle(QApplication::translate("soccer_window", "Robots Roles:", 0));
        gandalf_role_label->setText(QApplication::translate("soccer_window", "     -- None --", 0));
        leona_role_label->setText(QApplication::translate("soccer_window", "     -- None --", 0));
        presto_role_label->setText(QApplication::translate("soccer_window", "    -- None --", 0));
        gandalf_label->setText(QApplication::translate("soccer_window", "Gandalf:", 0));
        leona_label->setText(QApplication::translate("soccer_window", "Leona:", 0));
        presto_label->setText(QApplication::translate("soccer_window", "Presto:", 0));
        optionsGroupBox->setTitle(QApplication::translate("soccer_window", "Options:", 0));
        show_field_areas_checkbox->setText(QApplication::translate("soccer_window", "Show Areas", 0));
        show_rnames_checkBox->setText(QApplication::translate("soccer_window", "Show Names", 0));
        show_rcentroids_checkbox->setText(QApplication::translate("soccer_window", "Show Centroids", 0));
        show_visionlogs_checkbox->setText(QApplication::translate("soccer_window", "Show Vision Logs", 0));
        read_parameters->setText(QApplication::translate("soccer_window", "Read Parameters", 0));
        detection_status_group->setTitle(QApplication::translate("soccer_window", "Detection:", 0));
        gandalf_detec_label->setText(QApplication::translate("soccer_window", "Not Detected", 0));
        leona_detec_label->setText(QApplication::translate("soccer_window", "Not Detected", 0));
        presto_detec_label->setText(QApplication::translate("soccer_window", "Not Detected", 0));
        gandalf_detec_col_label->setText(QString());
        leona_detec_col_label->setText(QString());
        presto_detec_col_label->setText(QString());
        gandalf_loss_rate->setText(QString());
        leona_loss_rate->setText(QString());
        presto_loss_rate->setText(QString());
        ball_detec_label->setText(QApplication::translate("soccer_window", "Ball not found", 0));
        ball_detec_col_label->setText(QString());
        cam_id_label->setText(QApplication::translate("soccer_window", "Cam ID:", 0));
        serial_status_group->setTitle(QApplication::translate("soccer_window", "Serial Status:", 0));
        gandalf_serial_label->setText(QApplication::translate("soccer_window", "Closed", 0));
        leona_serial_label->setText(QApplication::translate("soccer_window", "Closed", 0));
        presto_serial_label->setText(QApplication::translate("soccer_window", "Closed", 0));
        gandalf_serial_col->setText(QString());
        leona_detec_col->setText(QString());
        presto_detec_col->setText(QString());
        pushButton->setText(QApplication::translate("soccer_window", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class soccer_window: public Ui_soccer_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOCCER_WINDOW_H
