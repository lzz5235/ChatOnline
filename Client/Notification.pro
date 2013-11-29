# -------------------------------------------------
# Project created by QtCreator 2013-09-22T17:24:30
# -------------------------------------------------
QT += network \
    sql \
    xml \
    widgets \
    gui \
    declarative
TARGET = Notification
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    xml/tinyxmlparser.cpp \
    xml/tinyxmlerror.cpp \
    xml/tinyxml.cpp \
    xml/tinystr.cpp \
    xml/SimpleXml.cpp \
    xml/EasyXml.cpp \
    utilities/FuncTools.cpp \
    clogin.cpp \
    command/command.cpp \
    csettingdlg.cpp \
    cgv.cpp \
    cmaindlg.cpp \
    talkdlg.cpp \
    command/XMLBuild.cpp \
    connect/connect.cpp
HEADERS += mainwindow.h \
    connect/connect.h \
    xml/McuMakeXMLInterface.h \
    xml/global_Param.h \
    xml/tinyxml.h \
    xml/tinystr.h \
    xml/SimpleXml.h \
    xml/EasyXml.h \
    utilities/FuncTools.h \
    clogin.h \
    global.h \
    command/command.h \
    csettingdlg.h \
    command/IMakeXml.h \
    command/data.h \
    cgv.h \
    extern.h \
    cmaindlg.h \
    talkdlg.h \
    command/CXMLInterface.h \
    command/XMLBuild.h \
    structure.h \
    xml/rscCMD.h
FORMS += \
    clogin.ui \
    csettingdlg.ui \
    cmaindlg.ui \
    ctalkdlg.ui

RESOURCES += \
    res.qrc























