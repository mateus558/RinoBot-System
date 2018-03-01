/********************************************************************************
** Form generated from reading UI file 'setparameters.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
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
    QLabel *setColorlbl;
    QLabel *configurelbl;
    QLabel *setPointslbl;
    QLabel *idlbl;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SetParameters)
    {
        if (SetParameters->objectName().isEmpty())
            SetParameters->setObjectName(QStringLiteral("SetParameters"));
        SetParameters->setWindowModality(Qt::NonModal);
        SetParameters->resize(997, 516);
        centralwidget = new QWidget(SetParameters);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        camera_video = new QLabel(centralwidget);
        camera_video->setObjectName(QStringLiteral("camera_video"));
        camera_video->setGeometry(QRect(250, 10, 741, 451));
        camera_video->setStyleSheet(QStringLiteral("Background-color: #000;"));
        initCapture = new QPushButton(centralwidget);
        initCapture->setObjectName(QStringLiteral("initCapture"));
        initCapture->setGeometry(QRect(140, 330, 51, 31));
        fps_number = new QLCDNumber(centralwidget);
        fps_number->setObjectName(QStringLiteral("fps_number"));
        fps_number->setGeometry(QRect(170, 380, 64, 23));
        fps_number->setStyleSheet(QStringLiteral("Background-Color: #000"));
        fps_label = new QLabel(centralwidget);
        fps_label->setObjectName(QStringLiteral("fps_label"));
        fps_label->setGeometry(QRect(130, 380, 31, 21));
        readParameters = new QPushButton(centralwidget);
        readParameters->setObjectName(QStringLiteral("readParameters"));
        readParameters->setGeometry(QRect(10, 160, 151, 31));
        configRobots = new QPushButton(centralwidget);
        configRobots->setObjectName(QStringLiteral("configRobots"));
        configRobots->setGeometry(QRect(10, 120, 71, 31));
        T1_color = new QPushButton(centralwidget);
        T1_color->setObjectName(QStringLiteral("T1_color"));
        T1_color->setGeometry(QRect(10, 50, 71, 31));
        T2_color = new QPushButton(centralwidget);
        T2_color->setObjectName(QStringLiteral("T2_color"));
        T2_color->setGeometry(QRect(90, 50, 71, 31));
        mapPoints = new QPushButton(centralwidget);
        mapPoints->setObjectName(QStringLiteral("mapPoints"));
        mapPoints->setGeometry(QRect(10, 230, 61, 31));
        attackArrea_btn = new QPushButton(centralwidget);
        attackArrea_btn->setObjectName(QStringLiteral("attackArrea_btn"));
        attackArrea_btn->setGeometry(QRect(90, 230, 101, 31));
        defenseArrea_btn = new QPushButton(centralwidget);
        defenseArrea_btn->setObjectName(QStringLiteral("defenseArrea_btn"));
        defenseArrea_btn->setGeometry(QRect(90, 270, 101, 31));
        ball_color = new QPushButton(centralwidget);
        ball_color->setObjectName(QStringLiteral("ball_color"));
        ball_color->setGeometry(QRect(170, 50, 71, 31));
        camera_label = new QLabel(centralwidget);
        camera_label->setObjectName(QStringLiteral("camera_label"));
        camera_label->setGeometry(QRect(10, 330, 101, 31));
        spinBox = new QSpinBox(centralwidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(50, 380, 47, 23));
        spinBox->setMaximum(1000);
        spinBox->setValue(300);
        config_serial = new QPushButton(centralwidget);
        config_serial->setObjectName(QStringLiteral("config_serial"));
        config_serial->setGeometry(QRect(90, 120, 71, 31));
        calibrate_camera = new QPushButton(centralwidget);
        calibrate_camera->setObjectName(QStringLiteral("calibrate_camera"));
        calibrate_camera->setGeometry(QRect(10, 420, 231, 41));
        setColorlbl = new QLabel(centralwidget);
        setColorlbl->setObjectName(QStringLiteral("setColorlbl"));
        setColorlbl->setGeometry(QRect(10, 20, 81, 17));
        configurelbl = new QLabel(centralwidget);
        configurelbl->setObjectName(QStringLiteral("configurelbl"));
        configurelbl->setGeometry(QRect(10, 100, 81, 17));
        setPointslbl = new QLabel(centralwidget);
        setPointslbl->setObjectName(QStringLiteral("setPointslbl"));
        setPointslbl->setGeometry(QRect(10, 210, 101, 17));
        idlbl = new QLabel(centralwidget);
        idlbl->setObjectName(QStringLiteral("idlbl"));
        idlbl->setGeometry(QRect(20, 380, 67, 21));
        SetParameters->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(SetParameters);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        SetParameters->setStatusBar(statusbar);

        retranslateUi(SetParameters);

        QMetaObject::connectSlotsByName(SetParameters);
    } // setupUi

    void retranslateUi(QMainWindow *SetParameters)
    {
        SetParameters->setWindowTitle(QApplication::translate("SetParameters", "Set Parameters", Q_NULLPTR));
        camera_video->setText(QApplication::translate("SetParameters", "TextLabel", Q_NULLPTR));
        initCapture->setText(QApplication::translate("SetParameters", "Off", Q_NULLPTR));
        fps_label->setText(QApplication::translate("SetParameters", "FPS:", Q_NULLPTR));
        readParameters->setText(QApplication::translate("SetParameters", "Read Parameters", Q_NULLPTR));
        configRobots->setText(QApplication::translate("SetParameters", "Robots", Q_NULLPTR));
        T1_color->setText(QApplication::translate("SetParameters", "Team 1", Q_NULLPTR));
        T2_color->setText(QApplication::translate("SetParameters", "Team 2", Q_NULLPTR));
        mapPoints->setText(QApplication::translate("SetParameters", "Map", Q_NULLPTR));
        attackArrea_btn->setText(QApplication::translate("SetParameters", "Attack Area", Q_NULLPTR));
        defenseArrea_btn->setText(QApplication::translate("SetParameters", "Defense Area", Q_NULLPTR));
        ball_color->setText(QApplication::translate("SetParameters", "Ball", Q_NULLPTR));
        camera_label->setText(QApplication::translate("SetParameters", "Set Camera:", Q_NULLPTR));
        config_serial->setText(QApplication::translate("SetParameters", "Serial", Q_NULLPTR));
        calibrate_camera->setText(QApplication::translate("SetParameters", "Calibrate (Video4Linux)", Q_NULLPTR));
        setColorlbl->setText(QApplication::translate("SetParameters", "Set Colors:", Q_NULLPTR));
        configurelbl->setText(QApplication::translate("SetParameters", "Configure:", Q_NULLPTR));
        setPointslbl->setText(QApplication::translate("SetParameters", "Set Points:", Q_NULLPTR));
        idlbl->setText(QApplication::translate("SetParameters", "ID:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SetParameters: public Ui_SetParameters {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETPARAMETERS_H
