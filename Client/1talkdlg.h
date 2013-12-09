#ifndef TALKDLG_H
#define TALKDLG_H

#include <QDialog>
#include <QDir>
#include "command/command.h"
#include "connect/connect.h"

namespace Ui {
    class CTalkDlg;
}

class CTalkDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CTalkDlg(CConnect *link, IMakeXml *xml, FriendInformation frd,QWidget *parent = 0);
    ~CTalkDlg();

private:
    Ui::CTalkDlg *ui;

private:
    void initWnd();
    void initWidget();
    void initAction();

private:
    IMakeXml            *m_MXml;
    CConnect            *m_link;
    FriendInformation   m_frd;

private slots:
    void connected2server();
    void connect2serverFaild();
    void readBack(string data);
};

#endif // TALKDLG_H
