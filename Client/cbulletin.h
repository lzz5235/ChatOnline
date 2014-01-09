#ifndef CBULLETIN_H
#define CBULLETIN_H

#include <QDialog>

namespace Ui {
class cbulletin;
}

class cbulletin : public QDialog
{
    Q_OBJECT

public:
    explicit cbulletin(QWidget *parent = 0);
    ~cbulletin();

private:
    Ui::cbulletin *ui;
};

#endif // CBULLETIN_H
