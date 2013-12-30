#include "chistory.h"
#include "ui_chistory.h"

CHistory::CHistory(FriendInformation frd,
                   QString strhistory,
                   QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CHistory),
    m_history(strhistory)
{
    ui->setupUi(this);
    initWnd();
    initWidget();
    initAction();
}

CHistory::~CHistory()
{
    delete ui;
}


void CHistory::initWnd()
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
}

void CHistory::initWidget()
{
    ui->tb_history->setText(m_history);
}

void CHistory::initAction()
{
    connect(ui->pb_close, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->pb_min, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->pb_confirm, SIGNAL(clicked()), this, SLOT(close()));
}
