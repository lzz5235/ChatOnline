#ifndef CCLIENTSOCKET_H
#define CCLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>


class CClientSocket : public QObject
{
    Q_OBJECT
public:
    explicit CClientSocket(QObject *parent = 0);
        void SetSocket(int Descriptor);
    
signals:
        void senderSignal();
        void userLoginSignal();
        void deleteSignal();
    
public slots:
        void connected();
        void clientDisconnected();
        void receiveMessage();
        void sendMessage();
        void deleteSocket();
private:
        QTcpSocket *socket;
        int Description; // User ID
    
};

#endif // CCLIENTSOCKET_H
