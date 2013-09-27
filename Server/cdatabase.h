#ifndef CDATABASE_H
#define CDATABASE_H

#include <QObject>
#include <QtSql>
#include <QDebug>


#define PATH "/home/lzz/Notification.db"


class CDatabase : public QObject
{
    Q_OBJECT
public:
    explicit CDatabase(QObject *parent = 0);
    bool init();
    int loginRequest();
    int registerRequest();
    int quitRequest();
    int messageRequest();
    int changeStausRequest();
    int getAllInformationRequest();
    int addMessageRequest();
    int getFriendsAccount();
    bool loginSuccess();
    
signals:
    
public slots:

private:
    QSqlDatabase db;
    QSqlQuery query;


    void createTable();
};

#endif // CDATABASE_H
