#include "cclientsocket.h"


CClientSocket::CClientSocket(QObject *parent) :
    QTcpSocket(parent),
    blockSize(0)
{
    //QThreadPool::globalInstance()->setMaxThreadCount(20);
    Parse.initxmlparse();
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
    in.setVersion(QDataStream::Qt_5_0);

    if (blockSize == 0)
    {
        if (bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> blockSize;
    }
    if (bytesAvailable() < blockSize)
        return;
    in >>m_data;

    qDebug()<< blockSize;
    qDebug()<<m_data;

    //QByteArray buffer(blockSize, Qt::Uninitialized);

    //qDebug() << buffer.data();

    //in.readRawData(buffer.data(), blockSize);
    //QString string(buffer);

   // qDebug() << "xml is %s \n" << string;

    quint32 code = Parse.ReadXMLFromClient(m_data);

    if(LOGIN == code)
    {
        Parse.Read_Login_XmlFile(m_data,save);
        save.requestKind = LOGIN;
        save.myAccount = save.logInf.account;
    }
    else if(CHANGE_INFORMATION == code)
    {
        Parse.Read_TRANS_UPDATE_XmlFile(m_data,save);
        save.requestKind = CHANGE_INFORMATION;
    }
    else if (HAVE_MESSAGE ==code)
    {
        Parse.Read_TRANS_SEND_XmlFile(m_data,save);
        save.requestKind = TALK;
    }
    else if(GET_FRIEND_INFORMATION == code)
    {
        Parse.Read_TRANS_GET_ADDRESS_XmlFile(m_data,save);
        save.requestKind = GET_FRIEND_INFORMATION;
    }
    else if(GET_USER_INFORMATION ==code)
    {
        Parse.Read_TRANS_GET_ADDRESS_XmlFile(m_data,save);
        save.requestKind = GET_USER_INFORMATION;
        save.myAccount = save.logInf.account;
//        save.peerAccount = save.logInf.account;
    }
    else if(CHECK_CONNECTION ==code)
    {
        save.requestKind = CHECK_CONNECTION;
    }
    else
    {
        Parse.Read_TRANS_LOGOUT_XmlFile(m_data,save);
        save.replyKind = QUIT;
        save.myAccount = save.logInf.account;
    }


    blockSize = 0;
    emit sendSignal(save);
}

bool CClientSocket::sendMessage(saveStruct &temp)
{
    QString data;
    bool flag = false;

    if(LOGIN_SUCCESS == temp.replyKind)
    {
        //Parse.Create_TRANS_ADDRESS_XmlFile(data,temp);
        Parse.Create_TRANS_LOGIN_BACK_XmlFile(data,temp);
        qDebug()<<data;
        flag = sendData(data);
    }
    else if(TALK == temp.replyKind)
    {
        Parse.Create_TRANS_SEND_XmlFile(data,temp);
        qDebug() << data;
        flag = sendData(data);
    }
    else if(QUIT == temp.replyKind)
    {
        Parse.Create_RESULT_XmlFile(data);
        flag = sendData(data);
    }
    else if(GET_FRIEND_INFORMATION == temp.replyKind)
    {
        Parse.Create_TRANS_ADDRESS_XmlFile(data,temp);
        qDebug()<<data;
        flag = sendData(data);
    }
    else if(GET_USER_INFORMATION == temp.replyKind)
    {
        Parse.Create_TRANS_USER_ADDRESS_XmlFile(data,temp);
        qDebug()<<data;
        flag = sendData(data);
    }
    else if(CHANGE_INFORMATION == temp.replyKind)
    {
        Parse.Create_TRANS_UPDATE_XmlFile(data,temp);
        flag = sendData(data);
    }
    else if(CHECK_CONNECTION == temp.replyKind)
    {
        flag =  sendResult("Result");
    }
    else if(CHANGE_STATUE == temp.replyKind)
    {
        Parse.Create_LOGINEDINFO_XmlFile(data,temp);
        flag = sendData(data);
    }
    data.clear();
    return flag;
}

void CClientSocket::deleteSocket()
{
    emit deleteSignal(save);
    deleteLater();
}

bool CClientSocket::sendData(QString strData)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);

    out << (qint16)0;
    out << QString(strData.toStdString().c_str());

    out.device()->seek(0);

    out << (qint16)(block.size() - sizeof(qint16));
    qDebug()<<(qint16)(block.size() - sizeof(qint16));
    int sended = write(block);
    if(sended == block.size())
        return true;
    else
        return false;
}

bool CClientSocket::sendResult(QString strData)
{
    QString data;
    Parse.Create_RESULT_XmlFile(data);
    qDebug() << "Result :"<<data;
    qDebug()<<sendData(data);
    data.clear();
}
