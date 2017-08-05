/********************************************************************************
** Form generated from reading UI file 'video4linuxconfig.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEO4LINUXCONFIG_H
#define UI_VIDEO4LINUXCONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_video4linuxConfig
{
public:
    QLabel *brightness_label;
    QLabel *contrast_label;
    QLabel *saturation_label;
    QLabel *white_bal_label;
    QLabel *sharpness_label;
    QLabel *exposure_label;
    QLabel *focus_label;
    QSlider *bright_slider;
    QSlider *contrast_slider;
    QSlider *saturation_slider;
    QSlider *white_bal_slider;
    QSlider *sharpness_slider;
    QSlider *exposure_slider;
    QSlider *focus_slider;
    QLabel *camera_view;
    QLCDNumber *bright_lcd;
    QLCDNumber *contrast_lcd;
    QLCDNumber *saturation_lcd;
    QLCDNumber *white_bal_lcd;
    QLCDNumber *sharpness_lcd;
    QLCDNumber *exposure_lcd;
    QLCDNumber *focus_lcd;
    QPushButton *pushButton;

    void setupUi(QWidget *video4linuxConfig)
    {
        if (video4linuxConfig->objectName().isEmpty())
            video4linuxConfig->setObjectName(QStringLiteral("video4linuxConfig"));
        video4linuxConfig->resize(697, 251);
        brightness_label = new QLabel(video4linuxConfig);
        brightness_label->setObjectName(QStringLiteral("brightness_label"));
        brightness_label->setGeometry(QRect(20, 10, 91, 17));
        contrast_label = new QLabel(video4linuxConfig);
        contrast_label->setObjectName(QStringLiteral("contrast_label"));
        contrast_label->setGeometry(QRect(20, 40, 91, 17));
        saturation_label = new QLabel(video4linuxConfig);
        saturation_label->setObjectName(QStringLiteral("saturation_label"));
        saturation_label->setGeometry(QRect(20, 70, 91, 17));
        white_bal_label = new QLabel(video4linuxConfig);
        white_bal_label->setObjectName(QStringLiteral("white_bal_label"));
        white_bal_label->setGeometry(QRect(20, 100, 111, 17));
        sharpness_label = new QLabel(video4linuxConfig);
        sharpness_label->setObjectName(QStringLiteral("sharpness_label"));
        sharpness_label->setGeometry(QRect(20, 130, 111, 17));
        exposure_label = new QLabel(video4linuxConfig);
        exposure_label->setObjectName(QStringLiteral("exposure_label"));
        exposure_label->setGeometry(QRect(20, 160, 81, 17));
        focus_label = new QLabel(video4linuxConfig);
        focus_label->setObjectName(QStringLiteral("focus_label"));
        focus_label->setGeometry(QRect(20, 190, 81, 17));
        bright_slider = new QSlider(video4linuxConfig);
        bright_slider->setObjectName(QStringLiteral("bright_slider"));
        bright_slider->setGeometry(QRect(140, 10, 160, 16));
        bright_slider->setMaximum(255);
        bright_slider->setOrientation(Qt::Horizontal);
        contrast_slider = new QSlider(video4linuxConfig);
        contrast_slider->setObjectName(QStringLiteral("contrast_slider"));
        contrast_slider->setGeometry(QRect(140, 40, 160, 16));
        contrast_slider->setMaximum(255);
        contrast_slider->setOrientation(Qt::Horizontal);
        saturation_slider = new QSlider(video4linuxConfig);
        saturation_slider->setObjectName(QStringLiteral("saturation_slider"));
        saturation_slider->setGeometry(QRect(140, 70, 160, 16));
        saturation_slider->setMaximum(255);
        saturation_slider->setOrientation(Qt::Horizontal);
        white_bal_slider = new QSlider(video4linuxConfig);
        white_bal_slider->setObjectName(QStringLiteral("white_bal_slider"));
        white_bal_slider->setGeometry(QRect(140, 100, 160, 16));
        white_bal_slider->setMinimum(2000);
        white_bal_slider->setMaximum(6500);
        white_bal_slider->setOrientation(Qt::Horizontal);
        sharpness_slider = new QSlider(video4linuxConfig);
        sharpness_slider->setObjectName(QStringLiteral("sharpness_slider"));
        sharpness_slider->setGeometry(QRect(140, 130, 160, 16));
        sharpness_slider->setMaximum(255);
        sharpness_slider->setOrientation(Qt::Horizontal);
        exposure_slider = new QSlider(video4linuxConfig);
        exposure_slider->setObjectName(QStringLiteral("exposure_slider"));
        exposure_slider->setGeometry(QRect(140, 160, 160, 16));
        exposure_slider->setMinimum(3);
        exposure_slider->setMaximum(2047);
        exposure_slider->setOrientation(Qt::Horizontal);
        focus_slider = new QSlider(video4linuxConfig);
        focus_slider->setObjectName(QStringLiteral("focus_slider"));
        focus_slider->setGeometry(QRect(140, 190, 160, 16));
        focus_slider->setMaximum(250);
        focus_slider->setOrientation(Qt::Horizontal);
        camera_view = new QLabel(video4linuxConfig);
        camera_view->setObjectName(QStringLiteral("camera_view"));
        camera_view->setGeometry(QRect(390, 10, 291, 201));
        camera_view->setStyleSheet(QStringLiteral("Background-Color: #000"));
        bright_lcd = new QLCDNumber(video4linuxConfig);
        bright_lcd->setObjectName(QStringLiteral("bright_lcd"));
        bright_lcd->setGeometry(QRect(310, 10, 64, 23));
        bright_lcd->setStyleSheet(QStringLiteral("Background-Color: #000"));
        bright_lcd->setProperty("intValue", QVariant(255));
        contrast_lcd = new QLCDNumber(video4linuxConfig);
        contrast_lcd->setObjectName(QStringLiteral("contrast_lcd"));
        contrast_lcd->setGeometry(QRect(310, 40, 64, 23));
        contrast_lcd->setStyleSheet(QStringLiteral("Background-Color: #000"));
        contrast_lcd->setProperty("intValue", QVariant(255));
        saturation_lcd = new QLCDNumber(video4linuxConfig);
        saturation_lcd->setObjectName(QStringLiteral("saturation_lcd"));
        saturation_lcd->setGeometry(QRect(310, 70, 64, 23));
        saturation_lcd->setStyleSheet(QStringLiteral("Background-Color: #000"));
        saturation_lcd->setProperty("intValue", QVariant(255));
        white_bal_lcd = new QLCDNumber(video4linuxConfig);
        white_bal_lcd->setObjectName(QStringLiteral("white_bal_lcd"));
        white_bal_lcd->setGeometry(QRect(310, 100, 64, 23));
        white_bal_lcd->setStyleSheet(QStringLiteral("Background-Color: #000"));
        white_bal_lcd->setProperty("intValue", QVariant(6500));
        sharpness_lcd = new QLCDNumber(video4linuxConfig);
        sharpness_lcd->setObjectName(QStringLiteral("sharpness_lcd"));
        sharpness_lcd->setGeometry(QRect(310, 130, 64, 23));
        sharpness_lcd->setStyleSheet(QStringLiteral("Background-Color: #000"));
        sharpness_lcd->setProperty("intValue", QVariant(255));
        exposure_lcd = new QLCDNumber(video4linuxConfig);
        exposure_lcd->setObjectName(QStringLiteral("exposure_lcd"));
        exposure_lcd->setGeometry(QRect(310, 160, 64, 23));
        exposure_lcd->setStyleSheet(QStringLiteral("Background-Color: #000"));
        exposure_lcd->setProperty("intValue", QVariant(2047));
        focus_lcd = new QLCDNumber(video4linuxConfig);
        focus_lcd->setObjectName(QStringLiteral("focus_lcd"));
        focus_lcd->setGeometry(QRect(310, 190, 64, 23));
        focus_lcd->setStyleSheet(QStringLiteral("Background-Color: #000"));
        focus_lcd->setProperty("intValue", QVariant(250));
        pushButton = new QPushButton(video4linuxConfig);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(20, 220, 111, 25));

        retranslateUi(video4linuxConfig);

        QMetaObject::connectSlotsByName(video4linuxConfig);
    } // setupUi

    void retranslateUi(QWidget *video4linuxConfig)
    {
        video4linuxConfig->setWindowTitle(QApplication::translate("video4linuxConfig", "Form", Q_NULLPTR));
        brightness_label->setText(QApplication::translate("video4linuxConfig", "Brightness:", Q_NULLPTR));
        contrast_label->setText(QApplication::translate("video4linuxConfig", "Contrast:", Q_NULLPTR));
        saturation_label->setText(QApplication::translate("video4linuxConfig", "Saturation:", Q_NULLPTR));
        white_bal_label->setText(QApplication::translate("video4linuxConfig", "White Balance:", Q_NULLPTR));
        sharpness_label->setText(QApplication::translate("video4linuxConfig", "Sharpness:", Q_NULLPTR));
        exposure_label->setText(QApplication::translate("video4linuxConfig", "Exposure:", Q_NULLPTR));
        focus_label->setText(QApplication::translate("video4linuxConfig", "Focus:", Q_NULLPTR));
        camera_view->setText(QApplication::translate("video4linuxConfig", "video", Q_NULLPTR));
        pushButton->setText(QApplication::translate("video4linuxConfig", "Set to Default", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class video4linuxConfig: public Ui_video4linuxConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEO4LINUXCONFIG_H
