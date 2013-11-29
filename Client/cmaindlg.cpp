#include "cmaindlg.h"
#include "ui_cmaindlg.h"
#include <QDir>

CMainDlg::CMainDlg(CConnect *link, IMakeXml *xml, QWidget *parent):
    QDialog(parent),
    ui(new Ui::CMainDlg),
    m_link(link),
    m_MXml(xml)
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
    ui->lb_top->setStyleSheet("#lb_topbar{border-image:url(:resource/pic/top_bar.png);}");
    ui->pb_close->setStyleSheet("#pb_close{border-image:url(:resource/pic/close.png);}");

    ui->pb_addfriend->setHidden(true);
}

void CMainDlg::initWidget()
{

}

void CMainDlg::initAction()
{
    connect(ui->pb_close, SIGNAL(clicked()), this, SLOT(close()));
}

void CMainDlg::close()
{
    qApp->quit();
}
