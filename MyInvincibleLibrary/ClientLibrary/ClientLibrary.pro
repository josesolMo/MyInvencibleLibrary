#-------------------------------------------------
#
# Project created by QtCreator 2019-05-17T15:53:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ClientLibrary
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    imagenes.qrc

LIBS += -L/usr/include/json-c/ -ljson-c

QMAKE_CXXFLAGS += -std=gnu++11
