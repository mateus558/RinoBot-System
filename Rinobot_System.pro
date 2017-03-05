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
    cph.cpp \
    cpo.cpp \
    fuzzy.cpp \
    mover.cpp \
    cph2.cpp \
    cpo2.cpp \
    cpo3.cpp

HEADERS  += mainwindow.h \
    vision.h \
    setparameters.h \
    robot.h \
    utils.h \
    configrobots.h \
    setcolorrange.h \
    settingsdialog.h \
    soccer_window.h \
    cph.h \
    cpo.h \
    fuzzy.h \
    serial.h \
    mover.h \
    cph2.h \
    cpo2.h \
    cpo3.h

FORMS    += mainwindow.ui \
    setparameters.ui \
    configrobots.ui \
    setcolorrange.ui \
    settingsdialog.ui \
    soccer_window.ui

INCLUDEPATH += "/usr/local/include/opencv2"
LIBS += `pkg-config --cflags --libs opencv`
QT += serialport
