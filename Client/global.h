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

//this is very important release must emit
#define DEBUG 1

#endif // GLOBAL_H
