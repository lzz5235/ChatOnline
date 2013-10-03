#include "cclientsocket.h"


CClientSocket::CClientSocket(QObject *parent) :
    QTcpSocket(parent)
{
    save.clientSocket = this;
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
    QDataStream in(this);
    xmlparse Parse;
    in.setVersion(QDataStream::Qt_4_8);

    //
    if (blockSize == 0)
    {
        if (bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> blockSize;
    }
    if (bytesAvailable() < blockSize)
        return;
    QByteArray buffer(blockSize, Qt::Uninitialized);

    in.readRawData(buffer.data(), blockSize);
    QString string(buffer);

    quint32 code = Parse.ReadXMLFromClient(string);


    if(CHECK_CONNECTION == save.requestKind)
    {
        save.replyKind = CHECK_CONNECTION;
        sendMessage(save);
        blockSize = 0;
        return;
    }
    else if(LOGIN == code)
    {
        //problem
        save.myAccount = save.logInf.account;
    }
    else if(CHECK_MESSAGE == save.requestKind)
        in >> save.myAccount;
    else if(REGISTER == save.requestKind)
        in >> save.userInf;
    else if(TALK == save.requestKind)
        in >> save.message;
    else if(ADD_FRIEND == save.requestKind)
        in >> save.message;
    else if(GET_FRIEND_INFORMATION == save.requestKind)
        in >> save.peerAccount;
    else if(DISAGREE_FRIEND == save.requestKind)
        in >> save.peerAccount;
    else if(GET_USER_INFORMATION == save.requestKind)
        in >> save.peerAccount;
    else if(CHANGE_PASSWORD == save.requestKind)
        in >> save.tempStr;
    else if(CHANGE_INFORMATION == save.requestKind)
        in >> save.userInf;
    else if(DELETE_FRIEND == save.requestKind)
        in >> save.peerAccount;
    else if(CHANGE_REMARK == save.requestKind)
        in >> save.message;
    else if(CHANGE_STATUE == save.requestKind)
        in >> save.status;

    blockSize = 0;
    emit sendSignal(save);
}

void CClientSocket::sendMessage(saveStruct &temper)
{

}

void CClientSocket::deleteSocket()
{
    if(!save.myAccount.isEmpty())
        emit deleteSignal(save.myAccount);
    deleteLater();
}
