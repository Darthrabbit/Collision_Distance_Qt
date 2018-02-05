#-------------------------------------------------
#
# Project created by QtCreator 2018-02-02T17:17:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CollisionDetection
TEMPLATE = app


SOURCES += main.cpp\
        simulation.cpp \
    fahrzeug.cpp \
    sensor.cpp \
    begrenzung.cpp

HEADERS  += simulation.h \
    fahrzeug.h \
    sensor.h \
    global.h \
    begrenzung.h

FORMS    += simulation.ui

CONFIG += c++11
