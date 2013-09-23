#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete Myserver;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(! ui->textEdit->toPlainText().isEmpty() || ! ui->textEdit_2->toPlainText().isEmpty())
    {
        MAXCONNECTION = ui->textEdit_2->toPlainText().toInt();
        QThreadPool::globalInstance()->setMaxThreadCount(MAXCONNECTION);
        ui->textEdit_2->setEnabled(false);

        PORT = ui->textEdit->toPlainText().toInt();
        ui->textEdit->setEnabled(false);

        Myserver = new CServer(this);
        Myserver->StartServer(PORT);
    }
    else
    {
        QMessageBox::critical(this,tr("Alert!"),tr("Please input the port or MAXCONNECTION "),QMessageBox::Ok);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    exit(0);
}
