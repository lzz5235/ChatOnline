#ifndef FRIENDBUTTON_H_
#define FRIENDBUTTON_H_

#include "connect/connect.h"
#include "cchatroom.h"
#include "command/IMakeXml.h"
#include "extern.h"
#include <QMenu>
#include <QTimer>
#include <QToolButton>
#include <QMessageBox>

class CChatRoom;

//放置在主窗口的好友按钮
class CFriendItem : public QToolButton
{
	Q_OBJECT

public:
    CFriendItem(CConnect *tLink, IMakeXml *xml,const FriendInformation &theFriend, UserInformation &myself, QWidget *parent = 0);
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


private:
    QString             m_Account;
    QString             m_Name;
    QString             m_strStatus;
    FriendInformation   m_friInf;
    UserInformation     m_myself;
    bool                m_isOpen;
    CConnect            *m_link;
    IMakeXml            *m_MXml;
    CChatRoom           *m_room;
    //右键菜单
    QMenu               *m_menu;

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

signals:
    //void deleteFriendSignal(const QString &peerAccount);

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
    void connected2server();
    void connect2serverFaild();
    void readBack(string data);
};

#endif
