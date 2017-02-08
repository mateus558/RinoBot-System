/********************************************************************************
** Form generated from reading UI file 'setcolorrange.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
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
    QSlider *horizontalSlider;
    QSlider *horizontalSlider_2;
    QSlider *horizontalSlider_3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QSlider *horizontalSlider_5;
    QSlider *horizontalSlider_4;
    QSlider *horizontalSlider_6;
    QLabel *label_6;
    QLabel *label_7;
    QLCDNumber *lcdNumber;
    QLCDNumber *lcdNumber_2;
    QLCDNumber *lcdNumber_3;
    QLCDNumber *lcdNumber_4;
    QLCDNumber *lcdNumber_5;
    QLCDNumber *lcdNumber_6;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;

    void setupUi(QWidget *SetColorRange)
    {
        if (SetColorRange->objectName().isEmpty())
            SetColorRange->setObjectName(QStringLiteral("SetColorRange"));
        SetColorRange->setWindowModality(Qt::WindowModal);
        SetColorRange->resize(864, 444);
        horizontalSlider = new QSlider(SetColorRange);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(70, 30, 160, 16));
        horizontalSlider->setMaximum(255);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider_2 = new QSlider(SetColorRange);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setGeometry(QRect(70, 60, 160, 16));
        horizontalSlider_2->setMaximum(255);
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        horizontalSlider_3 = new QSlider(SetColorRange);
        horizontalSlider_3->setObjectName(QStringLiteral("horizontalSlider_3"));
        horizontalSlider_3->setGeometry(QRect(70, 90, 160, 16));
        horizontalSlider_3->setMaximum(255);
        horizontalSlider_3->setOrientation(Qt::Horizontal);
        label = new QLabel(SetColorRange);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 30, 59, 14));
        label_2 = new QLabel(SetColorRange);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 60, 59, 14));
        label_3 = new QLabel(SetColorRange);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 90, 59, 14));
        label_4 = new QLabel(SetColorRange);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 150, 59, 14));
        label_5 = new QLabel(SetColorRange);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 210, 59, 14));
        horizontalSlider_5 = new QSlider(SetColorRange);
        horizontalSlider_5->setObjectName(QStringLiteral("horizontalSlider_5"));
        horizontalSlider_5->setGeometry(QRect(70, 180, 160, 16));
        horizontalSlider_5->setMaximum(255);
        horizontalSlider_5->setSliderPosition(255);
        horizontalSlider_5->setOrientation(Qt::Horizontal);
        horizontalSlider_4 = new QSlider(SetColorRange);
        horizontalSlider_4->setObjectName(QStringLiteral("horizontalSlider_4"));
        horizontalSlider_4->setGeometry(QRect(70, 150, 160, 16));
        horizontalSlider_4->setMaximum(255);
        horizontalSlider_4->setValue(255);
        horizontalSlider_4->setSliderPosition(255);
        horizontalSlider_4->setOrientation(Qt::Horizontal);
        horizontalSlider_6 = new QSlider(SetColorRange);
        horizontalSlider_6->setObjectName(QStringLiteral("horizontalSlider_6"));
        horizontalSlider_6->setGeometry(QRect(70, 210, 160, 16));
        horizontalSlider_6->setMaximum(255);
        horizontalSlider_6->setValue(255);
        horizontalSlider_6->setOrientation(Qt::Horizontal);
        label_6 = new QLabel(SetColorRange);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 180, 59, 14));
        label_7 = new QLabel(SetColorRange);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(300, 20, 541, 361));
        label_7->setStyleSheet(QStringLiteral("Background-Color: #000"));
        lcdNumber = new QLCDNumber(SetColorRange);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(240, 30, 31, 16));
        lcdNumber->setStyleSheet(QStringLiteral("Background-Color: #000"));
        lcdNumber_2 = new QLCDNumber(SetColorRange);
        lcdNumber_2->setObjectName(QStringLiteral("lcdNumber_2"));
        lcdNumber_2->setGeometry(QRect(240, 60, 31, 16));
        lcdNumber_2->setStyleSheet(QStringLiteral("Background-Color: #000"));
        lcdNumber_3 = new QLCDNumber(SetColorRange);
        lcdNumber_3->setObjectName(QStringLiteral("lcdNumber_3"));
        lcdNumber_3->setGeometry(QRect(240, 90, 31, 16));
        lcdNumber_3->setStyleSheet(QStringLiteral("Background-Color: #000"));
        lcdNumber_4 = new QLCDNumber(SetColorRange);
        lcdNumber_4->setObjectName(QStringLiteral("lcdNumber_4"));
        lcdNumber_4->setGeometry(QRect(240, 150, 31, 16));
        lcdNumber_4->setStyleSheet(QStringLiteral("Background-Color: #000"));
        lcdNumber_4->setProperty("value", QVariant(255));
        lcdNumber_5 = new QLCDNumber(SetColorRange);
        lcdNumber_5->setObjectName(QStringLiteral("lcdNumber_5"));
        lcdNumber_5->setGeometry(QRect(240, 180, 31, 16));
        lcdNumber_5->setStyleSheet(QStringLiteral("Background-Color: #000"));
        lcdNumber_5->setProperty("value", QVariant(255));
        lcdNumber_6 = new QLCDNumber(SetColorRange);
        lcdNumber_6->setObjectName(QStringLiteral("lcdNumber_6"));
        lcdNumber_6->setGeometry(QRect(240, 210, 31, 16));
        lcdNumber_6->setStyleSheet(QStringLiteral("Background-Color: #000"));
        lcdNumber_6->setProperty("value", QVariant(255));
        pushButton = new QPushButton(SetColorRange);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(40, 250, 211, 31));
        pushButton_2 = new QPushButton(SetColorRange);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(300, 390, 80, 22));
        groupBox = new QGroupBox(SetColorRange);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 0, 271, 111));
        groupBox_2 = new QGroupBox(SetColorRange);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 120, 271, 111));
        groupBox_2->raise();
        groupBox->raise();
        horizontalSlider->raise();
        horizontalSlider_2->raise();
        horizontalSlider_3->raise();
        label->raise();
        label_2->raise();
        label_3->raise();
        label_4->raise();
        label_5->raise();
        horizontalSlider_5->raise();
        horizontalSlider_4->raise();
        horizontalSlider_6->raise();
        label_6->raise();
        label_7->raise();
        lcdNumber->raise();
        lcdNumber_2->raise();
        lcdNumber_3->raise();
        lcdNumber_4->raise();
        lcdNumber_5->raise();
        lcdNumber_6->raise();
        pushButton->raise();
        pushButton_2->raise();

        retranslateUi(SetColorRange);

        QMetaObject::connectSlotsByName(SetColorRange);
    } // setupUi

    void retranslateUi(QWidget *SetColorRange)
    {
        SetColorRange->setWindowTitle(QApplication::translate("SetColorRange", "Color Ranges", 0));
        label->setText(QApplication::translate("SetColorRange", "H min:", 0));
        label_2->setText(QApplication::translate("SetColorRange", "S min:", 0));
        label_3->setText(QApplication::translate("SetColorRange", "V min:", 0));
        label_4->setText(QApplication::translate("SetColorRange", "H max:", 0));
        label_5->setText(QApplication::translate("SetColorRange", "V max:", 0));
        label_6->setText(QApplication::translate("SetColorRange", "S max:", 0));
        label_7->setText(QApplication::translate("SetColorRange", "TextLabel", 0));
        pushButton->setText(QApplication::translate("SetColorRange", "Set", 0));
        pushButton_2->setText(QApplication::translate("SetColorRange", "Capture", 0));
        groupBox->setTitle(QApplication::translate("SetColorRange", "Min color", 0));
        groupBox_2->setTitle(QApplication::translate("SetColorRange", "Max color", 0));
    } // retranslateUi

};

namespace Ui {
    class SetColorRange: public Ui_SetColorRange {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETCOLORRANGE_H
