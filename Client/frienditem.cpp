#include "frienditem.h"

CFriendItem::CFriendItem(CConnect *tLink,
                         IMakeXml *xml,
                         const FriendInformation &theFriend,
                         UserInformation &myself,
                         QWidget *parent):
    m_link(tLink),
    m_MXml(xml),
    m_friInf(theFriend),
    m_Account(myself.account),
    m_Name(myself.nickName),
    m_myself(myself)
{
    initWnd();
    initWidget();
    initAction();
}

void CFriendItem::initWnd()
{
    m_isOpen = false;
    getStatusFromInt(m_friInf.status, m_strStatus);
    QString mark;
    if(m_friInf.remark.isEmpty())
        mark = m_friInf.name;
    else
        mark = m_friInf.remark;

    creatMenu();
    setContextMenuPolicy(Qt::CustomContextMenu);
    setIconSize( QSize(AVATAR_SIZE, AVATAR_SIZE) );
    setAutoRaise(true);
    setToolButtonStyle( Qt::ToolButtonTextBesideIcon );
    setButtonStatus();
}

void CFriendItem::initWidget()
{
    m_room = new CChatRoom(m_link, m_MXml, m_myself, m_friInf);
    m_room->setWindowFlags(Qt::FramelessWindowHint);
}

void CFriendItem::initAction()
{
    connect(m_link, SIGNAL(connectedsuccessful()), this, SLOT(connected2server()));
    connect(m_link, SIGNAL(connectionFailedSignal()),this, SLOT(connect2serverFaild()));
    connect(m_link, SIGNAL(dataIsReady(string)), this, SLOT(readBack(string)));
    connect(m_room, SIGNAL(closeWnd()), this, SLOT(chatRoomQuit()));
    connect(this, SIGNAL(clicked()), this, SLOT(clickedFriendButton()));
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(clickedRightButton(const QPoint &)));
}

CFriendItem::~CFriendItem()
{
    closeChatRoom();
}

void CFriendItem::getStatusFromInt(int n, QString &str) const
{

}

void CFriendItem::creatMenu()
{
    m_menu = new QMenu(this);
	QAction *actShow = new QAction(tr("Show his(her) information"), this);
	QAction *actRemark = new QAction(tr("Change remark"), this);
    connect(actShow, SIGNAL(triggered()), this, SLOT(clickedShowInformation()));
    connect(actRemark, SIGNAL(triggered()), this, SLOT(clickedChangeRemark()));
    m_menu->addAction(actShow);
    m_menu->addAction(actRemark);
}

void CFriendItem::clickedShowInformation()
{

}

void CFriendItem::clickedChangeRemark()
{

}

void CFriendItem::clickedFriendButton()
{
    qDebug() << "clickedFriendButton " << endl;
	openChatRoom();
}

void CFriendItem::setButtonStatus()
{
	QString str = QString("pictures/%1.bmp").
        arg(QString::number(m_friInf.avatarNumber));

	QString text, mark;
    getStatusFromInt(m_friInf.status, m_strStatus);
    if(m_friInf.remark.isEmpty())
        mark = m_friInf.name;
	else
        mark = m_friInf.remark;
    if(OFFLINE==m_friInf.status || STEALTH==m_friInf.status)
    {
        QPixmap pixmap;
        QIcon icon(str);
        pixmap = icon.pixmap(QSize(AVATAR_SIZE, AVATAR_SIZE), QIcon::Disabled, QIcon::On);
        setIcon(pixmap);
        text = QString("%1 (%2)\n%3").arg(mark).arg(m_friInf.account).arg(m_strStatus);
    }
    else
    {
        setIcon( QIcon(str) );
        text = QString("%1(%2)\n%3").arg(mark).arg(m_friInf.account).arg(m_strStatus);
    }
    setText(text);
}

void CFriendItem::clickedRightButton(const QPoint &point)
{
    m_menu->exec(QCursor::pos());
}

void CFriendItem::openChatRoom()
{
    if(m_isOpen)
    {
        return;
    }

    m_room->show();
    m_isOpen = true;
}

void CFriendItem::chatRoomQuit()
{
    m_isOpen = false;
    m_room->hide();
}

void CFriendItem::changeRemark(const QString &newRemark)
{
    m_friInf.remark = newRemark;
	QString text = QString("%1(%2)\n%3").arg(newRemark)
        .arg(m_friInf.account).arg(m_strStatus);
	setText(text);
}

void CFriendItem::changeStatus(int status)
{
    getStatusFromInt(status, m_strStatus);
    QString text = QString("%1(%2)\n%3").arg(m_friInf.remark)
        .arg(m_friInf.account).arg(m_strStatus);
	setText(text);
}

void CFriendItem::closeChatRoom()
{
    if(m_isOpen)
	{
        m_room->close();
        m_isOpen = false;
	}
}

void CFriendItem::connected2server()
{

}

void CFriendItem::connect2serverFaild()
{

}

void CFriendItem::readBack(string data)
{
#ifdef DEBUG
    QMessageBox::information(NULL, ("check"),
        ("Test to connecte to server successful, and return is %s.", data.c_str()));
#endif
}



