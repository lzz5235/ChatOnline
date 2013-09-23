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
    cclientsocket.cpp

HEADERS  += mainwindow.h \
    cserver.h \
    cdatabase.h \
    cclientsocket.h

FORMS    += mainwindow.ui
