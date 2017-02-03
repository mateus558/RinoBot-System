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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_soccer_window
{
public:
    QLabel *game_view;
    QPushButton *start_game;
    QPushButton *switch_fields;
    QPushButton *iterate;
    QLCDNumber *fps_lcd;
    QLabel *fps_label;
    QGroupBox *battery_level_group;
    QProgressBar *gandalf_battery_level;
    QProgressBar *leona_battery_level;
    QProgressBar *presto_baterry_level;
    QGroupBox *robots_roles_group;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *gandalf_label;
    QLabel *leona_label;
    QLabel *presto_label;
    QRadioButton *showAreasRadioButton;
    QGroupBox *optionsGroupBox;
    QPushButton *read_parameters;

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
        iterate = new QPushButton(soccer_window);
        iterate->setObjectName(QStringLiteral("iterate"));
        iterate->setGeometry(QRect(760, 220, 111, 31));
        fps_lcd = new QLCDNumber(soccer_window);
        fps_lcd->setObjectName(QStringLiteral("fps_lcd"));
        fps_lcd->setGeometry(QRect(810, 440, 64, 23));
        fps_lcd->setStyleSheet(QStringLiteral("Background-color: #000;"));
        fps_label = new QLabel(soccer_window);
        fps_label->setObjectName(QStringLiteral("fps_label"));
        fps_label->setGeometry(QRect(770, 440, 31, 20));
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
        label = new QLabel(robots_roles_group);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(8, 30, 101, 20));
        label_2 = new QLabel(robots_roles_group);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(8, 50, 91, 20));
        label_3 = new QLabel(robots_roles_group);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 70, 101, 20));
        gandalf_label = new QLabel(soccer_window);
        gandalf_label->setObjectName(QStringLiteral("gandalf_label"));
        gandalf_label->setGeometry(QRect(20, 510, 59, 14));
        leona_label = new QLabel(soccer_window);
        leona_label->setObjectName(QStringLiteral("leona_label"));
        leona_label->setGeometry(QRect(20, 530, 59, 14));
        presto_label = new QLabel(soccer_window);
        presto_label->setObjectName(QStringLiteral("presto_label"));
        presto_label->setGeometry(QRect(20, 550, 59, 14));
        showAreasRadioButton = new QRadioButton(soccer_window);
        showAreasRadioButton->setObjectName(QStringLiteral("showAreasRadioButton"));
        showAreasRadioButton->setGeometry(QRect(420, 500, 100, 20));
        optionsGroupBox = new QGroupBox(soccer_window);
        optionsGroupBox->setObjectName(QStringLiteral("optionsGroupBox"));
        optionsGroupBox->setGeometry(QRect(409, 479, 141, 101));
        read_parameters = new QPushButton(soccer_window);
        read_parameters->setObjectName(QStringLiteral("read_parameters"));
        read_parameters->setGeometry(QRect(730, 130, 171, 41));
        optionsGroupBox->raise();
        game_view->raise();
        start_game->raise();
        switch_fields->raise();
        iterate->raise();
        fps_lcd->raise();
        fps_label->raise();
        battery_level_group->raise();
        robots_roles_group->raise();
        gandalf_label->raise();
        leona_label->raise();
        presto_label->raise();
        showAreasRadioButton->raise();
        read_parameters->raise();

        retranslateUi(soccer_window);

        QMetaObject::connectSlotsByName(soccer_window);
    } // setupUi

    void retranslateUi(QWidget *soccer_window)
    {
        soccer_window->setWindowTitle(QApplication::translate("soccer_window", "Play Soccer", 0));
        game_view->setText(QApplication::translate("soccer_window", "TextLabel", 0));
        start_game->setText(QApplication::translate("soccer_window", "Start Game", 0));
        switch_fields->setText(QApplication::translate("soccer_window", "Switch ATK/DEF Area", 0));
        iterate->setText(QApplication::translate("soccer_window", "Iterator", 0));
        fps_label->setText(QApplication::translate("soccer_window", "FPS:", 0));
        battery_level_group->setTitle(QApplication::translate("soccer_window", "Battery Levels:", 0));
        robots_roles_group->setTitle(QApplication::translate("soccer_window", "Robots Roles:", 0));
        label->setText(QApplication::translate("soccer_window", "     -- None --", 0));
        label_2->setText(QApplication::translate("soccer_window", "     -- None --", 0));
        label_3->setText(QApplication::translate("soccer_window", "    -- None --", 0));
        gandalf_label->setText(QApplication::translate("soccer_window", "Gandalf:", 0));
        leona_label->setText(QApplication::translate("soccer_window", "Leona:", 0));
        presto_label->setText(QApplication::translate("soccer_window", "Presto:", 0));
        showAreasRadioButton->setText(QApplication::translate("soccer_window", "Show Areas", 0));
        optionsGroupBox->setTitle(QApplication::translate("soccer_window", "Options:", 0));
        read_parameters->setText(QApplication::translate("soccer_window", "Read Parameters", 0));
    } // retranslateUi

};

namespace Ui {
    class soccer_window: public Ui_soccer_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOCCER_WINDOW_H
