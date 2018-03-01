/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionRead_Parameters;
    QAction *actionSet_Parameters;
    QAction *actionOpen_Camera;
    QAction *actionShow_Areas;
    QAction *actionShow_VisionLog;
    QAction *actionSwap_ATK_DEF;
    QAction *actionSwap_Teams;
    QAction *actionOpen_InfoWindow;
    QWidget *centralWidget;
    QLabel *logo;
    QGraphicsView *game_view;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_9;
    QPushButton *btn_startGame;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_7;
    QLabel *fps_label;
    QLabel *cam_id_label;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_8;
    QLCDNumber *lcd_fps;
    QSpinBox *cam_id_spinBox;
    QVBoxLayout *verticalLayout;
    QLabel *strategylbl;
    QLabel *currentStrategylbl;
    QHBoxLayout *horizontalLayout;
    QComboBox *cbox_strategyOptions;
    QPushButton *btn_changeStrategy;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *gandalf_label;
    QLabel *leona_label;
    QLabel *presto_label;
    QVBoxLayout *verticalLayout_2;
    QLabel *gandalf_detec_col_label;
    QLabel *leona_detec_col_label;
    QLabel *presto_detec_col_label;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *gandalf_detec_label;
    QLabel *leona_detec_label;
    QLabel *presto_detec_label;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_5;
    QLabel *ball_detec_col_label;
    QLabel *serial_status_col_label;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_6;
    QLabel *ball_detec_label;
    QLabel *serial_status_label;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QMenu *menuSettings;
    QMenu *menuParameters;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(1280, 720);
        QIcon icon;
        icon.addFile(QStringLiteral("../../Untitled1.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setAutoFillBackground(false);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionRead_Parameters = new QAction(MainWindow);
        actionRead_Parameters->setObjectName(QStringLiteral("actionRead_Parameters"));
        actionSet_Parameters = new QAction(MainWindow);
        actionSet_Parameters->setObjectName(QStringLiteral("actionSet_Parameters"));
        actionOpen_Camera = new QAction(MainWindow);
        actionOpen_Camera->setObjectName(QStringLiteral("actionOpen_Camera"));
        actionOpen_Camera->setCheckable(true);
        actionShow_Areas = new QAction(MainWindow);
        actionShow_Areas->setObjectName(QStringLiteral("actionShow_Areas"));
        actionShow_Areas->setCheckable(true);
        actionShow_VisionLog = new QAction(MainWindow);
        actionShow_VisionLog->setObjectName(QStringLiteral("actionShow_VisionLog"));
        actionShow_VisionLog->setCheckable(true);
        actionSwap_ATK_DEF = new QAction(MainWindow);
        actionSwap_ATK_DEF->setObjectName(QStringLiteral("actionSwap_ATK_DEF"));
        actionSwap_ATK_DEF->setCheckable(true);
        actionSwap_Teams = new QAction(MainWindow);
        actionSwap_Teams->setObjectName(QStringLiteral("actionSwap_Teams"));
        actionSwap_Teams->setCheckable(true);
        actionOpen_InfoWindow = new QAction(MainWindow);
        actionOpen_InfoWindow->setObjectName(QStringLiteral("actionOpen_InfoWindow"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        logo = new QLabel(centralWidget);
        logo->setObjectName(QStringLiteral("logo"));
        logo->setGeometry(QRect(60, 10, 231, 241));
        logo->setMinimumSize(QSize(231, 241));
        logo->setMaximumSize(QSize(231, 241));
        logo->setPixmap(QPixmap(QString::fromUtf8("rino.png")));
        logo->setScaledContents(true);
        logo->setTextInteractionFlags(Qt::NoTextInteraction);
        game_view = new QGraphicsView(centralWidget);
        game_view->setObjectName(QStringLiteral("game_view"));
        game_view->setGeometry(QRect(368, 40, 901, 611));
        verticalLayoutWidget_4 = new QWidget(centralWidget);
        verticalLayoutWidget_4->setObjectName(QStringLiteral("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(10, 260, 351, 431));
        verticalLayout_9 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        btn_startGame = new QPushButton(verticalLayoutWidget_4);
        btn_startGame->setObjectName(QStringLiteral("btn_startGame"));

        verticalLayout_9->addWidget(btn_startGame);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        fps_label = new QLabel(verticalLayoutWidget_4);
        fps_label->setObjectName(QStringLiteral("fps_label"));

        verticalLayout_7->addWidget(fps_label);

        cam_id_label = new QLabel(verticalLayoutWidget_4);
        cam_id_label->setObjectName(QStringLiteral("cam_id_label"));

        verticalLayout_7->addWidget(cam_id_label);


        horizontalLayout_6->addLayout(verticalLayout_7);

        horizontalSpacer_4 = new QSpacerItem(88, 30, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        lcd_fps = new QLCDNumber(verticalLayoutWidget_4);
        lcd_fps->setObjectName(QStringLiteral("lcd_fps"));
        lcd_fps->setStyleSheet(QStringLiteral("Background-color: #000;"));
        lcd_fps->setLineWidth(4);

        verticalLayout_8->addWidget(lcd_fps);

        cam_id_spinBox = new QSpinBox(verticalLayoutWidget_4);
        cam_id_spinBox->setObjectName(QStringLiteral("cam_id_spinBox"));
        cam_id_spinBox->setMaximum(999);
        cam_id_spinBox->setValue(0);

        verticalLayout_8->addWidget(cam_id_spinBox);


        horizontalLayout_6->addLayout(verticalLayout_8);


        verticalLayout_9->addLayout(horizontalLayout_6);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        strategylbl = new QLabel(verticalLayoutWidget_4);
        strategylbl->setObjectName(QStringLiteral("strategylbl"));

        verticalLayout->addWidget(strategylbl);

        currentStrategylbl = new QLabel(verticalLayoutWidget_4);
        currentStrategylbl->setObjectName(QStringLiteral("currentStrategylbl"));

        verticalLayout->addWidget(currentStrategylbl);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        cbox_strategyOptions = new QComboBox(verticalLayoutWidget_4);
        cbox_strategyOptions->setObjectName(QStringLiteral("cbox_strategyOptions"));
        cbox_strategyOptions->setCursor(QCursor(Qt::ArrowCursor));
        cbox_strategyOptions->setLocale(QLocale(QLocale::English, QLocale::UnitedStatesVirginIslands));

        horizontalLayout->addWidget(cbox_strategyOptions);

        btn_changeStrategy = new QPushButton(verticalLayoutWidget_4);
        btn_changeStrategy->setObjectName(QStringLiteral("btn_changeStrategy"));

        horizontalLayout->addWidget(btn_changeStrategy);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_9->addLayout(verticalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        gandalf_label = new QLabel(verticalLayoutWidget_4);
        gandalf_label->setObjectName(QStringLiteral("gandalf_label"));

        verticalLayout_4->addWidget(gandalf_label);

        leona_label = new QLabel(verticalLayoutWidget_4);
        leona_label->setObjectName(QStringLiteral("leona_label"));

        verticalLayout_4->addWidget(leona_label);

        presto_label = new QLabel(verticalLayoutWidget_4);
        presto_label->setObjectName(QStringLiteral("presto_label"));

        verticalLayout_4->addWidget(presto_label);


        horizontalLayout_2->addLayout(verticalLayout_4);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        gandalf_detec_col_label = new QLabel(verticalLayoutWidget_4);
        gandalf_detec_col_label->setObjectName(QStringLiteral("gandalf_detec_col_label"));
        gandalf_detec_col_label->setStyleSheet(QStringLiteral("background-color : red"));

        verticalLayout_2->addWidget(gandalf_detec_col_label);

        leona_detec_col_label = new QLabel(verticalLayoutWidget_4);
        leona_detec_col_label->setObjectName(QStringLiteral("leona_detec_col_label"));
        leona_detec_col_label->setStyleSheet(QStringLiteral("background-color : red"));

        verticalLayout_2->addWidget(leona_detec_col_label);

        presto_detec_col_label = new QLabel(verticalLayoutWidget_4);
        presto_detec_col_label->setObjectName(QStringLiteral("presto_detec_col_label"));
        presto_detec_col_label->setStyleSheet(QStringLiteral("background-color : red"));

        verticalLayout_2->addWidget(presto_detec_col_label);


        horizontalLayout_2->addLayout(verticalLayout_2);

        horizontalSpacer_3 = new QSpacerItem(38, 75, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        gandalf_detec_label = new QLabel(verticalLayoutWidget_4);
        gandalf_detec_label->setObjectName(QStringLiteral("gandalf_detec_label"));

        verticalLayout_3->addWidget(gandalf_detec_label);

        leona_detec_label = new QLabel(verticalLayoutWidget_4);
        leona_detec_label->setObjectName(QStringLiteral("leona_detec_label"));

        verticalLayout_3->addWidget(leona_detec_label);

        presto_detec_label = new QLabel(verticalLayoutWidget_4);
        presto_detec_label->setObjectName(QStringLiteral("presto_detec_label"));

        verticalLayout_3->addWidget(presto_detec_label);


        horizontalLayout_2->addLayout(verticalLayout_3);


        verticalLayout_9->addLayout(horizontalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout_9->addItem(verticalSpacer_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalSpacer = new QSpacerItem(88, 30, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        ball_detec_col_label = new QLabel(verticalLayoutWidget_4);
        ball_detec_col_label->setObjectName(QStringLiteral("ball_detec_col_label"));
        ball_detec_col_label->setStyleSheet(QStringLiteral("background-color : red"));

        verticalLayout_5->addWidget(ball_detec_col_label);

        serial_status_col_label = new QLabel(verticalLayoutWidget_4);
        serial_status_col_label->setObjectName(QStringLiteral("serial_status_col_label"));
        serial_status_col_label->setStyleSheet(QStringLiteral("background-color : red"));

        verticalLayout_5->addWidget(serial_status_col_label);


        horizontalLayout_3->addLayout(verticalLayout_5);

        horizontalSpacer_2 = new QSpacerItem(32, 30, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        ball_detec_label = new QLabel(verticalLayoutWidget_4);
        ball_detec_label->setObjectName(QStringLiteral("ball_detec_label"));

        verticalLayout_6->addWidget(ball_detec_label);

        serial_status_label = new QLabel(verticalLayoutWidget_4);
        serial_status_label->setObjectName(QStringLiteral("serial_status_label"));

        verticalLayout_6->addWidget(serial_status_label);


        horizontalLayout_3->addLayout(verticalLayout_6);


        verticalLayout_9->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout_9->addItem(verticalSpacer);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1280, 22));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        menuParameters = new QMenu(menuBar);
        menuParameters->setObjectName(QStringLiteral("menuParameters"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuSettings->menuAction());
        menuBar->addAction(menuParameters->menuAction());
        menuSettings->addAction(actionOpen_Camera);
        menuSettings->addAction(actionShow_Areas);
        menuSettings->addAction(actionShow_VisionLog);
        menuSettings->addAction(actionSwap_ATK_DEF);
        menuSettings->addAction(actionSwap_Teams);
        menuSettings->addSeparator();
        menuSettings->addAction(actionOpen_InfoWindow);
        menuParameters->addAction(actionRead_Parameters);
        menuParameters->addAction(actionSet_Parameters);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Rinobot - IEEE Very Small Size Soccer", Q_NULLPTR));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", Q_NULLPTR));
        actionRead_Parameters->setText(QApplication::translate("MainWindow", "Read Parameters", Q_NULLPTR));
        actionSet_Parameters->setText(QApplication::translate("MainWindow", "Set Parameters", Q_NULLPTR));
        actionOpen_Camera->setText(QApplication::translate("MainWindow", "Open Camera", Q_NULLPTR));
        actionShow_Areas->setText(QApplication::translate("MainWindow", "Show Areas", Q_NULLPTR));
        actionShow_VisionLog->setText(QApplication::translate("MainWindow", "Show VisionLog", Q_NULLPTR));
        actionSwap_ATK_DEF->setText(QApplication::translate("MainWindow", "Swap ATK/DEF", Q_NULLPTR));
        actionSwap_Teams->setText(QApplication::translate("MainWindow", "Swap Teams", Q_NULLPTR));
        actionOpen_InfoWindow->setText(QApplication::translate("MainWindow", "Open Info Window", Q_NULLPTR));
        actionOpen_InfoWindow->setShortcut(QApplication::translate("MainWindow", "I", Q_NULLPTR));
        logo->setText(QString());
        btn_startGame->setText(QApplication::translate("MainWindow", "Game", Q_NULLPTR));
        btn_startGame->setShortcut(QApplication::translate("MainWindow", "Space", Q_NULLPTR));
        fps_label->setText(QApplication::translate("MainWindow", "FPS:", Q_NULLPTR));
        cam_id_label->setText(QApplication::translate("MainWindow", "Cam ID:", Q_NULLPTR));
        strategylbl->setText(QApplication::translate("MainWindow", "Strategy:", Q_NULLPTR));
        currentStrategylbl->setText(QApplication::translate("MainWindow", "Current: ", Q_NULLPTR));
        btn_changeStrategy->setText(QApplication::translate("MainWindow", "Change", Q_NULLPTR));
        gandalf_label->setText(QApplication::translate("MainWindow", "Gandalf:", Q_NULLPTR));
        leona_label->setText(QApplication::translate("MainWindow", "Leona:", Q_NULLPTR));
        presto_label->setText(QApplication::translate("MainWindow", "Presto:", Q_NULLPTR));
        gandalf_detec_col_label->setText(QString());
        leona_detec_col_label->setText(QString());
        presto_detec_col_label->setText(QString());
        gandalf_detec_label->setText(QApplication::translate("MainWindow", "Not Detected", Q_NULLPTR));
        leona_detec_label->setText(QApplication::translate("MainWindow", "Not Detected", Q_NULLPTR));
        presto_detec_label->setText(QApplication::translate("MainWindow", "Not Detected", Q_NULLPTR));
        ball_detec_col_label->setText(QString());
        serial_status_col_label->setText(QString());
        ball_detec_label->setText(QApplication::translate("MainWindow", "Ball not found", Q_NULLPTR));
        serial_status_label->setText(QApplication::translate("MainWindow", "Serial Closed", Q_NULLPTR));
        menuSettings->setTitle(QApplication::translate("MainWindow", "Settings", Q_NULLPTR));
        menuParameters->setTitle(QApplication::translate("MainWindow", "Parameters", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
