#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "command/command.h"
#include "connect/connect.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(CConnect *link, QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

private:
    IMakeXml    *m_MXml;
    CConnect    *m_link;
};

#endif // MAINWINDOW_H
