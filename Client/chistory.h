#ifndef CHISTORY_H
#define CHISTORY_H

#include <QDir>
#include <QDialog>
#include "command/data.h"
#include <QTextCodec>
#include "command/data.h"

namespace Ui {
class CHistory;
}

class CHistory : public QDialog
{
    Q_OBJECT

public:
    explicit CHistory(FriendInformation frd, QString strhistory, QWidget *parent = 0);
    ~CHistory();

private:
    Ui::CHistory    *ui;
    QString         m_history;

private:
    void initWnd();
    void initWidget();
    void initAction();
};

#endif // CHISTORY_H
