#include "cserver.h"

CServer::CServer(QObject *parent) :
    QTcpServer(parent)
{

}

void CServer::changeStatu()
{

}

void CServer::StartServer(int PORT)
{
    if(listen(QHostAddress::Any,PORT ) )
    {
        qDebug()<< "Notification Start...........";

    }
    else
    {
        qDebug()<< "Notification Can't start......";
    }
}

void CServer::incomingConnection(int handle)
{
    CClientSocket *client = new CClientSocket(this);
    client->SetSocket(handle);
}
