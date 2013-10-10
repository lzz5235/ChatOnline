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
    in.setVersion(QDataStream::Qt_4_8);

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

    if(LOGIN == code)
    {
        Parse.Read_Login_XmlFile(string,save);
        save.requestKind = LOGIN;
        save.myAccount = save.logInf.account;
    }
    else if(CHANGE_INFORMATION == code)
    {

    }
    else if (HAVE_MESSAGE ==code)
    {
        //Parse.Read_TRANS_SEND_XmlFile(string,save);
    }
    else if(GET_FRIEND_INFORMATION == code)
    {
        Parse.Read_TRANS_GET_ADDRESS_XmlFile(string,save);
        save.requestKind = GET_FRIEND_INFORMATION;
    }
    else if(GET_USER_INFORMATION ==code)
    {
        Parse.Read_TRANS_GET_ADDRESS_XmlFile(string,save);
        save.requestKind = GET_USER_INFORMATION;
        save.myAccount = save.logInf.account;
        save.peerAccount = save.logInf.account;
    }
    else if(CHECK_CONNECTION ==code)
    {

    }
    else
    {
        Parse.Read_TRANS_LOGOUT_XmlFile(string,save);
        save.replyKind = QUIT;
        save.myAccount = save.logInf.account;
    }


    blockSize = 0;
    emit sendSignal(save);
}

void CClientSocket::sendMessage(saveStruct &temp)
{
    QString data;
    if(LOGIN_SUCCESS == temp.replyKind)
    {
        Parse.Create_RESULT_XmlFile(data);
        write(data.toAscii());
        data.clear();
        Parse.Create_TRANS_ADDRESS_XmlFile(data,temp);
        write(data.toAscii());
    }
    else if(QUIT == temp.replyKind)
    {
        Parse.Create_RESULT_XmlFile(data);
        write(data.toAscii());
    }
    else if(GET_FRIEND_INFORMATION == temp.replyKind)
    {
        Parse.Create_TRANS_ADDRESS_XmlFile(data,temp);
        write(data.toAscii());
    }
    else if(GET_USER_INFORMATION == temp.replyKind)
    {
        Parse.Create_TRANS_ADDRESS_XmlFile(data,temp);
        write(data.toAscii());
    }
    data.clear();
}

void CClientSocket::deleteSocket()
{
    if(!save.myAccount.isEmpty())
        emit deleteSignal(save.myAccount);
    deleteLater();
}
