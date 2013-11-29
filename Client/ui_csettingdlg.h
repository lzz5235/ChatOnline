/********************************************************************************
** Form generated from reading UI file 'csettingdlg.ui'
**
** Created: Mon Oct 7 10:42:55 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CSETTINGDLG_H
#define UI_CSETTINGDLG_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QDialog>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_CSettingDlg
{
public:
    QLabel *lb_topbar;
    QLabel *lb_serverIP;
    QLineEdit *le_ip;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QLineEdit *lineEdit_3;
    QLabel *label_3;
    QLineEdit *le_port;
    QLabel *lb_serverPort;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pb_test;
    QSpacerItem *horizontalSpacer;
    QPushButton *pb_cancel;
    QPushButton *pb_confirm;
    QLabel  *lb_logo;
    QPushButton *pb_close;

    void setupUi(QDialog *CSettingDlg)
    {
        if (CSettingDlg->objectName().isEmpty())
            CSettingDlg->setObjectName(QString::fromUtf8("CSettingDlg"));
        CSettingDlg->resize(640, 480);
        lb_topbar = new QLabel(CSettingDlg);
        lb_topbar->setObjectName(QString::fromUtf8("lb_topbar"));
        lb_topbar->setGeometry(QRect(0, 0, 641, 30));
        lb_serverIP = new QLabel(CSettingDlg);
        lb_serverIP->setObjectName(QString::fromUtf8("lb_serverIP"));
        lb_serverIP->setGeometry(QRect(30, 120, 54, 12));
        le_ip = new QLineEdit(CSettingDlg);
        le_ip->setObjectName(QString::fromUtf8("le_ip"));
        le_ip->setGeometry(QRect(110, 100, 201, 50));
        lineEdit_2 = new QLineEdit(CSettingDlg);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(110, 170, 201, 50));
        label_2 = new QLabel(CSettingDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 190, 54, 12));
        lineEdit_3 = new QLineEdit(CSettingDlg);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(400, 170, 201, 50));
        label_3 = new QLabel(CSettingDlg);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(320, 190, 54, 12));
        le_port = new QLineEdit(CSettingDlg);
        le_port->setObjectName(QString::fromUtf8("le_port"));
        le_port->setGeometry(QRect(400, 100, 201, 50));
        lb_serverPort = new QLabel(CSettingDlg);
        lb_serverPort->setObjectName(QString::fromUtf8("lb_serverPort"));
        lb_serverPort->setGeometry(QRect(320, 120, 54, 12));
        lb_logo = new QLabel(CSettingDlg);
        lb_logo->setObjectName(QString::fromUtf8("lb_logo"));
        lb_logo->setGeometry(QRect(5, 5, 24, 24));
        horizontalLayoutWidget = new QWidget(CSettingDlg);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(40, 420, 571, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pb_test = new QPushButton(CSettingDlg);
        pb_test->setObjectName(QString::fromUtf8("pb_test"));
        pb_test->setGeometry(QRect(40, 402, 66, 31));
        pb_close = new QPushButton(CSettingDlg);
        pb_close->setObjectName(QString::fromUtf8("pb_close"));
        pb_close->setGeometry(QRect(615, 5, 20, 20));

        pb_cancel = new QPushButton(CSettingDlg);
        pb_cancel->setObjectName(QString::fromUtf8("pb_cancel"));
        pb_cancel->setGeometry(QRect(475, 402, 66, 31));

        pb_confirm = new QPushButton(CSettingDlg);
        pb_confirm->setObjectName(QString::fromUtf8("pb_confirm"));
        pb_confirm->setGeometry(QRect(545, 402, 66, 31));

        retranslateUi(CSettingDlg);

        QMetaObject::connectSlotsByName(CSettingDlg);
    } // setupUi

    void retranslateUi(QDialog *CSettingDlg)
    {
        CSettingDlg->setWindowTitle(QApplication::translate("CSettingDlg", "Dialog", 0));
        lb_topbar->setText(QString());
        lb_serverIP->setText(QApplication::translate("CSettingDlg", "serverIP", 0));
        label_2->setText(QApplication::translate("CSettingDlg", "TextLabel", 0));
        label_3->setText(QApplication::translate("CSettingDlg", "TextLabel", 0));
        lb_serverPort->setText(QApplication::translate("CSettingDlg", "serverPort", 0));
        pb_test->setText(QApplication::translate("CSettingDlg", "link", 0));
        pb_cancel->setText(QApplication::translate("CSettingDlg", "Cancle(&C)", 0));
        pb_confirm->setText(QApplication::translate("CSettingDlg", "confirm", 0));
    } // retranslateUi

};

namespace Ui {
    class CSettingDlg: public Ui_CSettingDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CSETTINGDLG_H
