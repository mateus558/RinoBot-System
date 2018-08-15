#-------------------------------------------------
#
# Project created by QtCreator 2016-10-15T08:48:10
#
#-------------------------------------------------

QT       += core gui

#Se der merda apagar
#*************************************************
# remove possible other optimization flags
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE -= -O3

# add the desired -O3 if not present
QMAKE_CXXFLAGS_RELEASE *= -Ofast
#*************************************************

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
    fuzzy.cpp \
    navigation.cpp \
    game_functions.cpp \
    video4linuxconfig.cpp \
    drawobjects.cpp \
    mover.cpp \
    informationwindow.cpp
    mover.cpp

HEADERS  += mainwindow.h \
    vision.h \
    setparameters.h \
    robot.h \
    utils.h \
    configrobots.h \
    setcolorrange.h \
    settingsdialog.h \
    fuzzy.h \
    serial.h \
    navigation.h \
    game_functions.h \
    video4linuxconfig.h \
    drawobjects.h \
    mover.h \
    informationwindow.h
    mover.h

FORMS    += mainwindow.ui \
    setparameters.ui \
    configrobots.ui \
    setcolorrange.ui \
    settingsdialog.ui \
    video4linuxconfig.ui \
    informationwindow.ui

INCLUDEPATH += "/usr/local/include/opencv2"
LIBS += `pkg-config --cflags --libs opencv`
QT += serialport

