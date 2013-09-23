#ifndef CSERVER_H
#define CSERVER_H

#include <QTcpServer>
#include <QAbstractSocket>
#include "cclientsocket.h"
#include "cdatabase.h"


class CServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit CServer(QObject *parent = 0);
    void changeStatu();
    void StartServer(int PORT);
    
signals:
    
public slots:

protected:
        void incomingConnection(int handle);

private:
    
};

#endif // CSERVER_H
