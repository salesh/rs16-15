#-------------------------------------------------
#
# Project created by QtCreator 2016-05-12T00:18:04
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RemoteNiP-client
TEMPLATE = app


SOURCES += main.cpp\
        remoteclient.cpp

HEADERS  += remoteclient.h

FORMS    += remoteclient.ui

QMAKE_CXXFLAGS += -std=c++11

CONFIG += mobility

DISTFILES +=
