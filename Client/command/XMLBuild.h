#ifndef XMLBUILD_H
#define XMLBUILD_H
#include "data.h"
#include <string>
#include <map>

using namespace std;

class CXMLBuild
{
public:
    CXMLBuild();
    ~CXMLBuild();
    void init(int type);


    string TRANS_LOGIN(string username, string password, int status, string system = "OS_WINDOWS");
    string TRANS_LOGOUT(string username);
    string TRANS_GET_ADDRESS(string who);
    string TRANS_SEND(string from, string nickname_f, string to, string nickname_t, string content, string broadcast = "false");
    string TRANS_UPDATE(UserInformation user);
    string TRANS_TEST();

private:
    bool readfile(string path);
    bool readXmlFromResource();
    string orgnizeXML(char* strName, int length);
    inline string xmlFind(string name)
    {
        map<string, string>::iterator it = m_xmlBuild.begin();
        while(it != m_xmlBuild.end())
        {
            if(it->first == name)
            {
                return it->second;
            }
            it++;
        }
        return string("");
    }

private:
    map<string, string> m_xmlBuild;
};

#endif //XMLBUILD_H
