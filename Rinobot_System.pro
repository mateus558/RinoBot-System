#-------------------------------------------------
#
# Project created by QtCreator 2016-10-15T08:48:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Rinobot_System
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    vision.cpp \
    setparameters.cpp \
    robot.cpp \
    utils.cpp \
    configrobots.cpp \
    setcolorrange.cpp \
    serial.cpp \
    settingsdialog.cpp \
    soccer_window.cpp \
    fuzzy.cpp \
    navigation.cpp \
    game_functions.cpp \
    video4linuxconfig.cpp \
    drawobjects.cpp \
    mover.cpp
    mover.cpp

HEADERS  += mainwindow.h \
    vision.h \
    setparameters.h \
    robot.h \
    utils.h \
    configrobots.h \
    setcolorrange.h \
    settingsdialog.h \
    soccer_window.h \
    fuzzy.h \
    serial.h \
    navigation.h \
    game_functions.h \
    video4linuxconfig.h \
    drawobjects.h \
    mover.h
    mover.h

FORMS    += mainwindow.ui \
    setparameters.ui \
    configrobots.ui \
    setcolorrange.ui \
    settingsdialog.ui \
    soccer_window.ui \
    video4linuxconfig.ui

INCLUDEPATH += "/usr/local/include/opencv2"
LIBS += `pkg-config --cflags --libs opencv`
QT += serialport
