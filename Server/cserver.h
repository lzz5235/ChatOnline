#ifndef CSERVER_H
#define CSERVER_H

#include <QTcpServer>
#include <QAbstractSocket>
#include <QMap>

#include "cclientsocket.h"
#include "cdatabase.h"
#include "protocol.h"

class CServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit CServer(QObject *parent = 0);
    ~CServer();

    void changeStatu();
    void StartServer(int PORT);    
    
signals:
    
public slots:
    void disconnect(QString &account);
    void sendMessage(saveStruct &saveinfo);

protected:
        void incomingConnection(int handle);
private:
    QMap<QString,CClientSocket *> ClientSocketMap;
    int description; //socket fd

    CDatabase data;
    saveStruct temp;
};

#endif // CSERVER_H
