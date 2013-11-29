#ifndef CONNECT_H
#define CONNECT_H
#include <string>
#include <QTcpSocket>
#include "global.h"
#include "command/IMakeXml.h"
#include "command/CXMLInterface.h"
#include "command/command.h"

using namespace std;

class CConnect : public QObject
{
    Q_OBJECT
public:
    CConnect(QObject *parent = 0);
    CConnect(ServerNode server, QObject *parent = 0);
    ~CConnect();
    void setServer(ServerNode server);
    bool conct2Server();
    bool sendData(string strData);
    string parseData(string strData);
    inline int getStatus()
    {
        return m_status;
    }

    inline QString getError()
    {
        return m_error;
    }

private:
    QTcpSocket  *m_link;
    CONSTATUS   m_status;
    ServerNode  m_server;
    QString     m_data;
    int         m_blockSize;
    QString     m_error;

private slots:
    void readData();
    void linkConnected();
    void serverDisconnected();
    void displayError(QAbstractSocket::SocketError socketError);

signals:
    void dataIsReady(string date);
    void connectionFailedSignal();
    void disconnectedSignal();
    void connectedsuccessful();
};

#endif // CONNECT_H
