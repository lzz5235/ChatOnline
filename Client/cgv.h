#ifndef CGV_H
#define CGV_H
#include <list>
#include <map>
#include <QFileInfo>
#include <QSettings>
#include <QStringList>
#include "./command/data.h"
#include "./utilities/FuncTools.h"
#include <structure.h>
#include "extern.h"
#include <QDebug>

using namespace std;

class CGV
{
public:
    CGV()
    {
        m_set = new QSettings(iniPath, QSettings::IniFormat);
    }

    virtual ~CGV(void)
    {
        delete m_set;
    }

    string getVersion();
    string getCurFilePath();
    string getIp();
    string getPort();
    KVRt getStatus();

    KVRt getValue(string value);
    bool setValue(KVList &kv);

private:
    string m_version;
    string m_curFilePath;
    string m_Ip;
    string m_Port;
    QSettings *m_set;
};

#endif // CGV_H
