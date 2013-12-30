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
    int         userID;                             //�û�id����Ҫ����������
    QString     account;                            //account
    QString     password;                           //password
    QString     nickName;                           //�س�
    int         avatarNumber;                       //headIcon
    int         status;                             //��¼״̬
    QString     cellphone;                          //�ֻ�����
    QString     officephone;                        //�绰����
    QString     birthday;				//����
    QString     city;                               //���ڳ���
    QString     description;                        //��������
    QString     mail;                               //��������
    QString     dormitory;                          //����
    int         age;
    QString     sex;
    QString     other;                              //����
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
    int     friendKind;                         //��������
    QString remark;                             //���ѱ�ע
    int     userID;                             //�û�id����Ҫ����������
    QString nickName;                           //�س�
    QString cellphone;                          //�ֻ�����
    QString officephone;                        //�绰����
    QString birthday;                           //����
    QString city;                               //���ڳ���
    QString description;                        //��������
    QString mail;                               //��������
    QString dormitory;                          //����
    int     age;
    QString sex;
    QString other;                              //����

    FriendInformation()
    {
        avatarNumber = status = friendKind = 0;
    }
};

enum
{
    LOGIN_SUCCESS = 11,                             //��¼�ɹ�
    LOGIN_NO_ACCOUNT = 12,                          //û������û���
    LOGIN_WRONG_PWD = 13,                           //�������
    HAVE_LOGINED = 14,                              //���û��Ѿ���¼��
    GET_ALL_SUCCESS = 16,
    NO_MESSAGE = 41,                                //û����Ϣ
    HAVE_MESSAGE = 42,                              //����Ϣ
    GET_FRIEND_SUCCESS = 61,                        //��ú�������
    GET_USER_INF_SUCCESS = 63,                      //��ã����ѵģ���ϸ����
    CHANGE_INFORMATION_SUCCESS = 64,                //�ı��������ϳɹ�
    CHANGE_REMARK_SUCCESS = 65,                     //�޸ı�ע�ɹ�
    OLD_PWD_IS_WRONG = 70,                          //�������Ǵ��
    CHANGE_PWD_SUCCESS = 71                         //�޸�����ɹ�
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
