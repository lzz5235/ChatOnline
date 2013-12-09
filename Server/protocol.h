#ifndef PROTOCOL_H
#define PROTOCOL_H


#include <QString>
#include <QVector>

class CServer;
class CClientSocket;

/**************************************************************
    以下是服务端用到的所有数据结构，包括
    用户信息
    密码修改信息
    好友信息（这个好友可能一期是不需要的）
    用户登录信息
    用户请求类型
    以及部分数据库中字段
***************************************************************/
struct UserInformation
{
    QString nickName;
    QString account;
    QString password;
    QString sex;
    QString description;
    QString mobileNumber;
    QString officephone;
    QString dormitory;
    QString mail;
    QString location;
    QString lastlogintime;
    QString registertime;
    QString birthday;
    int status;

};

enum
{
	ID = 0,
	NICKNAME = 1,
	ACCOUNT = 2,
	PASSWORD = 3,
	SEX = 4,
	DESCRIPTION = 5,
	STATUS = 6,
	MOBILE_NUMBER = 7,
	OFFICE_NUMBER = 8,
	DORMITORY = 9,
	MAIL = 10,
	LOCATION = 11,
	LASTLOGINTIME = 12,
	REGISTERTIME  = 13,
	BIRTHDAY = 14
};

struct FriendInformation
{
    QString nickName;
    QString account;
    QString SEX;
    QString description;
    QString mobileNumber;
    QString officephone;
    QString dormitory;
    QString mail;
    QString location;
    QString birthday;
    int status;
    int friendKind;
    QString remark;
};

struct TempStrings
{
        QString oldpwd;
        QString newpwd;
        QString account;
};


struct LoginInformation
{
        QString account;
        QString password;
        int status;
};


struct Message
{
    int kind;
    int fromfriendid;
    int tofriendid;
    QString BROADCAST;
    QString fromfriend;
    QString tofriend;
    QString text;
    QString DateRec;
    QString DateSend;
};

struct saveStruct
{
        qint32 requestKind;
        qint32 replyKind;
        CClientSocket *clientSocket;

        QString myAccount;
        QString peerAccount;
        UserInformation userInf;
        LoginInformation logInf;
        FriendInformation theFriend;
        Message message;
        qint32 status;

        TempStrings tempStr;
        QVector<Message> messageVec;
        QVector<FriendInformation> friendsVec;
        QVector<QString> accountVec;

};


enum
{
    LOGIN = 1,
    REGISTER = 2,
    TALK = 3,
    CHECK_MESSAGE = 4,
    ADD_FRIEND = 5,
    GET_FRIEND_INFORMATION = 6,
    DELETE_FRIEND = 7,
    GET_USER_INFORMATION = 8,
    CHANGE_INFORMATION = 9,
    CHANGE_REMARK = 10,
    CHANGE_PASSWORD = 11,
    CHANGE_STATUE = 12,
    CHECK_CONNECTION = 19,
    QUIT = 20
};

enum
{
    LOGIN_SUCCESS = 11,
    LOGIN_NO_ACCOUNT = 12,
    LOGIN_WRONG_PWD = 13,
    HAVE_LOGINED = 14,
    GET_ALL_SUCCESS = 16,

    REGISTER_EXIST = 21,
    REGISTER_SUCCESS = 22,

    NO_MESSAGE = 41,
    HAVE_MESSAGE = 42,
    HAVE_TALK_MESSAGE = 43,

    FRIEND_REQUESTED = 51,
    FRIEDN_NO_ACCOUNT = 52,
    ALREAD_FRIENDS = 53,

    GET_FRIEND_SUCCESS = 61,
    DELETE_FRIEND_SUCCESS = 62,
    GET_USER_INF_SUCCESS = 63,
    CHANGE_INFORMATION_SUCCESS = 64,
    CHANGE_REMARK_SUCCESS = 65,

    OLD_PWD_IS_WRONG = 70,
    CHANGE_PWD_SUCCESS = 71
};


enum
{
        OFFLINE = 0,
        INLINE = 1
};

enum
{
    MALE = 0,
    FEMALE = 1
};


enum
{
        KIND = 0,
        Fromfriend = 1,
        Fromfriendid = 2,
        Tofriend = 3,
        Tofriendid =4,
        TEXT = 5
};

enum
{
        VERIFYING = 0,
        FRIEND = 1,
        GOOD_FRIEND = 2,
        MYSELF = 5
};

enum
{
        MESSAGE = 1,
        REQUEST_FRIEND = 2,
        AGREE_FRIEND = 3,
        DISAGREE_FRIEND = 4,
        END_FRIEND = 5,
        BE_DELETED = 8,
        TALK_MESSAGE = 9
};

#endif // PROTOCOL_H
