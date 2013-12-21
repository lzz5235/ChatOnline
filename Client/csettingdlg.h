#ifndef CSETTINGDLG_H
#define CSETTINGDLG_H

#include <QDialog>
#include <QSettings>
#include <QLabel>
#include "cgv.h"
#include "command/command.h"
#include "connect/connect.h"

namespace Ui
{
    class CSettingDlg;
}

class CSettingDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CSettingDlg(CConnect *link, IMakeXml *xml, QWidget *parent = 0);
    ~CSettingDlg();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::CSettingDlg *ui;
    QSettings       *m_sets;
    IMakeXml        *m_MXml;
    CConnect        *m_link;
    QLabel          *m_logo;
    bool            m_bActive;

private:
    void initWnd();
    void initAction();
    void disAction();
    bool loadSetting();

signals:
    void setClosed();

private slots:
    bool checkServer();
    void dlgClose();
    void submit();
    void connected2server();
    void connect2serverFaild();
    void readBack(string data);
};

#endif // CSETTINGDLG_H
