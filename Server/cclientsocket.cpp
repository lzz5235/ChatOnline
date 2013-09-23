#include "cclientsocket.h"

CClientSocket::CClientSocket(QObject *parent) :
    QObject(parent)
{

}

void CClientSocket::SetSocket(int Descriptor)
{
    socket = new QTcpSocket(this);

    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(clientDisconnected()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(receiveMessage()));

    socket->setSocketDescriptor(Descriptor);
    Description  = Descriptor;
    qDebug() << Description <<"client connected event";
}
void CClientSocket::connected()
{
    qDebug() << Description <<"client connected event";
}
void CClientSocket::clientDisconnected()
{
    qDebug() << Description <<"client disconnected event";
}
void CClientSocket::receiveMessage()
{
    qDebug() << socket->readAll() ;

    //MyTask *mytask = new MyTask();
    //mytask->setAutoDelete(true);
    //connect(mytask,SIGNAL(Result(int)),this,SLOT(TaskResult(int)),Qt::QueuedConnection );
    //connect(mytask,SIGNAL(Result(int)),this,SLOT(TaskResult(int)));
    //QThreadPool::globalInstance()->start(mytask);
}

void CClientSocket::sendMessage()
{

}

void CClientSocket::deleteSocket()
{

}
