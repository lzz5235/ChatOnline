#ifndef FRIENDBUTTON_H_
#define FRIENDBUTTON_H_

#include "connect/connect.h"
#include "cchatroom.h"
#include "command/IMakeXml.h"
#include "cmaindlg.h"
#include "extern.h"
#include <QMenu>
#include <QStyle>
#include <QTimer>
#include <QToolButton>
#include <QMessageBox>

class CChatRoom;

//放置在主窗口的好友按钮
class CFriendItem : public QToolButton
{
	Q_OBJECT

public:
    CFriendItem(IMakeXml *xml, const FriendInformation &theFriend, UserInformation &myself, CMainDlg *parent = 0);
    ~CFriendItem();

	bool isRoomOpen() const
    {
        return m_isOpen;
    }
    CChatRoom *getRoomPoint() const
    {
        return m_room;
    }
	FriendInformation &getInformation()
    {
        return m_friInf;
    }
	FriendInformation getInformation() const
    {
        return m_friInf;
    }

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    QString                     m_Account;
    QString                     m_Name;
    QString                     m_strStatus;
    FriendInformation           m_friInf;
    UserInformation             m_myself;
    bool                        m_isOpen;
    CChatRoom                   *m_room;
    //右键菜单
    QMenu                       *m_menu;
    CMainDlg                    *m_parent;
    IMakeXml                    *m_xml;
    QTimer                      *m_msgTipTimer;
    QSize                       m_normalIconSize;

private:
    //将好友状态从数字形式转换为字符串形式
    void getStatusFromInt(int n, QString &str) const;
    void creatMenu();
    void openChatRoom();
    void setButtonStatus();
    void closeChatRoom();
    void initWnd();
    void initWidget();
    void initAction();
    void disAction();

signals:
    //void deleteFriendSignal(const QString &peerAccount);
    void sendMessage(XMLPARA);

public slots:
    void clickedFriendButton();
    void clickedRightButton(const QPoint &);
    void clickedShowInformation();
    void clickedChangeRemark();
    //聊天窗口关闭了
    void chatRoomQuit();
    //修改好友状态
    void changeRemark(const QString &newRemark);
    void changeStatus(int status);
    void messageTip(recordItem);
    void changeIcon();
};

#endif
