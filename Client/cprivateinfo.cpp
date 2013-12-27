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
    //QWidget::installEventFilter(this);
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
    ui->confirmPwdLineEdit->setEchoMode(QLineEdit::Password);
}

void CPrivateInfo::initWidget()
{
    //头像设置
    m_num = 1;
    ui->avatarFrame->setObjectName("avatar");
    QString str = QString("QFrame#avatar{border-image:url(:/head/resource/head/%1.jpg)}")
        .arg(QString::number(m_num));
    ui->avatarFrame->setStyleSheet(str);
    ui->avatarLabel->setAlignment(Qt::AlignCenter);
    QString headNum = QString("1 / %1").arg(QString::number(allAvatar));
    ui->avatarLabel->setText(headNum);
}

void CPrivateInfo::initAction()
{
    connect(ui->pb_close, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->pb_confirm, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->pastButton, SIGNAL(clicked()), this, SLOT(clickedPastButton()));
    connect(ui->nextButton, SIGNAL(clicked()), this, SLOT(clickedNextButton()));
    connect(ui->pb_confirm, SIGNAL(clicked()), this, SLOT(clickedConfirm()));

}

void CPrivateInfo::disAction()
{
    disconnect(ui->pb_close, SIGNAL(clicked()), this, SLOT(close()));
    disconnect(ui->pb_confirm, SIGNAL(clicked()), this, SLOT(close()));
    disconnect(ui->pastButton, SIGNAL(clicked()), this, SLOT(clickedPastButton()));
    disconnect(ui->nextButton, SIGNAL(clicked()), this, SLOT(clickedNextButton()));
    disconnect(ui->pb_confirm, SIGNAL(clicked()), this, SLOT(clickedConfirm()));
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
    regExp.setPattern("^\\d{0,15}$");
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

    if(ui->passwordLineEdit->text() != ui->confirmPwdLineEdit->text())
    {
        //QMessageBox::critical(this, "Error", "两次输入密码不相同，请再试一遍");
        QMessageBox::critical(this, tr("Error"),
            tr("The two passwords are not the same. Please try again"));
        return false;
    }
    return true;
}

void CPrivateInfo::clickedConfirm()
{
    if(informationRestrain())
        passwordRestrain();
}

void CPrivateInfo::connected2server()
{
    qDebug() << "login connected successful!" << endl;
}

void CPrivateInfo::connect2serverFaild()
{
    qDebug() << "login connected faild" << endl;
}

void CPrivateInfo::readBack(string data)
{
#ifdef DEBUG
    QMessageBox::information(NULL, ("check"),
        ("CPrivateInfo Test to connecte to server successful, and return is %s.", data.c_str()));
#endif


    //m_MXml->parseRsp(data, )
}