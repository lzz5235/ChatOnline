#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

#include "XMLBuild.h"
#include "utilities/FuncTools.h"
#include "xml/SimpleXml.h"
#include "data.h"
#include <QFileInfoList>
#include <QDir>
#include <QFile>
#include <QString>
#include <list>
#include "xml/rscCMD.h"
#include <QDebug>
#include <QTextCodec>

CXMLBuild::CXMLBuild()
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName( "utf-8" ) );
}

CXMLBuild::~CXMLBuild()
{

}

void CXMLBuild::init(int type)
{
    switch(type)
    {
        case VERSION_1:
        {
            readfile(xmltemplate);
            break;
        }

        case VERSION_2:
        {
            readXmlFromResource();
            break;
        }

        default:
        {
            break;
        }

    }
}

string CXMLBuild::TRANS_LOGIN(string username, string password, int status, string system)
{
    string strxml(xmlFind("TRANS_LOGIN.xml"));

    list<XMLNODEINFO> lstNodeInfo;
    XMLNODEINFO nodeinfo;
    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/LOGIN/USERNAME";
    nodeinfo.strData = username;
    lstNodeInfo.push_back(nodeinfo);

    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/LOGIN/PASSWORD";
    nodeinfo.strData = password;
    lstNodeInfo.push_back(nodeinfo);

    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/LOGIN/STATUS";
    char szStatus[16];
    memset(szStatus, 0, 16);
    itoa(status, szStatus);
    nodeinfo.strData = szStatus;
    lstNodeInfo.push_back(nodeinfo);

    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/LOGIN/SYSTEM";
    nodeinfo.strData = system;
    lstNodeInfo.push_back(nodeinfo);

    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/LOGIN/LOGINTIME";
    nodeinfo.strData = ConvertTimeFormat(GetCurrTime());
    lstNodeInfo.push_back(nodeinfo);

    CSimpleXml xml;
    xml.OpenXml(strxml);
    xml.ModifyXml(lstNodeInfo);
    xml.GetXml(strxml);
    return strxml;
}

string CXMLBuild::TRANS_LOGOUT(string username)
{
    string strxml(xmlFind("TRANS_LOGOUT.xml"));

    list<XMLNODEINFO> lstNodeInfo;
    XMLNODEINFO nodeinfo;
    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/LOGOUT/USERNAME";
    nodeinfo.strData = username;
    lstNodeInfo.push_back(nodeinfo);

    CSimpleXml xml;
    xml.OpenXml(strxml);
    xml.ModifyXml(lstNodeInfo);
    xml.GetXml(strxml);
    return strxml;
}

string CXMLBuild::TRANS_GET_ADDRESS(string who)
{
    string strxml(xmlFind("TRANS_GET_ADDRESS.xml"));

    list<XMLNODEINFO> lstNodeInfo;
    XMLNODEINFO nodeinfo;
    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/GET_ADDRESS";
    nodeinfo.strData = who;
    lstNodeInfo.push_back(nodeinfo);

    CSimpleXml xml;
    xml.OpenXml(strxml);
    xml.ModifyXml(lstNodeInfo);
    xml.GetXml(strxml);
    return strxml;
}

string CXMLBuild::TRANS_SEND(string from, string nickname_f, string to, string nickname_t, string content, string time, string broadcast)
{
    string strxml(xmlFind("TRANS_SEND.xml"));
    CEasyXml xml;
    xml.Open(strxml);

    list<XMLNODEINFO> lstNodeInfo;
    XMLNODEINFO nodeinfo;
    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/SEND/MESSAGE/FROM/USERID";
    nodeinfo.strData = from;
    lstNodeInfo.push_back(nodeinfo);
    xml.Modify(nodeinfo.strNodeName, nodeinfo.strData);

    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/SEND/MESSAGE/FROM/NICKNAME";
    nodeinfo.strData = nickname_f;
    lstNodeInfo.push_back(nodeinfo);
    xml.Modify(nodeinfo.strNodeName, nodeinfo.strData);

    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/SEND/MESSAGE/FROM/MESSAGESENDTIME";
    nodeinfo.strData = time;
    lstNodeInfo.push_back(nodeinfo);
    xml.Modify(nodeinfo.strNodeName, nodeinfo.strData);

    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/SEND/MESSAGE/TO/USERID";
    nodeinfo.strData = to;
    lstNodeInfo.push_back(nodeinfo);
    xml.Modify(nodeinfo.strNodeName, nodeinfo.strData);

    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/SEND/MESSAGE/TO/NICKNAME";
    nodeinfo.strData = nickname_t;
    lstNodeInfo.push_back(nodeinfo);
    xml.Modify(nodeinfo.strNodeName, nodeinfo.strData);

    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/SEND/MESSAGE/BROADCAST";
    nodeinfo.strData = broadcast;
    lstNodeInfo.push_back(nodeinfo);
    xml.Modify(nodeinfo.strNodeName, nodeinfo.strData);

    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/SEND/MESSAGE/CONTENT";
    nodeinfo.strData = content;
    lstNodeInfo.push_back(nodeinfo);
    xml.Modify(nodeinfo.strNodeName, nodeinfo.strData);

//here simple xml is not work
//    CSimpleXml xml;
//    xml.OpenXml(strxml);
//    xml.ModifyXml(lstNodeInfo);
//    xml.GetXml(strxml);
    strxml = xml.GetXml();
    return strxml;
}

string CXMLBuild::TRANS_UPDATE(UserInformation user)
{
    string strxml(xmlFind("TRANS_UPDATE.xml"));
    CEasyXml xml;
    xml.Open(strxml);

    list<XMLNODEINFO> lstNodeInfo;
    XMLNODEINFO nodeinfo;
    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/UPDATE/USERNAME";
    nodeinfo.strData = user.account.toStdString();
    lstNodeInfo.push_back(nodeinfo);
    xml.Modify(nodeinfo.strNodeName, nodeinfo.strData);

    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/UPDATE/USERID";
    nodeinfo.strData = QString::number(user.userID).toStdString();
    lstNodeInfo.push_back(nodeinfo);
    xml.Modify(nodeinfo.strNodeName, nodeinfo.strData);

    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/UPDATE/NICKNAME";
    nodeinfo.strData = user.nickName.toStdString();
    lstNodeInfo.push_back(nodeinfo);
    xml.Modify(nodeinfo.strNodeName, nodeinfo.strData);

    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/UPDATE/OLDPASSWORD";
    nodeinfo.strData = user.password.toStdString();
    lstNodeInfo.push_back(nodeinfo);
    xml.Modify(nodeinfo.strNodeName, nodeinfo.strData);

    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/UPDATE/NEWPASSWORD";
    nodeinfo.strData = user.newpassword.toStdString();
    lstNodeInfo.push_back(nodeinfo);
    xml.Modify(nodeinfo.strNodeName, nodeinfo.strData);

    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/UPDATE/AVATARNUM";
    nodeinfo.strData = QString::number(user.avatarNumber).toStdString();
    lstNodeInfo.push_back(nodeinfo);
    xml.Modify(nodeinfo.strNodeName, nodeinfo.strData);

    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/UPDATE/SEX";
    nodeinfo.strData = user.sex.toStdString();
    lstNodeInfo.push_back(nodeinfo);
    xml.Modify(nodeinfo.strNodeName, nodeinfo.strData);

    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/UPDATE/AGE";
    nodeinfo.strData = QString::number(user.age).toStdString();
    lstNodeInfo.push_back(nodeinfo);
    xml.Modify(nodeinfo.strNodeName, nodeinfo.strData);

    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/UPDATE/CONTACT/CELLPHONE";
    nodeinfo.strData = user.cellphone.toStdString();
    lstNodeInfo.push_back(nodeinfo);
    xml.Modify(nodeinfo.strNodeName, nodeinfo.strData);

    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/UPDATE/CONTACT/OFFICEPHONE";
    nodeinfo.strData = user.officephone.toStdString();
    lstNodeInfo.push_back(nodeinfo);
    xml.Modify(nodeinfo.strNodeName, nodeinfo.strData);

    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/UPDATE/CONTACT/MAIL";
    nodeinfo.strData = user.mail.toStdString();
    lstNodeInfo.push_back(nodeinfo);
    xml.Modify(nodeinfo.strNodeName, nodeinfo.strData);

    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/UPDATE/OTHER_INFORMATION";
    nodeinfo.strData = user.other.toStdString();
    lstNodeInfo.push_back(nodeinfo);
    xml.Modify(nodeinfo.strNodeName, nodeinfo.strData);

    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/UPDATE/DORMITORY";
    nodeinfo.strData = user.dormitory.toStdString();
    lstNodeInfo.push_back(nodeinfo);
    xml.Modify(nodeinfo.strNodeName, nodeinfo.strData);

    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/UPDATE/DESCRIPTION";
    nodeinfo.strData = user.description.toStdString();
    lstNodeInfo.push_back(nodeinfo);
    xml.Modify(nodeinfo.strNodeName, nodeinfo.strData);

    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/UPDATE/STATUS";
    nodeinfo.strData = QString::number(user.status).toStdString();
    lstNodeInfo.push_back(nodeinfo);
    xml.Modify(nodeinfo.strNodeName, nodeinfo.strData);

    nodeinfo.strNodeName = "TRANS_NOTIFICATION/ACTION/UPDATE/BIRTHDAY";
    nodeinfo.strData = user.birthday.toStdString();
    lstNodeInfo.push_back(nodeinfo);
    xml.Modify(nodeinfo.strNodeName, nodeinfo.strData);

//    CSimpleXml xml;
//    xml.OpenXml(strxml);
//    xml.ModifyXml(lstNodeInfo);
//    xml.GetXml(strxml);
    strxml = xml.GetXml();
    return strxml;
}

string CXMLBuild::TRANS_TEST()
{
    string strxml(xmlFind("TRANS_TEST.xml"));
    return strxml;
}

bool CXMLBuild::readfile(string path)
{
    QDir dir;
    QString qstrpath;
    qstrpath.append(path.c_str());
    dir.cd(qstrpath);
    if(!dir.exists())
    {
        printf("the dir doesnot exist!");
        return false;
    }

    QFileInfoList flist = dir.entryInfoList();
    for(int i = 0; i < flist.size(); i++)
    {
        QFile file(flist.at(i).fileName());
        if(file.exists( ) && file.isReadable())
        {
            string strfile = string(file.readAll().data());
            QString qstrfile = flist.at(i).fileName();

            m_xmlBuild.insert(pair<string, string>(string(qstrfile.toLatin1()), strfile));
        }
    }
}

bool CXMLBuild::readXmlFromResource()
{
    m_xmlBuild.insert(pair<string, string>(string("MEMBER.xml"), orgnizeXML((char*)NXML::MEMBER, sizeof(NXML::MEMBER))));
    m_xmlBuild.insert(pair<string, string>(string("TRANS_GET_ADDRESS.xml"), orgnizeXML((char*)NXML::TRANS_GET_ADDRESS, sizeof(NXML::TRANS_GET_ADDRESS))));
    m_xmlBuild.insert(pair<string, string>(string("TRANS_RESULT.xml"), orgnizeXML((char*)NXML::TRANS_RESULT, sizeof(NXML::TRANS_RESULT))));
    m_xmlBuild.insert(pair<string, string>(string("TRANS_SEND.xml"), orgnizeXML((char*)NXML::TRANS_SEND, sizeof(NXML::TRANS_SEND))));
    m_xmlBuild.insert(pair<string, string>(string("TRANS_LOGIN.xml"), orgnizeXML((char*)NXML::TRANS_LOGIN, sizeof(NXML::TRANS_LOGIN))));
    m_xmlBuild.insert(pair<string, string>(string("TRANS_UPDATE.xml"), orgnizeXML((char*)NXML::TRANS_UPDATE, sizeof(NXML::TRANS_UPDATE))));
    m_xmlBuild.insert(pair<string, string>(string("TRANS_ADDRESS.xml"), orgnizeXML((char*)NXML::TRANS_ADDRESS, sizeof(NXML::TRANS_ADDRESS))));
    m_xmlBuild.insert(pair<string, string>(string("TRANS_LOGIN_BACK.xml"), orgnizeXML((char*)NXML::TRANS_LOGIN_BACK, sizeof(NXML::TRANS_LOGIN_BACK))));
    m_xmlBuild.insert(pair<string, string>(string("TRANS_TEST.xml"), orgnizeXML((char*)NXML::TRANS_TEST, sizeof(NXML::TRANS_TEST))));
}

string CXMLBuild::orgnizeXML(char* strName, int length)
{
    char szXML[length + 1];
    memset(szXML, 0, sizeof(szXML));
    memcpy(szXML, strName, length);
#ifdef DEBUG
    qDebug() << "xml is %s \n" << QString(szXML);
#endif
    return string(szXML);
}
