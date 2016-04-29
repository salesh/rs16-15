#-------------------------------------------------
#
# Project created by QtCreator 2016-04-29T00:44:10
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RemoteNiP-server
TEMPLATE = app


SOURCES += main.cpp\
        remoteserver.cpp

HEADERS  += remoteserver.h

FORMS    += remoteserver.ui

QMAKE_CXXFLAGS += -std=c++11
