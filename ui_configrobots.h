/********************************************************************************
** Form generated from reading UI file 'configrobots.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGROBOTS_H
#define UI_CONFIGROBOTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigRobots
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QComboBox *select_robot;
    QSpinBox *robot_channel;
    QComboBox *robot_role;
    QLineEdit *robot_ID;
    QPushButton *configColorRange;
    QPushButton *save;

    void setupUi(QWidget *ConfigRobots)
    {
        if (ConfigRobots->objectName().isEmpty())
            ConfigRobots->setObjectName(QStringLiteral("ConfigRobots"));
        ConfigRobots->setWindowModality(Qt::ApplicationModal);
        ConfigRobots->resize(259, 240);
        label = new QLabel(ConfigRobots);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 91, 16));
        label_2 = new QLabel(ConfigRobots);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 60, 59, 14));
        label_3 = new QLabel(ConfigRobots);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 90, 59, 14));
        label_4 = new QLabel(ConfigRobots);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 120, 59, 14));
        select_robot = new QComboBox(ConfigRobots);
        select_robot->setObjectName(QStringLiteral("select_robot"));
        select_robot->setGeometry(QRect(110, 20, 131, 22));
        robot_channel = new QSpinBox(ConfigRobots);
        robot_channel->setObjectName(QStringLiteral("robot_channel"));
        robot_channel->setGeometry(QRect(80, 60, 47, 23));
        robot_role = new QComboBox(ConfigRobots);
        robot_role->setObjectName(QStringLiteral("robot_role"));
        robot_role->setGeometry(QRect(80, 90, 121, 22));
        robot_ID = new QLineEdit(ConfigRobots);
        robot_ID->setObjectName(QStringLiteral("robot_ID"));
        robot_ID->setGeometry(QRect(80, 120, 71, 22));
        configColorRange = new QPushButton(ConfigRobots);
        configColorRange->setObjectName(QStringLiteral("configColorRange"));
        configColorRange->setGeometry(QRect(20, 160, 231, 31));
        save = new QPushButton(ConfigRobots);
        save->setObjectName(QStringLiteral("save"));
        save->setGeometry(QRect(20, 200, 231, 31));

        retranslateUi(ConfigRobots);

        QMetaObject::connectSlotsByName(ConfigRobots);
    } // setupUi

    void retranslateUi(QWidget *ConfigRobots)
    {
        ConfigRobots->setWindowTitle(QApplication::translate("ConfigRobots", "Configure Robots", Q_NULLPTR));
        label->setText(QApplication::translate("ConfigRobots", "Select Robot:", Q_NULLPTR));
        label_2->setText(QApplication::translate("ConfigRobots", "Channel:", Q_NULLPTR));
        label_3->setText(QApplication::translate("ConfigRobots", "Role:", Q_NULLPTR));
        label_4->setText(QApplication::translate("ConfigRobots", "ID:", Q_NULLPTR));
        configColorRange->setText(QApplication::translate("ConfigRobots", "Config Color Range", Q_NULLPTR));
        save->setText(QApplication::translate("ConfigRobots", "Save", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ConfigRobots: public Ui_ConfigRobots {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGROBOTS_H
