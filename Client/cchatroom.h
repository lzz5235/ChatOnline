#ifndef CCHATROOM_H
#define CCHATROOM_H

#include <QDialog>
#include <QDir>
#include <QMouseEvent>
#include "frienditem.h"
#include "command/data.h"
#include "connect/connect.h"
#include "cfrienddlg.h"

namespace Ui {
class CChatRoom;
}

class CChatRoom : public QDialog
{
    Q_OBJECT

public:
    explicit CChatRoom(CConnect *link, IMakeXml *xml, UserInformation myself, FriendInformation frd, QWidget *parent = 0);
    ~CChatRoom();
    bool OnClose();

private:
    Ui::CChatRoom                       *ui;
    IMakeXml                            *m_MXml;
    CConnect                            *m_link;
    UserInformation                     m_myself;
    FriendInformation                   m_friend;
    QPoint                              m_Ptbefore;
    QPoint                              m_Ptcur;
    bool                                m_bAtClose;
    CFriendDlg                          *m_myfriendinfo;

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
    void connected2server();
    void connect2serverFaild();
    void readBack(string data);

signals:
    void closeWnd();
};

#endif // CCHATROOM_H
