#include "cfrienddlg.h"
#include "ui_cfrienddlg.h"

CFriendDlg::CFriendDlg(FriendInformation frd, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CFriendDlg),
    m_myfrd(frd)
{
    ui->setupUi(this);
    initWnd();
    initWidget();
    initAction();
}

CFriendDlg::~CFriendDlg()
{
    delete ui;
}

void CFriendDlg::mousePressEvent(QMouseEvent * ev)
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
    }
}

void CFriendDlg::mouseMoveEvent(QMouseEvent *ev)
{
    QMouseEvent *mv = (QMouseEvent*) ev;
    QRect labelrect = QRect(ui->lb_top->pos() + this->pos(), ui->lb_top->size());
    if(labelrect.contains(mv->globalPos()))
    {
        this->move(mv->globalX() - m_Ptcur.rx(), mv->globalY() - m_Ptcur.ry());
        m_Ptbefore = mv->globalPos();
        //sleep(0.1);
    }
}

void CFriendDlg::initWnd()
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
    ui->pb_min->setStyleSheet("#pb_min{border-image:url(:resource/pic/min.png);}");
    ui->le_address->setReadOnly(true);
    ui->le_age->setReadOnly(true);
    ui->le_cellphone->setReadOnly(true);
    ui->le_description->setReadOnly(true);
    ui->le_mail->setReadOnly(true);
    ui->le_officephone->setReadOnly(true);
    ui->le_sex->setReadOnly(true);
}

void CFriendDlg::initWidget()
{
    //头像设置
    ui->lb_headPic->setObjectName("avatar");
    QString str = QString("QFrame#avatar{border-image:url(:/head/resource/head/%1.jpg)}")
        .arg(QString::number(m_myfrd.avatarNumber));
    ui->lb_headPic->setStyleSheet(str);
    ui->lb_frdName->setAlignment(Qt::AlignHCenter);
    ui->lb_frdName->setText(m_myfrd.nickName);
    ui->le_address->setText(QString("%1 %2").arg(m_myfrd.city).arg(m_myfrd.dormitory));
    ui->le_age->setText(QString("%1").arg(m_myfrd.age));
    ui->le_cellphone->setText(m_myfrd.cellphone);
    ui->le_officephone->setText(m_myfrd.officephone);
    ui->le_description->setText(m_myfrd.other);
    ui->le_mail->setText(m_myfrd.mail);
    ui->le_sex->setText(m_myfrd.sex);
}

void CFriendDlg::initAction()
{
    connect(ui->pb_close, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->pb_min, SIGNAL(clicked()), this, SLOT(close()));
}
