#ifndef GLOBAL_H
#define GLOBAL_H
#include <string>
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

enum FUTURE
{
    ABOUT = 1               //future buttons
};


//this is very important release must emit
#define DEBUG 1

#define ANIMATIONTIME 1000*0.5

#define allAvatar   34

#endif // GLOBAL_H
