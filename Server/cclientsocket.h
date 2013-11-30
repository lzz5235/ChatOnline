#ifndef CCLIENTSOCKET_H
#define CCLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QDataStream>
#include "protocol.h"
#include "xmlparse.h"


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
        bool sendData(QString strData);
        saveStruct save;
        int Description; // User ID
        qint16 blockSize;
        xmlparse Parse;
        QString m_data;

};

#endif // CCLIENTSOCKET_H
