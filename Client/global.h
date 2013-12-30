#ifndef GLOBAL_H
#define GLOBAL_H
#include <string>
#include <list>
#include <QString>
using namespace std;

typedef string strXml;
typedef const string &C_STR;
typedef const char* LPCSTR;
typedef char* LPSTR;

//login wnd
#define wndSizeWidth 320
#define wndSizeHeight 285

//login username logo
#define logonameSizeWidth 50
#define logopwdSizeHeight 50

//setting dlg size
#define setdlgSizeWidth 640
#define setdlgSizeHeight 480

//setting files path
#define SETFILEPATH "setting.ini"

//maindly size
#define MAINWNDWIDTH 230
#define MAINWNDHEIGH 692

//avatar
#define AVATAR_SIZE 70

//friends size
#define FRDWIDTH    145
#define FRDHEIGH    70

//toolbutton margin
#define MARGINTOOLBUTTON    20


struct ServerNode
{
    string Ip;
    string Port;
};

enum CONSTATUS
{
    IDLE = 1,
    CONNECTING,
    CONNECTED,
    CLOSED
};

enum FRIENDSTATUS
{
    OFFLINE = 0,			//离线
    ONLINE = 1,				//在线
    FREE = 2,               //Q我吧
    BUSY = 3,				//忙碌
    LEAVE = 4,				//离开
    DISTURB = 5,			//请勿打扰
    STEALTH = 6,				//隐身
    QUIT                    //quit
};

//登录状态查询函数
static map<int, string> mpsSta2Enm;
inline void initMpSta2Enm()
{
    mpsSta2Enm.insert(pair<int, string>(OFFLINE, "离线"));
    mpsSta2Enm.insert(pair<int, string>(ONLINE, "在线"));
    mpsSta2Enm.insert(pair<int, string>(FREE, "呼叫我吧"));
    mpsSta2Enm.insert(pair<int, string>(BUSY, "忙碌"));
    mpsSta2Enm.insert(pair<int, string>(LEAVE, "离开"));
    mpsSta2Enm.insert(pair<int, string>(DISTURB, "请勿打搅"));
}

enum GENDER                 //性别
{
    MALE = 0,
    FEMALE
};

enum FUTURE
{
    ABOUT = 1               //future buttons
};

struct recordItem
{
    QString sendid;
    QString recvid;
    QString content;
    QString time;
};

struct historyItem
{
    QString userid;
    list<recordItem> sndOrder;
};

//this is very important release must emit
#define DEBUG 1

#define ANIMATIONTIME 1000*0.2

#define allAvatar   34

//self info file
#define HISTORY    "history"

//every time save history
#define SAVEHISTORYTIME 10000

#endif // GLOBAL_H
