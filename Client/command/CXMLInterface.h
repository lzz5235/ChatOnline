#ifndef CXMLINTERFACE_H
#define CXMLINTERFACE_H
#include "IMakeXml.h"
#include "data.h"
#include <string>

using namespace std;

class CXMLInterface : public IMakeXml
{
protected:
    virtual string xmlLogin(XMLPARA &xmlLogin) = 0;
    virtual string xmlUpdate(XMLPARA &xmlUpdate) = 0;
    virtual string xmlSend(XMLPARA &xmlSend) = 0;
    virtual string xmlLogout(XMLPARA &xmlLogout) = 0;
    virtual string xmlGetAddress(XMLPARA &xmlGetAddress) = 0;
    virtual string xmlTest() = 0;

protected:
    virtual int parseRsp(string strRsp, XMLPARA &back) = 0;
    virtual void RspXmlLogin(string strRsp, XMLPARA &back) = 0;
    virtual void RspXmlGetAddress(string strRsp, XMLPARA &back) = 0;
    virtual void RspXmlUpdate(string strRsp, XMLPARA &back) = 0;
    virtual void RspXmlLogout(string strRsp, XMLPARA &back) = 0;
    virtual void RspXmlSend(string strRsp, XMLPARA &back) = 0;
    virtual void RspXmlTest(string strRsp, XMLPARA &back) = 0;
    virtual void RspXmlResult(string strRsp, XMLPARA &back) = 0;
    virtual void RspXmlLoginInfo(string strRsp, XMLPARA &back) = 0;
    virtual void RspXmlNewUpdate(string strRsp, XMLPARA &back) = 0;
};

#endif // CXMLINTERFACE_H
