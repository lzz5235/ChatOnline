#include <QDebug>
#include "cdatabase.h"

CDatabase::CDatabase(QObject *parent) :
    QObject(parent)
{
    if(false == init())
    {
        qDebug() << "Database start Fail!";
        return;
    }
    else
    {
        qDebug() << "Database start Success!";
    }
}

bool CDatabase::init()
{
    if (!QFile::exists(PATH))
    {
        qDebug() << "No Such Database File";
        //return false;
    }

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(PATH);

    if(!db.open())
    {
          qDebug()<< "Open Database File Error!";
          return false;
    }
    else
    {
        createTable();
        qDebug()<< "Create Tables If Not Exists";
    }
    return true;
}

qint32 CDatabase::loginRequest(const LoginInformation &logInf, QVector<FriendInformation> &friendsVec)
{
    QSqlQuery query;
    query.prepare("select * from user where account=:account");
    query.bindValue(":account", logInf.account);
    query.exec();
    errorSQLOrder(query, "loginRequest1");


    if(!query.next())
        return LOGIN_NO_ACCOUNT ;
    else if(query.value(PASSWORD).toString()!=logInf.password)
        return LOGIN_WRONG_PWD ;
    else if(query.value(STATUS) != OFFLINE)
    {
        qDebug()<<query.value(NICKNAME).toString();
        qDebug()<<query.value(ACCOUNT).toString();
        qDebug()<<query.value(PASSWORD).toString();
        qDebug()<<query.value(SEX).toString();
        qDebug()<<query.value(STATUS).toString();
        return HAVE_LOGINED;
    }
    else
    {
        //loginSuccess(query, logInf, friendsVec);
        login_AUTHOR_Request(query, logInf, friendsVec);
        return LOGIN_SUCCESS;
    }
}

qint32 CDatabase::login_AUTHOR_Request(QSqlQuery &query, const LoginInformation &logInf, QVector<FriendInformation> &friendsVec)
{
    friendsVec.clear();

    FriendInformation fri;
    fri.nickName = query.value(NICKNAME).toString();
    fri.account = logInf.account;
    fri.SEX = query.value(SEX).toString();
    fri.description = query.value(DESCRIPTION).toString();
    fri.mobileNumber = query.value(MOBILE_NUMBER).toString();
    fri.officephone = query.value(OFFICE_NUMBER).toString();
    fri.dormitory = query.value(DORMITORY).toString();
    fri.mail = query.value(MAIL).toString();
    fri.location = query.value(LOCATION).toString();
    fri.birthday = query.value(BIRTHDAY).toString();
    fri.status = logInf.status;
    fri.friendKind = MYSELF;
    fri.remark = query.value(DESCRIPTION).toString();
    fri.avatarunmber = query.value(AVATARNUMBER).toString();
    friendsVec.push_back(fri);

    query.prepare("update user set status=:sta where account=':acc' ");
    query.bindValue(":acc", logInf.account);
    query.bindValue(":sta", QString::number(logInf.status));
    query.exec();
    errorSQLOrder(query, "loginSuccess1");
}

qint32 CDatabase::registerRequest(const UserInformation &userInf)
{
    qint32 replyKind;
    QSqlQuery query;
    query.prepare("select count(account) from user where account=:account");
    query.bindValue(":account", userInf.account);
    query.exec();
    errorSQLOrder(query, "registerRequest1");
    query.next();
    if(query.value(0).toInt() != 0)
    {
        replyKind = REGISTER_EXIST;
        return replyKind;
    }

    query.prepare("insert into user values(NULL,:name,:acc,:pwd,:sex,:description,:status,:mobilephone,"
                  ":officephone,:dormitory,:mail,:location,:lastlogintime,"
                    ":registertime, :birthday,:avatarunmber)");
    query.bindValue(":name", userInf.nickName);
    query.bindValue(":acc", userInf.account);
    query.bindValue(":pwd", userInf.password);
    query.bindValue(":sex",userInf.sex);
    query.bindValue(":description", userInf.description);
    query.bindValue(":mobilephone", userInf.mobileNumber);
    query.bindValue(":officephone", userInf.officephone);
    query.bindValue(":dormitory", userInf.dormitory);
    query.bindValue(":mail", userInf.mail);
    query.bindValue(":location", userInf.location);
    query.bindValue(":lastlogintime", userInf.lastlogintime);
    query.bindValue(":registertime", userInf.registertime);
    query.bindValue(":birthday", userInf.birthday);
    query.bindValue(":avatarunmber", userInf.avatarunmber);


    query.exec();
    errorSQLOrder(query, "registerRequest2");
    replyKind = REGISTER_SUCCESS;
    return replyKind;
}

qint32 CDatabase::quitRequest(const QString &acc)
{
    QSqlQuery query;

    query.prepare("update user set status=0 where account=:acc");
    query.bindValue(":acc", acc);
    query.exec();
    errorSQLOrder(query, "quitRequest1");
    changeStatusRequest(acc, OFFLINE);
    return QUIT;
}

qint32 CDatabase::messageRequest(const Message &mes)
{
    addMessageRequest(mes);
    return 0;
}

qint32 CDatabase::addFriendRequest(const Message &mes)
{
    if(REQUEST_FRIEND == mes.kind)
        return requestFriend(mes);

    if(AGREE_FRIEND == mes.kind)
    {
        agreeFriend(mes);
        return GET_FRIEND_SUCCESS;
    }

    else if(DISAGREE_FRIEND == mes.kind)
    {
        disagreeFriend(mes);
        return DISAGREE_FRIEND;
    }
    return 0;
}

qint32 CDatabase::getFriendInf(const LoginInformation &logInf, QVector<FriendInformation> &friendsVec)
{
    QSqlQuery query;
    query.prepare("select * from user where account=:account");
    query.bindValue(":account", logInf.account);
    query.exec();
    errorSQLOrder(query, "loginRequest1");


    if(!query.next())
        return LOGIN_NO_ACCOUNT ;
    else if(query.value(PASSWORD).toString()!=logInf.password)
        return LOGIN_WRONG_PWD ;
    else if(query.value(STATUS) != OFFLINE)
    {
        qDebug()<<query.value(NICKNAME).toString();
        qDebug()<<query.value(ACCOUNT).toString();
        qDebug()<<query.value(PASSWORD).toString();
        qDebug()<<query.value(SEX).toString();
        qDebug()<<query.value(STATUS).toString();
        return HAVE_LOGINED;
    }
    else
    {
        loginSuccess(query, logInf, friendsVec);
        return LOGIN_SUCCESS;
    }
}

qint32 CDatabase::checkRequest(const QString &acc, QVector<Message> &messageVec)
{
    QSqlQuery query;
    Message mes;
    messageVec.clear();

    query.prepare("select * from tmp where tofriend=:rec");
    query.bindValue(":rec", acc);
    query.exec();
    errorSQLOrder(query, "checkRequest1");
    while(query.next())
    {
        mes.kind = query.value(KIND).toInt();
        mes.fromfriend = query.value(Fromfriend).toString();
        mes.fromfriendid = query.value(Fromfriendid).toInt();
        mes.tofriend = query.value(Tofriend).toString();
        mes.tofriendid = query.value(Tofriendid).toInt();
        mes.text = query.value(TEXT).toString();
        messageVec.push_back(mes);
    }
    if(messageVec.isEmpty())
        return NO_MESSAGE;


    query.prepare("delete from tmp where tofriend=:rec");
    query.bindValue(":rec", acc);
    query.exec();
    errorSQLOrder(query, "checkRequest2");
    return HAVE_MESSAGE;
}

qint32 CDatabase::getFriendInfRequest(const QString &acc, FriendInformation &fri)
{
    QSqlQuery query;
    query.prepare("select * from user where account=:acc");
    query.bindValue(":acc", acc);
    query.exec();
    errorSQLOrder(query, "getFriendRequest1");
    while(query.next())
    {
        fri.account = query.value(ACCOUNT).toString();
        fri.nickName = query.value(NICKNAME).toString();
        fri.SEX = query.value(SEX).toString();
        fri.description = query.value(DESCRIPTION).toString();
        fri.mobileNumber = query.value(MOBILE_NUMBER).toString();
        fri.officephone = query.value(OFFICE_NUMBER).toString();
        fri.dormitory = query.value(DORMITORY).toString();
        fri.mail = query.value(MAIL).toString();
        fri.location = query.value(LOCATION).toString();
        fri.birthday = query.value(BIRTHDAY).toString();
        fri.avatarunmber = query.value(AVATARNUMBER).toString();
        fri.status = query.value(STATUS).toInt();        
        fri.friendKind = VERIFYING;
        fri.remark.clear();
    }
    return GET_FRIEND_SUCCESS;
}

qint32 CDatabase::deleteFriendRequest(const QString &myAcc, const QString &peerAcc)
{
    QSqlQuery query;


    //这里要插入查询语句
    //select * from friend where id in (select id from user where account = "LZZ" )
    query.prepare("delete from friend where id in(select id from user where  accout = :one) and friendid in (select id from user where account = :two)");
    query.bindValue(":one", myAcc);
    query.bindValue(":two", peerAcc);
    query.exec();
    errorSQLOrder(query, "deleteFriendRequest1");

    query.prepare("delete from friend where id in(select id from user where  accout = :one) and friendid in (select id from user where account = :two)");
    query.bindValue(":one", peerAcc);
    query.bindValue(":two", myAcc);
    query.exec();
    errorSQLOrder(query, "deleteFriendRequest2");
    return DELETE_FRIEND_SUCCESS;
}
//struct UserInformation
//{
//    QString nickName;
//    QString account;
//    QString password;
//    QString sex;
//    QString description;
//    QString mobileNumber;
//    QString officephone;
//    QString dormitory;
//    QString mail;
//    QString location;
//    QString lastlogintime;
//    QString registertime;
//    QString birthday;
//    int status;

//};
qint32 CDatabase::getUserInfRequest(const QString &acc, UserInformation &userInf)
{
    QSqlQuery query;
    query.prepare("select * from user where account=:acc");
    query.bindValue(":acc", acc);
    query.exec();
    errorSQLOrder(query, "getUserInfRequest1");
    while(query.next())
    {
        userInf.nickName = query.value(NICKNAME).toString();
        userInf.account = query.value(ACCOUNT).toString();
        userInf.password = query.value(PASSWORD).toString();        
        userInf.sex = query.value(SEX).toString();
        userInf.description = query.value(DESCRIPTION).toString();
        userInf.mobileNumber = query.value(MOBILE_NUMBER).toString();
        userInf.officephone = query.value(OFFICE_NUMBER).toString();
        userInf.dormitory = query.value(DORMITORY).toString();
        userInf.mail = query.value(MAIL).toString();
        userInf.location = query.value(LOCATION).toString();
        userInf.birthday = query.value(BIRTHDAY).toString();
        userInf.avatarunmber = query.value(AVATARNUMBER).toString();
        userInf.status = query.value(STATUS).toInt();
    }
    return GET_USER_INF_SUCCESS;
}

qint32 CDatabase::changeInformationRequest(const UserInformation &userInf)
{
    QSqlQuery query;

    query.prepare("delete from user where account=:acc");
    query.bindValue(":acc", userInf.account);
    query.exec();
    errorSQLOrder(query, "changeInformationRequest1");
    query.prepare("insert into user values(NULL,:name,:acc,:pwd,:sex,:description,:status,:mobilephone,"
                  ":officephone,:dormitory,:mail,:location,:lastlogintime,"
                    ":registertime, :birthday,:avatarunmber )");
    query.bindValue(":name", userInf.nickName);
    query.bindValue(":acc", userInf.account);
    query.bindValue(":pwd", userInf.password);
    query.bindValue(":sex",userInf.sex);
    query.bindValue(":description", userInf.description);
    query.bindValue(":mobilephone", userInf.mobileNumber);
    query.bindValue(":officephone", userInf.officephone);
    query.bindValue(":dormitory", userInf.dormitory);
    query.bindValue(":mail", userInf.mail);
    query.bindValue(":location", userInf.location);
    query.bindValue(":lastlogintime", userInf.lastlogintime);
    query.bindValue(":registertime", userInf.registertime);
    query.bindValue(":birthday", userInf.birthday);
    query.bindValue(":avatarunmber", userInf.avatarunmber);
    query.exec();
    errorSQLOrder(query, "changeInformationRequest2");
    return CHANGE_INFORMATION_SUCCESS;
}

qint32 CDatabase::changeRemarkRequset(const Message &message)
{
    QSqlQuery query;

    query.prepare("update friend set friendname=:remark where id=:one and friendid=:two");
    query.bindValue(":one", message.fromfriendid);
    query.bindValue(":two", message.tofriendid);
    query.bindValue(":remark", message.tofriend);
    query.exec();
    errorSQLOrder(query, "changeRemarkRequset1");
    return CHANGE_REMARK_SUCCESS;
}

qint32 CDatabase::changePasswordRequest(const TempStrings &tempStr)
{
    QSqlQuery query;

    query.prepare("select * from user where account=:acc");
    query.bindValue(":acc", tempStr.account);
    query.exec();
    errorSQLOrder(query, "changePasswordRequest1");
    query.next();
    if(query.value(PASSWORD).toString() != tempStr.oldpwd)
        return OLD_PWD_IS_WRONG;

    query.prepare("update user set password=:pwd where account=:acc");
    query.bindValue(":pwd", tempStr.newpwd);
    query.bindValue(":acc", tempStr.account);
    query.exec();
    errorSQLOrder(query, "changePasswordRequest2");
    return CHANGE_PWD_SUCCESS;
}

qint32 CDatabase::changeStatusRequest(const QString &acc, qint32 status)
{
    QSqlQuery query;
    query.prepare("update user set status=:status where account=:acc");
    query.bindValue(":acc", acc);
    query.bindValue(":status", QString::number(status));
    query.exec();
    errorSQLOrder(query, "changeStatusRequest1");
    return 0;
}


void CDatabase::addMessageRequest(const Message &mes)
{
    QSqlQuery query;

    query.prepare("insert into tmp values(NULL,:fromfriend, :fromfriendid, :tofriend, :tofriendid, :message ,:messagetype)");
    query.bindValue(":fromfriend",mes.fromfriend);
    query.bindValue(":fromfriendid",mes.fromfriendid);
    query.bindValue(":tofriend",mes.tofriend);
    query.bindValue(":tofriendid",mes.tofriendid);
    query.bindValue(":message", mes.text);
    query.bindValue(":messagetype", QString::number(mes.kind));
    query.exec();
    errorSQLOrder(query, "addMessageRequest1");
}

void CDatabase::getFriendsAccount(const QString &acc, QVector<QString> &friVec)
{
    friVec.clear();
    QSqlQuery query;
    query.prepare("select account from user where id in(select friendid from friend where id in(select id from user where account=:acc))");
    query.bindValue(":acc", acc);
    query.exec();
    errorSQLOrder(query, "getFriendsAccount1");

    while(query.next())
    {
        if(query.value(2).toInt() != 0)
            friVec.push_back(query.value(1).toString());
    }
}

void CDatabase::createTable()
{
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS user("
                    "id  INTEGER PRIMARY KEY,"
                    "nickname  CHAR(18) NULL,"
                    "account  CHAR NULL,"
                    "password  CHAR(18) NULL,"
                    "sex CHAR(7) NULL,"
                    "description  LONG VARCHAR NULL,"
                    "status  INTEGER NULL,"
                    "mobilephone  INTEGER NULL,"
                    "officephone  INTEGER NULL,"
                    "dormitory  VARCHAR(20) NULL,"
                    "mail  VARCHAR(20) NULL,"
                    "location  VARCHAR(20) NULL,"
                    "lastlogintime  DATE NULL,"
                    "registertime  CHAR(18) NULL,"
                    "birthday  INTEGER NULL,"
                    "avatarunmber INTEGER NULL)");
    errorSQLOrder(query, "createTable1");

    query.exec("CREATE TABLE IF NOT EXISTS friend("
                    "id  INTEGER ,"
                    "friendname  VARCHAR(20) NULL,"
                    "friendid  INTEGER NULL)");
    errorSQLOrder(query, "createTable2");

    query.exec("CREATE TABLE IF NOT EXISTS tmp("
                    "id  INTEGER PRIMARY KEY,"
                    "fromfriend  VARCHAR(20) NULL,"
                    "fromfriendid  INTEGER NULL,"
                    "tofriend  VARCHAR(20) NULL,"
                    "tofriendid  INTEGER NULL,"
                    "message  VARCHAR(20) NULL,"
                    "messagetype  INTEGER NULL)");
    errorSQLOrder(query, "createTable3");
}


void CDatabase::errorSQLOrder(QSqlQuery query, QString mark)
{

    if(!query.isActive())
    {
        QString str = query.lastError().text() + "\n" + mark;
        qDebug() << str;
    }
}

//struct FriendInformation
//{
//    QString nickName;
//    QString account;
//    QString SEX;
//    QString description;
//    QString mobileNumber;
//    QString officephone;
//    QString dormitory;
//    QString mail;
//    QString location;
//    QString birthday;
//    int status;
//    int friendKind;
//    QString remark;
//};
void CDatabase::loginSuccess(QSqlQuery &query, const LoginInformation &logInf, QVector<FriendInformation> &friendsVec)
{
    friendsVec.clear();
    FriendInformation fri;

    query.prepare("select * from user where id in(select friendid from friend where id in(select id from user where account=:acc ))");
    query.bindValue(":acc", logInf.account);
    query.exec();
    errorSQLOrder(query, "loginSuccess2");


    while(query.next())
    {
        qDebug()<<query.value(NICKNAME).toString();
        qDebug()<<query.value(ACCOUNT).toString();
        qDebug()<<query.value(PASSWORD).toString();
        qDebug()<<query.value(SEX).toString();
        qDebug()<<query.value(STATUS).toString();

//        fri.friendKind = query.value(12).toInt();
//        if(0 == fri.friendKind)
//            continue;

        fri.nickName = query.value(NICKNAME).toString();
        fri.account = query.value(ACCOUNT).toString();
        fri.SEX = query.value(SEX).toString();
        fri.description = query.value(DESCRIPTION).toString();
        fri.mobileNumber = query.value(MOBILE_NUMBER).toString();
        fri.officephone = query.value(OFFICE_NUMBER).toString();
        fri.dormitory = query.value(DORMITORY).toString();
        fri.mail = query.value(MAIL).toString();
        fri.location = query.value(LOCATION).toString();
        fri.birthday = query.value(BIRTHDAY).toString();
        fri.avatarunmber = query.value(AVATARNUMBER).toString();
        fri.status = query.value(STATUS).toInt();
        friendsVec.push_back(fri);
    }
}

qint32 CDatabase::requestFriend(const Message &mes)
{
    QSqlQuery query;
    query.prepare("select count(account) from user where account=:account");
    query.bindValue(":account", mes.tofriend);
    query.exec();
    errorSQLOrder(query, "requestFriend1");
    query.next();
    if(0 == query.value(0).toInt())
        return FRIEDN_NO_ACCOUNT;

    query.prepare("select count() from friend where id=:one and friendid=:two");
    query.bindValue(":one", mes.fromfriendid);
    query.bindValue(":two", mes.tofriendid);
    query.exec();
    errorSQLOrder(query, "requestFriend2");
    query.next();
    if(0 != query.value(0).toInt())
        return ALREAD_FRIENDS;

    query.prepare("insert into friend values(:one,' ',:two )");
    query.bindValue(":one", mes.fromfriendid);
    query.bindValue(":two", mes.tofriendid);
    query.exec();
    errorSQLOrder(query, "requestFriend3");
    query.prepare("insert into friend values(:one,' ',:two )");
    query.bindValue(":one", mes.tofriendid);
    query.bindValue(":two", mes.fromfriendid);
    query.exec();
    errorSQLOrder(query, "requestFriend4");
    return FRIEND_REQUESTED;
}

void CDatabase::agreeFriend(const Message &mes)
{
    QSqlQuery query;

    query.prepare("update friend set friendname=:three where id=:one and firendid=:two");
    query.bindValue(":one", mes.fromfriendid);
    query.bindValue(":two", mes.tofriendid);
    query.bindValue(":thress",mes.tofriend);
    query.exec();
    errorSQLOrder(query, "agreeFriend1");
    query.prepare("update friend set friendname=:three where id=:one and firendid=:two");
    query.bindValue(":one", mes.tofriendid);
    query.bindValue(":two", mes.fromfriendid);
    query.bindValue(":thress",mes.fromfriend);
    query.exec();
    errorSQLOrder(query, "agreeFriend2");
}

void CDatabase::disagreeFriend(const Message &mes)
{
    QSqlQuery query;

    query.prepare("delete from friend where id=:one and friendid=:two");
    query.bindValue(":one", mes.fromfriend);
    query.bindValue(":two", mes.tofriendid);
    query.exec();
    errorSQLOrder(query, "disagreeFriend1");

    query.prepare("delete from friend where id=:one and friendid=:two");
    query.bindValue(":one", mes.tofriend);
    query.bindValue(":two", mes.fromfriend);
    query.exec();
    errorSQLOrder(query, "disagreeFriend2");
}
