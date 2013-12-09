#ifndef CLOGIN_H
#define CLOGIN_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QMessageBox>
#include "command/data.h"
#include "csettingdlg.h"
#include "command/command.h"
#include "cmaindlg.h"

namespace Ui
{
    class CLogin;
}

class CLogin : public QDialog
{
    Q_OBJECT
public:
    CLogin(CConnect *link, IMakeXml *xml, QWidget *parent = 0);
    ~CLogin();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::CLogin *ui;
    UserInformation     m_userinfo;
    IMakeXml            *m_MXml;
    CConnect            *m_link;
    CMainDlg            *m_maindlg;
    CSettingDlg         *m_settingDlg;

private:
    void initWnd();
    void initWidget();
    void initAction();

private slots:
    void close();
    void toSettingDlg();
    void submit();
    void settingClosed();
    void connected2server();
    void connect2serverFaild();
    void readBack(string data);
};

#endif // CLOGIN_H
