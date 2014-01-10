#-------------------------------------------------
#
# Project created by QtCreator 2013-09-23T16:36:40
#
#-------------------------------------------------

QT       += core gui
QT       += network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cserver.cpp \
    cdatabase.cpp \
    cclientsocket.cpp \
    xmlparse.cpp \
    xmlParse/tinystr.cpp \
    xmlParse/tinyxml.cpp \
    xmlParse/tinyxmlerror.cpp \
    xmlParse/tinyxmlparser.cpp

HEADERS  += mainwindow.h \
    cserver.h \
    cdatabase.h \
    cclientsocket.h \
    protocol.h \
    xmlparse.h \
    xmlParse/tinystr.h \
    xmlParse/tinyxml.h

FORMS    += mainwindow.ui

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x000000

OTHER_FILES += \
    android/res/values-ru/strings.xml \
    android/res/values-nb/strings.xml \
    android/res/values-rs/strings.xml \
    android/res/values-zh-rCN/strings.xml \
    android/res/values-it/strings.xml \
    android/res/values-id/strings.xml \
    android/res/values-de/strings.xml \
    android/res/values-ms/strings.xml \
    android/res/values-fr/strings.xml \
    android/res/values-et/strings.xml \
    android/res/values-pl/strings.xml \
    android/res/values-pt-rBR/strings.xml \
    android/res/values-ja/strings.xml \
    android/res/layout/splash.xml \
    android/res/values-zh-rTW/strings.xml \
    android/res/values-nl/strings.xml \
    android/res/values-el/strings.xml \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/res/values-fa/strings.xml \
    android/res/values-ro/strings.xml \
    android/res/values-es/strings.xml \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/src/org/qtproject/qt5/android/bindings/QtActivity.java \
    android/src/org/qtproject/qt5/android/bindings/QtApplication.java \
    android/version.xml \
    android/AndroidManifest.xml
