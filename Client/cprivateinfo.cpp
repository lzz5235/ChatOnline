#include "cprivateinfo.h"
#include "ui_cprivateinfo.h"

CPrivateInfo::CPrivateInfo(CConnect *link, IMakeXml *xml, UserInformation myself, QWidget *parent) :
    QDialog(parent),
    m_link(link),
    m_MXml(xml),
    m_userinfo(myself),
    ui(new Ui::CPrivateInfo)
{
    ui->setupUi(this);
    initWnd();
    initWidget();
    initAction();
}

CPrivateInfo::~CPrivateInfo()
{
    delete ui;
}

void CPrivateInfo::mousePressEvent(QMouseEvent * ev)
{
    QMouseEvent *mv = (QMouseEvent*) ev;
    if(mv->buttons() & Qt::LeftButton)
    {
        QRect labelrect = QRect(ui->lb_top->pos() + this->pos(), ui->lb_top->size());
        if(labelrect.contains(mv->globalPos()))
        {
            m_Ptbefore = mv->globalPos();
            m_Ptcur = mv->pos();
        }
    }
}

void CPrivateInfo::mouseMoveEvent(QMouseEvent *ev)
{
    QMouseEvent *mv = (QMouseEvent*) ev;
    QRect labelrect = QRect(ui->lb_top->pos() + this->pos(), ui->lb_top->size());
    if(labelrect.contains(mv->globalPos()))
    {
        this->move(mv->globalX() - m_Ptcur.rx(), mv->globalY() - m_Ptcur.ry());
        m_Ptbefore = mv->globalPos();
        sleep(0.1);
    }
}

bool CPrivateInfo::eventFilter(QObject *watched, QEvent *event)
{
  if( watched == this )
  {
      //窗口停用，变为不活动的窗口
      if(QEvent::WindowDeactivate == event->type())
      {
          qDebug() << "deactive status " << endl;
          disAction();
          return true ;
      }
      else
      {
          initAction();
          return false ;
      }
  }
  return false ;
}

void CPrivateInfo::closeEvent(QCloseEvent *)
{
    emit privateClose();
}

void CPrivateInfo::initWnd()
{
    //drop frame
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    //setFixedSize(MAINWNDWIDTH, MAINWNDHEIGH);

    QPalette pal;
    QPixmap pixmap( QDir::toNativeSeparators
            ("://resource/pic/back_set.png") );
    pal.setBrush(QPalette::Window, QBrush(pixmap));
    setPalette(pal);
    ui->lb_top->setStyleSheet("#lb_top{border-image:url(:resource/pic/top_bar.png);}");
    ui->pb_close->setStyleSheet("#pb_close{border-image:url(:resource/pic/close.png);}");
    ui->pb_min->setStyleSheet("#pb_min{border-image:url(:resource/pic/min.png);}");
    ui->pb_confirm->setStyleSheet("pb_record_2{border-image:url(:resource/pic/confirm.png);color: white;border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
                                   "#pb_record_2:hover{color: green;}");

    //将密码栏和验证密码栏设置为密码风格
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    ui->passwordLineEdit_2->setEchoMode(QLineEdit::Password);
    ui->confirmPwdLineEdit->setEchoMode(QLineEdit::Password);
    ui->nicknameLineEdit->setText(m_userinfo.nickName);
    ui->birthdayLineEdit->setText(m_userinfo.birthday);
    ui->mobileNumLineEdit->setText(m_userinfo.cellphone);
    ui->phoneNumLineEdit->setText(m_userinfo.officephone);
    ui->cityLineEdit->setText(QString("%1 %2").arg(m_userinfo.city).arg(m_userinfo.dormitory));
    ui->aboutTextEdit->setText(m_userinfo.description);
    ui->mail->setText(m_userinfo.mail);

    switch(m_userinfo.sex.toInt())
    {
    case MALE:
        ui->sex->setCurrentIndex(MALE);
        break;
    case FEMALE:
        ui->sex->setCurrentIndex(FEMALE);
        break;
    }
}

void CPrivateInfo::initWidget()
{
    //头像设置
    m_num = m_userinfo.avatarNumber;
    ui->avatarFrame->setObjectName("avatar");
    QString str = QString("QFrame#avatar{border-image:url(:/head/resource/head/%1.jpg)}")
        .arg(QString::number(m_userinfo.avatarNumber));
    ui->avatarFrame->setStyleSheet(str);
    ui->avatarLabel->setAlignment(Qt::AlignCenter);
    QString headNum = QString("%1 / %2").arg(QString::number(m_userinfo.avatarNumber)).arg(QString::number(allAvatar));
    ui->avatarLabel->setText(headNum);
    ui->accountLineEdit->setText(m_userinfo.account);
    ui->accountLineEdit->setReadOnly(true);
    ui->sex->insertItem(MALE, "男");
    ui->sex->insertItem(FEMALE, "女");
}

void CPrivateInfo::initAction()
{
    connect(ui->pb_close, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->pb_confirm, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->pastButton, SIGNAL(clicked()), this, SLOT(clickedPastButton()));
    connect(ui->nextButton, SIGNAL(clicked()), this, SLOT(clickedNextButton()));
    connect(ui->pb_confirm, SIGNAL(clicked()), this, SLOT(clickedConfirm()));
    connect(ui->quitPushButton, SIGNAL(clicked()), this, SLOT(close()));
}

void CPrivateInfo::disAction()
{
    disconnect(ui->pb_close, SIGNAL(clicked()), this, SLOT(close()));
    disconnect(ui->pb_confirm, SIGNAL(clicked()), this, SLOT(close()));
    disconnect(ui->pastButton, SIGNAL(clicked()), this, SLOT(clickedPastButton()));
    disconnect(ui->nextButton, SIGNAL(clicked()), this, SLOT(clickedNextButton()));
    disconnect(ui->pb_confirm, SIGNAL(clicked()), this, SLOT(clickedConfirm()));
    disconnect(ui->quitPushButton, SIGNAL(clicked()), this, SLOT(close()));
}

void CPrivateInfo::clickedPastButton()
{
    m_num--;
    if(m_num < 1)
        m_num = allAvatar;
    QString labelStr = QString("%1 / %2").arg(QString::number(m_num)).
        arg(QString::number(allAvatar));
    QString str = QString("QFrame#avatar{border-image:url(:/head/resource/head/%1.jpg)}")
        .arg(QString::number(m_num));
    ui->avatarFrame->setStyleSheet(str);
    ui->avatarLabel->setText(labelStr);
}

void CPrivateInfo::clickedNextButton()
{
    m_num++;
    if(m_num > allAvatar)
        m_num = 1;
    QString labelStr = QString("%1 / %2").arg(QString::number(m_num)).
        arg(QString::number(allAvatar));
    QString str = QString("QFrame#avatar{border-image:url(:/head/resource/head/%1.jpg)}")
        .arg(QString::number(m_num));
    ui->avatarFrame->setStyleSheet(str);
    ui->avatarLabel->setText(labelStr);
}

bool CPrivateInfo::informationRestrain()
{
    QRegExp regExp;
    regExp.setPattern("^[A-Za-z][A-Za-z0-9]{5,19}$");
    if(!regExp.exactMatch(ui->accountLineEdit->text()))
    {
        //QMessageBox::critical(this, "Error", "帐号格式错误，请再试一遍");
        QMessageBox::critical(this, tr("Error"),
            tr("Account's Format is wrong. Please try again"));
        return false;
    }

    if(ui->nicknameLineEdit->text().isEmpty()
        || ui->nicknameLineEdit->text().size() > 40)
    {
        //QMessageBox::critical(this, "Error", "呢称格式错误，请再试一遍");
        QMessageBox::critical(this, tr("Error"),
            tr("Nickname's Format is wrong. Please try again"));
        return false;
    }
    regExp.setPattern("(^(\\d{3,4}-)\\d{7,8})$|(1[0-9]{10})");
    if(!ui->phoneNumLineEdit->text().isEmpty() &&
        !regExp.exactMatch(ui->phoneNumLineEdit->text()))
    {
        //QMessageBox::critical(this, "Error", "密码格式错误，请再试一遍");
        QMessageBox::critical(this, tr("Error"),
            tr("Phone number's Format is wrong. Please try again"));
        return false;
    }
    if(!ui->mobileNumLineEdit->text().isEmpty() &&
        !regExp.exactMatch(ui->mobileNumLineEdit->text()))
    {
        //QMessageBox::critical(this, "Error", "密码格式错误，请再试一遍");
        QMessageBox::critical(this, tr("Error"),
            tr("Mobile number's Format is wrong. Please try again"));
        return false;
    }
    regExp.setPattern("^\\d{4}-\\d{1,2}-\\d{1,2}$");
    if( !regExp.exactMatch(ui->birthdayLineEdit->text())
        && !ui->birthdayLineEdit->text().isEmpty())
    {
        //QMessageBox::critical(this, "Error", "出生日期格式错误，请再试一遍");
        QMessageBox::critical(this, tr("Error"),
            tr("Birthday's Format is wrong. Please try again"));
        return false;
    }
    if(ui->cityLineEdit->text().size() > 40)
    {
        QMessageBox::critical(this, tr("Error"),
            tr("City's Format is wrong. Please try again"));
        return false;
    }
    if(ui->aboutTextEdit->toPlainText().size() > 400)
    {
        QMessageBox::critical(this, tr("Error"),
            tr("About myself's Format is wrong. Please try again"));
        return false;
    }
    return true;
}

bool CPrivateInfo::passwordRestrain()
{
    QRegExp regExp;
    regExp.setPattern("^[A-Za-z0-9]{6,20}$");
    if(!regExp.exactMatch(ui->passwordLineEdit->text()))
    {
        //QMessageBox::critical(this, "Error", "密码格式错误，请再试一遍");
        QMessageBox::critical(this, tr("Error"),
            tr("password's Format is wrong. Please try again"));
        return false;
    }

    if(ui->passwordLineEdit_2->text() != ui->confirmPwdLineEdit->text())
    {
        //QMessageBox::critical(this, "Error", "两次输入密码不相同，请再试一遍");
        QMessageBox::critical(this, tr("Error"),
            tr("The two passwords are not the same. Please try again"));
        return false;
    }
    return true;
}

void CPrivateInfo::updateMyInfo(UserInformation myinfo)
{
    m_userinfo = myinfo;
}

void CPrivateInfo::clickedConfirm()
{
    if(!informationRestrain())
    {
        this->show();
        return;
    }
    if(!passwordRestrain())
    {
        this->show();
        return;
    }

    UserInformation myself = m_userinfo;
    myself.avatarNumber = m_num;
    myself.birthday = ui->birthdayLineEdit->text();
    myself.cellphone = ui->mobileNumLineEdit->text();
    myself.nickName = ui->nicknameLineEdit->text();
    myself.dormitory = ui->cityLineEdit->text();
    myself.description = ui->aboutTextEdit->toPlainText();
    myself.mail = ui->mail->text();
    myself.officephone = ui->phoneNumLineEdit->text();
    myself.other = ui->aboutTextEdit->toPlainText();
    myself.age = ui->age->text().toInt();
    if(ui->sex->currentIndex() == MALE)
        myself.sex.setNum(MALE);
    else
        myself.sex.setNum(FEMALE);


    emit updatedMyInfo(myself);
}
