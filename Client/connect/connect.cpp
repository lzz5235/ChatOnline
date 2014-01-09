#include "connect/connect.h"
#include <QMessageBox>
#include <stdlib.h>

CConnect::CConnect(QObject *parent)
    : QObject(parent),
      m_status(IDLE),
      m_data(QString("")),
      m_blockSize(0),
      m_link(new QTcpSocket(this)),
      m_error("")
{
    connect(m_link, SIGNAL(connected()), this, SLOT(linkConnected()) );
    connect(m_link, SIGNAL(readyRead()), this, SLOT(readData()) );
    connect(m_link, SIGNAL(disconnected()),
        this, SLOT(ServerDisconnected()));
    connect(m_link, SIGNAL(error(QAbstractSocket::SocketError)),
        this, SLOT(displayError(QAbstractSocket::SocketError)));
}

CConnect::CConnect(ServerNode server, QObject *parent)
    :QObject(parent),
     m_status(IDLE),
     m_server(server),
     m_data(QString("")),
     m_blockSize(0),
     m_link(new QTcpSocket(this)),
     m_error("")
{
    connect(m_link, SIGNAL(connected()), this, SLOT(linkConnected()) );
    connect(m_link, SIGNAL(readyRead()), this, SLOT(readResult()) );
    connect(m_link, SIGNAL(disconnected()),
        this, SLOT(ServerDisconnected()));
    connect(m_link, SIGNAL(error(QAbstractSocket::SocketError)),
        this, SLOT(displayError(QAbstractSocket::SocketError)));
}

CConnect::~CConnect()
{

}

void CConnect::setServer(ServerNode server)
{
    m_server = server;
}

bool CConnect::conct2Server()
{
    if(m_status == CLOSED || m_status == IDLE)
    {
        m_link->abort();
        qDebug() << "abort link" << endl;
        QString qstrIP = QString(m_server.Ip.c_str());
        qint16 port = std::atoi(m_server.Port.c_str());
        m_link->connectToHost(qstrIP, port);
    }
    return true;
}

bool CConnect::sendData(string strData)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);

    out << (qint16)0;
    out << QString::fromStdString(strData);

    out.device()->seek(0);
    out << (qint16)(block.size() - sizeof(qint16));
    int sended = m_link->write(block);
    qDebug() << "size is " << sended << "send data is " << block << endl;
    if(sended == block.size())
        return true;
    else
        return false;
}

string CConnect::parseData(string strData)
{

}

void CConnect::readData()
{
    QDataStream in(m_link);
    in.setVersion(QDataStream::Qt_4_8);

    if (m_blockSize == 0)
    {
        if (m_link->bytesAvailable() < (int)sizeof(qint16))
            return;
        in >> m_blockSize;
        qDebug() << "out message is " << m_blockSize << endl;
    }

    if (m_link->bytesAvailable() < m_blockSize)
    {
        m_blockSize = 0;
        return;
    }

    in >> m_data;
    m_blockSize = 0;
    qDebug() << "out message is " << m_data << endl;
    emit dataIsReady(m_data.toStdString());
}

void CConnect::linkConnected()
{
    if(m_status == CLOSED || m_status == IDLE || m_status == CONNECTING)
    {
        m_status = CONNECTED;
        emit connectedsuccessful();
    }
}

void CConnect::ServerDisconnected()
{
    emit disconnectedSignal();
}

void CConnect::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
    case QAbstractSocket::RemoteHostClosedError:
    {
        m_error = "RemoteHostClosedError";
        break;
    }
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(NULL, ("Client"),
            ("The host was not found. Please check the "
            "host name and port settings."));
        emit connectionFailedSignal();
        m_error = "HostNotFoundError";
        break;
    case QAbstractSocket::ConnectionRefusedError:

        QMessageBox::information(NULL, ("Client"),
            ("The connection was refused by the peer. "
            "Make sure the fortune server is running, "
            "and check that the host name and port "
            "settings are correct."));
        emit connectionFailedSignal();
        m_error = "ConnectionRefusedError";
        break;
    default:
        QMessageBox::information(NULL, ("Client"),
            ("For unknown reasons, connected failed"));
        m_error = "donot know!";
        emit connectionFailedSignal();
    }
}
