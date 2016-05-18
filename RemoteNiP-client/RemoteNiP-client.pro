#-------------------------------------------------
#
# Project created by QtCreator 2016-05-12T00:18:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RemoteNiP-client
TEMPLATE = app


SOURCES += main.cpp\
        remoteclient.cpp

HEADERS  += remoteclient.h

FORMS    += remoteclient.ui

CONFIG += mobility
MOBILITY = 

