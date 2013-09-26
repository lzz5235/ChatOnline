#ifndef XMLPARSE_H
#define XMLPARSE_H

#include <QString>
#include "xmlParse/tinystr.h"
#include "xmlParse/tinyxml.h"

class xmlparse
{
public:

    bool Create_Login_XmlFile(QString& szFileName);
    bool Create_Login_Back_XmlFile(QString& szFileName);
    bool Create_Member_XmlFile(QString& szFileName);
    bool Create_TRANS_ADDRESS_XmlFile(QString& szFileName);
    bool Create_TRANS_GET_ADDRESS_XmlFile(QString& szFileName);
    bool Create_TRANS_GET_MEMBER_XmlFile(QString& szFileName);
    bool Create_TRANS_LOGOUT_XmlFile(QString& szFileName);
    bool Create_TRANS_SEND_XmlFile(QString& szFileName);


public:

    bool Read_Login_XmlFile(QString& szFileName);
    bool Read_Login_Back_XmlFile(QString& szFileName);
    bool Read_Member_XmlFile(QString& szFileName);
    bool Read_TRANS_ADDRESS_XmlFile(QString& szFileName);
    bool Read_TRANS_GET_ADDRESS_XmlFile(QString& szFileName);
    bool Read_TRANS_GET_MEMBER_XmlFile(QString& szFileName);
    bool Read_TRANS_LOGOUT_XmlFile(QString& szFileName);
    bool Read_TRANS_SEND_XmlFile(QString& szFileName);

};




#endif // XMLPARSE_H
