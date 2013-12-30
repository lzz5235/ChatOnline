#include "frienditem.h"

CFriendItem::CFriendItem(IMakeXml *xml,
                         const FriendInformation &theFriend,
                         UserInformation &myself,
                         CMainDlg *parent):
    m_friInf(theFriend),
    m_Account(myself.account),
    m_Name(myself.nickName),
    m_myself(myself),
    m_parent(parent),
    m_xml(xml)
{
    initWnd();
    initWidget();
    initAction();
    //QWidget::installEventFilter(this);
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

    m_pAnimation = new QPropertyAnimation(this, "geometry");
    QRect geo = this->geometry();
    m_pAnimation->setDuration(5000);
    m_pAnimation->setKeyValueAt(0.0,QRect(geo.x(),geo.y(),width(),height()));
    m_pAnimation->setKeyValueAt(0.25,QRect(geo.x()-2,geo.y()+2,width(),height()));
    m_pAnimation->setKeyValueAt(0.5,QRect(geo.x(),geo.y(),width(),height()));
    m_pAnimation->setKeyValueAt(0.75,QRect(geo.x()+2,geo.y()+2,width(),height()));
    m_pAnimation->setKeyValueAt(1.0,QRect(geo.x(),geo.y(),width(),height()));
    m_pAnimation->start();
}

void CFriendItem::initWidget()
{
    m_room = new CChatRoom(m_xml, m_myself, m_friInf, m_parent);
    m_room->setWindowFlags(Qt::FramelessWindowHint);
}

void CFriendItem::initAction()
{
    connect(m_room, SIGNAL(closeWnd()), this, SLOT(chatRoomQuit()));
    connect(this, SIGNAL(clicked()), this, SLOT(clickedFriendButton()));
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(clickedRightButton(const QPoint &)));
    connect(m_room, SIGNAL(sendMessage(XMLPARA)), this, SIGNAL(sendMessage(XMLPARA)));
    connect(m_parent, SIGNAL(getSuccessful(recordItem)), this, SLOT(startAnimation(recordItem)));
}

void CFriendItem::disAction()
{
    disconnect(m_room, SIGNAL(closeWnd()), this, SLOT(chatRoomQuit()));
    disconnect(this, SIGNAL(clicked()), this, SLOT(clickedFriendButton()));
    disconnect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(clickedRightButton(const QPoint &)));

}

bool CFriendItem::eventFilter(QObject *watched, QEvent *event)
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
    if(m_room)
        m_room->friendInfo();
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

    if(m_pAnimation)
        m_pAnimation->stop();
    m_room->show();
    m_isOpen = true;
}

void CFriendItem::chatRoomQuit()
{
    m_room->hide();
    m_isOpen = false;
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
        m_room->hide();
        m_isOpen = false;
	}
}

void CFriendItem::startAnimation(recordItem record)
{
    if ( NULL != m_pAnimation && record.sendid == QString::number(m_friInf.userID))
    {
        m_pAnimation->start();
    }
}


