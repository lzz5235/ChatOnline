#ifndef CMAINDLG_H
#define CMAINDLG_H

#include <QDialog>
#include "command/command.h"
#include "connect/connect.h"

namespace Ui {
    class CMainDlg;
}

class CMainDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CMainDlg(CConnect *link, IMakeXml *xml, QWidget *parent = 0);
    ~CMainDlg();

private:
    Ui::CMainDlg *ui;

private:
    void initWnd();
    void initWidget();
    void initAction();

private slots:
    void close();

private:
    IMakeXml    *m_MXml;
    CConnect    *m_link;
};

#endif // CMAINDLG_H
