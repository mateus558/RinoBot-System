/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QWidget *centralWidget;
    QPushButton *setParameters;
    QPushButton *pushButton_5;
    QLabel *label;
    QComboBox *strategy_choosen;
    QLabel *logo;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->resize(382, 195);
        QIcon icon;
        icon.addFile(QStringLiteral("../../Untitled1.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setAutoFillBackground(false);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        setParameters = new QPushButton(centralWidget);
        setParameters->setObjectName(QStringLiteral("setParameters"));
        setParameters->setGeometry(QRect(30, 30, 141, 31));
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(30, 70, 141, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(210, 10, 101, 16));
        strategy_choosen = new QComboBox(centralWidget);
        strategy_choosen->setObjectName(QStringLiteral("strategy_choosen"));
        strategy_choosen->setGeometry(QRect(210, 40, 161, 22));
        logo = new QLabel(centralWidget);
        logo->setObjectName(QStringLiteral("logo"));
        logo->setGeometry(QRect(210, 70, 131, 111));
        logo->setPixmap(QPixmap(QString::fromUtf8("Untitled1.png")));
        logo->setScaledContents(true);
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Rinobot - IEEE Very Small Size Soccer", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        setParameters->setText(QApplication::translate("MainWindow", "Set Parameters", 0));
        pushButton_5->setText(QApplication::translate("MainWindow", "Play Soccer!", 0));
        label->setText(QApplication::translate("MainWindow", "Select Strategy:", 0));
        logo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
