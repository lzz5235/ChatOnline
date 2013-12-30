#ifndef CABOUTDLG_H
#define CABOUTDLG_H

#include <QDialog>
#include <QDir>
#include <QPoint>
#include <QMouseEvent>
#include <QTextCodec>
#include "command/data.h"

namespace Ui {
class CAboutDlg;
}

class CAboutDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CAboutDlg(QWidget *parent = 0);
    ~CAboutDlg();

private:
    Ui::CAboutDlg                       *ui;
    QPoint                              m_Ptbefore;
    QPoint                              m_Ptcur;

protected:
    void mousePressEvent(QMouseEvent * ev);
    void mouseMoveEvent(QMouseEvent *ev);

private:
    void initWnd();
    void initWidget();
    void initAction();
};

#endif // CABOUTDLG_H
