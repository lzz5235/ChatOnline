/********************************************************************************
** Form generated from reading UI file 'clogin.ui'
**
** Created: Tue Oct 8 20:34:56 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLOGIN_H
#define UI_CLOGIN_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QComboBox>
#include <QDialog>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CLogin
{
public:
    QPushButton *pb_login;
    QPushButton *pb_set;
    QComboBox *cb_status;
    QLineEdit *le_username;
    QLineEdit *le_userpassword;
    QLabel *username;
    QLabel *userpassword;
    QLabel *lb_curtime;
    QLabel *lb_logo;
    QPushButton *pb_about;
    QPushButton *pb_close;
    QLabel *lb_topbar;
    QLabel *lb_warnning;

    void setupUi(QDialog *CLogin)
    {
        if (CLogin->objectName().isEmpty())
            CLogin->setObjectName(QString::fromUtf8("CLogin"));
        CLogin->setWindowModality(Qt::NonModal);
        CLogin->resize(320, 285);
        pb_login = new QPushButton(CLogin);
        pb_login->setObjectName(QString::fromUtf8("pb_login"));
        pb_login->setGeometry(QRect(60, 230, 201, 41));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        pb_login->setFont(font);
        pb_login->setCursor(QCursor(Qt::OpenHandCursor));
        pb_set = new QPushButton(CLogin);
        pb_set->setObjectName(QString::fromUtf8("pb_set"));
        pb_set->setGeometry(QRect(254, 5, 20, 20));
        cb_status = new QComboBox(CLogin);
        cb_status->setObjectName(QString::fromUtf8("cb_status"));
        cb_status->setGeometry(QRect(220, 200, 69, 22));
        le_username = new QLineEdit(CLogin);
        le_username->setObjectName(QString::fromUtf8("le_username"));
        le_username->setGeometry(QRect(80, 80, 211, 50));
        QFont font1;
        font1.setPointSize(20);
        le_username->setFont(font1);
        le_userpassword = new QLineEdit(CLogin);
        le_userpassword->setObjectName(QString::fromUtf8("le_userpassword"));
        le_userpassword->setGeometry(QRect(80, 140, 211, 50));
        le_userpassword->setFont(font1);
        username = new QLabel(CLogin);
        username->setObjectName(QString::fromUtf8("username"));
        username->setGeometry(QRect(30, 80, 54, 12));
        userpassword = new QLabel(CLogin);
        userpassword->setObjectName(QString::fromUtf8("userpassword"));
        userpassword->setGeometry(QRect(30, 140, 54, 12));
        lb_curtime = new QLabel(CLogin);
        lb_curtime->setObjectName(QString::fromUtf8("lb_curtime"));
        lb_curtime->setGeometry(QRect(40, 200, 81, 16));
        lb_logo = new QLabel(CLogin);
        lb_logo->setObjectName(QString::fromUtf8("lb_logo"));
        lb_logo->setGeometry(QRect(5, 5, 24, 24));
        pb_about = new QPushButton(CLogin);
        pb_about->setObjectName(QString::fromUtf8("pb_about"));
        pb_about->setGeometry(QRect(272, 5, 20, 20));
        pb_close = new QPushButton(CLogin);
        pb_close->setObjectName(QString::fromUtf8("pb_close"));
        pb_close->setGeometry(QRect(290, 5, 20, 20));
        lb_topbar = new QLabel(CLogin);
        lb_topbar->setObjectName(QString::fromUtf8("lb_topbar"));
        lb_topbar->setGeometry(QRect(0, 0, 321, 31));
        lb_warnning = new QLabel(CLogin);
        lb_warnning->setObjectName(QString::fromUtf8("lb_warnning"));
        lb_warnning->setGeometry(QRect(70, 50, 181, 16));
        lb_topbar->raise();
        pb_login->raise();
        pb_set->raise();
        cb_status->raise();
        le_username->raise();
        le_userpassword->raise();
        username->raise();
        userpassword->raise();
        lb_curtime->raise();
        lb_logo->raise();
        pb_about->raise();
        pb_close->raise();
        lb_warnning->raise();

        retranslateUi(CLogin);

        QMetaObject::connectSlotsByName(CLogin);
    } // setupUi

    void retranslateUi(QDialog *CLogin)
    {
        CLogin->setWindowTitle(QApplication::translate("CLogin", "Dialog", 0));
        pb_login->setText(QString());
        pb_set->setText(QString());
        username->setText(QString());
        userpassword->setText(QString());
        lb_curtime->setText(QString());
        lb_logo->setText(QString());
        pb_about->setText(QString());
        pb_close->setText(QString());
        lb_topbar->setText(QString());
        lb_warnning->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CLogin: public Ui_CLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLOGIN_H
