#ifndef TALKDLG_H
#define TALKDLG_H

#include <QDialog>
#include "command/command.h"
#include "connect/connect.h"

namespace Ui {
    class CTalkDlg;
}

class CTalkDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CTalkDlg(CConnect *link, QWidget *parent = 0);
    ~CTalkDlg();

private:
    Ui::CTalkDlg *ui;

private:
    IMakeXml    *m_MXml;
    CConnect    *m_link;
};

#endif // TALKDLG_H
