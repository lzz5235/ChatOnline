#include "cdatabase.h"

CDatabase::CDatabase(QObject *parent) :
    QObject(parent)
{
    if(false == init())
    {
        qDebug() << "Database start Fail!";
        return;
    }
    else
    {
        qDebug() << "Database start Success!";
    }

}

bool CDatabase::init()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/lzz/test.db");

    if(!db.open())
    {
          qDebug()<< "错误","无法打开数据库！";
          return false;
    }
    return true;
}
