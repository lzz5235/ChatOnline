#include "clogin.h"
#include "ui_clogin.h"
#include "global.h"
#include "extern.h"
#include "cmaindlg.h"
#include "utilities/FuncTools.h"
#include "cgv.h"
#include <QDir>
#include <QPicture>
#include <QTime>
#include <QMessageBox>

CLogin::CLogin(CConnect *link, IMakeXml *xml, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CLogin),
    m_link(link),
    m_MXml(xml)
{
    ui->setupUi(this);
    initWnd();
    initWidget();
    initAction();
}

CLogin::~CLogin()
{
    delete ui;
}

void CLogin::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void CLogin::initWnd()
{
    //drop frame
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    setFixedSize(wndSizeWidth, wndSizeHeight);

    QPalette pal;
    QPixmap pixmap( QDir::toNativeSeparators
            (":resource/pic/back.png") );
    pal.setBrush(QPalette::Window, QBrush(pixmap));
    setPalette(pal);
    ui->le_userpassword->setEchoMode(QLineEdit::Password);

    ui->username->setFixedSize(logonameSizeWidth, logopwdSizeHeight);
    ui->username->setStyleSheet("#username{border-image:url(:resource/pic/username.png);}");

    ui->userpassword->setFixedSize(logonameSizeWidth, logopwdSizeHeight);
    ui->userpassword->setStyleSheet("#userpassword{border-image:url(:resource/pic/password.png);}");

    ui->lb_logo->setStyleSheet("#lb_logo{border-image:url(:resource/pic/DSlab-01.png);}");
    ui->pb_login->setStyleSheet("#pb_login{border-image:url(:resource/pic/confirm.png);color: white;border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
                                "#pb_login:hover{color: green;}");

    ui->lb_topbar->setStyleSheet("#lb_topbar{border-image:url(:resource/pic/top_bar.png);}");
    ui->pb_set->setStyleSheet("#pb_set{border-image:url(:resource/pic/config.png);}");
    ui->pb_about->setStyleSheet("#pb_about{border-image:url(:resource/pic/about.png);}");
    ui->pb_close->setStyleSheet("#pb_close{border-image:url(:resource/pic/close.png);}");
    ui->lb_curtime->setStyleSheet("#lb_curtime{color:red}");

    ui->cb_status->setStyleSheet("#cb_status{color:red}");

    ui->le_username->setFocus();
}

void CLogin::initWidget()
{
    ui->pb_close->setToolTip(tr("quit Notification"));
    ui->pb_login->setText(tr("Submit"));
    QTime time;
    ui->lb_curtime->setText(time.currentTime().toString());

    CGV gv;
    map<string, int> g_mapStatus = gv.getStatus();
    map<string, int>::iterator it = g_mapStatus.begin();
    while(it != g_mapStatus.end())
    {
        QString qstrItem(it->first.c_str());
        ui->cb_status->insertItem(it->second, qstrItem);
        it++;
    }
}

void  CLogin::initAction()
{
    connect(ui->pb_close, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->pb_set, SIGNAL(clicked()), this, SLOT(toSettingDlg()));
    connect(ui->pb_login, SIGNAL(clicked()), this, SLOT(submit()));
    connect(m_link, SIGNAL(connectedsuccessful()), this, SLOT(connected2server()));
    connect(m_link, SIGNAL(connectionFailedSignal()),this, SLOT(connect2serverFaild()));
    connect(m_link, SIGNAL(dataIsReady(string)), this, SLOT(readBack(string)));
}

void CLogin::close()
{
    qApp->quit();
}

void CLogin::toSettingDlg()
{
    this->hide();
    m_settingDlg = new CSettingDlg(m_link, m_MXml);
    m_settingDlg->setWindowFlags(Qt::FramelessWindowHint);
    connect(m_settingDlg, SIGNAL(setClosed()), this, SLOT(settingClosed()));
    m_settingDlg->show();
    m_settingDlg->exec();
}

void CLogin::submit()
{
//    this->hide();
//    QVector<FriendInformation> vcFrnd;

//    UserInformation *lzz1 = new UserInformation;
//    lzz1->nickName = "王绪国";
//    lzz1->other = "lzz";
//    lzz1->status = 1;
//    lzz1->avatarNumber = 8;

//    FriendInformation lzz;
//    lzz.name = "lizhaozhong";
//    lzz.remark = "lzz";
//    lzz.status = 1;
//    lzz.avatarNumber = 10;
//    vcFrnd.push_back(lzz);

//    m_maindlg = new CMainDlg(m_link, m_MXml, lzz1);
//    m_maindlg->initFriends(vcFrnd);
//    m_maindlg->setWindowFlags(Qt::FramelessWindowHint);
//    m_maindlg->show();
//    m_maindlg->exec();

    if(m_link->getStatus() != CONNECTED)
    {
        ServerNode ser;
        CGV gv;
        string ip = gv.getIp();
        string port = gv.getPort();
        ser.Ip = ip;
        ser.Port = port;
        m_link->setServer(ser);
        if(!m_link->conct2Server())
        {
            qDebug() << m_link->getError();
            return;
        }
    }

    XMLPARA xmlLogin;
    xmlLogin.iCmdType = LOGIN;
    xmlLogin.mapCmdPara.insert(pair<string, string>(USERNAME, ui->le_username->text().toStdString()));
    xmlLogin.mapCmdPara.insert(pair<string, string>(PASSWORD, ui->le_userpassword->text().toStdString()));
    xmlLogin.mapCmdPara.insert(pair<string, string>(LOGINTIME, ui->lb_curtime->text().toStdString()));
    char szStatus[16] = "";
    itoa(ui->cb_status->currentIndex(), szStatus);
    xmlLogin.mapCmdPara.insert(pair<string, string>(STATUS, szStatus));
    string strLogin = m_MXml->parseCmd2Xml(xmlLogin);
    m_link->sendData(strLogin);
}

void CLogin::settingClosed()
{
    this->show();
    if(m_settingDlg)
        delete m_settingDlg;
}

void CLogin::connected2server()
{
    qDebug() << "connected successful!" << endl;
}

void CLogin::connect2serverFaild()
{
    qDebug() << "connected faild" << endl;
}

void CLogin::readBack(string data)
{
#ifdef DEBUG
    QMessageBox::information(NULL, ("check"),
        ("Test to connecte to server successful, and return is %s.", data.c_str()));
#endif


    //m_MXml->parseRsp(data, )
}
