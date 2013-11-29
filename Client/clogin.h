#ifndef CLOGIN_H
#define CLOGIN_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
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
    QLabel              *m_lb_username ;
    QLabel              *m_lb_userpassword;
    QLabel              *m_lb_curtime;
    QLineEdit           *m_le_username;
    QLineEdit           *m_le_userpassword;
    QComboBox           *m_lt_status;
    QPushButton         *m_pb_Login;
    QPushButton         *m_pb_set;
    UserInformation     *m_userinfo;
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
};

#endif // CLOGIN_H
