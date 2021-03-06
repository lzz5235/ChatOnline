#ifndef CCHATROOM_H
#define CCHATROOM_H

#include <QDialog>
#include <QDir>
#include <QMouseEvent>
#include "frienditem.h"
#include "command/data.h"
#include "connect/connect.h"
#include "cfrienddlg.h"
#include "cmaindlg.h"
#include "chistory.h"

class CMainDlg;

namespace Ui {
class CChatRoom;
}

class CChatRoom : public QDialog
{
    Q_OBJECT

public:
    explicit CChatRoom(IMakeXml *xml, UserInformation myself, FriendInformation frd, CMainDlg *parent = 0);
    ~CChatRoom();
    bool OnClose();

private:
    Ui::CChatRoom                       *ui;
    UserInformation                     m_myself;
    FriendInformation                   m_friend;
    QPoint                              m_Ptbefore;
    QPoint                              m_Ptcur;
    bool                                m_bAtClose;
    CFriendDlg                          *m_myfriendinfo;
    CMainDlg                            *m_parent;
    IMakeXml                            *m_xml;
    CHistory                            *m_history;

protected:
    void mousePressEvent(QMouseEvent * ev);
    void mouseMoveEvent(QMouseEvent *ev);
    bool eventFilter(QObject *watched, QEvent *event);
    void mouseReleaseEvent(QMouseEvent *);

private:
    void initWnd();
    void initWidget();
    void initAction();
    void disAction();

public:
    void friendInfo();

private slots:
    void pressSendMessage();
    void updateHistory(recordItem);
    void readHistory();

signals:
    void closeWnd();
    void sendMessage(XMLPARA);
};

#endif // CCHATROOM_H
