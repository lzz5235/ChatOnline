#include "cchatroom.h"
#include "ui_cchatroom.h"

CChatRoom::CChatRoom(CConnect *link, IMakeXml *xml, UserInformation myself, FriendInformation frd, QWidget *parent) :
    ui(new Ui::CChatRoom),
    m_link(link),
    m_MXml(xml),
    m_myself(myself),
    m_friend(frd),
    m_myfriendinfo(NULL)
{
    ui->setupUi(this);
    initWnd();
    initWidget();
    initAction();
    QWidget::installEventFilter(this);
}

CChatRoom::~CChatRoom()
{
    delete ui;
}

void CChatRoom::mousePressEvent(QMouseEvent * ev)
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

        QRect frnpic = QRect(ui->f_otherside->pos() + this->pos(), ui->f_otherside->size());
        if(frnpic.contains(mv->globalPos()))
        {
            friendInfo();
        }
    }
}


void CChatRoom::mouseReleaseEvent(QMouseEvent * ev)
{
    QMouseEvent *mv = (QMouseEvent*) ev;
    if(mv->buttons() & Qt::LeftButton)
    {
        QRect frnpic = QRect(ui->f_otherside->pos() + this->pos(), ui->f_otherside->size());
        if(frnpic.contains(mv->globalPos()))
        {
            friendInfo();
        }
    }
}

void CChatRoom::mouseMoveEvent(QMouseEvent *ev)
{
    QMouseEvent *mv = (QMouseEvent*) ev;
    QRect labelrect = QRect(ui->lb_top->pos() + this->pos(), ui->lb_top->size());
    if(labelrect.contains(mv->globalPos()))
    {
        this->move(mv->globalX() - m_Ptcur.rx(), mv->globalY() - m_Ptcur.ry());
        m_Ptbefore = mv->globalPos();
        sleep(0.1);
    }
}

bool CChatRoom::eventFilter(QObject *watched, QEvent *event)
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

void CChatRoom::initWnd()
{
    //drop frame
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    //setFixedSize(MAINWNDWIDTH, MAINWNDHEIGH);

    QPalette pal;
    QPixmap pixmap( QDir::toNativeSeparators
            ("://resource/pic/back_set.png") );
    pal.setBrush(QPalette::Window, QBrush(pixmap));
    setPalette(pal);
    ui->lb_top->setStyleSheet("#lb_top{border-image:url(:resource/pic/top_bar.png);}");
    ui->pb_close->setStyleSheet("#pb_close{border-image:url(:resource/pic/close.png);}");
    ui->pb_close_3->setStyleSheet("pb_close_3{border-image:url(:resource/pic/confirm.png);color: white;border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
                                  "#pb_close_3:hover{color: green;}");
    ui->pb_min->setStyleSheet("#pb_min{border-image:url(:resource/pic/min.png);}");
    ui->pb_record_2->setStyleSheet("pb_record_2{border-image:url(:resource/pic/confirm.png);color: white;border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
                                   "#pb_record_2:hover{color: green;}");
    ui->pb_send_2->setStyleSheet("pb_send_2{border-image:url(:resource/pic/confirm.png);color: white;border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
                                 "#pb_send_2:hover{color: green;}");
    ui->pb_setfont_2->setStyleSheet("pb_setfont_2{border-image:url(:resource/pic/confirm.png);color: white;border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
                                    "#pb_setfont_2:hover{color: green;}");
}

void CChatRoom::initWidget()
{
    ui->pb_close_3->setText("关闭");
    ui->pb_send_2->setText("发送");
    ui->pb_setfont_2->setText("Font");
    ui->pb_record_2->setText("历史纪录");

    QString strIcon = QString("#f_otherside{border-image:url(:head/resource/head/%1.jpg)}").arg(m_friend.avatarNumber);
    ui->f_otherside->setStyleSheet(strIcon);
    ui->lb_friendInfo->setText(m_friend.nickName);
    ui->lb_friendInfo->setAlignment(Qt::AlignHCenter);
}

void CChatRoom::initAction()
{
    connect(ui->pb_close, SIGNAL(clicked()), this, SIGNAL(closeWnd()));

    //because qt showminimize() function is not work
    connect(ui->pb_min, SIGNAL(clicked()), this, SIGNAL(closeWnd()));
    connect(m_link, SIGNAL(connectedsuccessful()), this, SLOT(connected2server()));
    connect(m_link, SIGNAL(connectionFailedSignal()),this, SLOT(connect2serverFaild()));
    //connect(m_link, SIGNAL(dataIsReady(string)), this, SLOT(readBack(string)));
}

void CChatRoom::disAction()
{
    disconnect(ui->pb_close, SIGNAL(clicked()), this, SIGNAL(closeWnd()));
    disconnect(m_link, SIGNAL(connectedsuccessful()), this, SLOT(connected2server()));
    disconnect(m_link, SIGNAL(connectionFailedSignal()),this, SLOT(connect2serverFaild()));
    //disconnect(m_link, SIGNAL(dataIsReady(string)), this, SLOT(readBack(string)));
}

void CChatRoom::connected2server()
{

}

void CChatRoom::connect2serverFaild()
{

}

void CChatRoom::readBack(string data)
{
#ifdef DEBUG
    QMessageBox::information(NULL, ("check"),
        ("CChatRoom Test to connecte to server successful, and return is %s.", data.c_str()));
#endif
}

void CChatRoom::friendInfo()
{
    if(NULL == m_myfriendinfo)
    {
        m_myfriendinfo = new CFriendDlg(m_friend);
        m_myfriendinfo->setWindowFlags(Qt::FramelessWindowHint);
        m_myfriendinfo->show();
    }

    if(m_myfriendinfo->isActiveWindow())
    {
        return;
    }
    else
    {
        m_myfriendinfo->show();
    }
}