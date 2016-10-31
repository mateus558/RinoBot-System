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
    setcolorrange.cpp

HEADERS  += mainwindow.h \
    vision.h \
    setparameters.h \
    robot.h \
    utils.h \
    configrobots.h \
    setcolorrange.h

FORMS    += mainwindow.ui \
    setparameters.ui \
    configrobots.ui \
    setcolorrange.ui

INCLUDEPATH += "/usr/local/include/opencv2"
LIBS += `pkg-config --cflags --libs opencv`
