#ifndef CMAINDLG_H
#define CMAINDLG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QSignalMapper>
#include "command/command.h"
#include "connect/connect.h"
#include "command/data.h"
#include "frienditem.h"
#include "cgv.h"
#include "cchatroom.h"
#include "caboutdlg.h"
#include "cprivateinfo.h"

namespace Ui {
    class CMainDlg;
}

class CMainDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CMainDlg(CConnect *link, IMakeXml *xml, UserInformation *myself, QWidget *parent = 0);
    void initFriends(QVector<FriendInformation> &vcFriends);
    ~CMainDlg();

protected:
    void mousePressEvent(QMouseEvent * ev);
    void mouseMoveEvent(QMouseEvent *ev);

private:
    Ui::CMainDlg    *ui;
    QVBoxLayout     *layout;
    QGroupBox       *groupBox;

private:
    //托盘图标和它的按钮
    QSystemTrayIcon *trayIcon;
    QAction         *onlineAction;
    QAction         *talkAction;
    QAction         *busyAction;
    QAction         *leaveAction;
    QAction         *disturbAction;
    QAction         *stealthAction;
    QAction         *quitAction;
    QMenu           *trayIconMenu;
    QSignalMapper   *trayMap;
    QTimer          *m_animation;

    //右下角功能菜单
    QMenu           *m_mnFuture;
    QAction         *m_acTest;
    QAction         *m_acAbout;

    CChatRoom       *m_room;
    CPrivateInfo    *m_privateSetDlg;

    //创建托盘图标
    void createTrayIcon();
    void createFutureMenu();
    void setStatusFromInt(int n, QString &str) const;

private:
    void initWnd();
    void initWidget();
    void initAction();
    void updateFriends();
    void insertItem(FriendInformation &frd);
    void initMyself();
    void privateSet();

    template <typename T>
    void rotateWidget(T *t, float angle, QString &img)
    {
        QMatrix leftmatrix;
        leftmatrix.rotate(angle);
        t->setIcon(QPixmap(img).transformed(leftmatrix, Qt::SmoothTransformation));
    }

private slots:
    void close();
    void connected2server();
    void connect2serverFaild();
    void readBack(string data);
    void changeState(int n);
    void ontrayIconactivated(QSystemTrayIcon::ActivationReason reason);
    void editFinished();
    void furuteAbout();
    void showFutureWnd();
    void animationStop();
    void animationShake();

private:
    IMakeXml                            *m_MXml;
    CConnect                            *m_link;
    QVector<FriendInformation>          m_vcFriends;
    QMap<QString, CFriendItem*>         m_frndMap;
    UserInformation                     *m_myself;
    QPoint                              m_Ptbefore;
    QPoint                              m_Ptcur;
};

#endif // CMAINDLG_H
