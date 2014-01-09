#include "caboutdlg.h"
#include "ui_caboutdlg.h"

CAboutDlg::CAboutDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAboutDlg)
{
    ui->setupUi(this);
    initWnd();
    initWidget();
    initAction();
}

CAboutDlg::~CAboutDlg()
{
    delete ui;
}

void CAboutDlg::mousePressEvent(QMouseEvent * ev)
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

void CAboutDlg::mouseMoveEvent(QMouseEvent *ev)
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

void CAboutDlg::initWnd()
{
    //drop frame
    Qt::WindowFlags flags = Qt::Widget;
    flags |= Qt::WindowStaysOnTopHint;

    setWindowFlags(flags | Qt::FramelessWindowHint);
    //setFixedSize(MAINWNDWIDTH, MAINWNDHEIGH);

    QPalette pal;
    QPixmap pixmap( QDir::toNativeSeparators
            ("://resource/pic/back_set.png") );
    pal.setBrush(QPalette::Window, QBrush(pixmap));
    setPalette(pal);
    ui->lb_top->setStyleSheet("#lb_top{border-image:url(:resource/pic/top_bar.png);}");
    ui->pb_close->setStyleSheet("#pb_close{border-image:url(:resource/pic/close.png);}");
    ui->pb_min->setStyleSheet("#pb_min{border-image:url(:resource/pic/min.png);}");
    ui->pb_confirm->setStyleSheet("pb_record_2{border-image:url(:resource/pic/confirm.png);color: white;border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
                                   "#pb_record_2:hover{color: green;}");
}

void CAboutDlg::initWidget()
{

}

void CAboutDlg::initAction()
{
    connect(ui->pb_close, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->pb_confirm, SIGNAL(clicked()), this, SLOT(close()));
}
