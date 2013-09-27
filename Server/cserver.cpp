#include "cserver.h"

CServer::CServer(QObject *parent) :
    QTcpServer(parent)
{
    data.init();
}

CServer::~CServer()
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

void CServer::disconnect(QString &account)
{
    ClientSocketMap.remove(account);
}

void CServer::sendMessage(saveStruct &saveinfo)
{

}

void CServer::incomingConnection(int handle)
{
    CClientSocket *client = new CClientSocket();
    //client->SetSocket(handle);
    client->SetSocket(handle);

    connect(client,SIGNAL(sendSignal(saveStruct&)),this,SLOT(sendMessage(saveStruct&)));
    connect(client,SIGNAL(deleteSignal(QString&)),this,SLOT(disconnect(QString&)));
}
