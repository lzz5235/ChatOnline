#ifndef CCLIENTSOCKET_H
#define CCLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include "protocol.h"


class CClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit CClientSocket(QObject *parent = 0);
    void SetSocket(int Descriptor);

signals:
        void sendSignal(saveStruct &temper);
        void userLoginSignal(UserInformation &userinfo);
        void deleteSignal(QString &account);
    
public slots:
        void clientConnected();
        void clientDisconnected();
        void receiveMessage();
        void sendMessage(saveStruct &temper);
        void deleteSocket();
private:
    saveStruct saveinfo;
    int Description; // User ID

};

#endif // CCLIENTSOCKET_H
