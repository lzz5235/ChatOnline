/********************************************************************************
** Form generated from reading UI file 'cmaindlg.ui'
**
** Created: Mon Oct 7 10:42:55 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMAINDLG_H
#define UI_CMAINDLG_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QDialog>
#include <QFrame>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QToolBox>
#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_CMainDlg
{
public:
    QToolBox        *tb_friend;
    QWidget         *page;
    QFrame          *f_myself;
    QLineEdit       *lb_myselfinfo;
    QPushButton     *pb_addfriend;
    QPushButton     *pb_setting;
    QPushButton     *pb_fresh;
    QLabel          *lb_top;
    QPushButton     *pb_close;
    QPushButton     *pb_min;
    QLabel          *lb_status;
    QLabel          *lb_myNickName;
    QLabel          *lb_topbar;
    QLabel          *lb_buttonbar;

    void setupUi(QDialog *CMainDlg)
    {
        if (CMainDlg->objectName().isEmpty())
            CMainDlg->setObjectName(QString::fromUtf8("CMainDlg"));
        CMainDlg->resize(192, 515);
        tb_friend = new QToolBox(CMainDlg);
        tb_friend->setObjectName(QString::fromUtf8("tb_friend"));
        tb_friend->setGeometry(QRect(40, 100, 111, 361));
        f_myself = new QFrame(CMainDlg);
        f_myself->setObjectName(QString::fromUtf8("f_myself"));
        f_myself->setGeometry(QRect(30, 35, 80, 80));
        f_myself->setFrameShape(QFrame::StyledPanel);
        f_myself->setFrameShadow(QFrame::Raised);
        lb_myselfinfo = new QLineEdit(CMainDlg);
        lb_myselfinfo->setObjectName(QString::fromUtf8("lb_myselfinfo"));
        lb_myselfinfo->setGeometry(QRect(120, 85, 90, 20));
        lb_myselfinfo->setStyleSheet("#lb_myselfinfo{border-width:0;border-style:outset;background-color:rgba(235,235,235,0)}");
        lb_top = new QLabel(CMainDlg);
        lb_top->setObjectName(QString::fromUtf8("lb_topbar"));
        lb_top->setGeometry(QRect(0, 0, 230, 30));
        lb_status = new QLabel(CMainDlg);
        lb_status->setObjectName(QString::fromUtf8("lb_status"));
        lb_status->setGeometry(QRect(93, 99, 11, 11));
        lb_myNickName = new QLabel(CMainDlg);
        lb_myNickName->setObjectName(QString::fromUtf8("lb_myNickName"));
        lb_myNickName->setGeometry(QRect(120, 60, 90, 20));
        lb_topbar = new QLabel(CMainDlg);
        lb_topbar->setObjectName(QString::fromUtf8("lb_topbar"));
        lb_topbar->setGeometry(QRect(0, 130, 250, 2));
        lb_buttonbar = new QLabel(CMainDlg);
        lb_buttonbar->setObjectName(QString::fromUtf8("lb_buttonbar"));
        lb_buttonbar->setGeometry(QRect(0, 635, 250, 2));
        pb_addfriend = new QPushButton(CMainDlg);
        pb_addfriend->setObjectName(QString::fromUtf8("pb_addfriend"));
        pb_addfriend->setGeometry(QRect(120, 650, 23, 23));
        pb_setting = new QPushButton(CMainDlg);
        pb_setting->setObjectName(QString::fromUtf8("pb_setting"));
        pb_setting->setGeometry(QRect(180, 640, 41, 41));
        pb_fresh = new QPushButton(CMainDlg);
        pb_fresh->setObjectName(QString::fromUtf8("pb_fresh"));
        pb_fresh->setGeometry(QRect(150, 650, 23, 23));
        pb_close = new QPushButton(CMainDlg);
        pb_close->setObjectName(QString::fromUtf8("pb_close"));
        pb_close->setGeometry(QRect(205, 5, 20, 20));
        pb_min = new QPushButton(CMainDlg);
        pb_min->setObjectName(QString::fromUtf8("pb_min"));
        pb_min->setGeometry(QRect(184, 5, 20, 20));
        retranslateUi(CMainDlg);
        lb_status->raise();
        lb_myselfinfo->raise();
        lb_myNickName->raise();

        tb_friend->setCurrentIndex(0);
        tb_friend->removeItem(0);
        tb_friend->setGeometry(QRect(22, 130, 185, 501));

        QMetaObject::connectSlotsByName(CMainDlg);
        tb_friend->setFocus();

    } // setupUi

    void retranslateUi(QDialog *CMainDlg)
    {
        CMainDlg->setWindowTitle(QApplication::translate("CMainDlg", "Dialog", 0));
        lb_myselfinfo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CMainDlg: public Ui_CMainDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMAINDLG_H
