#include "cmaindlg.h"
#include "ui_cmaindlg.h"
#include <QDir>
#include <QMouseEvent>
#include <QCryptographicHash>

CMainDlg::CMainDlg(CConnect *link, IMakeXml *xml,  UserInformation *myself, QWidget *parent):
    QDialog(parent),
    ui(new Ui::CMainDlg),
    m_link(link),
    m_MXml(xml),
    m_myself(myself),
    m_Ptbefore(QPoint(0, 0)),
    m_privateSetDlg(NULL)
{
    ui->setupUi(this);
    initWnd();
    initWidget();
    initAction();
    //主窗口需要接受所有消息,所以不用disconnect
    //QWidget::installEventFilter(this);
}

CMainDlg::~CMainDlg()
{
    delete ui;
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
        sleep(0.5);
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
    ui->pb_fresh->setStyleSheet("#pb_fresh{border-image:url(:resource/pic/fresh_cycle.png);}");
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
    layout->setContentsMargins(MARGINTOOLBUTTON, MARGINTOOLBUTTON, MARGINTOOLBUTTON, MARGINTOOLBUTTON);

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

void CMainDlg::initFriends()
{
    XMLPARA xmlGetAddress;
    xmlGetAddress.iCmdType = GETADDRESS;
    xmlGetAddress.mapCmdPara.insert(pair<string, string>(USERGETWHO, "-1"));
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

    qDebug() << "send to get address " << strGetAddress.c_str() << endl;
    m_link->sendData(strGetAddress);
}

void CMainDlg::updateFriends()
{
    m_frndMap.clear();
    int itemCount = layout->count();
    while(itemCount)
    {
        delete layout->itemAt(0)->widget();
        itemCount--;
    }
    layout->update();
    QVector<FriendInformation>::Iterator it = m_vcFriends.begin();
    while(it != m_vcFriends.end())
    {
        insertItem(*it);
        it++;
    }

}

void CMainDlg::insertItem(FriendInformation &frd)
{
    CFriendItem *item = new CFriendItem(m_link, m_MXml, frd, *m_myself, this);
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
    item->setText(frd.nickName);
    item->setFixedSize(FRDWIDTH - 30, FRDHEIGH);
    layout->addWidget(item);
    m_frndMap.insert(frd.account, item);
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
            qDebug() << "getmessage " << endl;
            break;
        }

        case GETADDRESS:
        {
            qDebug() << "getmessage " << endl;
            getAddress(data);
            break;
        }

        case RESULT:
        {
            qDebug() << "getmessage " << endl;
            break;
        }

        case LOGIN:
        {
            qDebug() << "getmessage " << endl;
            break;
        }

        case UPDATEINFO:
        {
            qDebug() << "getmessage " << endl;
            break;
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
            if(this->isHidden())
            {
                Qt::WindowFlags flags = Qt::Widget;
                flags |= Qt::WindowStaysOnTopHint;

                setWindowFlags(flags | Qt::FramelessWindowHint);
                flags &= ~(Qt::WindowStaysOnTopHint);
                this->showNormal();
            }
            break;
        case QSystemTrayIcon::DoubleClick:
            if(this->isHidden())
            {
                setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
                this->showNormal();
            }
            break;
        case QSystemTrayIcon::MiddleClick:
            QMessageBox::information(this,"MiddleClick","trayIcon MiddleClicked!");
            break;
        case QSystemTrayIcon::Context:
            QMessageBox::information(this,"Context","trayIcon Context!");
            break;
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
    about.show();
    about.exec();
    m_mnFuture->menuAction()->setVisible(false);
    m_animation = new QTimer(this);
    connect(m_animation, SIGNAL(timeout()), this, SLOT(animationShake()));
    m_animation->start(ANIMATIONTIME);
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
    m_privateSetDlg = new CPrivateInfo(m_link, m_MXml, *m_myself);
    m_privateSetDlg->setWindowFlags(Qt::FramelessWindowHint);
    m_privateSetDlg->show();
}

void CMainDlg::animationStop()
{
    m_animation->stop();
}

void CMainDlg::animationShake()
{
    QString strHead = QString(":/head/resource/head/28.jpg");
    rotateWidget(m_frndMap.begin().value(), -10, strHead);
    qDebug() << "start animation" << endl;
}

void CMainDlg::getMessage(string &data)
{

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
            frd.nickName = QString("    %1").arg((*it)[USERNICKNAME].c_str());
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

void CMainDlg::getNewLogin(string &data)
{

}

void CMainDlg::getNewUpdage(string &data)
{

}

void CMainDlg::getResult(string &data)
{

}
