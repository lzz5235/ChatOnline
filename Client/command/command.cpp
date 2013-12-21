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
    initstrCMD2enumCMD();
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
    string ack = "";
    xml.Query("TRANS_NOTIFICATION/HEAD/TYPE", ack);
    int rtType = getElement(mpstr2enm, ack);
    switch(rtType)
    {
        case RESULT:
        {
            CEasyXml xml;
            xml.Open(strRsp);
            string ack;
            xml.Query("TRANS_NOTIFICATION/ACTION/ACK", ack);
            if("200" == ack)
            {
                return 1;
            }
            else
            {
                return -1;
            }
         }

        default :
        {
            return rtType;
        }
    }

}

int CCommand::parseRsp(string strRsp, XMLPARA &back)
{
    switch(back.iCmdType)
    {
    case RESULT:
        RspXmlResult(strRsp, back);
        break;

    case LOGIN_BACK:
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

void CCommand::RspXmlResult(string strRsp, XMLPARA &back)
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
    string strUserName = getElement(xmlUpdate.mapCmdPara, USERNAME);
    string strNickName = getElement(xmlUpdate.mapCmdPara, USERNICKNAME);
    string strUserId = getElement(xmlUpdate.mapCmdPara, USERID);
    string strSex = getElement(xmlUpdate.mapCmdPara, USERSEX);
    string strAge = getElement(xmlUpdate.mapCmdPara, USERAGE);
    string strCellPhone = getElement(xmlUpdate.mapCmdPara, USERCELLPHONE);
    string strOfficePhone = getElement(xmlUpdate.mapCmdPara, USEROFFICEPHONE);
    string strMail = getElement(xmlUpdate.mapCmdPara, USERMAIL);
    string strOtherInfo = getElement(xmlUpdate.mapCmdPara, USEROTHER);
    string strDormitory = getElement(xmlUpdate.mapCmdPara, USERDORMITORY);
    string strDescription = getElement(xmlUpdate.mapCmdPara, USERDESCRIPTION);
    string strStatus = getElement(xmlUpdate.mapCmdPara, USERSTATUS);
    string strBirthday = getElement(xmlUpdate.mapCmdPara, USERBIRTHDAY);
    string strAvatarNumber = getElement(xmlUpdate.mapCmdPara, USERAVATARNUM);
    string strCity = getElement(xmlUpdate.mapCmdPara, USERCITY);
    string strPassword = getElement(xmlUpdate.mapCmdPara, USERPASSWORD);

    UserInformation user;
    user.account = QString(strUserName.c_str());
    user.nickName = QString(strNickName.c_str());
    user.age = QString(strAge.c_str()).toInt();
    user.avatarNumber = QString(strAvatarNumber.c_str()).toInt();
    user.birthday = QString(strBirthday.c_str());
    user.cellphone = QString(strCellPhone.c_str());
    user.city = QString(strCity.c_str());
    user.description = QString(strDescription.c_str());
    user.dormitory = QString(strDormitory.c_str());
    user.mail = QString(strMail.c_str());
    user.officephone = QString(strOfficePhone.c_str());
    user.other = QString(strOtherInfo.c_str());
    user.userID = QString(strUserId.c_str()).toInt();
    user.sex = QString(strSex.c_str());
    user.status = QString(strStatus.c_str()).toInt();
    user.password = QString(strPassword.c_str());

    return m_xml.TRANS_UPDATE(user);
}

string CCommand::xmlSend(XMLPARA &xmlSend)
{
    string strSenderUserID = getElement(xmlSend.mapCmdPara, USERSENDERID);
    string strSenderNickName = getElement(xmlSend.mapCmdPara, USERSENDERNAME);

    string strRecverUserId = getElement(xmlSend.mapCmdPara, USERRECVERID);
    string strRecverNickName = getElement(xmlSend.mapCmdPara, USERRECVERNAME);

    string strContent = getElement(xmlSend.mapCmdPara, USERCONTENT);
    string strBeBroadcast = getElement(xmlSend.mapCmdPara, USERBROADCAST);

    return m_xml.TRANS_SEND(strSenderUserID, strSenderNickName, strRecverUserId, strRecverNickName, strContent, strBeBroadcast);
}

string CCommand::xmlLogout(XMLPARA &xmlLogout)
{
    string username = getElement(xmlLogout.mapCmdPara, USERNAME);
    return m_xml.TRANS_LOGOUT(username);
}

string CCommand::xmlGetAddress(XMLPARA &xmlGetAddress)
{
    string strWho = getElement(xmlGetAddress.mapCmdPara, USERGETWHO);
    return m_xml.TRANS_GET_ADDRESS(strWho);
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
    CSimpleXml xml;
    xml.OpenXml(strRsp);
    XMLNODEINFO xmlnode;

    xmlnode.strNodeName = "TRANS_NOTIFICATION/ACTION/LOGIN_BACK/ACK";
    xml.AccessXmlNode(xmlnode, QUERY);
    back.xmlBack.mapBackPara[LOGINRESULT] = xmlnode.strData;

    string strParseRspXml = strRsp;

    while (1)
    {
        const unsigned long nPosL = strParseRspXml.find("<MEMBER>");
        if (nPosL == strParseRspXml.npos)
        {
            break;
        }
        const unsigned long nPosR = strParseRspXml.find("</MEMBER>");
        if (nPosR != string::npos)
        {
            string strXmlS = strParseRspXml.substr(nPosL, nPosR - nPosL + strlen("</MEMBER>"));
            string strRspXmlTmp = strParseRspXml.substr(nPosR + strlen("</MEMBER>"));
            strParseRspXml = strRspXmlTmp;

            CSimpleXml xml;
            xml.OpenXml(strXmlS);
            XMLNODEINFO xmlnode;
            map<string, string> mapTermInfo;

            xmlnode.strNodeName = "MEMBER/NICKNAME";
            xmlnode.strData = "";
            xml.AccessXmlNode(xmlnode, QUERY);
            mapTermInfo.insert(make_pair(USERNICKNAME, xmlnode.strData));

            xmlnode.strNodeName = "MEMBER/USERID";
            xmlnode.strData = "";
            xml.AccessXmlNode(xmlnode, QUERY);
            mapTermInfo.insert(make_pair(USERID, xmlnode.strData));

            xmlnode.strNodeName = "MEMBER/SEX";
            xmlnode.strData = "";
            xml.AccessXmlNode(xmlnode, QUERY);
            mapTermInfo.insert(make_pair(USERSEX, xmlnode.strData));

            xmlnode.strNodeName = "MEMBER/AGE";
            xmlnode.strData = "";
            xml.AccessXmlNode(xmlnode, QUERY);
            mapTermInfo.insert(make_pair(USERAGE, xmlnode.strData));

            xmlnode.strNodeName = "MEMBER/AVATARNUMBER";
            xmlnode.strData = "";
            xml.AccessXmlNode(xmlnode, QUERY);
            mapTermInfo.insert(make_pair(USERAVATARNUM, xmlnode.strData));

            xmlnode.strNodeName = "MEMBER/CONTACT/CELLPHONE";
            xmlnode.strData = "";
            xml.AccessXmlNode(xmlnode, QUERY);
            mapTermInfo.insert(make_pair(USERCELLPHONE, xmlnode.strData));

            xmlnode.strNodeName = "MEMBER/CONTACT/OFFICEPHONE";
            xmlnode.strData = "";
            xml.AccessXmlNode(xmlnode, QUERY);
            mapTermInfo.insert(make_pair(USEROFFICEPHONE, xmlnode.strData));

            xmlnode.strNodeName = "MEMBER/CONTACT/MAIL";
            xmlnode.strData = "";
            xml.AccessXmlNode(xmlnode, QUERY);
            mapTermInfo.insert(make_pair(USERMAIL, xmlnode.strData));

            xmlnode.strNodeName = "MEMBER/OTHER_INFORMATION";
            xmlnode.strData = "";
            xml.AccessXmlNode(xmlnode, QUERY);
            mapTermInfo.insert(make_pair(USERDESCRIPTION, xmlnode.strData));

            xmlnode.strNodeName = "MEMBER/DORMITORY";
            xmlnode.strData = "";
            xml.AccessXmlNode(xmlnode, QUERY);
            mapTermInfo.insert(make_pair(USERDORMITORY, xmlnode.strData));

            back.lstCmdPara.push_back(mapTermInfo);
        }
    }
}

void CCommand::RspXmlGetAddress(string strRsp, XMLPARA &back)
{
    CSimpleXml xml;
    xml.OpenXml(strRsp);
    XMLNODEINFO xmlnode;

    xmlnode.strNodeName = "TRANS_NOTIFICATION/ACTION/GET_ADDRESS/ACK";
    xml.AccessXmlNode(xmlnode, QUERY);
    back.xmlBack.mapBackPara[GETADDRESSRESULT] = xmlnode.strData;

    string strParseRspXml = strRsp;

    while (1)
    {
        const unsigned long nPosL = strParseRspXml.find("<MEMBER>");
        if (nPosL == strParseRspXml.npos)
        {
            break;
        }
        const unsigned long nPosR = strParseRspXml.find("</MEMBER>");
        if (nPosR != string::npos)
        {
            string strXmlS = strParseRspXml.substr(nPosL, nPosR - nPosL + strlen("</MEMBER>"));
            string strRspXmlTmp = strParseRspXml.substr(nPosR + strlen("</MEMBER>"));
            strParseRspXml = strRspXmlTmp;

            CSimpleXml xml;
            xml.OpenXml(strXmlS);
            XMLNODEINFO xmlnode;
            map<string, string> mapTermInfo;

            xmlnode.strNodeName = "MEMBER/NICKNAME";
            xmlnode.strData = "";
            xml.AccessXmlNode(xmlnode, QUERY);
            mapTermInfo.insert(make_pair(USERNICKNAME, xmlnode.strData));

            xmlnode.strNodeName = "MEMBER/USERID";
            xmlnode.strData = "";
            xml.AccessXmlNode(xmlnode, QUERY);
            mapTermInfo.insert(make_pair(USERID, xmlnode.strData));

            xmlnode.strNodeName = "MEMBER/SEX";
            xmlnode.strData = "";
            xml.AccessXmlNode(xmlnode, QUERY);
            mapTermInfo.insert(make_pair(USERSEX, xmlnode.strData));

            xmlnode.strNodeName = "MEMBER/AGE";
            xmlnode.strData = "";
            xml.AccessXmlNode(xmlnode, QUERY);
            mapTermInfo.insert(make_pair(USERAGE, xmlnode.strData));

            xmlnode.strNodeName = "MEMBER/AVATARNUMBER";
            xmlnode.strData = "";
            xml.AccessXmlNode(xmlnode, QUERY);
            mapTermInfo.insert(make_pair(USERAVATARNUM, xmlnode.strData));

            xmlnode.strNodeName = "MEMBER/STATUS";
            xmlnode.strData = "";
            xml.AccessXmlNode(xmlnode, QUERY);
            mapTermInfo.insert(make_pair(USERSTATUS, xmlnode.strData));

            xmlnode.strNodeName = "MEMBER/CONTACT/CELLPHONE";
            xmlnode.strData = "";
            xml.AccessXmlNode(xmlnode, QUERY);
            mapTermInfo.insert(make_pair(USERCELLPHONE, xmlnode.strData));

            xmlnode.strNodeName = "MEMBER/CONTACT/OFFICEPHONE";
            xmlnode.strData = "";
            xml.AccessXmlNode(xmlnode, QUERY);
            mapTermInfo.insert(make_pair(USEROFFICEPHONE, xmlnode.strData));

            xmlnode.strNodeName = "MEMBER/CONTACT/MAIL";
            xmlnode.strData = "";
            xml.AccessXmlNode(xmlnode, QUERY);
            mapTermInfo.insert(make_pair(USERMAIL, xmlnode.strData));

            xmlnode.strNodeName = "MEMBER/OTHER_INFORMATION";
            xmlnode.strData = "";
            xml.AccessXmlNode(xmlnode, QUERY);
            mapTermInfo.insert(make_pair(USERDESCRIPTION, xmlnode.strData));

            xmlnode.strNodeName = "MEMBER/DORMITORY";
            xmlnode.strData = "";
            xml.AccessXmlNode(xmlnode, QUERY);
            mapTermInfo.insert(make_pair(USERDORMITORY, xmlnode.strData));

            back.lstCmdPara.push_back(mapTermInfo);
        }
    }
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
