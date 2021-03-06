#ifndef CMAINDLG_H
#define CMAINDLG_H

#include <QTimer>
#include <QMutex>
#include <QDialog>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QPropertyAnimation>
#include <QSignalMapper>
#include "command/command.h"
#include "connect/connect.h"
#include "command/data.h"
#include "frienditem.h"
#include "cgv.h"
#include "cchatroom.h"
#include "caboutdlg.h"
#include "cprivateinfo.h"

class CChatRoom;
class CFriendItem;

namespace Ui {
    class CMainDlg;
}

class CMainDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CMainDlg(CConnect *link, IMakeXml *xml, UserInformation *myself, QWidget *parent = 0);
    ~CMainDlg();

protected:
    void mousePressEvent(QMouseEvent * ev);
    void mouseMoveEvent(QMouseEvent *ev);
    bool eventFilter(QObject *watched, QEvent *event);

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
    void disAction();
    void updateFriends();
    void insertItem(FriendInformation &frd);
    void initMyself();
    void initMyDataDir();
    void createHistory();
    void privateSet();
    void getMessage(string &data);
    void getAddress(string &data);
    void getloginedInfo(string &data);
    void getNewUpdate(string &data);
    void getResult(string &data);

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
    void futureTest();
    void showFutureWnd();
    void animationStop();
    void animationShake();
    void initFriends(string strWho = "-1");
    void closePrivateDlg();
    void saveHistory();
    void write2File(QString, historyItem);
    void readFromHistoryItemForSave(QFile *, recordItem);
    void sendMessage(XMLPARA);
    void rotateUpdateIcon();
    void updateMyself(UserInformation);

private:
    IMakeXml                            *m_MXml;
    CConnect                            *m_link;
    QVector<FriendInformation>          m_vcFriends;
    QMap<QString, CFriendItem*>         m_frndMap;
    UserInformation                     *m_myself;
    QPoint                              m_Ptbefore;
    QPoint                              m_Ptcur;
    bool                                m_privateOpen;
    QMap<QString, historyItem>          m_allHistory;
    QTimer                              *m_cycleSaveHistory;
    QTimer                              *m_cycleRotateUpdateIcon;
    QMutex                              m_mtxHistory;
    int                                 m_iAngel;

signals:
    void getSuccessful(recordItem);
};

#endif // CMAINDLG_H
