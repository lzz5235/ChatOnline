#include <QApplication.h>
#include "mainwindow.h"
#include "clogin.h"
#include "csettingdlg.h"
#include <QFileInfo>
#include <QString>
#include <QSettings>
#include <QDir>
#include "command/IMakeXml.h"
#include "connect/connect.h"
#include <QTextCodec>

void preInit()
{

}

int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8"); //获取系统编码
    QTextCodec::setCodecForLocale(codec);

    QApplication a(argc, argv);
    preInit();
    IMakeXml *xml = new CCommand(VERSION_2);
    CConnect *link = new CConnect();
    CLogin login(link, xml);
    login.show();
    return a.exec();
}
