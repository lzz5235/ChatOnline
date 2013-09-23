#ifndef CCLIENTSOCKET_H
#define CCLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThreadPool>

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
        void disconnected();
        void readyRead();
    
};

#endif // CCLIENTSOCKET_H
