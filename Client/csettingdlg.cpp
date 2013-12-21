#include "csettingdlg.h"
#include "global.h"
#include "ui_csettingdlg.h"
#include "xml/rscCMD.h"
#include <QDir>
#include <QDebug>
#include <QTextCodec>
#include <QMessageBox>

CSettingDlg::CSettingDlg(CConnect *link, IMakeXml *xml, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSettingDlg),
    m_link(link),
    m_MXml(xml),
    m_bActive(true)
{
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    ui->setupUi(this);
    initWnd();
    loadSetting();
    initAction();
    //QWidget::installEventFilter(this);
}

CSettingDlg::~CSettingDlg()
{
    delete ui;
}

void CSettingDlg::initWnd()
{
    this->setWindowOpacity(1);
    this->setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(setdlgSizeWidth, setdlgSizeHeight);

    QPalette pal;
    QPixmap pixmap( QDir::toNativeSeparators
            (":resource/pic/back_set.png") );
    pal.setBrush(QPalette::Window, QBrush(pixmap));
    setPalette(pal);

    ui->lb_topbar->setStyleSheet("#lb_topbar{border-image:url(:resource/pic/top_bar.png);}");
    ui->pb_cancel->setStyleSheet("#pb_cancel{border-image:url(:resource/pic/confirm.png);color: white;border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
                                "#pb_cancel:hover{color: green;}; pressed{coloe :red}");
    ui->pb_confirm->setStyleSheet("#pb_confirm{border-image:url(:resource/pic/confirm.png);color: white;border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
                                "#pb_confirm:hover{color: green;}");
    ui->pb_test->setStyleSheet("#pb_test{border-image:url(:resource/pic/confirm.png);color: white;border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
                                "#pb_test:hover{color: green;}");

    ui->lb_logo->setStyleSheet("#lb_logo{border-image:url(:resource/pic/DSlab-01.png);}");
    ui->pb_close->setStyleSheet("#pb_close{border-image:url(:resource/pic/close.png);}");
}

bool CSettingDlg::loadSetting()
{
    CGV gv;
    string strIP = gv.getIp();
    ui->le_ip->setText(QString(strIP.c_str()));

    string strPort = gv.getPort();
    ui->le_port->setText(QString(strPort.c_str()));
    return true;
}

void  CSettingDlg::initAction()
{
    connect(ui->pb_cancel, SIGNAL(clicked()), this, SLOT(dlgClose()));
    connect(ui->pb_confirm, SIGNAL(clicked()), this, SLOT(submit()));
    connect(ui->pb_test, SIGNAL(clicked()), this, SLOT(checkServer()));
    connect(ui->pb_close, SIGNAL(clicked()), this, SLOT(dlgClose()));
    connect(m_link, SIGNAL(connectedsuccessful()), this, SLOT(connected2server()));
    connect(m_link, SIGNAL(connectionFailedSignal()),this, SLOT(connect2serverFaild()));
    connect(m_link, SIGNAL(dataIsReady(string)), this, SLOT(readBack(string)));
}

void CSettingDlg::disAction()
{
    disconnect(ui->pb_cancel, SIGNAL(clicked()), this, SLOT(dlgClose()));
    disconnect(ui->pb_confirm, SIGNAL(clicked()), this, SLOT(submit()));
    disconnect(ui->pb_test, SIGNAL(clicked()), this, SLOT(checkServer()));
    disconnect(ui->pb_close, SIGNAL(clicked()), this, SLOT(dlgClose()));
    disconnect(m_link, SIGNAL(connectedsuccessful()), this, SLOT(connected2server()));
    disconnect(m_link, SIGNAL(connectionFailedSignal()),this, SLOT(connect2serverFaild()));
    disconnect(m_link, SIGNAL(dataIsReady(string)), this, SLOT(readBack(string)));
}

bool CSettingDlg::eventFilter(QObject *watched, QEvent *event)
{
  if( watched == this )
  {
      //窗口停用，变为不活动的窗口
      if(QEvent::WindowDeactivate == event->type() && m_bActive == true)
      {
          qDebug() << "deactive status " << endl;
          disAction();
          m_bActive = false;
          return true ;
      }
      else if(QEvent::WindowActivate == event->type() && m_bActive == false)
      {
          initAction();
          m_bActive = true;
          return false ;
      }
  }
  return false ;
}

bool CSettingDlg::checkServer()
{
    if(m_link->getStatus() != CONNECTED)
    {
        ServerNode ser;
        ser.Ip = ui->le_ip->text().toStdString();
        ser.Port = ui->le_port->text().toStdString();
        m_link->setServer(ser);
        if(!m_link->conct2Server())
        {
            qDebug() << m_link->getError();
            return false;
        }
    }

    XMLPARA xml;
    xml.iCmdType = TEST;
    string test = m_MXml->parseCmd2Xml(xml);
    m_link->sendData(test);
    return true;
}

void CSettingDlg::dlgClose()
{
    hide();
    emit setClosed();
}

void CSettingDlg::submit()
{
    CGV gv;
    QString qstrIP = ui->le_ip->text();
    QString qstrPORT = ui->le_port->text();
    KVList kv;
    kv.KVData.insert(pair<string, string>("SERVER/IP", qstrIP.toStdString().c_str()));
    kv.KVData.insert(pair<string, string>("SERVER/PORT", qstrPORT.toStdString().c_str()));
    gv.setValue(kv);

    hide();
    emit setClosed();
}

void CSettingDlg::connected2server()
{
    qDebug() << "connected successful!" << endl;
}

void CSettingDlg::connect2serverFaild()
{
    qDebug() << "connected faild" << endl;
}

void CSettingDlg::readBack(string data)
{
#ifdef DEBUG
    QMessageBox::information(NULL, ("check"),
        ("CSettingDlg to connecte to server successful, and return is %s.", data.c_str()));
#endif
    int type = m_MXml->parseRspType(data);
    qDebug() << "type is " << type << endl;
}
