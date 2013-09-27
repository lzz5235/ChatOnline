#include "cclientsocket.h"

CClientSocket::CClientSocket(QObject *parent) :
    QTcpSocket(parent)
{
    saveinfo.clientSocket = this;
    connect(this,SIGNAL(connected()),this,SLOT(clientConnected()));
    connect(this,SIGNAL(readyRead()),this,SLOT(receiveMessage()));
    connect(this,SIGNAL(disconnected()),this,SLOT(clientDisconnected()));
    connect(this,SIGNAL(disconnected()),this,SLOT(deleteSocket()));
}

void CClientSocket::SetSocket(int Descriptor)
{
    this->setSocketDescriptor(Descriptor);
    Description  = Descriptor;
    qDebug() << Description <<"client connected event";
}
void CClientSocket::clientConnected()
{
    qDebug() << Description <<"client connected event";
}
void CClientSocket::clientDisconnected()
{
    //delete socket;
    qDebug() << Description <<"client disconnected event";
}

void CClientSocket::receiveMessage()
{

}

void CClientSocket::sendMessage(saveStruct &temper)
{

}

void CClientSocket::deleteSocket()
{

}
