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

QT_BEGIN_NAMESPACE

class Ui_CMainDlg
{
public:
    QToolBox *tb_friend;
    QWidget *page;
    QFrame *f_myself;
    QLabel *lb_myselfinfo;
    QPushButton *pb_addfriend;
    QPushButton *pb_setting;
    QPushButton *pb_fresh;
    QLabel      *lb_top;
    QPushButton *pb_close;

    void setupUi(QDialog *CMainDlg)
    {
        if (CMainDlg->objectName().isEmpty())
            CMainDlg->setObjectName(QString::fromUtf8("CMainDlg"));
        CMainDlg->resize(192, 515);
        tb_friend = new QToolBox(CMainDlg);
        tb_friend->setObjectName(QString::fromUtf8("tb_friend"));
        tb_friend->setGeometry(QRect(40, 100, 111, 361));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setGeometry(QRect(30, 150, 171, 481));
        tb_friend->addItem(page, QString::fromUtf8("Page 1"));
        f_myself = new QFrame(CMainDlg);
        f_myself->setObjectName(QString::fromUtf8("f_myself"));
        f_myself->setGeometry(QRect(30, 30, 80, 80));
        f_myself->setFrameShape(QFrame::StyledPanel);
        f_myself->setFrameShadow(QFrame::Raised);
        lb_myselfinfo = new QLabel(CMainDlg);
        lb_myselfinfo->setObjectName(QString::fromUtf8("lb_myselfinfo"));
        lb_myselfinfo->setGeometry(QRect(120, 30, 80, 80));
        lb_top = new QLabel(CMainDlg);
        lb_top->setObjectName(QString::fromUtf8("lb_topbar"));
        lb_top->setGeometry(QRect(0, 0, 230, 30));
        pb_addfriend = new QPushButton(CMainDlg);
        pb_addfriend->setObjectName(QString::fromUtf8("pb_addfriend"));
        pb_addfriend->setGeometry(QRect(120, 650, 23, 23));
        pb_setting = new QPushButton(CMainDlg);
        pb_setting->setObjectName(QString::fromUtf8("pb_setting"));
        pb_setting->setGeometry(QRect(170, 640, 41, 41));
        pb_fresh = new QPushButton(CMainDlg);
        pb_fresh->setObjectName(QString::fromUtf8("pb_fresh"));
        pb_fresh->setGeometry(QRect(140, 650, 23, 23));
        pb_close = new QPushButton(CMainDlg);
        pb_close->setObjectName(QString::fromUtf8("pb_close"));
        pb_close->setGeometry(QRect(205, 5, 20, 20));
        retranslateUi(CMainDlg);

        tb_friend->setCurrentIndex(0);
        tb_friend->setGeometry(QRect(30, 130, 171, 481));

        QMetaObject::connectSlotsByName(CMainDlg);
    } // setupUi

    void retranslateUi(QDialog *CMainDlg)
    {
        CMainDlg->setWindowTitle(QApplication::translate("CMainDlg", "Dialog", 0));
        tb_friend->setItemText(tb_friend->indexOf(page), QApplication::translate("CMainDlg", "Page 1", 0));
        lb_myselfinfo->setText(QString());
        pb_addfriend->setText(QApplication::translate("CMainDlg", "+", 0));
        pb_setting->setText(QApplication::translate("CMainDlg", "gear", 0));
        pb_fresh->setText(QApplication::translate("CMainDlg", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class CMainDlg: public Ui_CMainDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMAINDLG_H
