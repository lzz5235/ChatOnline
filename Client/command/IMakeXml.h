#ifndef IMAKEXML_H
#define IMAKEXML_H
#include "data.h"

class IMakeXml
{
public:
    virtual string parseCmd2Xml(XMLPARA &para) = 0;
    virtual int parseRspType(string strRsp) = 0;
    virtual int parseRsp(string strRsp, XMLPARA &back) = 0;
    virtual string getLastError() = 0;
    virtual ~IMakeXml()
    {

    }
};

#endif // IMAKEXML_H
