/********************************************************************************
** Form generated from reading UI file 'setparameters.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETPARAMETERS_H
#define UI_SETPARAMETERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetParameters
{
public:
    QWidget *centralwidget;
    QLabel *camera_video;
    QPushButton *initCapture;
    QLCDNumber *fps_number;
    QLabel *fps_label;
    QPushButton *readParameters;
    QPushButton *configRobots;
    QPushButton *T1_color;
    QPushButton *T2_color;
    QPushButton *mapPoints;
    QPushButton *attackArrea_btn;
    QPushButton *defenseArrea_btn;
    QPushButton *ball_color;
    QLabel *camera_label;
    QSpinBox *spinBox;
    QPushButton *config_serial;
    QPushButton *calibrate_camera;
    QPushButton *save_image;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SetParameters)
    {
        if (SetParameters->objectName().isEmpty())
            SetParameters->setObjectName(QStringLiteral("SetParameters"));
        SetParameters->setWindowModality(Qt::ApplicationModal);
        SetParameters->resize(987, 516);
        centralwidget = new QWidget(SetParameters);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        camera_video = new QLabel(centralwidget);
        camera_video->setObjectName(QStringLiteral("camera_video"));
        camera_video->setGeometry(QRect(20, 10, 771, 451));
        camera_video->setStyleSheet(QStringLiteral("Background-color: #000;"));
        initCapture = new QPushButton(centralwidget);
        initCapture->setObjectName(QStringLiteral("initCapture"));
        initCapture->setGeometry(QRect(800, 10, 181, 31));
        fps_number = new QLCDNumber(centralwidget);
        fps_number->setObjectName(QStringLiteral("fps_number"));
        fps_number->setGeometry(QRect(870, 430, 64, 23));
        fps_number->setStyleSheet(QStringLiteral("Background-Color: #000"));
        fps_label = new QLabel(centralwidget);
        fps_label->setObjectName(QStringLiteral("fps_label"));
        fps_label->setGeometry(QRect(840, 440, 31, 16));
        readParameters = new QPushButton(centralwidget);
        readParameters->setObjectName(QStringLiteral("readParameters"));
        readParameters->setGeometry(QRect(800, 330, 181, 31));
        configRobots = new QPushButton(centralwidget);
        configRobots->setObjectName(QStringLiteral("configRobots"));
        configRobots->setGeometry(QRect(800, 50, 181, 31));
        T1_color = new QPushButton(centralwidget);
        T1_color->setObjectName(QStringLiteral("T1_color"));
        T1_color->setGeometry(QRect(800, 130, 181, 31));
        T2_color = new QPushButton(centralwidget);
        T2_color->setObjectName(QStringLiteral("T2_color"));
        T2_color->setGeometry(QRect(800, 90, 181, 31));
        mapPoints = new QPushButton(centralwidget);
        mapPoints->setObjectName(QStringLiteral("mapPoints"));
        mapPoints->setGeometry(QRect(20, 470, 101, 21));
        attackArrea_btn = new QPushButton(centralwidget);
        attackArrea_btn->setObjectName(QStringLiteral("attackArrea_btn"));
        attackArrea_btn->setGeometry(QRect(130, 470, 101, 21));
        defenseArrea_btn = new QPushButton(centralwidget);
        defenseArrea_btn->setObjectName(QStringLiteral("defenseArrea_btn"));
        defenseArrea_btn->setGeometry(QRect(240, 470, 111, 21));
        ball_color = new QPushButton(centralwidget);
        ball_color->setObjectName(QStringLiteral("ball_color"));
        ball_color->setGeometry(QRect(800, 170, 181, 31));
        camera_label = new QLabel(centralwidget);
        camera_label->setObjectName(QStringLiteral("camera_label"));
        camera_label->setGeometry(QRect(800, 370, 101, 16));
        spinBox = new QSpinBox(centralwidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(800, 390, 47, 23));
        spinBox->setMaximum(1000);
        spinBox->setValue(300);
        config_serial = new QPushButton(centralwidget);
        config_serial->setObjectName(QStringLiteral("config_serial"));
        config_serial->setGeometry(QRect(800, 210, 181, 31));
        calibrate_camera = new QPushButton(centralwidget);
        calibrate_camera->setObjectName(QStringLiteral("calibrate_camera"));
        calibrate_camera->setGeometry(QRect(800, 250, 181, 31));
        save_image = new QPushButton(centralwidget);
        save_image->setObjectName(QStringLiteral("save_image"));
        save_image->setGeometry(QRect(800, 290, 181, 31));
        SetParameters->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(SetParameters);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        SetParameters->setStatusBar(statusbar);

        retranslateUi(SetParameters);

        QMetaObject::connectSlotsByName(SetParameters);
    } // setupUi

    void retranslateUi(QMainWindow *SetParameters)
    {
        SetParameters->setWindowTitle(QApplication::translate("SetParameters", "Set Parameters", 0));
        camera_video->setText(QApplication::translate("SetParameters", "TextLabel", 0));
        initCapture->setText(QApplication::translate("SetParameters", "Init Capture", 0));
        fps_label->setText(QApplication::translate("SetParameters", "FPS:", 0));
        readParameters->setText(QApplication::translate("SetParameters", "Read Parameters", 0));
        configRobots->setText(QApplication::translate("SetParameters", "Configure Robots", 0));
        T1_color->setText(QApplication::translate("SetParameters", "Set team 1 color", 0));
        T2_color->setText(QApplication::translate("SetParameters", "Set team 2 color", 0));
        mapPoints->setText(QApplication::translate("SetParameters", "Set map points", 0));
        attackArrea_btn->setText(QApplication::translate("SetParameters", "Set attack area", 0));
        defenseArrea_btn->setText(QApplication::translate("SetParameters", "Set defense area", 0));
        ball_color->setText(QApplication::translate("SetParameters", "Set ball color", 0));
        camera_label->setText(QApplication::translate("SetParameters", "Select camera:", 0));
        config_serial->setText(QApplication::translate("SetParameters", "Configure Serial", 0));
        calibrate_camera->setText(QApplication::translate("SetParameters", "Calibrate Camera", 0));
        save_image->setText(QApplication::translate("SetParameters", "Save Image", 0));
    } // retranslateUi

};

namespace Ui {
    class SetParameters: public Ui_SetParameters {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETPARAMETERS_H
