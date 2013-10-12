#include "xmlparse.h"
#include <QDebug>

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
        qDebug() << TYPE->FirstChild()->Value() ;
        qDebug() << USERNAME->FirstChild()->Value() ;
        qDebug() << PASSWORD->FirstChild()->Value() ;
        qDebug() << SYSTEM->FirstChild()->Value() ;
        qDebug() << LOGINTIME->FirstChild()->Value() ;
        qDebug() << STATUS->FirstChild()->Value() ;

        save.logInf.account = QString(QLatin1String( USERNAME->FirstChild()->Value() ));
        save.logInf.password = QString(QLatin1String( PASSWORD->FirstChild()->Value() ));
        save.logInf.status = QString(QLatin1String( STATUS->FirstChild()->Value() )).toInt();


    }
    catch (QString& e)
    {
        return false;
    }
    return true;
}

bool xmlparse::Create_TRANS_ADDRESS_XmlFile(QString& szFileName,saveStruct &save)
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
        TiXmlText *GET_ADDRESSTEXT = new TiXmlText("ADDRESS");

        VERSION->LinkEndChild(VERSIONTEXT);
        MESSAGEID->LinkEndChild(MESSAGEIDTEXT);
        _TYPE->LinkEndChild(GET_ADDRESSTEXT);

        TiXmlElement *ACTION = new TiXmlElement("ACTION");
        RootElement->LinkEndChild(ACTION);

        TiXmlElement *GET_ADDRESS = new TiXmlElement("GET_ADDRESS");
        ACTION->LinkEndChild(GET_ADDRESS);

        TiXmlElement *MEMBER_LIST = new TiXmlElement("MEMBER_LIST");
        GET_ADDRESS->LinkEndChild(MEMBER_LIST);

        QVector<FriendInformation> ::Iterator i = save.friendsVec.begin();

        while(i!= save.friendsVec.end())
        {
            TiXmlElement *MEMBER = new TiXmlElement("MEMBER");
            MEMBER_LIST->LinkEndChild(MEMBER);
            TiXmlElement *USERNAME = new TiXmlElement("USERNAME");
            MEMBER->LinkEndChild(USERNAME);
            TiXmlText *USERNAMETEXT = new TiXmlText(i->nickName.toStdString().c_str());
            USERNAME->LinkEndChild(USERNAMETEXT);


            TiXmlElement *USERID = new TiXmlElement("USERID");
            MEMBER->LinkEndChild(USERID);
            TiXmlText *USERIDTEXT = new TiXmlText(i->account.toStdString().c_str());
            USERID->LinkEndChild(USERIDTEXT);

            TiXmlElement *SEX = new TiXmlElement("SEX");
            MEMBER->LinkEndChild(SEX);
            TiXmlText *SEXTEXT = new TiXmlText(i->SEX.toStdString().c_str());
            SEX->LinkEndChild(SEXTEXT);

            TiXmlElement *CONTACT = new TiXmlElement("CONTACT");
            MEMBER->LinkEndChild(CONTACT);

            TiXmlElement *CELLPHONE = new TiXmlElement("CELLPHONE");
            CONTACT->LinkEndChild(CELLPHONE);
            TiXmlText *CELLPHONETEXT = new TiXmlText(i->mobileNumber.toStdString().c_str());
            CELLPHONE->LinkEndChild(CELLPHONETEXT);

            TiXmlElement *OFFICEPHONE = new TiXmlElement("OFFICEPHONE");
            CONTACT->LinkEndChild(OFFICEPHONE);
            TiXmlText *OFFICEPHONETEXT = new TiXmlText(i->officephone.toStdString().c_str());
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
            TiXmlText *MAILTEXT = new TiXmlText(i->mail.toStdString().c_str());
            MAIL->LinkEndChild(MAILTEXT);

            TiXmlElement *OTHER_INFORMATION = new TiXmlElement("OTHER_INFORMATION");
            MEMBER->LinkEndChild(OTHER_INFORMATION);
            TiXmlText *OTHER_INFORMATIONTEXT = new TiXmlText("none");
            OTHER_INFORMATION->LinkEndChild(OTHER_INFORMATIONTEXT);

            TiXmlElement *DORMITORY = new TiXmlElement("DORMITORY");
            MEMBER->LinkEndChild(DORMITORY);
            TiXmlText *DORMITORYTEXT = new TiXmlText("none");
            DORMITORY->LinkEndChild(DORMITORYTEXT);
        }
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

bool xmlparse::Create_TRANS_UPDATE_XmlFile(QString &szFileName, saveStruct &save)
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
        TiXmlText *_UPDATE = new TiXmlText("UPDATE");

        VERSION->LinkEndChild(VERSIONTEXT);
        MESSAGEID->LinkEndChild(MESSAGEIDTEXT);
        _TYPE->LinkEndChild(_UPDATE);

        TiXmlElement *ACTION = new TiXmlElement("ACTION");
        RootElement->LinkEndChild(ACTION);

        TiXmlElement *UPDATE = new TiXmlElement("UPDATE");
        ACTION->LinkEndChild(UPDATE);


        TiXmlElement *USERNAME = new TiXmlElement("USERNAME");
        UPDATE->LinkEndChild(USERNAME);
        TiXmlText *USERNAMETEXT = new TiXmlText(save.userInf.nickName.toStdString().c_str());
        USERNAME->LinkEndChild(USERNAMETEXT);


        TiXmlElement *USERID = new TiXmlElement("USERID");
        UPDATE->LinkEndChild(USERID);
        TiXmlText *USERIDTEXT = new TiXmlText(save.userInf.account.toStdString().c_str());
        USERID->LinkEndChild(USERIDTEXT);

        TiXmlElement *SEX = new TiXmlElement("SEX");
        UPDATE->LinkEndChild(SEX);
        TiXmlText *SEXTEXT = new TiXmlText(save.userInf.sex.toStdString().c_str());
        SEX->LinkEndChild(SEXTEXT);

        TiXmlElement *CONTACT = new TiXmlElement("CONTACT");
        UPDATE->LinkEndChild(CONTACT);

        TiXmlElement *CELLPHONE = new TiXmlElement("CELLPHONE");
        CONTACT->LinkEndChild(CELLPHONE);
        TiXmlText *CELLPHONETEXT = new TiXmlText(save.userInf.mobileNumber.toStdString().c_str());
        CELLPHONE->LinkEndChild(CELLPHONETEXT);

        TiXmlElement *OFFICEPHONE = new TiXmlElement("OFFICEPHONE");
        CONTACT->LinkEndChild(OFFICEPHONE);
        TiXmlText *OFFICEPHONETEXT = new TiXmlText(save.userInf.officephone.toStdString().c_str());
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
        TiXmlText *MAILTEXT = new TiXmlText(save.userInf.mail.toStdString().c_str());
        MAIL->LinkEndChild(MAILTEXT);

        TiXmlElement *OTHER_INFORMATION = new TiXmlElement("OTHER_INFORMATION");
        UPDATE->LinkEndChild(OTHER_INFORMATION);
        TiXmlText *OTHER_INFORMATIONTEXT = new TiXmlText("none");
        OTHER_INFORMATION->LinkEndChild(OTHER_INFORMATIONTEXT);

        TiXmlElement *DORMITORY = new TiXmlElement("DORMITORY");
        UPDATE->LinkEndChild(DORMITORY);
        TiXmlText *DORMITORYTEXT = new TiXmlText(save.userInf.dormitory.toStdString().c_str());
        DORMITORY->LinkEndChild(DORMITORYTEXT);

        TiXmlElement *DESCRIPTION = new TiXmlElement("DESCRIPTION");
        UPDATE->LinkEndChild(DESCRIPTION);
        TiXmlText *DESCRIPTIONTEXT = new TiXmlText(save.userInf.description.toStdString().c_str());
        DORMITORY->LinkEndChild(DESCRIPTIONTEXT);

        TiXmlElement *STATUS = new TiXmlElement("STATUS");
        UPDATE->LinkEndChild(STATUS);
        TiXmlText *STATUSTEXT = new TiXmlText(QString::number(save.userInf.status).toStdString().c_str());
        DORMITORY->LinkEndChild(STATUSTEXT);

        TiXmlElement *BIRTHDAY = new TiXmlElement("BIRTHDAY");
        UPDATE->LinkEndChild(BIRTHDAY);
        TiXmlText *BIRTHDAYTEXT = new TiXmlText(save.userInf.birthday.toStdString().c_str());
        DORMITORY->LinkEndChild(BIRTHDAYTEXT);

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

bool xmlparse::Read_TRANS_GET_ADDRESS_XmlFile(QString& szFileName,saveStruct &save)
{
    QString Name;
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
        qDebug() << TYPE->FirstChild()->Value();
        qDebug() << GET_ADDRESS->FirstChild()->Value() ;

        if("-1"==GET_ADDRESS->FirstChild()->Value())
        {
            save.requestKind = GET_FRIEND_INFORMATION;
        }
        else
        {
            save.logInf.account = QString(QLatin1String(GET_ADDRESS->FirstChild()->Value()));
        }

    }
    catch (QString& e)
    {
        return false;
    }
    return true;
}

bool xmlparse::Read_TRANS_UPDATE_XmlFile(QString &szFileName, saveStruct &save)
{
    try
    {
        TiXmlDocument *myDocument = new TiXmlDocument(szFileName.toStdString().c_str());
        myDocument->LoadFile();
        TiXmlElement *RootElement = myDocument->RootElement();


        TiXmlElement *HEAD = RootElement->FirstChildElement();
        TiXmlElement *VERSION = HEAD->FirstChildElement();
        TiXmlElement *MESSAGEID = VERSION->NextSiblingElement();
        TiXmlElement *_TYPE = MESSAGEID->NextSiblingElement();


        TiXmlElement *ACTION = HEAD->NextSiblingElement();
        TiXmlElement *UPDATE = ACTION->FirstChildElement();


        TiXmlElement *USERNAME = UPDATE->FirstChildElement();
        TiXmlElement *USERID = USERNAME->NextSiblingElement();
        TiXmlElement *SEX = USERID->NextSiblingElement();

        TiXmlElement *CONTACT = SEX->NextSiblingElement();

        TiXmlElement *CELLPHONE = CONTACT->FirstChildElement();
        TiXmlElement *OFFICEPHONE = CELLPHONE->NextSiblingElement();
        TiXmlElement *OTHER_CONTACT = OFFICEPHONE->NextSiblingElement();

        TiXmlElement *TYPE = OTHER_CONTACT->FirstChildElement();
        TiXmlElement *CONTENT = TYPE->NextSiblingElement();


        TiXmlElement *MAIL = OTHER_CONTACT->NextSiblingElement();


        TiXmlElement *OTHER_INFORMATION = CONTACT->NextSiblingElement();
        TiXmlElement *DORMITORY = OTHER_INFORMATION->NextSiblingElement();
        TiXmlElement *DESCRIPTION = DORMITORY->NextSiblingElement();
        TiXmlElement *STATUS = DESCRIPTION->NextSiblingElement();
        TiXmlElement *BIRTHDAY = STATUS->NextSiblingElement();


        save.userInf.account = QString(QLatin1String(USERNAME->FirstChild()->Value()));
        save.userInf.account = QString(QLatin1String(USERID->FirstChild()->Value()));
        save.userInf.sex = QString(QLatin1String(SEX->FirstChild()->Value()));
        save.userInf.mobileNumber = QString(QLatin1String(CELLPHONE->FirstChild()->Value()));
        save.userInf.officephone = QString(QLatin1String(OFFICEPHONE->FirstChild()->Value()));
        save.userInf.mail = QString(QLatin1String(MAIL->FirstChild()->Value()));
        save.userInf.dormitory = QString(QLatin1String(DORMITORY->FirstChild()->Value()));
        save.userInf.description = QString(QLatin1String(DESCRIPTION->FirstChild()->Value()));
        save.userInf.status = QString(QLatin1String(STATUS->FirstChild()->Value())).toInt();
        save.userInf.birthday = QString(QLatin1String(BIRTHDAY->FirstChild()->Value()));

        qDebug() << VERSION->FirstChild()->Value() ;
        qDebug() << MESSAGEID->FirstChild()->Value() ;
        qDebug() << _TYPE->FirstChild()->Value() ;
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
        qDebug() << DESCRIPTION->FirstChild()->Value() ;
        qDebug() << STATUS->FirstChild()->Value() ;
        qDebug() << BIRTHDAY->FirstChild()->Value() ;

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

//}


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

        qDebug() << TYPE->FirstChild()->Value() ;
        qDebug() << USERNAME->FirstChild()->Value() ;
        save.status = OFFLINE;
        save.logInf.account = QString(QLatin1String(USERNAME->FirstChild()->Value()));
    }
    catch (QString& e)
    {
        return false;
    }
    return true;
}


bool xmlparse::Create_TRANS_SEND_XmlFile(QString& szFileName,saveStruct &save)
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
        TiXmlText *USERIDTEXT = new TiXmlText(QString::number(save.message.fromfriendid).toStdString().c_str());
        USERID1->LinkEndChild(USERIDTEXT);

        TiXmlElement *NICKNAME1 = new TiXmlElement("NICKNAME");
        FROM->LinkEndChild(NICKNAME1);
        TiXmlText *NICKNAMETEXT = new TiXmlText(save.message.fromfriend.toStdString().c_str());
        NICKNAME1->LinkEndChild(NICKNAMETEXT);

        TiXmlElement *MESSAGESENDTIME1 = new TiXmlElement("MESSAGESENDTIME");
        FROM->LinkEndChild(MESSAGESENDTIME1);
        TiXmlText *MESSAGESENDTIMETEXT1 = new TiXmlText(save.message.DateSend.toStdString().c_str());
        MESSAGESENDTIME1->LinkEndChild(MESSAGESENDTIMETEXT1);



        TiXmlElement *USERID2 = new TiXmlElement("USERID");
        To->LinkEndChild(USERID2);
        TiXmlText *USERIDTEXT2 = new TiXmlText(QString::number(save.message.tofriendid).toStdString().c_str());
        USERID2->LinkEndChild(USERIDTEXT2);

        TiXmlElement *NICKNAME2 = new TiXmlElement("NICKNAME");
        To->LinkEndChild(NICKNAME2);
        TiXmlText *NICKNAMETEXT2 = new TiXmlText(save.message.tofriend.toStdString().c_str());
        NICKNAME2->LinkEndChild(NICKNAMETEXT2);

        TiXmlElement *MESSAGESENDTIME2 = new TiXmlElement("MESSAGESENDTIME");
        To->LinkEndChild(MESSAGESENDTIME2);
        TiXmlText *MESSAGESENDTIMETEXT2 = new TiXmlText(save.message.DateRec.toStdString().c_str());
        MESSAGESENDTIME2->LinkEndChild(MESSAGESENDTIMETEXT2);

        TiXmlElement *BROADCAST = new TiXmlElement("BROADCAST");
        MESSAGE->LinkEndChild(BROADCAST);
        TiXmlText *BROADCASTTEXT = new TiXmlText(save.message.BROADCAST.toStdString().c_str());
        BROADCAST->LinkEndChild(BROADCASTTEXT);

        TiXmlElement *CONTENT = new TiXmlElement("CONTENT");
        MESSAGE->LinkEndChild(CONTENT);
        TiXmlText *CONTENTTEXT = new TiXmlText(save.message.text.toStdString().c_str());
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
        qDebug() << TYPE->FirstChild()->Value() ;

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
        TiXmlElement *ACTION = HEAD->NextSiblingElement();
        TiXmlElement *GET_ADDRESS = ACTION->FirstChildElement();
        if("-1" == GET_ADDRESS->Value())
            return GET_FRIEND_INFORMATION;
        else
            return GET_USER_INFORMATION;
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
