#include "talkdlg.h"
#include "ui_ctalkdlg.h"

CTalkDlg::CTalkDlg(CConnect *link, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CTalkDlg)
{
    ui->setupUi(this);
}

CTalkDlg::~CTalkDlg()
{
    delete ui;
}
