#ifndef CDATABASE_H
#define CDATABASE_H

#include <QObject>
#include <QtSql>
#include "protocol.h"

#define PATH "/home/lzz/Notification.db"
//#define PATH "/Users/PJW/Desktop/Notification.db"


class CDatabase : public QObject
{
    Q_OBJECT
public:
    explicit CDatabase(QObject *parent = 0);
    bool init();//

    qint32 loginRequest(const LoginInformation &logInf,//
        QVector<FriendInformation> &friendsVec);
    qint32 registerRequest(const UserInformation &userInf);
    qint32 quitRequest(const QString &acc);
    qint32 messageRequest(const Message &mes);
    qint32 addFriendRequest(const Message &mes);
    qint32 checkRequest(const QString &acc, QVector<Message> &messageVec);
    qint32 getFriendInfRequest(const QString &acc, FriendInformation &fri);
    qint32 deleteFriendRequest(const QString &myAcc, const QString &peerAcc);
    qint32 getUserInfRequest(const QString &acc, UserInformation &userInf);
    qint32 changeInformationRequest(const UserInformation &userInf);
    qint32 changeRemarkRequset(const Message &message);
    qint32 changePasswordRequest(const TempStrings &tempStr);
    qint32 changeStatusRequest(const QString &acc, qint32 status);
    qint32 getAllInformationRequest(const QString &acc, QVector<FriendInformation>
        &friendsVec, QVector<Message> &messageVec);
    void addMessageRequest(const Message &mes);
    void getFriendsAccount(const QString &acc, QVector<QString> &friVec);
    
signals:
    
public slots:

private:
    QSqlDatabase db;
    QSqlQuery query;


    void errorSQLOrder(QSqlQuery query, QString mark);
    void loginSuccess(QSqlQuery &query, const LoginInformation &logInf,
        QVector<FriendInformation> &friendsVec);
    qint32 requestFriend(const Message &mes);
    void agreeFriend(const Message &mes);
    void disagreeFriend(const Message &mes);
    void createTable();
};

#endif // CDATABASE_H
