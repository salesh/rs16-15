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

DISTFILES += \
    img/AndroidManifest.xml \
    img/gradle/wrapper/gradle-wrapper.jar \
    img/gradlew \
    img/res/values/libs.xml \
    img/build.gradle \
    img/gradle/wrapper/gradle-wrapper.properties \
    img/gradlew.bat \
    img/AndroidManifest.xml \
    img/res/values/libs.xml \
    img/build.gradle

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/img
