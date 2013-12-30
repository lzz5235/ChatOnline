#include "cmaindlg.h"
#include "ui_cmaindlg.h"
#include <QDir>
#include <QMouseEvent>
#include <QCryptographicHash>

CMainDlg::CMainDlg(CConnect *link, IMakeXml *xml,  UserInformation *myself, QWidget *parent):
    QDialog(parent),
    ui(new Ui::CMainDlg),
    m_privateSetDlg(NULL),
    m_MXml(xml),
    m_link(link),
    m_myself(myself),
    m_Ptbefore(QPoint(0, 0)),
    m_privateOpen(false),
    m_iAngel(0)
{
    ui->setupUi(this);
    initWnd();
    initWidget();
    initAction();
    initMpSta2Enm();
}

CMainDlg::~CMainDlg()
{
    delete ui;
    if(m_cycleSaveHistory)
        delete m_cycleSaveHistory;
}

void CMainDlg::mousePressEvent(QMouseEvent * ev)
{
    QMouseEvent *mv = (QMouseEvent*) ev;
    if(mv->buttons() & Qt::LeftButton)
    {
        QRect labelrect = QRect(ui->lb_top->pos() + this->pos(), ui->lb_top->size());
        if(labelrect.contains(mv->globalPos()))
        {
            m_Ptbefore = mv->globalPos();
            m_Ptcur = mv->pos();
        }
        qDebug() << "Left Button down" << endl;

        QRect myself = QRect(ui->f_myself->pos() + this->pos(), ui->f_myself->size());
        if(myself.contains(mv->globalPos()))
        {
            privateSet();
        }
    }
}

void CMainDlg::mouseMoveEvent(QMouseEvent *ev)
{
    QMouseEvent *mv = (QMouseEvent*) ev;
    QRect labelrect = QRect(ui->lb_top->pos() + this->pos(), ui->lb_top->size());
    if(labelrect.contains(mv->globalPos()))
    {
        this->move(mv->globalX() - m_Ptcur.rx(), mv->globalY() - m_Ptcur.ry());
        m_Ptbefore = mv->globalPos();
        //sleep(0.5);
    }
}

bool CMainDlg::eventFilter(QObject *watched, QEvent *event)
{
  if( watched == this )
  {
      //窗口停用，变为不活动的窗口
      if(QEvent::WindowDeactivate == event->type())
      {
          qDebug() << "deactive status " << endl;
          disAction();
          return true ;
      }
      else
      {
          initAction();
          return false ;
      }
  }
  return false ;
}

void CMainDlg::initWnd()
{
    //drop frame
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    setFixedSize(MAINWNDWIDTH, MAINWNDHEIGH);

    QPalette pal;
    QPixmap pixmap( QDir::toNativeSeparators
            ("://resource/pic/main_back.png") );
    pal.setBrush(QPalette::Window, QBrush(pixmap));
    setPalette(pal);
    ui->lb_top->setStyleSheet("#lb_topbar{border-image:url(:resource/pic/top_bar.png); border-radius: 4px;}");
    ui->pb_close->setStyleSheet("#pb_close{border-image:url(:resource/pic/close.png);}");
    ui->pb_fresh->setStyleSheet("#pb_fresh{border-image:url(:resource/pic/main_back.png);}");
    ui->pb_setting->setStyleSheet("#pb_setting{border-image:url(:resource/pic/DSBtn.png);}");
    ui->pb_addfriend->setHidden(true);
    ui->pb_min->setStyleSheet("#pb_min{border-image:url(:resource/pic/min.png);}");
    ui->lb_topbar->setStyleSheet("#lb_topbar{border-image:url(:/resource/pic/bar.png);}");
    ui->lb_buttonbar->setStyleSheet("#lb_buttonbar{border-image:url(:/resource/pic/bar.png);}");
}

void CMainDlg::initWidget()
{
    groupBox = new QGroupBox(this);
    groupBox->setObjectName(QString::fromUtf8("group"));
    layout = new QVBoxLayout(groupBox);
    ui->tb_friend->addItem(groupBox, "您的好友");

    //设置当前所布局的组件与四周的边界
    layout->setContentsMargins(MARGINTOOLBUTTON - 5, MARGINTOOLBUTTON - 10, MARGINTOOLBUTTON, MARGINTOOLBUTTON);

    //居中对齐
    layout->setAlignment(Qt::AlignTop);
    groupBox->setGeometry(0, 0, 151, 461);
    trayIcon = new QSystemTrayIcon(this);
    QString strIcon = QString(":/resource/pic/DSBtn.png");
    QIcon icon(strIcon);
    trayIcon->setIcon(icon);
    createTrayIcon();
    trayIcon->show();
    createFutureMenu();
    m_animation = new QTimer(this);
    initMyself();
    initMyDataDir();

    m_privateSetDlg = new CPrivateInfo(m_link, m_MXml, *m_myself);
    m_privateSetDlg->setWindowFlags(Qt::FramelessWindowHint);

    m_cycleSaveHistory = new QTimer();
    connect(m_cycleSaveHistory, SIGNAL(timeout()), this, SLOT(saveHistory()));
    m_cycleSaveHistory->setInterval(SAVEHISTORYTIME);
    m_cycleSaveHistory->start();

    m_cycleRotateUpdateIcon = new QTimer();
    connect(m_cycleRotateUpdateIcon, SIGNAL(timeout()), this, SLOT(rotateUpdateIcon()));
    m_cycleRotateUpdateIcon->setInterval(ANIMATIONTIME);
    m_cycleRotateUpdateIcon->start();
}

void CMainDlg::initAction()
{
    connect(ui->pb_close, SIGNAL(clicked()), this, SLOT(close()));
    connect(m_link, SIGNAL(connectedsuccessful()), this, SLOT(connected2server()));
    connect(m_link, SIGNAL(connectionFailedSignal()),this, SLOT(connect2serverFaild()));
    connect(m_link, SIGNAL(dataIsReady(string)), this, SLOT(readBack(string)));
    connect(trayMap, SIGNAL(mapped(int)), this, SLOT(changeState(int)));
    connect(onlineAction, SIGNAL(triggered()), trayMap, SLOT(map()));
    connect(talkAction, SIGNAL(triggered()), trayMap, SLOT(map()));
    connect(busyAction, SIGNAL(triggered()), trayMap, SLOT(map()));
    connect(leaveAction, SIGNAL(triggered()), trayMap, SLOT(map()));
    connect(disturbAction, SIGNAL(triggered()), trayMap, SLOT(map()));
    connect(stealthAction, SIGNAL(triggered()), trayMap, SLOT(map()));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->pb_min, SIGNAL(clicked()), this, SLOT(hide()));
    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(ontrayIconactivated(QSystemTrayIcon::ActivationReason)));
    connect(ui->lb_myselfinfo, SIGNAL(editingFinished()), this, SLOT(editFinished()));
    connect(m_acAbout, SIGNAL(triggered()), this, SLOT(furuteAbout()));
    connect(ui->pb_setting, SIGNAL(clicked()), this, SLOT(showFutureWnd()));
    connect(ui->pb_fresh, SIGNAL(clicked()), this, SLOT(initFriends()));
    connect(m_privateSetDlg, SIGNAL(privateClose()), this, SLOT(closePrivateDlg()));
    connect(m_privateSetDlg, SIGNAL(updatedMyInfo(UserInformation)), this, SLOT(updateMyself(UserInformation)));
}

void CMainDlg::disAction()
{
    disconnect(ui->pb_close, SIGNAL(clicked()), this, SLOT(close()));
    disconnect(m_link, SIGNAL(connectedsuccessful()), this, SLOT(connected2server()));
    disconnect(m_link, SIGNAL(connectionFailedSignal()),this, SLOT(connect2serverFaild()));
    disconnect(m_link, SIGNAL(dataIsReady(string)), this, SLOT(readBack(string)));
    disconnect(trayMap, SIGNAL(mapped(int)), this, SLOT(changeState(int)));
    disconnect(onlineAction, SIGNAL(triggered()), trayMap, SLOT(map()));
    disconnect(talkAction, SIGNAL(triggered()), trayMap, SLOT(map()));
    disconnect(busyAction, SIGNAL(triggered()), trayMap, SLOT(map()));
    disconnect(leaveAction, SIGNAL(triggered()), trayMap, SLOT(map()));
    disconnect(disturbAction, SIGNAL(triggered()), trayMap, SLOT(map()));
    disconnect(stealthAction, SIGNAL(triggered()), trayMap, SLOT(map()));
    disconnect(quitAction, SIGNAL(triggered()), this, SLOT(close()));
    disconnect(ui->pb_min, SIGNAL(clicked()), this, SLOT(hide()));
    disconnect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(ontrayIconactivated(QSystemTrayIcon::ActivationReason)));
    disconnect(ui->lb_myselfinfo, SIGNAL(editingFinished()), this, SLOT(editFinished()));
    disconnect(m_acAbout, SIGNAL(triggered()), this, SLOT(furuteAbout()));
    disconnect(ui->pb_setting, SIGNAL(clicked()), this, SLOT(showFutureWnd()));
}

void CMainDlg::initFriends(string strWho)
{
    XMLPARA xmlGetAddress;
    xmlGetAddress.iCmdType = GETADDRESS;
    xmlGetAddress.mapCmdPara.insert(pair<string, string>(USERGETWHO, strWho));
    string strGetAddress = m_MXml->parseCmd2Xml(xmlGetAddress);

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

    qDebug() << "send to get address " << strGetAddress.c_str() << endl;
    m_link->sendData(strGetAddress);
}

void CMainDlg::updateFriends()
{
    m_frndMap.clear();
    int itemCount = layout->count();
    while(itemCount)
    {
        disconnect(layout->itemAt(0)->widget(), SIGNAL(sendMessage(string, XMLPARA)), this, SLOT(sendMessage(string, XMLPARA)));
        delete layout->itemAt(0)->widget();
        itemCount--;
    }
    QVector<FriendInformation>::Iterator it = m_vcFriends.begin();
    while(it != m_vcFriends.end())
    {
        insertItem(*it);
        it++;
    }
}

void CMainDlg::insertItem(FriendInformation &frd)
{
    CFriendItem *item = new CFriendItem(m_MXml, frd, *m_myself, this);
    item->setStyleSheet("QToolButton{border-style: flat;}");
    QString strHead = QString(":/head/resource/head/%1.jpg").arg(frd.avatarNumber);
    if(frd.status == OFFLINE)
    {
        QImage oldPic(strHead);
        QImage newPic = convert2Gray(strHead, oldPic.size());
        item->setIcon(QPixmap::fromImage(newPic));
    }
    else
    {
        item->setIcon(QPixmap(strHead));
    }
    QSize size;
    size.setHeight(AVATAR_SIZE - 10);
    size.setWidth(AVATAR_SIZE);
    item->setIconSize(size);
    item->setAutoRaise(false);
    item->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    string status = getElement(mpsSta2Enm, frd.status);
    item->setText(QString("%1 (%2)").arg(frd.nickName).arg(QString(status.c_str())));
    item->setFixedSize(FRDWIDTH, FRDHEIGH);
    item->setFocus();
    connect(item, SIGNAL(sendMessage(XMLPARA)), this, SLOT(sendMessage(XMLPARA)));
    layout->addWidget(item);
    m_frndMap.insert(QString::number(frd.userID), item);
    historyItem history;
    history.userid = frd.userID;

    m_mtxHistory.tryLock(500);
    m_allHistory.insert(QString::number(frd.userID), history);
    m_mtxHistory.unlock();
}

void CMainDlg::close()
{
    qApp->quit();
}

void CMainDlg::connected2server()
{
    qDebug() << "connected successful!" << endl;
}

void CMainDlg::connect2serverFaild()
{
    qDebug() << "connected faild" << endl;
}

void CMainDlg::createTrayIcon()
{
    trayMap = new QSignalMapper(this);

    //创建托盘图标中的各个按钮，并连接信号/糟
    onlineAction = new QAction("online", this);
    onlineAction->setIcon(QIcon(":/status/resource/status/online.bmp"));
    trayMap->setMapping(onlineAction, ONLINE);

    talkAction = new QAction("idle", this);
    talkAction->setIcon(QIcon(":/status/resource/status/idle.bmp"));
    trayMap->setMapping(talkAction, FREE);

    busyAction = new QAction("busy", this);
    busyAction->setIcon(QIcon(":/status/resource/status/busy.bmp"));
    trayMap->setMapping(busyAction, BUSY);

    leaveAction = new QAction("leave", this);
    leaveAction->setIcon(QIcon(":/status/resource/status/leave.bmp"));
    trayMap->setMapping(leaveAction, LEAVE);

    disturbAction = new QAction("disturb", this);
    disturbAction->setIcon(QIcon(":/status/resource/status/disturb.bmp"));
    trayMap->setMapping(disturbAction, DISTURB);

    stealthAction = new QAction("stealth", this);
    stealthAction->setIcon(QIcon(":/status/resource/status/stealth.bmp"));
    trayMap->setMapping(stealthAction, STEALTH);

    quitAction = new QAction("appQuit", this);

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(onlineAction);
    trayIconMenu->addAction(talkAction);
    trayIconMenu->addAction(busyAction);
    trayIconMenu->addAction(leaveAction);
    trayIconMenu->addAction(disturbAction);
    trayIconMenu->addAction(stealthAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
    trayIcon->setContextMenu(trayIconMenu);
}

void CMainDlg::createFutureMenu()
{
    m_mnFuture = new QMenu(this);
    m_acAbout = new QAction("About", this);
    m_acAbout->setIcon(QIcon(":/Future/resource/Future/about.bmp"));

    m_acTest = new QAction("test", this);
    m_mnFuture->addAction(m_acAbout);
    m_mnFuture->addAction(m_acTest);
    m_mnFuture->menuAction()->setVisible(false);
}

void CMainDlg::changeState(int n)
{
    m_myself->status = n;
    QString tStatus, icon;
    setStatusFromInt(m_myself->status, tStatus);

    icon = QString(":/status/resource/status/%1.bmp").arg(tStatus);
    QImage img(icon);
    ui->lb_status->setPixmap(QPixmap::fromImage(img));

    //here link to server change myself status
}

void CMainDlg::setStatusFromInt(int n, QString &str) const
{
    switch(n)
    {
    case ONLINE:
        str = "online";
        break;
    case FREE:
        str = "idle";
        break;
    case BUSY:
        str = "busy";
        break;
    case LEAVE:
        str = "leave";
        break;
    case DISTURB:
        str = "disturb";
        break;
    case STEALTH:
        str = "stealth";
        break;
    case QUIT:
        str = "quit";
        break;
    default:
        str = "online";
        break;
    }
}

void CMainDlg::readBack(string data)
{
#ifdef DEBUG
    QMessageBox::information(NULL, ("check"),
        ("Test to connecte to server successful, and return is %s.", data.c_str()));
#endif

    int rtCmd = m_MXml->parseRspType(data);
    qDebug() << "maindlg back is " << rtCmd << endl;
    switch(rtCmd)
    {
        case GETMESSAGE:
        {
            qDebug() << "GETMESSAGE " << endl;
            getMessage(data);
            break;
        }

        case GETADDRESS:
        {
            qDebug() << "GETADDRESS " << endl;
            getAddress(data);
            break;
        }

        case RESULT:
        {
            qDebug() << "RESULT " << endl;
            break;
        }

        case LOGININFO:
        {
            qDebug() << "LOGININFO " << endl;
            getloginedInfo(data);
            break;
        }

        case UPDATEINFO:
        {
            qDebug() << "UPDATEINFO " << endl;
            break;
        }

        case NEWUPDATE:
        {
            qDebug() << "NEWUPDATE" << endl;
            getNewUpdate(data);
        }
    }
}

void CMainDlg::initMyself()
{
    ui->f_myself->setObjectName("myself");
    QString strIcon = QString("#myself{border-image:url(:head/resource/head/%1.jpg)}").arg(m_myself->avatarNumber);
    ui->f_myself->setStyleSheet(strIcon);

    QString tStatus, icon;
    setStatusFromInt(m_myself->status, tStatus);

    icon = QString(":/status/resource/status/%1.bmp").arg(tStatus);
    QImage img(icon);
    ui->lb_status->setPixmap(QPixmap::fromImage(img));

    if( m_myself->other.isEmpty())
    {
        qDebug() << QString("%1 \n").arg("  hello!");
        ui->lb_myselfinfo->insert(QString("%1 \n").arg("这家伙太懒,啥也没写!"));
    }
    ui->lb_myselfinfo->insert(QString("%1 ").arg(m_myself->other));
    ui->lb_myselfinfo->setCursorPosition(0);
    qDebug() << m_myself->nickName;
    ui->lb_myNickName->setText(m_myself->nickName);
}

void CMainDlg::initMyDataDir()
{
    QDir curDataDic(m_myself->account);
    if(curDataDic.exists())
    {
        QString filePath = "./" + m_myself->account + "/" + HISTORY;
        QFile infoFile(filePath);
        if(!infoFile.exists())
        {
            infoFile.open( QIODevice::Text | QIODevice::ReadWrite);

            infoFile.close();
        }
    }
    else
    {
        if(QDir::current().mkdir(m_myself->account))
        {
            qDebug() << "create directory successful" << endl;
        }
        else
        {
            qDebug() << "create directory faild" << endl;
            return;
        }

        QString filePath = "./" + m_myself->account + "/" + HISTORY;
        QFile infoFile(filePath);
        if(!infoFile.exists())
        {
            infoFile.open( QIODevice::Text | QIODevice::ReadWrite);

            infoFile.close();
        }
    }
}

void CMainDlg::ontrayIconactivated(QSystemTrayIcon::ActivationReason reason)
{
     switch(reason)
     {
        case QSystemTrayIcon::Trigger:
        {
            if(this->isHidden())
            {
                Qt::WindowFlags flags = Qt::Widget;
                flags |= Qt::WindowStaysOnTopHint;

                setWindowFlags(flags | Qt::FramelessWindowHint);
                flags &= ~(Qt::WindowStaysOnTopHint);
                this->showNormal();
            }
            break;
        }
        case QSystemTrayIcon::DoubleClick:
        {
            if(this->isHidden())
            {
                setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
                this->showNormal();
            }
        }
        break;
        case QSystemTrayIcon::MiddleClick:
         {
            #ifdef DEBUG
            QMessageBox::information(this,"MiddleClick","trayIcon MiddleClicked!");
            #endif
            break;
         }
        case QSystemTrayIcon::Context:
        {
            #ifdef DEBUG
            QMessageBox::information(this,"Context","trayIcon Context!");
            #endif
            break;
        }
        default:
             break;
     }
}

void CMainDlg::editFinished()
{
    ui->lb_myselfinfo->setCursorPosition(0);
}

void CMainDlg::furuteAbout()
{
    qDebug() << "furuteAbout " << endl;
    CAboutDlg about;
    m_mnFuture->menuAction()->setVisible(false);
    about.show();
    about.exec();
}

void CMainDlg::showFutureWnd()
{
    qDebug() << " m_mnFuture->show();" << endl;
    if(m_mnFuture->menuAction()->isVisible())
    {
        qDebug() << "hide" << endl;
        m_mnFuture->hide();
        m_mnFuture->menuAction()->setVisible(false);
    }
    else
    {
        qDebug() << "show" << endl;
        m_mnFuture->show();
        QPoint ptSet = ui->pb_setting->pos();
        QPoint ptFuture ;
        ptFuture.setX(ptSet.x() - m_mnFuture->size().rwidth() + this->pos().x());
        ptFuture.setY(ptSet.y() - m_mnFuture->size().rheight() + this->pos().y());
        m_mnFuture->menuAction()->setVisible(true);
        m_mnFuture->move(ptFuture);
    }
}

void CMainDlg::privateSet()
{
    if(m_privateOpen == false)
    {
        m_privateSetDlg->updateMyInfo(*m_myself);
        m_privateSetDlg->show();
        m_privateOpen = true;
    }
}

void CMainDlg::closePrivateDlg()
{
    m_privateOpen = false;
}

void CMainDlg::animationStop()
{
    m_animation->stop();
}

void CMainDlg::animationShake()
{
    QString strHead = QString(":/head/resource/head/28.jpg");

    //rotateWidget(m_frndMap.begin().value(), angel[m_iAngel], strHead);
    if(m_iAngel == 4)
        m_iAngel = 0;
    m_iAngel++;

    qDebug() << "start animation" << endl;
}

void CMainDlg::rotateUpdateIcon()
{
    if(m_iAngel == -360)
    {
        m_iAngel = 0;
    }
    m_iAngel -= 10;
    QString img = ":resource/pic/fresh_cycle.png";
    rotateWidget(ui->pb_fresh, m_iAngel, img);
    ui->pb_fresh->update();
}

void CMainDlg::updateMyself(UserInformation myself)
{
    XMLPARA xmlupdate;
    xmlupdate.iCmdType = UPDATEINFO;

    xmlupdate.mapCmdPara[USERNICKNAME] = myself.nickName.toStdString();
    xmlupdate.mapCmdPara[USERSEX] = myself.sex.toStdString();
    xmlupdate.mapCmdPara[USERNAME] = myself.account.toStdString();
    xmlupdate.mapCmdPara[USERID] = QString::number(myself.userID).toStdString();
    xmlupdate.mapCmdPara[USERAGE] = QString::number(myself.age).toStdString();
    xmlupdate.mapCmdPara[USERCELLPHONE] = myself.cellphone.toStdString();
    xmlupdate.mapCmdPara[USEROFFICEPHONE] = myself.officephone.toStdString();
    xmlupdate.mapCmdPara[USERMAIL] = myself.mail.toStdString();
    xmlupdate.mapCmdPara[USEROTHER] = myself.other.toStdString();
    xmlupdate.mapCmdPara[USERDORMITORY] = myself.dormitory.toStdString();
    xmlupdate.mapCmdPara[USERDESCRIPTION] = myself.description.toStdString();
    xmlupdate.mapCmdPara[USERSTATUS] = QString::number(myself.status).toStdString();
    xmlupdate.mapCmdPara[USERBIRTHDAY] = myself.birthday.toStdString();
    xmlupdate.mapCmdPara[USERAVATARNUM] = QString::number(myself.avatarNumber).toStdString();
    xmlupdate.mapCmdPara[USERCITY] = myself.city.toStdString();

    string xml = m_MXml->parseCmd2Xml(xmlupdate);
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

    qDebug() << "send to update myself " << xml.c_str() << endl;
    m_link->sendData(xml);
}

void CMainDlg::getMessage(string &data)
{
    XMLPARA back;
    back.iCmdType = GETMESSAGE;
    m_MXml->parseRsp(data, back);

    if(GETMESSAGESUCCESSFUL == back.xmlBack.mapBackPara[GETMESSAGERESULT])
    {
        m_mtxHistory.tryLock(500);
        list<map<string, string> >::iterator itPara = back.lstCmdPara.begin();
        if(itPara != back.lstCmdPara.end())
        {
            string recvid = (*itPara)[SENDERMESSAGEID];
            QMap<QString, historyItem>::Iterator it = m_allHistory.find(QString(recvid.c_str()));
            recordItem record;
            if(it != m_allHistory.end())
            {
                record.content = QString((*itPara)[MESSAGECONTENT].c_str());
                record.time = QString((*itPara)[MESSAGESENDTIME].c_str());
                record.sendid = QString((*itPara)[SENDERMESSAGEID].c_str());
                record.recvid = QString((*itPara)[RECVERMESSAGEID].c_str());
                it.value().sndOrder.push_back(record);
                emit getSuccessful(record);
            }
        }
        m_mtxHistory.unlock();
    }
}

void CMainDlg::getAddress(string &data)
{
    XMLPARA back;
    back.iCmdType = GETADDRESS;
    m_MXml->parseRsp(data, back);

    if(GETADDRESSSUCCESSFUL == back.xmlBack.mapBackPara[GETADDRESSRESULT])
    {
        list<map<string, string> >::iterator it = back.lstCmdPara.begin();
        while(it != back.lstCmdPara.end())
        {
            FriendInformation frd;
            frd.userID = atoi((*it)[USERID].c_str());
            frd.nickName = QString("%1").arg((*it)[USERNICKNAME].c_str());
            frd.age = atoi((*it)[USERAGE].c_str());
            frd.avatarNumber = atoi((*it)[USERAVATARNUM].c_str());
            frd.other = QString((*it)[USERDESCRIPTION].c_str());
            frd.status = atoi((*it)[USERSTATUS].c_str());
            QVector<FriendInformation>::Iterator it_alexist = m_vcFriends.begin();
            while(it_alexist != m_vcFriends.end())
            {
                if(it_alexist->userID == frd.userID)
                {
                    m_vcFriends.erase(it_alexist);
                    break;
                }
                it_alexist++;
            }
            m_vcFriends.push_back(frd);
            it++;
        }
        updateFriends();
    }
}

void CMainDlg::getloginedInfo(string &data)
{
    XMLPARA xmlLoginInfo;
    xmlLoginInfo.iCmdType = LOGININFO;

    m_MXml->parseRsp(data, xmlLoginInfo);
    if(LOGININFOSUCCESSFUL == xmlLoginInfo.xmlBack.mapBackPara[LOGININFORESULT])
    {
        list<map<string, string> >::iterator it = xmlLoginInfo.lstCmdPara.begin();
        if(it != xmlLoginInfo.lstCmdPara.end())
        {
            string strLoginInfo = (*it)[LOGININFOUSERID];
            initFriends(strLoginInfo);
        }
    }
}

void CMainDlg::getNewUpdate(string &data)
{
    XMLPARA xmlLoginInfo;
    xmlLoginInfo.iCmdType = NEWUPDATE;

    m_MXml->parseRsp(data, xmlLoginInfo);
    if(NEWUPDATESUCCESSFUL == xmlLoginInfo.xmlBack.mapBackPara[NEWUPDATERESULT])
    {
        list<map<string, string> >::iterator it = xmlLoginInfo.lstCmdPara.begin();
        if(it != xmlLoginInfo.lstCmdPara.end())
        {
            string strLoginInfo = (*it)[NEWUPDATEUSERID];
            initFriends(strLoginInfo);
        }
    }
}

void CMainDlg::getResult(string &data)
{

}

void CMainDlg::saveHistory()
{
    if(m_mtxHistory.tryLock(500))
    {
        qDebug() << "lock successful" << endl;
        createHistory();
        m_mtxHistory.unlock();
        qDebug() << "unlock successful" << endl;
        return;
    }
    qDebug() << "lock unsuccessful" << endl;
}

void CMainDlg::createHistory()
{
    QMap<QString, historyItem>::Iterator it = m_allHistory.begin();
    while(it != m_allHistory.end())
    {
        QDir curDataDic(m_myself->account);
        if(curDataDic.exists())
        {
            QString filePath = "./" + m_myself->account + "/" + it.key();
            write2File(filePath, *it);
        }
        else
        {
            if(QDir::current().mkdir(m_myself->account))
            {
                qDebug() << "create directory successful" << endl;
            }
            else
            {
                qDebug() << "create directory faild" << endl;
                return;
            }

            QString filePath = "./" + m_myself->account + "/" + it.key();
            write2File(filePath, *it);
        }
        it.value().sndOrder.clear();
        it++;
    }
}

void CMainDlg::write2File(QString filePath, historyItem item)
{
    QFile infoFile(filePath);
    if(!infoFile.exists())
    {
        infoFile.open( QIODevice::Text | QIODevice::ReadWrite);
        qDebug() << "create file name " << filePath << endl;
        list<recordItem>::iterator itRecord = item.sndOrder.begin();
        while(itRecord != item.sndOrder.end())
        {
            recordItem record = *itRecord;
            readFromHistoryItemForSave(&infoFile, record);
            itRecord++;
        }

        infoFile.close();
    }
    else
    {
        infoFile.open( QIODevice::Text | QIODevice::ReadWrite);
        qDebug() << "create file name " << filePath << endl;
        list<recordItem>::iterator itRecord = item.sndOrder.begin();
        while(itRecord != item.sndOrder.end())
        {
            recordItem record = *itRecord;
            readFromHistoryItemForSave(&infoFile, record);
            itRecord++;
        }
    }
}

void CMainDlg::readFromHistoryItemForSave(QFile *filePath, recordItem record)
{
    if(record.sendid.toInt() == m_myself->userID)
    {
        QString qstrRecord = QString("%1 %2 \n  %3 \n\n").arg(m_myself->nickName).arg(record.time).arg(record.content);
        qDebug() << "record is " << qstrRecord << endl;
        if(filePath->isWritable())
        {
            QTextStream in(filePath);
            //in.setCodec(CODEDECODE);
            in.seek(filePath->size());
            in << qstrRecord;
            //filePath->write(qstrRecord.toStdString().c_str(), qstrlen(qstrRecord.toStdString().c_str()));
        }
    }
    else
    {
        QMap<QString, CFriendItem*>::Iterator itFindWho = m_frndMap.find(record.sendid);
        if(itFindWho != m_frndMap.end())
        {
            FriendInformation frd = (*itFindWho.value()).getInformation();
            QString qstrRecord = QString("%1 %2 \n  %3 \n\n").arg(frd.nickName).arg(record.time).arg(record.content);
            qDebug() << "record is " << qstrRecord << endl;
            if(filePath->isWritable())
            {
                QTextStream in(filePath);
                //in.setCodec("utf-8");
                in.seek(filePath->size());
                in << qstrRecord;
                //filePath->write(qstrRecord.toStdString().c_str(), qstrlen(qstrRecord.toStdString().c_str()));
            }
        }
    }
}

void CMainDlg::sendMessage(XMLPARA data)
{
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

    string message = m_MXml->parseCmd2Xml(data);
    qDebug() << "send message " << message.c_str() << endl;
    if(m_link->sendData(message))
    {
        m_mtxHistory.tryLock(500);
        string recvid = data.mapCmdPara[USERRECVERID];
        QMap<QString, historyItem>::Iterator it = m_allHistory.find(QString(recvid.c_str()));
        recordItem record;
        if(it != m_allHistory.end())
        {
            record.content = QString(data.mapCmdPara[USERCONTENT].c_str());
            record.time = QString(data.mapCmdPara[USERSENDTIME].c_str());
            record.sendid = QString(data.mapCmdPara[USERSENDERID].c_str());
            record.recvid = QString(recvid.c_str());
            it.value().sndOrder.push_back(record);
            emit getSuccessful(record);
        }
        m_mtxHistory.unlock();
    }
}
