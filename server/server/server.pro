#-------------------------------------------------
#
# Project created by QtCreator 2013-09-23T11:13:07
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    cserver.cpp \
    cclientsocket.cpp

HEADERS += \
    cserver.h \
    cclientsocket.h
