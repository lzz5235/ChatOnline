#include "xmlparse.h"
#include <QDebug>

bool xmlparse::Create_Login_XmlFile(QString& szFileName)
{

    try
    {
        TiXmlDocument *myDocument = new TiXmlDocument();
        //创建一个根元素并连接。
        TiXmlElement *RootElement = new TiXmlElement("TRANS_NOTIFICATION");
        myDocument->LinkEndChild(RootElement);

        TiXmlElement *HEAD = new TiXmlElement("HEAD");
        RootElement->LinkEndChild(HEAD);

        //PersonElement->SetAttribute("ID", "1");

        TiXmlElement *VERSION = new TiXmlElement("VERSION");
        TiXmlElement *MESSAGEID = new TiXmlElement("MESSAGEID");
        TiXmlElement *TYPE = new TiXmlElement("TYPE");
        HEAD->LinkEndChild(VERSION);
        HEAD->LinkEndChild(MESSAGEID);
        HEAD->LinkEndChild(TYPE);


        TiXmlText *VERSIONTEXT = new TiXmlText("0.1");

        TiXmlText *MESSAGEIDTEXT = new TiXmlText("0");
        TiXmlText *LOGINTEXT = new TiXmlText("LOGIN");

        VERSION->LinkEndChild(VERSIONTEXT);
        MESSAGEID->LinkEndChild(MESSAGEIDTEXT);
        TYPE->LinkEndChild(LOGINTEXT);

        TiXmlElement *ACTION = new TiXmlElement("ACTION");
        RootElement->LinkEndChild(ACTION);

        TiXmlElement *LOGIN = new TiXmlElement("LOGIN");
        ACTION->LinkEndChild(LOGIN);


        TiXmlElement *USERNAME = new TiXmlElement("USERNAME");
        TiXmlElement *PASSWORD = new TiXmlElement("PASSWORD");
        TiXmlElement *SYSTEM = new TiXmlElement("SYSTEM");
        TiXmlElement *LOGINTIME = new TiXmlElement("LOGINTIME");
        TiXmlElement *STATUS = new TiXmlElement("STATUS");
        LOGIN->LinkEndChild(USERNAME);
        LOGIN->LinkEndChild(PASSWORD);
        LOGIN->LinkEndChild(SYSTEM);
        LOGIN->LinkEndChild(LOGINTIME);
        LOGIN->LinkEndChild(STATUS);


        TiXmlText *USERNAMETEXT = new TiXmlText("charles");
        USERNAME->LinkEndChild(USERNAMETEXT);

        TiXmlText *PASSWORDTEXT = new TiXmlText("wangxuguo");
        PASSWORD->LinkEndChild(PASSWORDTEXT);

        TiXmlText *SYSTEMTEXT = new TiXmlText("OS_WINDOWS");
        SYSTEM->LinkEndChild(SYSTEMTEXT);

        TiXmlText *LOGINTIMETEXT = new TiXmlText("2013-9-16 22:18");
        LOGINTIME->LinkEndChild(LOGINTIMETEXT);

        TiXmlText *STATUSTEXT = new TiXmlText("online");
        STATUS->LinkEndChild(STATUSTEXT);


        myDocument->SaveFile(szFileName.toStdString().c_str());//保存到文件
    }
    catch (QString& e)
    {
        return false;
    }
    return true;
}

bool xmlparse::Read_Login_XmlFile(QString& szFileName,saveStruct &save)
{//读取Xml文件，并遍历
    try
    {
        //创建一个XML的文档对象。
        TiXmlDocument *myDocument = new TiXmlDocument(szFileName.toStdString().c_str());
        myDocument->LoadFile();
        //获得根元素.
        TiXmlElement *RootElement = myDocument->RootElement();

        //qDebug() << RootElement->Value() ;

        TiXmlElement *HEAD = RootElement->FirstChildElement();

        TiXmlElement *VERSION = HEAD->FirstChildElement();
        TiXmlElement *MESSAGEID = VERSION->NextSiblingElement();
        TiXmlElement *TYPE = MESSAGEID->NextSiblingElement();

        TiXmlElement *ACTION = HEAD->NextSiblingElement();
        TiXmlElement *LOGIN = ACTION->FirstChildElement();

        TiXmlElement *USERNAME = LOGIN->FirstChildElement();
        TiXmlElement *PASSWORD = USERNAME->NextSiblingElement();
        TiXmlElement *SYSTEM   = PASSWORD->NextSiblingElement();
        TiXmlElement *LOGINTIME = SYSTEM->NextSiblingElement();
        TiXmlElement *STATUS = LOGINTIME->NextSiblingElement();


        qDebug() << VERSION->FirstChild()->Value() ;
        qDebug() << MESSAGEID->FirstChild()->Value() ;


        save.logInf.account = QString(QLatin1String( USERNAME->FirstChild()->Value() ));
        save.logInf.password = QString(QLatin1String( PASSWORD->FirstChild()->Value() ));
        save.logInf.status = QString(QLatin1String( STATUS->FirstChild()->Value() )).toInt();
        qDebug() << USERNAME->FirstChild()->Value() ;
        qDebug() << PASSWORD->FirstChild()->Value() ;
        qDebug() << SYSTEM->FirstChild()->Value() ;
        qDebug() << LOGINTIME->FirstChild()->Value() ;
        qDebug() << STATUS->FirstChild()->Value() ;

    }
    catch (QString& e)
    {
        return false;
    }
    return true;
}

bool xmlparse::Create_Login_Back_XmlFile(QString& szFileName,saveStruct &save)
{
    try
    {
        TiXmlDocument *myDocument = new TiXmlDocument();
        //创建一个根元素并连接。
        TiXmlElement *RootElement = new TiXmlElement("TRANS_NOTIFICATION");
        myDocument->LinkEndChild(RootElement);

        TiXmlElement *HEAD = new TiXmlElement("HEAD");
        RootElement->LinkEndChild(HEAD);

        //PersonElement->SetAttribute("ID", "1");

        TiXmlElement *VERSION = new TiXmlElement("VERSION");
        TiXmlElement *MESSAGEID = new TiXmlElement("MESSAGEID");
        TiXmlElement *_TYPE = new TiXmlElement("TYPE");
        HEAD->LinkEndChild(VERSION);
        HEAD->LinkEndChild(MESSAGEID);
        HEAD->LinkEndChild(_TYPE);


        TiXmlText *VERSIONTEXT = new TiXmlText("0.1");

        TiXmlText *MESSAGEIDTEXT = new TiXmlText("0");

        TiXmlText *LOGIN_BACKTEXT = new TiXmlText("LOGIN_BACK");

        VERSION->LinkEndChild(VERSIONTEXT);
        MESSAGEID->LinkEndChild(MESSAGEIDTEXT);
        _TYPE->LinkEndChild(LOGIN_BACKTEXT);

        TiXmlElement *ACTION = new TiXmlElement("ACTION");
        RootElement->LinkEndChild(ACTION);

        TiXmlElement *LOGIN_BACK = new TiXmlElement("LOGIN_BACK");
        ACTION->LinkEndChild(LOGIN_BACK);

        TiXmlElement *RESULT = new TiXmlElement("RESULT");
        LOGIN_BACK->LinkEndChild(RESULT);
        TiXmlText *RESULTTEXT = new TiXmlText("SUCCESS");
        RESULT->LinkEndChild(RESULTTEXT);

        TiXmlElement *MEMBERLIST = new TiXmlElement("MEMBERLIST");
        LOGIN_BACK->LinkEndChild(MEMBERLIST);

        TiXmlElement *MEMBER = new TiXmlElement("MEMBER");
        MEMBERLIST->LinkEndChild(MEMBER);

        TiXmlElement *USERNAME = new TiXmlElement("USERNAME");
        MEMBER->LinkEndChild(USERNAME);
        TiXmlText *USERNAMETEXT = new TiXmlText(save.userInf.nickName.toStdString().data());
        USERNAME->LinkEndChild(USERNAMETEXT);


        TiXmlElement *USERID = new TiXmlElement("USERID");
        MEMBER->LinkEndChild(USERID);
        TiXmlText *USERIDTEXT = new TiXmlText(save.userInf.account.toStdString().data());
        USERID->LinkEndChild(USERIDTEXT);

        TiXmlElement *SEX = new TiXmlElement("SEX");
        MEMBER->LinkEndChild(SEX);
        TiXmlText *SEXTEXT = new TiXmlText("male");
        SEX->LinkEndChild(SEXTEXT);

        TiXmlElement *CONTACT = new TiXmlElement("CONTACT");
        MEMBER->LinkEndChild(CONTACT);

        TiXmlElement *CELLPHONE = new TiXmlElement("CELLPHONE");
        CONTACT->LinkEndChild(CELLPHONE);
        TiXmlText *CELLPHONETEXT = new TiXmlText(save.userInf.mobileNumber.toStdString().data());
        CELLPHONE->LinkEndChild(CELLPHONETEXT);

        TiXmlElement *OFFICEPHONE = new TiXmlElement("OFFICEPHONE");
        CONTACT->LinkEndChild(OFFICEPHONE);
        TiXmlText *OFFICEPHONETEXT = new TiXmlText(save.userInf.officephone.toStdString().data());
        OFFICEPHONE->LinkEndChild(OFFICEPHONETEXT);

        TiXmlElement *OTHER_CONTACT = new TiXmlElement("OTHER_CONTACT");
        CONTACT->LinkEndChild(OTHER_CONTACT);

        TiXmlElement *TYPE = new TiXmlElement("TYPE");
        OTHER_CONTACT->LinkEndChild(TYPE);
        TiXmlText *TYPETEXT = new TiXmlText("QQ");
        TYPE->LinkEndChild(TYPETEXT);

        TiXmlElement *CONTENT = new TiXmlElement("CONTENT");
        OTHER_CONTACT->LinkEndChild(CONTENT);
        TiXmlText *CONTENTTEXT = new TiXmlText("none");
        CONTENT->LinkEndChild(CONTENTTEXT);

        TiXmlElement *MAIL = new TiXmlElement("MAIL");
        CONTACT->LinkEndChild(MAIL);
        TiXmlText *MAILTEXT = new TiXmlText(save.userInf.mail.toStdString().data());
        MAIL->LinkEndChild(MAILTEXT);

        TiXmlElement *OTHER_INFORMATION = new TiXmlElement("OTHER_INFORMATION");
        MEMBER->LinkEndChild(OTHER_INFORMATION);
        TiXmlText *OTHER_INFORMATIONTEXT = new TiXmlText("none");
        OTHER_INFORMATION->LinkEndChild(OTHER_INFORMATIONTEXT);

        TiXmlElement *DORMITORY = new TiXmlElement("DORMITORY");
        MEMBER->LinkEndChild(DORMITORY);
        TiXmlText *DORMITORYTEXT = new TiXmlText("none");
        DORMITORY->LinkEndChild(DORMITORYTEXT);

        TiXmlPrinter printer;
        myDocument->Accept(&printer);
        szFileName = QString::fromLocal8Bit(printer.CStr(),-1);
    }
    catch (QString& e)
    {
        return false;
    }
    return true;
}

bool xmlparse::Read_Login_Back_XmlFile(QString& szFileName)
{
    try
    {
        //创建一个XML的文档对象。
        TiXmlDocument *myDocument = new TiXmlDocument(szFileName.toStdString().c_str());
        myDocument->LoadFile();
        //获得根元素.
        TiXmlElement *RootElement = myDocument->RootElement();

        //qDebug() << RootElement->Value() ;

        TiXmlElement *HEAD = RootElement->FirstChildElement();

        TiXmlElement *VERSION = HEAD->FirstChildElement();
        TiXmlElement *MESSAGEID = VERSION->NextSiblingElement();
        TiXmlElement *TYPE = MESSAGEID->NextSiblingElement();

        TiXmlElement *ACTION = HEAD->NextSiblingElement();
        TiXmlElement *LOGIN_BACK = ACTION->FirstChildElement();
        TiXmlElement *RESULT = LOGIN_BACK->FirstChildElement();

        TiXmlElement *MEMBERLIST = RESULT->NextSiblingElement();
        TiXmlElement *MEMBER = MEMBERLIST->FirstChildElement();

        TiXmlElement *USERNAME = MEMBER->FirstChildElement();
        TiXmlElement *USERID = USERNAME->NextSiblingElement();
        TiXmlElement *SEX   = USERID->NextSiblingElement();
        TiXmlElement *CONTACT = SEX->NextSiblingElement();
        TiXmlElement *CELLPHONE = CONTACT->FirstChildElement();
        TiXmlElement *OFFICEPHONE = CELLPHONE->NextSiblingElement();
        TiXmlElement *OTHER_CONTACT = OFFICEPHONE->NextSiblingElement();
        TiXmlElement *_TYPE = OTHER_CONTACT->FirstChildElement();
        TiXmlElement *CONTENT = TYPE->NextSiblingElement();

        TiXmlElement *MAIL = OTHER_CONTACT->NextSiblingElement();
        TiXmlElement *OTHER_INFORMATION = CONTACT->NextSiblingElement();
        TiXmlElement *DORMITORY = OTHER_INFORMATION->NextSiblingElement();

        qDebug() << VERSION->FirstChild()->Value() ;
        qDebug() << MESSAGEID->FirstChild()->Value() ;
        qDebug() << RESULT->FirstChild()->Value() ;
        qDebug() << USERNAME->FirstChild()->Value() ;
        qDebug() << USERID->FirstChild()->Value() ;
        qDebug() << SEX->FirstChild()->Value() ;
        qDebug() << CELLPHONE->FirstChild()->Value() ;
        qDebug() << OFFICEPHONE->FirstChild()->Value() ;
        qDebug() << _TYPE->FirstChild()->Value() ;
        qDebug() << CONTENT->FirstChild()->Value() ;
        qDebug() << MAIL->FirstChild()->Value() ;
        qDebug() << OTHER_INFORMATION->FirstChild()->Value() ;
        qDebug() << DORMITORY->FirstChild()->Value() ;

    }
    catch (QString& e)
    {
        return false;
    }
    return true;
}

bool xmlparse::Create_Member_XmlFile(QString& szFileName,saveStruct &save)
{
    try
    {
        TiXmlDocument *myDocument = new TiXmlDocument();
        //创建一个根元素并连接。
        TiXmlElement *RootElement = new TiXmlElement("MEMBER");
        myDocument->LinkEndChild(RootElement);

        TiXmlElement *USERNAME = new TiXmlElement("USERNAME");
        RootElement->LinkEndChild(USERNAME);
        TiXmlText *USERNAMETEXT = new TiXmlText(" 周庆国 ");
        USERNAME->LinkEndChild(USERNAMETEXT);


        TiXmlElement *USERID = new TiXmlElement("USERID");
        RootElement->LinkEndChild(USERID);
        TiXmlText *USERIDTEXT = new TiXmlText("1");
        USERID->LinkEndChild(USERIDTEXT);

        TiXmlElement *SEX = new TiXmlElement("SEX");
        RootElement->LinkEndChild(SEX);
        TiXmlText *SEXTEXT = new TiXmlText("male");
        SEX->LinkEndChild(SEXTEXT);

        TiXmlElement *CONTACT = new TiXmlElement("CONTACT");
        RootElement->LinkEndChild(CONTACT);

        TiXmlElement *CELLPHONE = new TiXmlElement("CELLPHONE");
        CONTACT->LinkEndChild(CELLPHONE);
        TiXmlText *CELLPHONETEXT = new TiXmlText("18919880252");
        CELLPHONE->LinkEndChild(CELLPHONETEXT);

        TiXmlElement *OFFICEPHONE = new TiXmlElement("OFFICEPHONE");
        CONTACT->LinkEndChild(OFFICEPHONE);
        TiXmlText *OFFICEPHONETEXT = new TiXmlText("0931-3589039");
        OFFICEPHONE->LinkEndChild(OFFICEPHONETEXT);

        TiXmlElement *OTHER_CONTACT = new TiXmlElement("OTHER_CONTACT");
        CONTACT->LinkEndChild(OTHER_CONTACT);

        TiXmlElement *TYPE = new TiXmlElement("TYPE");
        OTHER_CONTACT->LinkEndChild(TYPE);
        TiXmlText *TYPETEXT = new TiXmlText("QQ");
        TYPE->LinkEndChild(TYPETEXT);

        TiXmlElement *CONTENT = new TiXmlElement("CONTENT");
        OTHER_CONTACT->LinkEndChild(CONTENT);
        TiXmlText *CONTENTTEXT = new TiXmlText("");
        CONTENT->LinkEndChild(CONTENTTEXT);

        TiXmlElement *MAIL = new TiXmlElement("MAIL");
        CONTACT->LinkEndChild(MAIL);
        TiXmlText *MAILTEXT = new TiXmlText("zhouqg@lzu.edu.cn");
        MAIL->LinkEndChild(MAILTEXT);

        TiXmlElement *OTHER_INFORMATION = new TiXmlElement("OTHER_INFORMATION");
        RootElement->LinkEndChild(OTHER_INFORMATION);
        TiXmlText *OTHER_INFORMATIONTEXT = new TiXmlText("");
        OTHER_INFORMATION->LinkEndChild(OTHER_INFORMATIONTEXT);

        TiXmlElement *DORMITORY = new TiXmlElement("DORMITORY");
        RootElement->LinkEndChild(DORMITORY);
        TiXmlText *DORMITORYTEXT = new TiXmlText("");
        DORMITORY->LinkEndChild(DORMITORYTEXT);


        myDocument->SaveFile(szFileName.toStdString().c_str());//保存到文件
    }
    catch (QString& e)
    {
        return false;
    }
    return true;
}

bool xmlparse::Read_Member_XmlFile(QString& szFileName,saveStruct &save)
{
    try
    {
        TiXmlDocument *myDocument = new TiXmlDocument(szFileName.toStdString().c_str());
        myDocument->LoadFile();

        TiXmlElement *MEMBER = myDocument->RootElement();
        TiXmlElement *USERNAME = MEMBER->FirstChildElement();
        TiXmlElement *USERID = USERNAME->NextSiblingElement();
        TiXmlElement *SEX   = USERID->NextSiblingElement();
        TiXmlElement *CONTACT = SEX->NextSiblingElement();
        TiXmlElement *CELLPHONE = CONTACT->FirstChildElement();
        TiXmlElement *OFFICEPHONE = CELLPHONE->NextSiblingElement();
        TiXmlElement *OTHER_CONTACT = OFFICEPHONE->NextSiblingElement();
        TiXmlElement *TYPE = OTHER_CONTACT->FirstChildElement();
        TiXmlElement *CONTENT = TYPE->NextSiblingElement();

        TiXmlElement *MAIL = OTHER_CONTACT->NextSiblingElement();
        TiXmlElement *OTHER_INFORMATION = CONTACT->NextSiblingElement();
        TiXmlElement *DORMITORY = OTHER_INFORMATION->NextSiblingElement();

        qDebug() << USERNAME->FirstChild()->Value() ;
        qDebug() << USERID->FirstChild()->Value() ;
        qDebug() << SEX->FirstChild()->Value() ;
        qDebug() << CELLPHONE->FirstChild()->Value() ;
        qDebug() << OFFICEPHONE->FirstChild()->Value() ;
        qDebug() << TYPE->FirstChild()->Value() ;
        qDebug() << CONTENT->FirstChild()->Value() ;
        qDebug() << MAIL->FirstChild()->Value() ;
        qDebug() << OTHER_INFORMATION->FirstChild()->Value() ;
        qDebug() << DORMITORY->FirstChild()->Value() ;

    }
    catch (QString& e)
    {
        return false;
    }
    return true;
}

bool xmlparse::Create_TRANS_ADDRESS_XmlFile(QString& szFileName)
{
    try
    {
        TiXmlDocument *myDocument = new TiXmlDocument();
        //创建一个根元素并连接。
        TiXmlElement *RootElement = new TiXmlElement("TRANS_NOTIFICATION");
        myDocument->LinkEndChild(RootElement);

        TiXmlElement *HEAD = new TiXmlElement("HEAD");
        RootElement->LinkEndChild(HEAD);

        //PersonElement->SetAttribute("ID", "1");

        TiXmlElement *VERSION = new TiXmlElement("VERSION");
        TiXmlElement *MESSAGEID = new TiXmlElement("MESSAGEID");
        TiXmlElement *_TYPE = new TiXmlElement("TYPE");
        HEAD->LinkEndChild(VERSION);
        HEAD->LinkEndChild(MESSAGEID);
        HEAD->LinkEndChild(_TYPE);

        TiXmlText *VERSIONTEXT = new TiXmlText("0.1");

        TiXmlText *MESSAGEIDTEXT = new TiXmlText("0");
        TiXmlText *GET_ADDRESSTEXT = new TiXmlText("GET_ADDRESS");

        VERSION->LinkEndChild(VERSIONTEXT);
        MESSAGEID->LinkEndChild(MESSAGEIDTEXT);
        _TYPE->LinkEndChild(GET_ADDRESSTEXT);

        TiXmlElement *ACTION = new TiXmlElement("ACTION");
        RootElement->LinkEndChild(ACTION);

        TiXmlElement *GET_ADDRESS = new TiXmlElement("GET_ADDRESS");
        ACTION->LinkEndChild(GET_ADDRESS);

        TiXmlElement *MEMBER_LIST = new TiXmlElement("MEMBER_LIST");
        GET_ADDRESS->LinkEndChild(MEMBER_LIST);

        TiXmlElement *MEMBER = new TiXmlElement("MEMBER");
        MEMBER_LIST->LinkEndChild(MEMBER);

        TiXmlElement *USERNAME = new TiXmlElement("USERNAME");
        MEMBER->LinkEndChild(USERNAME);
        TiXmlText *USERNAMETEXT = new TiXmlText(" 周庆国 ");
        USERNAME->LinkEndChild(USERNAMETEXT);


        TiXmlElement *USERID = new TiXmlElement("USERID");
        MEMBER->LinkEndChild(USERID);
        TiXmlText *USERIDTEXT = new TiXmlText("1");
        USERID->LinkEndChild(USERIDTEXT);

        TiXmlElement *SEX = new TiXmlElement("SEX");
        MEMBER->LinkEndChild(SEX);
        TiXmlText *SEXTEXT = new TiXmlText("male");
        SEX->LinkEndChild(SEXTEXT);

        TiXmlElement *CONTACT = new TiXmlElement("CONTACT");
        MEMBER->LinkEndChild(CONTACT);

        TiXmlElement *CELLPHONE = new TiXmlElement("CELLPHONE");
        CONTACT->LinkEndChild(CELLPHONE);
        TiXmlText *CELLPHONETEXT = new TiXmlText("18919880252");
        CELLPHONE->LinkEndChild(CELLPHONETEXT);

        TiXmlElement *OFFICEPHONE = new TiXmlElement("OFFICEPHONE");
        CONTACT->LinkEndChild(OFFICEPHONE);
        TiXmlText *OFFICEPHONETEXT = new TiXmlText("0931-3589039");
        OFFICEPHONE->LinkEndChild(OFFICEPHONETEXT);

        TiXmlElement *OTHER_CONTACT = new TiXmlElement("OTHER_CONTACT");
        CONTACT->LinkEndChild(OTHER_CONTACT);

        TiXmlElement *TYPE = new TiXmlElement("TYPE");
        OTHER_CONTACT->LinkEndChild(TYPE);
        TiXmlText *TYPETEXT = new TiXmlText("QQ");
        TYPE->LinkEndChild(TYPETEXT);

        TiXmlElement *CONTENT = new TiXmlElement("CONTENT");
        OTHER_CONTACT->LinkEndChild(CONTENT);
        TiXmlText *CONTENTTEXT = new TiXmlText("none");
        CONTENT->LinkEndChild(CONTENTTEXT);

        TiXmlElement *MAIL = new TiXmlElement("MAIL");
        CONTACT->LinkEndChild(MAIL);
        TiXmlText *MAILTEXT = new TiXmlText("zhouqg@lzu.edu.cn");
        MAIL->LinkEndChild(MAILTEXT);

        TiXmlElement *OTHER_INFORMATION = new TiXmlElement("OTHER_INFORMATION");
        MEMBER->LinkEndChild(OTHER_INFORMATION);
        TiXmlText *OTHER_INFORMATIONTEXT = new TiXmlText("none");
        OTHER_INFORMATION->LinkEndChild(OTHER_INFORMATIONTEXT);

        TiXmlElement *DORMITORY = new TiXmlElement("DORMITORY");
        MEMBER->LinkEndChild(DORMITORY);
        TiXmlText *DORMITORYTEXT = new TiXmlText("none");
        DORMITORY->LinkEndChild(DORMITORYTEXT);


        //if faild ,put result in this doc <RESULT>NO username</RESULT>

        myDocument->SaveFile(szFileName.toStdString().c_str());//保存到文件
    }
    catch (QString& e)
    {
        return false;
    }
    return true;
}

bool xmlparse::Read_TRANS_ADDRESS_XmlFile(QString& szFileName,saveStruct &save)
{
    try
    {
        //创建一个XML的文档对象。
        TiXmlDocument *myDocument = new TiXmlDocument(szFileName.toStdString().c_str());
        myDocument->LoadFile();
        //获得根元素.
        TiXmlElement *RootElement = myDocument->RootElement();

        //qDebug() << RootElement->Value() ;

        TiXmlElement *HEAD = RootElement->FirstChildElement();

        TiXmlElement *VERSION = HEAD->FirstChildElement();
        TiXmlElement *MESSAGEID = VERSION->NextSiblingElement();
        TiXmlElement *_TYPE = MESSAGEID->NextSiblingElement();

        TiXmlElement *ACTION = HEAD->NextSiblingElement();
        TiXmlElement *GET_ADDRESS = ACTION->FirstChildElement();


        TiXmlElement *MEMBER_LIST = GET_ADDRESS->FirstChildElement();

        TiXmlElement *MEMBER = MEMBER_LIST->FirstChildElement();

        TiXmlElement *USERNAME = MEMBER->FirstChildElement();
        TiXmlElement *USERID = USERNAME->NextSiblingElement();
        TiXmlElement *SEX   = USERID->NextSiblingElement();
        TiXmlElement *CONTACT = SEX->NextSiblingElement();
        TiXmlElement *CELLPHONE = CONTACT->FirstChildElement();
        TiXmlElement *OFFICEPHONE = CELLPHONE->NextSiblingElement();
        TiXmlElement *OTHER_CONTACT = OFFICEPHONE->NextSiblingElement();
        TiXmlElement *TYPE = OTHER_CONTACT->FirstChildElement();
        TiXmlElement *CONTENT = TYPE->NextSiblingElement();

        TiXmlElement *MAIL = OTHER_CONTACT->NextSiblingElement();
        TiXmlElement *OTHER_INFORMATION = CONTACT->NextSiblingElement();
        TiXmlElement *DORMITORY = OTHER_INFORMATION->NextSiblingElement();

        qDebug() << VERSION->FirstChild()->Value() ;
        qDebug() << MESSAGEID->FirstChild()->Value() ;

        qDebug() << USERNAME->FirstChild()->Value() ;
        qDebug() << USERID->FirstChild()->Value() ;
        qDebug() << SEX->FirstChild()->Value() ;
        qDebug() << CELLPHONE->FirstChild()->Value() ;
        qDebug() << OFFICEPHONE->FirstChild()->Value() ;
        qDebug() << TYPE->FirstChild()->Value() ;
        qDebug() << CONTENT->FirstChild()->Value() ;
        qDebug() << MAIL->FirstChild()->Value() ;
        qDebug() << OTHER_INFORMATION->FirstChild()->Value() ;
        qDebug() << DORMITORY->FirstChild()->Value() ;

    }
    catch (QString& e)
    {
        return false;
    }
    return true;
}

bool xmlparse::Create_TRANS_GET_ADDRESS_XmlFile(QString& szFileName)
{
    try
    {
        TiXmlDocument *myDocument = new TiXmlDocument();
        //创建一个根元素并连接。
        TiXmlElement *RootElement = new TiXmlElement("TRANS_NOTIFICATION");
        myDocument->LinkEndChild(RootElement);

        TiXmlElement *HEAD = new TiXmlElement("HEAD");
        RootElement->LinkEndChild(HEAD);

        //PersonElement->SetAttribute("ID", "1");

        TiXmlElement *VERSION = new TiXmlElement("VERSION");
        TiXmlElement *MESSAGEID = new TiXmlElement("MESSAGEID");
        TiXmlElement *TYPE = new TiXmlElement("TYPE");
        HEAD->LinkEndChild(VERSION);
        HEAD->LinkEndChild(MESSAGEID);
        HEAD->LinkEndChild(TYPE);


        TiXmlText *VERSIONTEXT = new TiXmlText("0.1");

        TiXmlText *MESSAGEIDTEXT = new TiXmlText("0");

        TiXmlText *GET_ADDRESSTEXT = new TiXmlText("GET_ADDRESS");

        VERSION->LinkEndChild(VERSIONTEXT);
        MESSAGEID->LinkEndChild(MESSAGEIDTEXT);
        TYPE->LinkEndChild(GET_ADDRESSTEXT);

        TiXmlElement *ACTION = new TiXmlElement("ACTION");
        RootElement->LinkEndChild(ACTION);

        TiXmlElement *GET_ADDRESS = new TiXmlElement("GET_ADDRESS");
        ACTION->LinkEndChild(GET_ADDRESS);
        TiXmlText *ADDRESSTEXT = new TiXmlText("-1");
        GET_ADDRESS->LinkEndChild(ADDRESSTEXT);

        myDocument->SaveFile(szFileName.toStdString().c_str());//保存到文件
    }
    catch (QString& e)
    {
        return false;
    }
    return true;
}

bool xmlparse::Read_TRANS_GET_ADDRESS_XmlFile(QString& szFileName,saveStruct &save)
{
    try
    {
        //创建一个XML的文档对象。
        TiXmlDocument *myDocument = new TiXmlDocument(szFileName.toStdString().c_str());
        myDocument->LoadFile();
        //获得根元素.
        TiXmlElement *RootElement = myDocument->RootElement();

        //qDebug() << RootElement->Value() ;

        TiXmlElement *HEAD = RootElement->FirstChildElement();

        TiXmlElement *VERSION = HEAD->FirstChildElement();
        TiXmlElement *MESSAGEID = VERSION->NextSiblingElement();
        TiXmlElement *TYPE = MESSAGEID->NextSiblingElement();

        TiXmlElement *ACTION = HEAD->NextSiblingElement();
        TiXmlElement *GET_ADDRESS = ACTION->FirstChildElement();

        qDebug() << VERSION->FirstChild()->Value() ;
        qDebug() << MESSAGEID->FirstChild()->Value() ;

        qDebug() << GET_ADDRESS->FirstChild()->Value() ;

    }
    catch (QString& e)
    {
        return false;
    }
    return true;
}

//bool xmlparse::Create_TRANS_GET_MEMBER_XmlFile(QString& szFileName)
//{
//    try
//    {
//        TiXmlDocument *myDocument = new TiXmlDocument();
//        //创建一个根元素并连接。
//        TiXmlElement *RootElement = new TiXmlElement("TRANS_ADDRESS");
//        myDocument->LinkEndChild(RootElement);

//        TiXmlElement *HEAD = new TiXmlElement("HEAD");
//        RootElement->LinkEndChild(HEAD);

//        //PersonElement->SetAttribute("ID", "1");

//        TiXmlElement *VERSION = new TiXmlElement("VERSION");
//        TiXmlElement *MESSAGEID = new TiXmlElement("MESSAGEID");
//        HEAD->LinkEndChild(VERSION);
//        HEAD->LinkEndChild(MESSAGEID);


//        TiXmlText *VERSIONTEXT = new TiXmlText("0.1");

//        TiXmlText *MESSAGEIDTEXT = new TiXmlText("0");

//        VERSION->LinkEndChild(VERSIONTEXT);
//        MESSAGEID->LinkEndChild(MESSAGEIDTEXT);

//        TiXmlElement *ACTION = new TiXmlElement("ACTION");
//        RootElement->LinkEndChild(ACTION);

//        TiXmlElement *GET_MEMBER = new TiXmlElement("GET_MEMBER");
//        ACTION->LinkEndChild(GET_MEMBER);
//        TiXmlText *MEMBERTEXT = new TiXmlText("-1");
//        GET_MEMBER->LinkEndChild(MEMBERTEXT);

//        myDocument->SaveFile(szFileName.toStdString().c_str());//保存到文件
//    }
//    catch (QString& e)
//    {
//        return false;
//    }
//    return true;
//}

//bool xmlparse::Read_TRANS_GET_MEMBER_XmlFile(QString& szFileName)
//{
//    try
//    {
//        //创建一个XML的文档对象。
//        TiXmlDocument *myDocument = new TiXmlDocument(szFileName.toStdString().c_str());
//        myDocument->LoadFile();
//        //获得根元素.
//        TiXmlElement *RootElement = myDocument->RootElement();

//        //qDebug() << RootElement->Value() ;

//        TiXmlElement *HEAD = RootElement->FirstChildElement();

//        TiXmlElement *VERSION = HEAD->FirstChildElement();
//        TiXmlElement *MESSAGEID = VERSION->NextSiblingElement();

//        TiXmlElement *ACTION = HEAD->NextSiblingElement();
//        TiXmlElement *GET_MEMBER = ACTION->FirstChildElement();

//        qDebug() << VERSION->FirstChild()->Value() ;
//        qDebug() << MESSAGEID->FirstChild()->Value() ;

//        qDebug() << GET_MEMBER->FirstChild()->Value() ;

//    }
//    catch (QString& e)
//    {
//        return false;
//    }
//    return true;
//}

bool xmlparse::Create_TRANS_LOGOUT_XmlFile(QString& szFileName)
{
    try
    {
        TiXmlDocument *myDocument = new TiXmlDocument();
        //创建一个根元素并连接。
        TiXmlElement *RootElement = new TiXmlElement("TRANS_NOTIFICATION");
        myDocument->LinkEndChild(RootElement);

        TiXmlElement *HEAD = new TiXmlElement("HEAD");
        RootElement->LinkEndChild(HEAD);

        //PersonElement->SetAttribute("ID", "1");

        TiXmlElement *VERSION = new TiXmlElement("VERSION");
        TiXmlElement *MESSAGEID = new TiXmlElement("MESSAGEID");
        TiXmlElement *TYPE = new TiXmlElement("TYPE");
        HEAD->LinkEndChild(VERSION);
        HEAD->LinkEndChild(MESSAGEID);
        HEAD->LinkEndChild(TYPE);


        TiXmlText *VERSIONTEXT = new TiXmlText("0.1");

        TiXmlText *MESSAGEIDTEXT = new TiXmlText("0");
        TiXmlText *LOGOUTTEXT = new TiXmlText("LOGOUT");

        VERSION->LinkEndChild(VERSIONTEXT);
        MESSAGEID->LinkEndChild(MESSAGEIDTEXT);
        TYPE->LinkEndChild(LOGOUTTEXT);

        TiXmlElement *ACTION = new TiXmlElement("ACTION");
        RootElement->LinkEndChild(ACTION);

        TiXmlElement *LOGOUT = new TiXmlElement("LOGOUT");
        ACTION->LinkEndChild(LOGOUT);

        TiXmlElement *USERNAME = new TiXmlElement("USERNAME");
        LOGOUT->LinkEndChild(USERNAME);

        TiXmlText *USERNAMETEXT = new TiXmlText("Charles");
        USERNAME->LinkEndChild(USERNAMETEXT);

        myDocument->SaveFile(szFileName.toStdString().c_str());//保存到文件
    }
    catch (QString& e)
    {
        return false;
    }
    return true;
}


bool xmlparse::Read_TRANS_LOGOUT_XmlFile(QString& szFileName,saveStruct &save)
{
    try
    {
        //创建一个XML的文档对象。
        TiXmlDocument *myDocument = new TiXmlDocument(szFileName.toStdString().c_str());
        myDocument->LoadFile();
        //获得根元素.
        TiXmlElement *RootElement = myDocument->RootElement();

        //qDebug() << RootElement->Value() ;

        TiXmlElement *HEAD = RootElement->FirstChildElement();

        TiXmlElement *VERSION = HEAD->FirstChildElement();
        TiXmlElement *MESSAGEID = VERSION->NextSiblingElement();
        TiXmlElement *TYPE = MESSAGEID->NextSiblingElement();

        TiXmlElement *ACTION = HEAD->NextSiblingElement();
        TiXmlElement *LOGOUT = ACTION->FirstChildElement();
        TiXmlElement *USERNAME = LOGOUT->FirstChildElement();

        qDebug() << VERSION->FirstChild()->Value() ;
        qDebug() << MESSAGEID->FirstChild()->Value() ;

        save.status = OFFLINE;

        qDebug() << USERNAME->FirstChild()->Value() ;

    }
    catch (QString& e)
    {
        return false;
    }
    return true;
}


bool xmlparse::Create_TRANS_SEND_XmlFile(QString& szFileName)
{
    try
    {
        TiXmlDocument *myDocument = new TiXmlDocument();
        //创建一个根元素并连接。
        TiXmlElement *RootElement = new TiXmlElement("TRANS_NOTIFICATION");
        myDocument->LinkEndChild(RootElement);

        TiXmlElement *HEAD = new TiXmlElement("HEAD");
        RootElement->LinkEndChild(HEAD);

        //PersonElement->SetAttribute("ID", "1");

        TiXmlElement *VERSION = new TiXmlElement("VERSION");
        TiXmlElement *MESSAGEID = new TiXmlElement("MESSAGEID");
        TiXmlElement *TYPE = new TiXmlElement("TYPE");
        HEAD->LinkEndChild(VERSION);
        HEAD->LinkEndChild(MESSAGEID);
        HEAD->LinkEndChild(TYPE);


        TiXmlText *VERSIONTEXT = new TiXmlText("0.1");

        TiXmlText *MESSAGEIDTEXT = new TiXmlText("0");
        TiXmlText *SENDTEXT = new TiXmlText("SEND");

        VERSION->LinkEndChild(VERSIONTEXT);
        MESSAGEID->LinkEndChild(MESSAGEIDTEXT);
        TYPE->LinkEndChild(SENDTEXT);

        TiXmlElement *ACTION = new TiXmlElement("ACTION");
        RootElement->LinkEndChild(ACTION);

        TiXmlElement *SEND = new TiXmlElement("SEND");
        ACTION->LinkEndChild(SEND);

        TiXmlElement *MESSAGE = new TiXmlElement("MESSAGE");
        SEND->LinkEndChild(MESSAGE);

        TiXmlElement *FROM = new TiXmlElement("FROM");
        MESSAGE->LinkEndChild(FROM);
        TiXmlElement *To = new TiXmlElement("To");
        MESSAGE->LinkEndChild(To);


        TiXmlElement *USERID1 = new TiXmlElement("USERID");
        FROM->LinkEndChild(USERID1);
        TiXmlText *USERIDTEXT = new TiXmlText("1");
        USERID1->LinkEndChild(USERIDTEXT);

        TiXmlElement *NICKNAME1 = new TiXmlElement("NICKNAME");
        FROM->LinkEndChild(NICKNAME1);
        TiXmlText *NICKNAMETEXT = new TiXmlText("huddy");
        NICKNAME1->LinkEndChild(NICKNAMETEXT);

        TiXmlElement *MESSAGESENDTIME1 = new TiXmlElement("MESSAGESENDTIME");
        FROM->LinkEndChild(MESSAGESENDTIME1);
        TiXmlText *MESSAGESENDTIMETEXT1 = new TiXmlText("2013-9-13 18:00");
        MESSAGESENDTIME1->LinkEndChild(MESSAGESENDTIMETEXT1);



        TiXmlElement *USERID2 = new TiXmlElement("USERID");
        To->LinkEndChild(USERID2);
        TiXmlText *USERIDTEXT2 = new TiXmlText("10");
        USERID2->LinkEndChild(USERIDTEXT2);

        TiXmlElement *NICKNAME2 = new TiXmlElement("NICKNAME");
        To->LinkEndChild(NICKNAME2);
        TiXmlText *NICKNAMETEXT2 = new TiXmlText("shengyong");
        NICKNAME2->LinkEndChild(NICKNAMETEXT2);

        TiXmlElement *MESSAGESENDTIME2 = new TiXmlElement("MESSAGESENDTIME");
        To->LinkEndChild(MESSAGESENDTIME2);
        TiXmlText *MESSAGESENDTIMETEXT2 = new TiXmlText("2013-9-13 18:01");
        MESSAGESENDTIME2->LinkEndChild(MESSAGESENDTIMETEXT2);

        TiXmlElement *BROADCAST = new TiXmlElement("BROADCAST");
        MESSAGE->LinkEndChild(BROADCAST);
        TiXmlText *BROADCASTTEXT = new TiXmlText("false");
        BROADCAST->LinkEndChild(BROADCASTTEXT);

        TiXmlElement *CONTENT = new TiXmlElement("CONTENT");
        MESSAGE->LinkEndChild(CONTENT);
        TiXmlText *CONTENTTEXT = new TiXmlText("你好啊，你叫啥？");
        CONTENT->LinkEndChild(CONTENTTEXT);

        myDocument->SaveFile(szFileName.toStdString().c_str());//保存到文件
    }
    catch (QString& e)
    {
        return false;
    }
    return true;
}

bool xmlparse::Create_RESULT_XmlFile(QString &szFileName)
{
    try
    {
        TiXmlDocument *myDocument = new TiXmlDocument();
        //创建一个根元素并连接。
        TiXmlElement *RootElement = new TiXmlElement("TRANS_NOTIFICATION");
        myDocument->LinkEndChild(RootElement);

        TiXmlElement *HEAD = new TiXmlElement("HEAD");
        RootElement->LinkEndChild(HEAD);

        //PersonElement->SetAttribute("ID", "1");

        TiXmlElement *VERSION = new TiXmlElement("VERSION");
        TiXmlElement *MESSAGEID = new TiXmlElement("MESSAGEID");
        TiXmlElement *TYPE = new TiXmlElement("TYPE");
        HEAD->LinkEndChild(VERSION);
        HEAD->LinkEndChild(MESSAGEID);
        HEAD->LinkEndChild(TYPE);


        TiXmlText *VERSIONTEXT = new TiXmlText("0.1");

        TiXmlText *MESSAGEIDTEXT = new TiXmlText("0");
        TiXmlText *RESULTTEXT = new TiXmlText("RESULT");

        VERSION->LinkEndChild(VERSIONTEXT);
        MESSAGEID->LinkEndChild(MESSAGEIDTEXT);
        TYPE->LinkEndChild(RESULTTEXT);

        TiXmlElement *ACTION = new TiXmlElement("ACTION");
        RootElement->LinkEndChild(ACTION);

        TiXmlElement *ACK = new TiXmlElement("ACK");
        ACTION->LinkEndChild(ACK);
        TiXmlElement *RESULT = new TiXmlElement("RESULT");
        ACTION->LinkEndChild(RESULT);

        TiXmlText *ACKTEXT = new TiXmlText("200");
        ACK->LinkEndChild(ACKTEXT);

        TiXmlText *RESTEXT = new TiXmlText("null");
        RESULT->LinkEndChild(RESTEXT);

        TiXmlPrinter printer;
        myDocument->Accept(&printer);
        szFileName = QString::fromLocal8Bit(printer.CStr(),-1);
    }
    catch (QString& e)
    {
        return false;
    }
    return true;
}


bool xmlparse::Read_TRANS_SEND_XmlFile(QString& szFileName,saveStruct &save)
{
    try
    {
        //创建一个XML的文档对象。
        TiXmlDocument *myDocument = new TiXmlDocument(szFileName.toStdString().c_str());
        myDocument->LoadFile();
        //获得根元素.
        TiXmlElement *RootElement = myDocument->RootElement();

        //qDebug() << RootElement->Value() ;

        TiXmlElement *HEAD = RootElement->FirstChildElement();

        TiXmlElement *VERSION = HEAD->FirstChildElement();
        TiXmlElement *MESSAGEID = VERSION->NextSiblingElement();
         TiXmlElement *TYPE = MESSAGEID->NextSiblingElement();

        TiXmlElement *ACTION = HEAD->NextSiblingElement();
        TiXmlElement *SEND = ACTION->FirstChildElement();
        TiXmlElement *MESSAGE = SEND->FirstChildElement();
        TiXmlElement *FROM = MESSAGE->FirstChildElement();

        TiXmlElement *USERID1 = FROM->FirstChildElement();
        TiXmlElement *NICKNAME1 = USERID1->NextSiblingElement();
        TiXmlElement *MESSAGEARRIVETIME1 = NICKNAME1->NextSiblingElement();

        TiXmlElement *TO = FROM->NextSiblingElement();
        TiXmlElement *USERID2 = TO->FirstChildElement();
        TiXmlElement *NICKNAME2 = USERID2->NextSiblingElement();
        TiXmlElement *MESSAGEARRIVETIME2 = NICKNAME2->NextSiblingElement();

        TiXmlElement *BROADCAST = TO->NextSiblingElement();
        TiXmlElement *CONTENT = BROADCAST->NextSiblingElement();

        qDebug() << VERSION->FirstChild()->Value() ;
        qDebug() << MESSAGEID->FirstChild()->Value() ;

        save.message.fromfriendid = QString(QLatin1String(USERID1->FirstChild()->Value())).toInt();
        save.message.fromfriend = QString(QLatin1String(NICKNAME1->FirstChild()->Value()));
        save.message.DateSend = QString(QLatin1String(MESSAGEARRIVETIME1->FirstChild()->Value()));
        qDebug() << USERID1->FirstChild()->Value() ;
        qDebug() << NICKNAME1->FirstChild()->Value() ;
        qDebug() << MESSAGEARRIVETIME1->FirstChild()->Value() ;

        save.message.tofriendid = QString(QLatin1String(USERID2->FirstChild()->Value())).toInt();
        save.message.tofriend = QString(QLatin1String(NICKNAME2->FirstChild()->Value()));
        save.message.DateRec = QString(QLatin1String(MESSAGEARRIVETIME2->FirstChild()->Value()));
        qDebug() << USERID2->FirstChild()->Value() ;
        qDebug() << NICKNAME2->FirstChild()->Value() ;
        qDebug() << MESSAGEARRIVETIME2->FirstChild()->Value() ;

        save.message.BROADCAST = QString(QLatin1String(BROADCAST->FirstChild()->Value())).toInt();
        save.message.text = QString(QLatin1String(CONTENT->FirstChild()->Value()));
        qDebug() << BROADCAST->FirstChild()->Value() ;
        qDebug() << CONTENT->FirstChild()->Value() ;

    }
    catch (QString& e)
    {
        return false;
    }
    return true;
}


qint32 xmlparse::ReadXMLFromClient(const QString string)
{
    TiXmlDocument *myDocument = new TiXmlDocument(string.toStdString().c_str());
    myDocument->LoadFile();

    TiXmlElement *RootElement = myDocument->RootElement();
    TiXmlElement *HEAD = RootElement->FirstChildElement();
    TiXmlElement *TYPE = HEAD->FirstChildElement()->NextSiblingElement()->NextSiblingElement();

    if("LOGIN" ==QString(QLatin1String(TYPE->Value())))
    {
        return LOGIN;
    }
    else if ("UPDATE" == QString(QLatin1String(TYPE->Value())))
    {
        return CHANGE_INFORMATION;
    }
    else if("SEND" == QString(QLatin1String(TYPE->Value())))
    {
            return HAVE_MESSAGE;
    }
    else if("GET_ADDRESS" == QString(QLatin1String(TYPE->Value())))
    {
        return GET_FRIEND_INFORMATION;
    }
    else if("LOGOUT" == QString(QLatin1String(TYPE->Value())))
    {
        return QUIT;
    }
    else if("TEST"==QString(QLatin1String(TYPE->Value())))
    {
        return CHECK_CONNECTION;
    }
    else
    {
        return QUIT;
    }
}
