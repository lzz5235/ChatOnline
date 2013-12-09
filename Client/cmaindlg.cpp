#include "cmaindlg.h"
#include "ui_cmaindlg.h"
#include <QDir>
#include <QMouseEvent>

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
        //sleep(0.5);
    }
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
}

void CMainDlg::initWidget()
{
    groupBox = new QGroupBox(this);
    groupBox->setObjectName(QString::fromUtf8("group"));
    layout = new QVBoxLayout(groupBox);
    ui->tb_friend->addItem(groupBox, "您的好友");

    //设置当前所布局的组件与四周的边界
    layout->setContentsMargins(10, 10, 10, 10);

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
}

void CMainDlg::initFriends(QVector<FriendInformation> &vcFriends)
{
    m_vcFriends.clear();
    QVector<FriendInformation>::Iterator it = vcFriends.begin();
    while(it != vcFriends.end())
    {
        m_vcFriends.push_back(*it);
        it++;
    }

    updateFriends();
}

void CMainDlg::updateFriends()
{
    QVector<FriendInformation>::Iterator it = m_vcFriends.begin();
    while(it != m_vcFriends.end())
    {
        insertItem(*it);
        it++;
    }

    initMyself();
}

void CMainDlg::insertItem(FriendInformation &frd)
{
    CFriendItem *item = new CFriendItem(m_link, m_MXml, frd, *m_myself, this);
    QString strHead = QString(":/head/resource/head/%1.jpg").arg(frd.avatarNumber);
    item->setIcon(QPixmap(strHead));
    QSize size;
    size.setHeight(AVATAR_SIZE - 10);
    size.setWidth(AVATAR_SIZE);
    item->setIconSize(size);
    item->setAutoRaise(true);
    item->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    item->setText(frd.name);
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

    quitAction = new QAction("quit", this);

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

void CMainDlg::ontrayIconactivated(QSystemTrayIcon::ActivationReason reason)
{
     switch(reason)
     {
        case QSystemTrayIcon::Trigger:
            if(this->isHidden())
            {
                setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
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
