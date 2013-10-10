#include "cserver.h"

CServer::CServer(QObject *parent) :
    QTcpServer(parent)
{
    data.init();
}

CServer::~CServer()
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

void CServer::friendRequest(const saveStruct &save)
{
    temp.message = save.message;
    temp.replyKind = data.addFriendRequest(temp.message);

    if(REQUEST_FRIEND == temp.message.kind)
        save.clientSocket->sendMessage(temp);
    else if(AGREE_FRIEND == temp.message.kind)
    {
        data.getFriendInfRequest(temp.message.tofriend, temp.theFriend);
        temp.replyKind = GET_FRIEND_SUCCESS;
        save.clientSocket->sendMessage(temp);
    }

    QMap<QString, CClientSocket*>::iterator iter;
    iter = ClientSocketMap.find(temp.message.tofriend);

    if(ClientSocketMap.end() == iter)
        data.addMessageRequest(temp.message);
    else
    {
        temp.replyKind = ADD_FRIEND;
        iter.value()->sendMessage(temp);
    }
}

void CServer::disconnect(QString &account)
{

    ClientSocketMap.remove(account);
    data.quitRequest(account);
}

void CServer::sendMessage(saveStruct &save)
{
    temp.requestKind = save.requestKind;

    if(LOGIN == temp.requestKind)
    {
        temp.logInf = save.logInf;
        temp.clientSocket = save.clientSocket;
        temp.replyKind = data.loginRequest(temp.logInf, temp.friendsVec);
        QMap<QString, CClientSocket*>::iterator iter;
        save.clientSocket->sendMessage(temp);
        if(LOGIN_SUCCESS == temp.replyKind)
            changeStatu(temp.logInf.account, temp.logInf.status);
    }
    else if(QUIT ==temp.requestKind)
    {
        temp.logInf = save.logInf;
        temp.clientSocket = save.clientSocket;
        temp.replyKind = data.quitRequest(temp.logInf.account);
        save.clientSocket->sendMessage(temp);
        if(0 == temp.replyKind)
            changeStatu(temp.logInf.account, temp.logInf.status);
    }
    else if(GET_FRIEND_INFORMATION == temp.requestKind)
    {
        temp.peerAccount = save.peerAccount;
        temp.clientSocket = save.clientSocket;
        data.loginRequest(temp.logInf, temp.friendsVec);
        temp.replyKind = GET_FRIEND_INFORMATION;
        save.clientSocket->sendMessage(temp);
    }
    else if(GET_USER_INFORMATION == temp.requestKind)
    {
        temp.peerAccount = save.peerAccount;
        temp.clientSocket = save.clientSocket;
        temp.replyKind = data.getUserInfRequest(temp.peerAccount, temp.userInf);
        save.clientSocket->sendMessage(temp);
    }
//    else if(REGISTER == temp.requestKind)
//    {
//        temp.userInf = save.userInf;
//        temp.replyKind = data.registerRequest(temp.userInf);
//        QMap<QString, CClientSocket*>::iterator iter;
//        save.clientSocket->sendMessage(temp);
//    }

//    else if(CHECK_MESSAGE == temp.requestKind)
//    {
//        temp.myAccount = save.myAccount;
//        temp.replyKind = data.checkRequest(temp.myAccount, temp.messageVec);
//        temp.clientSocket = save.clientSocket;
//        ClientSocketMap.insert(temp.myAccount, temp.clientSocket);
//        save.clientSocket->sendMessage(temp);
//    }
//    else if(TALK == temp.requestKind)
//    {
//        temp.message = save.message;
//        if(TALK_MESSAGE == temp.message.kind)
//        {
//            temp.replyKind = TALK;
//            QMap<QString, CClientSocket*>::iterator iter;
//            iter = ClientSocketMap.find(temp.message.tofriend);
//            if(ClientSocketMap.end() == iter)
//                data.messageRequest(save.message);
//            else
//                iter.value()->sendMessage(temp);
//        }
//    }
//    else if(CHANGE_PASSWORD == temp.requestKind)
//    {
//        temp.tempStr = save.tempStr;
//        temp.replyKind = data.changePasswordRequest(temp.tempStr);
//        save.clientSocket->sendMessage(temp);
//    }


//    else if(CHANGE_INFORMATION == temp.requestKind)
//    {
//        temp.userInf = save.userInf;
//        temp.replyKind = data.changeInformationRequest(temp.userInf);
//        save.clientSocket->sendMessage(temp);
//    }
//    else if(DELETE_FRIEND == temp.requestKind)
//    {
//        temp.peerAccount = save.peerAccount;
//        temp.myAccount = save.myAccount;
//        temp.replyKind = data.deleteFriendRequest(
//            temp.myAccount, temp.peerAccount);
//        save.clientSocket->sendMessage(temp);

//        QMap<QString, CClientSocket*>::iterator iter;
//        iter = ClientSocketMap.find(temp.peerAccount);
//        if(ClientSocketMap.end() == iter)
//        {
//            Message mes;
//            mes.kind = BE_DELETED;
//            mes.fromfriend = temp.myAccount;
//            mes.tofriend = temp.peerAccount;
//            data.messageRequest(mes);
//        }
//        else
//        {
//            temp.replyKind = BE_DELETED;
//            temp.myAccount = temp.myAccount;
//            iter.value()->sendMessage(temp);
//        }

//    }
//    else if(CHANGE_REMARK == temp.requestKind)
//    {
//        temp.message = save.message;
//        temp.replyKind = data.changeRemarkRequset(temp.message);
//        save.clientSocket->sendMessage(temp);
//    }
//    else if(ADD_FRIEND == temp.requestKind)
//        friendRequest(save);
//    else if(CHANGE_STATUE == temp.requestKind)
//        changeStatu(save.myAccount, save.status);
}

void CServer::incomingConnection(int handle)
{
    CClientSocket *client = new CClientSocket();
    //client->SetSocket(handle);
    client->SetSocket(handle);

    connect(client,SIGNAL(sendSignal(saveStruct&)),this,SLOT(sendMessage(saveStruct&)));
    connect(client,SIGNAL(deleteSignal(QString&)),this,SLOT(disconnect(QString&)));
}


void CServer::changeStatu(const QString &acc, qint32 status)
{
    temp.replyKind = CHANGE_STATUE;
    temp.status = status;
    temp.peerAccount = acc;
    data.changeStatusRequest(acc, temp.status);
    data.getFriendsAccount(acc, temp.accountVec);

    QMap<QString, CClientSocket*>::iterator iter;
    for(int i=0;i<temp.accountVec.size();i++)
    {
        iter = ClientSocketMap.find(temp.accountVec[i]);
        if(iter != ClientSocketMap.end())
            iter.value()->sendMessage(temp);
    }
}
