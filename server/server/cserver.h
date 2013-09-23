#ifndef CSERVER_H
#define CSERVER_H

#include <QTcpServer>
#include <QAbstractSocket>

class CServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit CServer(QObject *parent = 0);
    void changeStatu();
    void StartServer();
    
signals:
    
public slots:

protected:
        void incomingConnection(int handle);
    
};

#endif // CSERVER_H
