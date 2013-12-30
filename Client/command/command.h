#ifndef COMMAND_H
#define COMMAND_H
#include "data.h"
#include "utilities/FuncTools.h"
#include "IMakeXml.h"
#include "CXMLInterface.h"
#include "XMLBuild.h"
#include "xml/SimpleXml.h"
#include <QDebug>

class CCommand : public CXMLInterface
{
public:
    CCommand(float version);
    int init(float version);
    string parseCmd2Xml(XMLPARA &para);
    int parseRspType(string strRsp);
    int parseRsp(string strRsp, XMLPARA &back);
    string getLastError();

protected:
    virtual string xmlLogin(XMLPARA &xmlLogin);
    virtual string xmlUpdate(XMLPARA &xmlUpdate);
    virtual string xmlSend(XMLPARA &xmlSend);
    virtual string xmlLogout(XMLPARA &xmlLogout);
    virtual string xmlGetAddress(XMLPARA &xmlGetAddress);
    virtual string xmlTest();

protected:
    virtual int parseRspXml(string strRsp, XMLPARA &back);
    virtual void RspXmlLogin(string strRsp, XMLPARA &back);
    virtual void RspXmlGetAddress(string strRsp, XMLPARA &back);
    virtual void RspXmlUpdate(string strRsp, XMLPARA &back);
    virtual void RspXmlLogout(string strRsp, XMLPARA &back);
    virtual void RspXmlSend(string strRsp, XMLPARA &back);
    virtual void RspXmlTest(string strRsp, XMLPARA &back);
    virtual void RspXmlResult(string strRsp, XMLPARA &back);
    virtual void RspXmlLoginInfo(string strRsp, XMLPARA &back);
    virtual void RspXmlNewUpdate(string strRsp, XMLPARA &back);

private:
    string getVersion();

private:
    string m_strError;
    float m_version;
    CXMLBuild m_xml;
    string m_messageID;
};

#endif // COMMAND_H
