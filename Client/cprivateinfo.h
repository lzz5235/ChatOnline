#ifndef CPRIVATEINFO_H
#define CPRIVATEINFO_H

#include <QDialog>
#include <QDir>
#include <QPoint>
#include <QMouseEvent>
#include <QMessageBox>
#include "command/IMakeXml.h"
#include "connect/connect.h"

namespace Ui {
class CPrivateInfo;
}

class CPrivateInfo : public QDialog
{
    Q_OBJECT

public:
    explicit CPrivateInfo(CConnect *link, IMakeXml *xml, UserInformation myself, QWidget *parent = 0);
    ~CPrivateInfo();
    void updateMyInfo(UserInformation myinfo);

private:
    CConnect            *m_link;
    IMakeXml            *m_MXml;
    UserInformation     m_userinfo;
    Ui::CPrivateInfo    *ui;
    QPoint              m_Ptbefore;
    QPoint              m_Ptcur;
    qint32              m_num;

protected:
    void mousePressEvent(QMouseEvent * ev);
    void mouseMoveEvent(QMouseEvent *ev);
    bool eventFilter(QObject *watched, QEvent *event);
    void closeEvent(QCloseEvent *);

private:
    void initWnd();
    void initWidget();
    void initAction();
    void disAction();
    bool informationRestrain();
    bool passwordRestrain();

public slots:
    void clickedPastButton();
    void clickedNextButton();
    void clickedConfirm();

signals:
    void privateClose();
    void updatedMyInfo(UserInformation);
};

#endif // CPRIVATEINFO_H
