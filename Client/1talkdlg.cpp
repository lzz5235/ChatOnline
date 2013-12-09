#include "talkdlg.h"
#include "ui_CTalkDlg.h"

CTalkDlg::CTalkDlg(CConnect *link, IMakeXml *xml, FriendInformation frd,QWidget *parent)
   :QDialog(parent),
    ui(new Ui::CTalkDlg),
    m_link(link),
    m_MXml(xml),
    m_frd(frd)
{
    ui->setupUi(this);
    initWnd();
    initWidget();
    initAction();
}

CTalkDlg::~CTalkDlg()
{
    delete ui;
}

void CTalkDlg::initWnd()
{
    //drop frame
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    setFixedSize(wndSizeWidth, wndSizeHeight);

    QPalette pal;
    QPixmap pixmap( QDir::toNativeSeparators
            (":resource/pic/back.png") );
    pal.setBrush(QPalette::Window, QBrush(pixmap));
    setPalette(pal);

    ui->pb_close->setStyleSheet("#pb_close{border-image:url(:resource/pic/close.png);}");
}

void CTalkDlg::initWidget()
{

}

void CTalkDlg::initAction()
{
    connect(ui->pb_close, SIGNAL(clicked()), this, SLOT(close()));
    connect(m_link, SIGNAL(connectedsuccessful()), this, SLOT(connected2server()));
    connect(m_link, SIGNAL(connectionFailedSignal()),this, SLOT(connect2serverFaild()));
    connect(m_link, SIGNAL(dataIsReady(string)), this, SLOT(readBack(string)));
}

void CTalkDlg::connected2server()
{

}

void CTalkDlg::connect2serverFaild()
{

}

void CTalkDlg::readBack(string data)
{

}












