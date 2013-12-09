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
    LOGIN = 1,
    LOGOUT,
    SENDMESSAGE,
    GETMESSAGE,
    GETADDRESS,
    UPDATEINFO,
    TEST
};

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
    HAVE_TALK_MESSAGE = 43,
    ALREAD_FRIENDS = 53,                            //��Ӧ��������
    GET_FRIEND_SUCCESS = 61,                        //��ú�������
    GET_USER_INF_SUCCESS = 63,                      //��ã����ѵģ���ϸ����
    CHANGE_INFORMATION_SUCCESS = 64,                //�ı��������ϳɹ�
    CHANGE_REMARK_SUCCESS = 65,                     //�޸ı�ע�ɹ�
    OLD_PWD_IS_WRONG = 70,                          //�������Ǵ��
    CHANGE_PWD_SUCCESS = 71                         //�޸�����ɹ�
};

#define OS_SYSTEM   "MAC"

#define USERNAME    "username"
#define PASSWORD    "password"
#define STATUS      "status"
#define LOGINTIME   "logintime"

#endif // DATA_H
