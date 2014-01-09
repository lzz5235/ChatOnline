#include "cbulletin.h"
#include "ui_bulletin.h"

cbulletin::cbulletin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cbulletin)
{
    ui->setupUi(this);
}

cbulletin::~cbulletin()
{
    delete ui;
}
