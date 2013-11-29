/********************************************************************************
** Form generated from reading UI file 'ctalkdlg.ui'
**
** Created: Mon Oct 7 10:42:55 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CTALKDLG_H
#define UI_CTALKDLG_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QDialog>
#include <QFrame>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_CTalkDlg
{
public:
    QTextEdit *te_output;
    QTextEdit *textEdit;
    QFrame *f_otherside;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *lb_othersidedes;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pb_close;
    QPushButton *pb_send;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *pb_setfont;
    QSpacerItem *horizontalSpacer;
    QPushButton *pb_record;

    void setupUi(QDialog *CTalkDlg)
    {
        if (CTalkDlg->objectName().isEmpty())
            CTalkDlg->setObjectName(QString::fromUtf8("CTalkDlg"));
        CTalkDlg->resize(447, 437);
        te_output = new QTextEdit(CTalkDlg);
        te_output->setObjectName(QString::fromUtf8("te_output"));
        te_output->setGeometry(QRect(10, 30, 311, 221));
        textEdit = new QTextEdit(CTalkDlg);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 300, 311, 91));
        f_otherside = new QFrame(CTalkDlg);
        f_otherside->setObjectName(QString::fromUtf8("f_otherside"));
        f_otherside->setGeometry(QRect(330, 30, 101, 80));
        f_otherside->setFrameShape(QFrame::StyledPanel);
        f_otherside->setFrameShadow(QFrame::Raised);
        verticalLayoutWidget = new QWidget(f_otherside);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(-10, -10, 121, 401));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(CTalkDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(330, 120, 120, 40));
        lb_othersidedes = new QLabel(CTalkDlg);
        lb_othersidedes->setObjectName(QString::fromUtf8("lb_othersidedes"));
        lb_othersidedes->setGeometry(QRect(330, 180, 101, 231));
        verticalLayoutWidget_2 = new QWidget(CTalkDlg);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(330, 29, 111, 391));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayoutWidget_3 = new QWidget(CTalkDlg);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(10, 30, 311, 401));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(CTalkDlg);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 400, 312, 25));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_2 = new QSpacerItem(148, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        pb_close = new QPushButton(widget);
        pb_close->setObjectName(QString::fromUtf8("pb_close"));

        gridLayout->addWidget(pb_close, 0, 1, 1, 1);

        pb_send = new QPushButton(widget);
        pb_send->setObjectName(QString::fromUtf8("pb_send"));

        gridLayout->addWidget(pb_send, 0, 2, 1, 1);

        widget1 = new QWidget(CTalkDlg);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(11, 261, 312, 25));
        horizontalLayout = new QHBoxLayout(widget1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pb_setfont = new QPushButton(widget1);
        pb_setfont->setObjectName(QString::fromUtf8("pb_setfont"));

        horizontalLayout->addWidget(pb_setfont);

        horizontalSpacer = new QSpacerItem(148, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pb_record = new QPushButton(widget1);
        pb_record->setObjectName(QString::fromUtf8("pb_record"));

        horizontalLayout->addWidget(pb_record);


        retranslateUi(CTalkDlg);

        QMetaObject::connectSlotsByName(CTalkDlg);
    } // setupUi

    void retranslateUi(QDialog *CTalkDlg)
    {
        CTalkDlg->setWindowTitle(QApplication::translate("CTalkDlg", "Dialog", 0));
        label->setText(QApplication::translate("CTalkDlg", "\346\217\220\347\244\272\357\274\232\n"
"\346\214\211\344\270\213Ctrl+Enter\n"
"\345\217\257\344\273\245\347\233\264\346\216\245\345\217\221\351\200\201\344\277\241\346\201\257", 0));
        lb_othersidedes->setText(QString());
        pb_close->setText(QApplication::translate("CTalkDlg", "close", 0));
        pb_send->setText(QApplication::translate("CTalkDlg", "send", 0));
        pb_setfont->setText(QApplication::translate("CTalkDlg", "setFont", 0));
        pb_record->setText(QApplication::translate("CTalkDlg", "chatHistory", 0));
    } // retranslateUi

};

namespace Ui {
    class CTalkDlg: public Ui_CTalkDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CTALKDLG_H
