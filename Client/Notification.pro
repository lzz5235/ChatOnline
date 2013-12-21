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
    command/XMLBuild.cpp \
    connect/connect.cpp \
    frienditem.cpp \
    cchatroom.cpp \
    caboutdlg.cpp \
    cprivateinfo.cpp \
    cfrienddlg.cpp
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
    command/CXMLInterface.h \
    command/XMLBuild.h \
    structure.h \
    xml/rscCMD.h \
    frienditem.h \
    cchatroom.h \
    caboutdlg.h \
    cprivateinfo.h \
    cfrienddlg.h
FORMS += \
    clogin.ui \
    csettingdlg.ui \
    cmaindlg.ui \
    cchatroom.ui \
    caboutdlg.ui \
    cprivateinfo.ui \
    cfrienddlg.ui

RESOURCES += \
    res.qrc

OTHER_FILES +=























