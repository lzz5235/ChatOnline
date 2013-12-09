#include "command.h"
#include "xml/EasyXml.h"

CCommand::CCommand(float version)
{
    init(version);
}

int CCommand::init(float version)
{
    m_strError = "";
    m_version = version;
    m_xml.init(version);
    return 0;
}

string CCommand::parseCmd2Xml(XMLPARA &para)
{
    switch(para.iCmdType)
    {
    case LOGIN:
        return xmlLogin(para);
        break;

    case LOGOUT:
        return xmlLogout(para);
        break;

    case SENDMESSAGE:
        return xmlSend(para);
        break;

    case GETADDRESS:
        return xmlGetAddress(para);
        break;

    case UPDATEINFO:
        return xmlUpdate(para);
        break;

    case TEST:
        return xmlTest();
        break;
    }
    return string("");
}

int CCommand::parseRspType(string strRsp)
{
    CEasyXml xml;
    xml.Open(strRsp);
    string ack;
    xml.Query("TRANS_NOTIFICATION/HEAD/TYPE", ack);
    if("RESULT" == ack)
    {
        CEasyXml xml;
        xml.Open(strRsp);
        string ack;
        xml.Query("TRANS_NOTIFICATION/ACTION/ACK", ack);
        if("200" == ack)
        {

        }
    }
}

int CCommand::parseRsp(string strRsp, XMLPARA &back)
{
    switch(back.iCmdType)
    {
    case LOGIN:
        RspXmlLogin(strRsp, back);
        break;

    case LOGOUT:
        RspXmlLogout(strRsp, back);
        break;

    case SENDMESSAGE:
        RspXmlSend(strRsp, back);
        break;

    case GETADDRESS:
        RspXmlGetAddress(strRsp, back);
        break;

    case UPDATEINFO:
        RspXmlUpdate(strRsp, back);
        break;

    case TEST:
        RspXmlTest(strRsp, back);
        break;
    }
    return -1;
}

string CCommand::getLastError()
{

}

string CCommand::getVersion()
{

}

string CCommand::xmlLogin(XMLPARA &xmlLogin)
{
    string username = getElement(xmlLogin.mapCmdPara, USERNAME);
    string password = getElement(xmlLogin.mapCmdPara, PASSWORD);
    string status = getElement(xmlLogin.mapCmdPara, STATUS);
    return m_xml.TRANS_LOGIN(username, password, atoi(status.c_str()), OS_SYSTEM);
}

string CCommand::xmlUpdate(XMLPARA &xmlUpdate)
{

}

string CCommand::xmlSend(XMLPARA &xmlSend)
{

}

string CCommand::xmlLogout(XMLPARA &xmlLogout)
{

}

string CCommand::xmlGetAddress(XMLPARA &xmlGetAddress)
{

}

string CCommand::xmlTest()
{
    return m_xml.TRANS_TEST();
}

int CCommand::parseRspXml(string strRsp, XMLPARA &back)
{

}

void CCommand::RspXmlLogin(string strRsp, XMLPARA &back)
{

}

void CCommand::RspXmlGetAddress(string strRsp, XMLPARA &back)
{

}

void CCommand::RspXmlUpdate(string strRsp, XMLPARA &back)
{

}

void CCommand::RspXmlLogout(string strRsp, XMLPARA &back)
{

}

void CCommand::RspXmlSend(string strRsp, XMLPARA &back)
{

}

void  CCommand::RspXmlTest(string strRsp, XMLPARA &back)
{

}
