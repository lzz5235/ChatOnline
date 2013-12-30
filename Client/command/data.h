#ifndef DATA_H
#define DATA_H
#include <map>
#include <list>
#include <string>
#include <QString>
#include <stdint.h>
#include <stdio.h>
using namespace std;

typedef struct xml_Back
{
    map<string, string> mapBackPara;
    string backPara;
}XMLBACK;

typedef struct xml_Para
{
    map<string, string> mapCmdPara;
    list<map<string, string> >lstCmdPara;
    int iCmdType;
    XMLBACK xmlBack;
}XMLPARA;

enum cmdtype
{
    RESULT = 1,
    LOGIN,
    LOGIN_BACK,
    LOGININFO,
    LOGOUT,
    SENDMESSAGE,
    GETMESSAGE,
    GETADDRESS,
    UPDATEINFO,
    NEWUPDATE,
    TEST
};

//this para is used at send back data;
//in send back data, i must fetch the back data type
static map<string, int> mpstr2enm;
inline void initstrCMD2enumCMD()
{
    mpstr2enm.insert(pair<string, int>("RESULT", RESULT));
    mpstr2enm.insert(pair<string, int>("LOGIN_BACK", LOGIN_BACK));
    mpstr2enm.insert(pair<string, int>("SEND", GETMESSAGE));
    mpstr2enm.insert(pair<string, int>("ADDRESS", GETADDRESS));
    mpstr2enm.insert(pair<string, int>("LOGINEDINFO", LOGININFO));
    mpstr2enm.insert(pair<string, int>("UPDATE", UPDATEINFO));
    mpstr2enm.insert(pair<string, int>("NEWUPDATE", NEWUPDATE));
}

typedef cmdtype require;
typedef float version;

//xml command type
enum CMDTYPE
{
    VERSION_1 = 1,
    VERSION_2
};

#define xmltemplate "./template"

struct UserInformation
{
    int         userID;                             //用户id，主要用来传输中
    QString     account;                            //account
    QString     password;                           //password
    QString     nickName;                           //呢称
    int         avatarNumber;                       //headIcon
    int         status;                             //登录状态
    QString     cellphone;                          //手机号码
    QString     officephone;                        //电话号码
    QString     birthday;				//生日
    QString     city;                               //所在城市
    QString     description;                        //个人描述
    QString     mail;                               //个人邮箱
    QString     dormitory;                          //宿舍
    int         age;
    QString     sex;
    QString     other;                              //补充
    UserInformation()
    {
        status = 0;
    }
};

struct TempStrings
{
    QString oldpwd;
    QString newpwd;
    QString account;
};

struct LoginInformation
{
    int  userID;
    QString account;
    QString password;
    int status;

    LoginInformation()
    {
        status = 0;
    }
};

struct FriendInformation
{
    QString account;
    QString name;
    int     avatarNumber;
    int     status;
    QString about;
    int     friendKind;                         //好友类型
    QString remark;                             //好友备注
    int     userID;                             //用户id，主要用来传输中
    QString nickName;                           //呢称
    QString cellphone;                          //手机号码
    QString officephone;                        //电话号码
    QString birthday;                           //生日
    QString city;                               //所在城市
    QString description;                        //个人描述
    QString mail;                               //个人邮箱
    QString dormitory;                          //宿舍
    int     age;
    QString sex;
    QString other;                              //补充

    FriendInformation()
    {
        avatarNumber = status = friendKind = 0;
    }
};

enum
{
    LOGIN_SUCCESS = 11,                             //登录成功
    LOGIN_NO_ACCOUNT = 12,                          //没有这个用户名
    LOGIN_WRONG_PWD = 13,                           //密码错误
    HAVE_LOGINED = 14,                              //该用户已经登录了
    GET_ALL_SUCCESS = 16,
    NO_MESSAGE = 41,                                //没有信息
    HAVE_MESSAGE = 42,                              //有信息
    GET_FRIEND_SUCCESS = 61,                        //获得好友资料
    GET_USER_INF_SUCCESS = 63,                      //获得（好友的）详细资料
    CHANGE_INFORMATION_SUCCESS = 64,                //改变自身资料成功
    CHANGE_REMARK_SUCCESS = 65,                     //修改备注成功
    OLD_PWD_IS_WRONG = 70,                          //旧密码是错的
    CHANGE_PWD_SUCCESS = 71                         //修改密码成功
};

#define OS_SYSTEM   "MAC"
#define CODEDECODE  "GB2312"

//LOGIN
#define USERNAME    "username"
#define PASSWORD    "password"
#define STATUS      "status"
#define LOGINTIME   "logintime"

//UPDATE
#define USERNAME        "username"
#define USERNICKNAME    "nickname"
#define USERID          "userid"
#define USERPASSWORD    "userpassword"
#define USERSEX         "usersex"
#define USERAGE         "userage"
#define USERCELLPHONE   "usercellphone"
#define USEROFFICEPHONE "userofficephone"
#define USERMAIL        "usermail"
#define USEROTHER       "userother"
#define USERDORMITORY   "userdormitory"
#define USERDESCRIPTION "userdescription"
#define USERSTATUS      "userstatus"
#define USERBIRTHDAY    "userbirthday"
#define USERAVATARNUM   "useravatarnumber"
#define USERCITY        "usercity"
#define USERPASSWORD    "userpassword"

//SEND
#define USERCONTENT     "usercontent"
#define USERSENDERID    "usersendid"
#define USERRECVERID    "userrecvid"
#define USERSENDERNAME  "usersendername"
#define USERRECVERNAME  "userrecvername"
#define USERBROADCAST   "userbroadcast"
#define USERSENDTIME    "usersendtime"
#define BROADCAST       "false"

//GetAddress
#define USERGETWHO      "usergetwho"

//LOGIN BACK
#define LOGINRESULT     "loginresult"
#define LOGINSUCCESS    "200"

//GETADDRESS BACK
#define GETADDRESSRESULT    "getaddressresult"
#define GETADDRESSSUCCESSFUL    "200"

//MESSAGE
#define SENDERMESSAGEID     "sendermessageid"
#define RECVERMESSAGEID     "recvermessageid"
#define SENDERNICKNAME      "sendernickname"
#define RECVERNICKNAME      "recvernickname"
#define MESSAGECONTENT      "messagecontent"
#define MESSAGESENDTIME     "messagesendtime"
#define MESSAGERECVTIME     "messagerecvtime"
#define MESSAGEBROADCAST    "messagebroadcast"

//GETMESSAGE
#define GETMESSAGERESULT    "getmessageresult"
#define GETMESSAGESUCCESSFUL    "200"

//LOGININFO
#define LOGININFORESULT     "logininforesult"
#define LOGININFOSUCCESSFUL     "200"
#define LOGININFOUSERID     "logininfouserid"

//NEWUPDATE
#define NEWUPDATERESULT     "newupdateresult"
#define NEWUPDATESUCCESSFUL "200"
#define NEWUPDATEUSERID     "newupdateuserid"

#endif // DATA_H
