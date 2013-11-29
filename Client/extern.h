#ifndef EXTERN_H
#define EXTERN_H
#include <map>
#include <string>
#include "command/data.h"

using namespace std;
#define iniPath "setting.ini"

inline LoginInformation *createLoginInfo()
{

}

static LoginInformation *g_loginInfo = NULL;


#endif // EXTERN_H
