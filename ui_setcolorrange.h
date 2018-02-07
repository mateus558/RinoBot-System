/********************************************************************************
** Form generated from reading UI file 'setcolorrange.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETCOLORRANGE_H
#define UI_SETCOLORRANGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetColorRange
{
public:
    QLabel *label_7;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QGroupBox *groupBox;
    QLabel *label_4;
    QSlider *horizontalSlider_4;
    QLCDNumber *lcdNumber_4;
    QLabel *label;
    QSlider *horizontalSlider;
    QLCDNumber *lcdNumber;
    QGroupBox *groupBox_2;
    QLabel *label_6;
    QSlider *horizontalSlider_5;
    QLCDNumber *lcdNumber_5;
    QLabel *label_2;
    QSlider *horizontalSlider_2;
    QLCDNumber *lcdNumber_2;
    QGroupBox *groupBox_3;
    QLabel *label_5;
    QSlider *horizontalSlider_6;
    QLCDNumber *lcdNumber_6;
    QLabel *label_3;
    QSlider *horizontalSlider_3;
    QLCDNumber *lcdNumber_3;

    void setupUi(QWidget *SetColorRange)
    {
        if (SetColorRange->objectName().isEmpty())
            SetColorRange->setObjectName(QStringLiteral("SetColorRange"));
        SetColorRange->setWindowModality(Qt::WindowModal);
        SetColorRange->resize(940, 495);
        label_7 = new QLabel(SetColorRange);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(310, 20, 611, 461));
        label_7->setStyleSheet(QStringLiteral("Background-Color: #000"));
        pushButton = new QPushButton(SetColorRange);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(30, 400, 221, 31));
        pushButton_2 = new QPushButton(SetColorRange);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(30, 360, 221, 31));
        groupBox = new QGroupBox(SetColorRange);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 271, 91));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 60, 59, 14));
        horizontalSlider_4 = new QSlider(groupBox);
        horizontalSlider_4->setObjectName(QStringLiteral("horizontalSlider_4"));
        horizontalSlider_4->setGeometry(QRect(60, 60, 160, 16));
        horizontalSlider_4->setMaximum(255);
        horizontalSlider_4->setValue(255);
        horizontalSlider_4->setSliderPosition(255);
        horizontalSlider_4->setOrientation(Qt::Horizontal);
        lcdNumber_4 = new QLCDNumber(groupBox);
        lcdNumber_4->setObjectName(QStringLiteral("lcdNumber_4"));
        lcdNumber_4->setGeometry(QRect(230, 60, 31, 16));
        lcdNumber_4->setStyleSheet(QStringLiteral("Background-Color: #000"));
        lcdNumber_4->setProperty("value", QVariant(255));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 30, 59, 14));
        horizontalSlider = new QSlider(groupBox);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(60, 30, 160, 16));
        horizontalSlider->setMaximum(255);
        horizontalSlider->setOrientation(Qt::Horizontal);
        lcdNumber = new QLCDNumber(groupBox);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(230, 30, 31, 16));
        lcdNumber->setStyleSheet(QStringLiteral("Background-Color: #000"));
        groupBox_2 = new QGroupBox(SetColorRange);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 120, 271, 91));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 60, 59, 14));
        horizontalSlider_5 = new QSlider(groupBox_2);
        horizontalSlider_5->setObjectName(QStringLiteral("horizontalSlider_5"));
        horizontalSlider_5->setGeometry(QRect(60, 60, 160, 16));
        horizontalSlider_5->setMaximum(255);
        horizontalSlider_5->setSliderPosition(255);
        horizontalSlider_5->setOrientation(Qt::Horizontal);
        lcdNumber_5 = new QLCDNumber(groupBox_2);
        lcdNumber_5->setObjectName(QStringLiteral("lcdNumber_5"));
        lcdNumber_5->setGeometry(QRect(230, 60, 31, 16));
        lcdNumber_5->setStyleSheet(QStringLiteral("Background-Color: #000"));
        lcdNumber_5->setProperty("value", QVariant(255));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 30, 59, 14));
        horizontalSlider_2 = new QSlider(groupBox_2);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setGeometry(QRect(60, 30, 160, 16));
        horizontalSlider_2->setMaximum(255);
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        lcdNumber_2 = new QLCDNumber(groupBox_2);
        lcdNumber_2->setObjectName(QStringLiteral("lcdNumber_2"));
        lcdNumber_2->setGeometry(QRect(230, 30, 31, 16));
        lcdNumber_2->setStyleSheet(QStringLiteral("Background-Color: #000"));
        groupBox_3 = new QGroupBox(SetColorRange);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 230, 281, 91));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 60, 59, 14));
        horizontalSlider_6 = new QSlider(groupBox_3);
        horizontalSlider_6->setObjectName(QStringLiteral("horizontalSlider_6"));
        horizontalSlider_6->setGeometry(QRect(70, 60, 160, 16));
        horizontalSlider_6->setMaximum(255);
        horizontalSlider_6->setValue(255);
        horizontalSlider_6->setOrientation(Qt::Horizontal);
        lcdNumber_6 = new QLCDNumber(groupBox_3);
        lcdNumber_6->setObjectName(QStringLiteral("lcdNumber_6"));
        lcdNumber_6->setGeometry(QRect(240, 60, 31, 16));
        lcdNumber_6->setStyleSheet(QStringLiteral("Background-Color: #000"));
        lcdNumber_6->setProperty("value", QVariant(255));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 30, 59, 14));
        horizontalSlider_3 = new QSlider(groupBox_3);
        horizontalSlider_3->setObjectName(QStringLiteral("horizontalSlider_3"));
        horizontalSlider_3->setGeometry(QRect(70, 30, 160, 16));
        horizontalSlider_3->setMaximum(255);
        horizontalSlider_3->setOrientation(Qt::Horizontal);
        lcdNumber_3 = new QLCDNumber(groupBox_3);
        lcdNumber_3->setObjectName(QStringLiteral("lcdNumber_3"));
        lcdNumber_3->setGeometry(QRect(240, 30, 31, 16));
        lcdNumber_3->setStyleSheet(QStringLiteral("Background-Color: #000"));
        groupBox_2->raise();
        groupBox->raise();
        label_7->raise();
        pushButton->raise();
        pushButton_2->raise();
        groupBox_3->raise();

        retranslateUi(SetColorRange);

        QMetaObject::connectSlotsByName(SetColorRange);
    } // setupUi

    void retranslateUi(QWidget *SetColorRange)
    {
        SetColorRange->setWindowTitle(QApplication::translate("SetColorRange", "Color Ranges", Q_NULLPTR));
        label_7->setText(QApplication::translate("SetColorRange", "TextLabel", Q_NULLPTR));
        pushButton->setText(QApplication::translate("SetColorRange", "Set", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("SetColorRange", "Capture", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("SetColorRange", "Huehuehuehuehue        BR", Q_NULLPTR));
        label_4->setText(QApplication::translate("SetColorRange", "H max:", Q_NULLPTR));
        label->setText(QApplication::translate("SetColorRange", "H min:", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("SetColorRange", "Saturation", Q_NULLPTR));
        label_6->setText(QApplication::translate("SetColorRange", "S max:", Q_NULLPTR));
        label_2->setText(QApplication::translate("SetColorRange", "S min:", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("SetColorRange", "Value", Q_NULLPTR));
        label_5->setText(QApplication::translate("SetColorRange", "V max:", Q_NULLPTR));
        label_3->setText(QApplication::translate("SetColorRange", "V min:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SetColorRange: public Ui_SetColorRange {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETCOLORRANGE_H
