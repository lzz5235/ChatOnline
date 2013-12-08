#ifndef XMLPARSE_H
#define XMLPARSE_H

#include <QString>
#include <QVector>
#include "xmlParse/tinystr.h"
#include "xmlParse/tinyxml.h"
#include "protocol.h"

class xmlparse
{
public:

    bool Create_TRANS_ADDRESS_XmlFile(QString& szFileName,saveStruct &save);
    bool Create_TRANS_UPDATE_XmlFile(QString& szFileName,saveStruct &save);
    bool Create_TRANS_SEND_XmlFile(QString& szFileName,saveStruct &save);
    bool Create_TRANS_LOGIN_BACK_XmlFile(QString& szFileName,saveStruct &save);
    bool Create_RESULT_XmlFile(QString &szFileName);


public:

    bool Read_Login_XmlFile(QString& szFileName,saveStruct &save);
    bool Read_TRANS_GET_ADDRESS_XmlFile(QString& szFileName,saveStruct &save);
    bool Read_TRANS_UPDATE_XmlFile(QString& szFileName,saveStruct &save);
    bool Read_TRANS_LOGOUT_XmlFile(QString& szFileName,saveStruct &save);
    bool Read_TRANS_SEND_XmlFile(QString& szFileName,saveStruct &save);

public:

    qint32 ReadXMLFromClient(const QString string);
};




#endif // XMLPARSE_H
