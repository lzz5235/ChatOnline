#ifndef CFRIENDDLG_H
#define CFRIENDDLG_H

#include <QDir>
#include <QDialog>
#include <QMouseEvent>
#include "command/data.h"
#include "utilities/FuncTools.h"

namespace Ui {
class CFriendDlg;
}

class CFriendDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CFriendDlg(FriendInformation frd, QWidget *parent = 0);
    ~CFriendDlg();

protected:
    void mousePressEvent(QMouseEvent * ev);
    void mouseMoveEvent(QMouseEvent *ev);

private:
    Ui::CFriendDlg      *ui;
    FriendInformation   m_myfrd;
    int                 m_num;
    QPoint              m_Ptbefore;
    QPoint              m_Ptcur;


private:
    void initWnd();
    void initWidget();
    void initAction();
};

#endif // CFRIENDDLG_H
