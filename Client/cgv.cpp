#include "cgv.h"

string CGV::getVersion()
{

}

string CGV::getCurFilePath()
{

}

string CGV::getIp()
{
    KVRt value = getValue("SERVER/IP");
    if(!value.empty())
    {
        KVRt::iterator it = value.begin();
        if(it != value.end())
        {
            return it->first;
        }
    }

    return string("");
}

string CGV::getPort()
{
    KVRt value = getValue("SERVER/PORT");
    if(!value.empty())
    {
        KVRt::iterator it = value.begin();
        if(it != value.end())
        {
            return it->first;
        }
    }

    return string("");
}

KVRt CGV::getStatus()
{
    return getValue("STATUS/status");

    /*
    if(m_set)
    {
        QStringList statuslst = m_set->value("STATUS/status").toStringList();
        if(!statuslst.empty())
        {
            map<string, int> status;
            for(int i = 0; i < statuslst.count(); i++)
            {
                status.insert(pair<string, int>(statuslst[i].toStdString(), i));
            }
            return status;
        }
    }
    return map<string, int>();
    */

}

KVRt  CGV::getValue(string value)
{
    if(m_set)
    {
        QStringList statuslst = m_set->value(value.c_str()).toStringList();
        if(!statuslst.empty())
        {
            KVRt kvRtValue;
            for(int i = 0; i < statuslst.count(); i++)
            {
                kvRtValue.insert(pair<string, int>(statuslst[i].toStdString(), i));
            }
            return kvRtValue;
        }
    }
    return KVRt();
}

bool CGV::setValue(KVList &kv)
{
    if(m_set && !kv.KVGroup.empty())
    {
        m_set->beginGroup(kv.KVGroup.c_str());
        map<string, string>::iterator it = kv.KVData.begin();
        while(it != kv.KVData.end())
        {
            m_set->setValue(it->first.c_str(), it->second.c_str());
            it++;
        }
        return true;
    }
    else if(m_set)
    {
        map<string, string>::iterator it = kv.KVData.begin();
        while(it != kv.KVData.end())
        {
            m_set->setValue(it->first.c_str(), it->second.c_str());
            it++;
        }
        return true;
    }
    return false;
}
