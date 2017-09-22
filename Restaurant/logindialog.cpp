#include "logindialog.h"
#include "ui_logindialog.h"
#include "stafflogin.h"
#include <QMessageBox>
#include <QKeyEvent>        //回车登陆

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("登陆"));
    this->setFixedSize(this->width(),this->height());//固定窗口大小
    ui->staffBtn->setDefault(false);
    ui->staffBtn->setFocusPolicy(Qt::NoFocus);
    //this->setStyleSheet("background-color:lavender;");//窗口背景颜色
    //this->setStyleSheet("border-image:url(:/images/backgnd.png);");//背景图片
    setAppearance();
    QWidget::setTabOrder(ui->pwdLineEdit, ui->loginBtn);
    connect(ui->regBtn, SIGNAL(clicked(bool)), this, SLOT(register_clicked()));
    connect(ui->loginBtn, SIGNAL(clicked(bool)), this, SLOT(login_clicked()));
    connect(ui->nameCmBox, SIGNAL(editTextChanged(QString)), this, SLOT(getUserInfo(QString)));//把手机号编辑框中的字符传给函数，判断账户是否存在
    connect(ui->pwdLineEdit, SIGNAL(returnPressed()), ui->loginBtn, SIGNAL(clicked()), Qt::UniqueConnection);   //回车绑定登陆按钮

    Data::dataInit();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::setAppearance(){
    QImage im;
    im.load(":/images/background.png");
    QPalette palette;
    palette.setBrush(this->backgroundRole(),QBrush(im.scaled(this->width(),this->height())));
    this->setPalette(palette);
    //this->setAutoFillBackground(true);
    //最好不要在顶层窗口使用StyleSheet否则会被所有子部件继承
    ui->nameCmBox->setCurrentText("");
    ui->pwdLineEdit->setEchoMode(QLineEdit::Password);//密码隐藏显示
    ui->pwdLabel->setStyleSheet("background:transparent;");
    ui->userLabel->setStyleSheet("background:transparent;");
    ui->userPic->setStyleSheet("background:transparent;");
    //ui->pwdLineEdit->setStyleSheet("background:transparent;");
    //设置默认头像
    QImage img;
    QString path0 = ":/images/default.png";
    img.load(path0);
    QPixmap def=QPixmap::fromImage(img.scaled(ui->userPic->width(),ui->userPic->height()));
    ui->userPic->setPixmap(def);
    //设置手机号和密码之前的图片
    QString path1 = ":/images/password.png";
    QString path2 = ":/images/phone.png";
    img.load(path1);
    QPixmap pic1=QPixmap::fromImage(img.scaled(ui->pwdLabel->width(),ui->pwdLabel->height()));
    ui->pwdLabel->setPixmap(pic1);
    img.load(path2);
    QPixmap pic2=QPixmap::fromImage(img.scaled(ui->userLabel->width(),ui->userLabel->height()));
    ui->userLabel->setPixmap(pic2);
    //设置登陆按钮样式
    //ui->loginBtn->setStyleSheet("QPushButton{background-color:cornflowerblue; color:white;border-radius: 10px;  border: 2px groove gray;border-style: outset;}");
    ui->loginBtn->setStyleSheet("QPushButton{background-color:cornflowerblue;\
                                color: white;   border-radius: 10px;  border: 2px groove gray;\
                                border-style: outset;}"
                               "QPushButton:hover{background-color:white; color: black;}"
                              "QPushButton:pressed{background-color:rgb(85, 170, 255);\
                                               border-style: inset; }"
                               );
    //ui->regBtn->setStyleSheet("QPushButton{background-color:mediumseagreen; color:white;border-radius: 10px;  border: 2px groove gray;border-style: outset;}");
    ui->regBtn->setStyleSheet("QPushButton{background-color:mediumseagreen;\
                              color: white;   border-radius: 10px;  border: 2px groove gray;\
                              border-style: outset;}"
                             "QPushButton:hover{background-color:white; color: black;}"
                            "QPushButton:pressed{background-color:rgb(85, 170, 255);\
                                             border-style: inset; }"
                             );
    ui->staffBtn->setStyleSheet("QPushButton{background-color:peachpuff;\
                                color: black;   border-radius: 13px;  border: 4px groove gray;\
                                border-style: outset;}"
                               "QPushButton:hover{background-color:white; color: black;}"
                              "QPushButton:pressed{background-color:rgb(85, 170, 255);\
                                               border-style: inset; }");
}

void LoginDialog::register_clicked(){
    RegisterDialog reg(this);
    this->hide();
    reg.show();
    transmitdb(database);
    //mark 此处应该让刚注册的id能够立即登陆
    reg.exec();
    this->show();
}

void LoginDialog::login_clicked(){      //此处应该对一些错误输入有提示功能
    if(ui->nameCmBox->currentText() == "admin"){
        QImage img;
        QString path = ":/images/admin.jpg";
        img.load(path);
        QPixmap pic=QPixmap::fromImage(img.scaled(ui->userPic->width(),ui->userPic->height()));
        ui->userPic->setPixmap(pic);
        if(ui->pwdLineEdit->text()=="admin"){
            adminDlg= new AdminDialog;
            adminDlg->show();
            ui->nameCmBox->clear();
            ui->pwdLineEdit->clear();
            ui->nameCmBox->setFocus();
            //adminDlg->exec();无所谓
            //this->close();
        }
        else{
            if(ui->pwdLineEdit->text() == "")
                QMessageBox::warning(this, tr("警告"), tr("请输入密码"));
            else{
                QMessageBox::warning(this, tr("警告"), tr("密码错误！"));
                ui->pwdLineEdit->clear();
            }
            ui->pwdLineEdit->setFocus();
        }
    }
    else if(matchFlag == false){      //matchFlag在getUserInfo函数中
        qDebug()<<"name invalid";   //用户不存在
        QMessageBox::warning(this, tr("警告"), tr("用户不存在"));
        ui->nameCmBox->clear();
        ui->pwdLineEdit->clear();   //清空用户名密码
        ui->nameCmBox->setFocus();  //光标重新移回输入手机号的LineEdit上
    }
    else{       //手机号在数据库中存在时
        if(userpwd!=ui->pwdLineEdit->text()){
            //密码错误
            qDebug()<<"password does not match";
            if(ui->pwdLineEdit->text() == "")
                QMessageBox::warning(this, tr("警告"), tr("请输入密码"));
            else{
                QMessageBox::warning(this, tr("警告"), tr("密码错误！"));
                ui->pwdLineEdit->clear();
            }
            ui->pwdLineEdit->setFocus();
        }
        else{
            if(ui->nameCmBox->currentText() ==""){
                QMessageBox::warning(this,tr("警告"), tr("用户名为空！"));
            }
            //用户名和密码均正确
            else{
                //qDebug()<<"matchflag ="<<matchFlag;
                QSqlQuery query;
                query.prepare("select * from user where phone = :phone");
                query.bindValue(":phone", ui->nameCmBox->currentText());
                query.exec();
                while(query.next()){
                    customerID = query.value(0).toInt();
                    qDebug()<<"customerID: "<<customerID;
                }
                selectTable* selectDialog = new selectTable;
                selectDialog->setCurrentID(customerID);     //传入当前登陆的用户账号，以便后面的交互操作
                selectDialog->show();
                ui->nameCmBox->clear();
                ui->pwdLineEdit->clear();
                ui->nameCmBox->setFocus();
                //this->close();
            }
        }
    }
}

//id, pwd, phone, name, isMember
void LoginDialog::getUserInfo(QString phone){
    QSqlQuery query;
    //查询手机号码数据
    QString tempstring = "select * from user where phone = '"+phone+"'";
    qDebug()<<tempstring;
    if(phone=="admin"){
        qDebug()<<"administrator";
        QImage img;
        QString path = ":/images/admin.jpg";
        img.load(path);
        QPixmap pic=QPixmap::fromImage(img.scaled(ui->userPic->width(),ui->userPic->height()));
        ui->userPic->setPixmap(pic);
        matchFlag=true;
    }
    else if(!query.exec(tempstring)){    //查找数据库中对应的号码
        qDebug()<<query.lastError();
        matchFlag = false;
    }
    else{
        while(query.next())//仅用于qDebug
        {
            userid = query.value(0).toInt();
            userpwd = query.value(1).toString();
            userphone = query.value(2).toString();
            username = query.value(3).toString();
            member = query.value(4).toInt();
            qDebug()<<QString("id=%1    pwd=%2    phone=%3   name=%4    isMember=%5").arg(userid).arg(userpwd).arg(userphone).arg(username).arg(member);
        }
        if(userphone == phone)
            matchFlag=true;
        else
            matchFlag=false;
    }

    qDebug()<<matchFlag;
   // /*
    if(matchFlag==true){
        /*
        QString path=":/images/user2.png";
        QString diff="user"+QString::number(userid);
        path.replace("userx",diff);
        qDebug()<<diff;
        qDebug()<<path;
        */
        QImage img;
        QString path = ":/images/admin.jpg";
        img.load(path);
        QPixmap pic=QPixmap::fromImage(img.scaled(ui->userPic->width(),ui->userPic->height()));
        ui->userPic->setPixmap(pic);
    }
    else{
        //QPixmap pic;
        //ui->userPic->setPixmap(pic);
        QImage img;
        QString path0 = ":/images/default.png";
        img.load(path0);
        QPixmap def=QPixmap::fromImage(img.scaled(ui->userPic->width(),ui->userPic->height()));
        ui->userPic->setPixmap(def);
    }
}

void LoginDialog::on_staffBtn_clicked()
{
    staffLogin* staff = new staffLogin;
    staff->show();
    staff->exec();
    //this->close();
}
