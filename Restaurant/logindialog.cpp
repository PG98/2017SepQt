#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include "mainwindow.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("登陆系统"));
    ui->pwdLineEdit->setEchoMode(QLineEdit::Password);

    ui->loginBtn->setStyleSheet("QPushButton{background-color:black; color:white;border-radius: 10px;  border: 2px groove gray;border-style: outset;}");

    connect(ui->regBtn, SIGNAL(clicked(bool)), this, SLOT(register_clicked()));
    connect(ui->loginBtn, SIGNAL(clicked(bool)), this, SLOT(login_clicked()));
    connect(ui->nameCmBox, SIGNAL(editTextChanged(QString)), this, SLOT(getUserInfo(QString)));

    tableFlag = false;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("database.db");

    if(!database.open()){
        qDebug()<<database.lastError();
        qFatal("failed to connect");
    }
    else{
        qDebug()<<"open success";
        QSqlQuery query;

        query.prepare(select_table);
        if(!query.exec())
                {
                    qDebug()<<query.lastError();
                }
                else
                {
                    QString tableName;
                    while(query.next())
                    {
                        tableName = query.value(0).toString();
                        qDebug()<<tableName;
                        if(tableName.compare("user"))
                        {
                            tableFlag=false;
                            qDebug()<<"table does not exist";
                        }
                        else
                        {
                            tableFlag=true;
                            qDebug()<<"table exists";
                        }
                    }
                }
        if(tableFlag==false)
             {
                 query.prepare(create_sql);
                 if(!query.exec())
                 {
                     qDebug()<<query.lastError();
                 }
                 else
                 {
                     qDebug()<<"table created!";
                 }
             }

    }
}

LoginDialog::~LoginDialog()
{
    delete ui;
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

void LoginDialog::login_clicked(){      //mark此处应该对一些错误输入有提示功能
    if(matchFlag == false){      //matchFlag在getUserInfo函数中
        qDebug()<<"name invalid";   //用户不存在
        QMessageBox::warning(this, tr("警告"), tr("用户不存在"));
        ui->nameCmBox->clear();
        ui->pwdLineEdit->clear();   //清空用户名密码
        ui->nameCmBox->setFocus();  //光标重新移回输入手机号的LineEdit上
    }
    else{
        if(userpwd!=ui->pwdLineEdit->text()){
            //密码错误
            qDebug()<<"password  does not match";
            if(ui->pwdLineEdit->text() == "")
                QMessageBox::warning(this, tr("警告"), tr("请输入密码"));
            else{
                QMessageBox::warning(this, tr("警告"), tr("密码错误！"));
                ui->pwdLineEdit->clear();
            }
            ui->pwdLineEdit->setFocus();
        }
        else{
            //用户名和密码均正确
            if(ui->nameCmBox->currentText() == "admin"){
                AdminWindow admin(this);
                this->hide();
                //admin.show();
                //admin.exec();
                MainWindow w;
                w.show();
                //this->close();
            }
            else{
                orderChart order(this);
                this->hide();
                order.show();
                order.exec();
                this->close();
            }
        }
    }
}

//id, pwd, phone, email, history
void LoginDialog::getUserInfo(QString phone){
    QSqlQuery query;
    //查询手机号码数据
    QString tempstring = "select * from user where phone = '"+phone+"'";
    qDebug()<<tempstring;
    if(!query.exec(tempstring)){
        qDebug()<<query.lastError();
        matchFlag = false;
    }
    else{
        while(query.next())
        {
            userid = query.value(0).toInt();
            userpwd = query.value(1).toString();
            userphone = query.value(2).toString();
            userEmail = query.value(3).toString();
            userHistory = query.value(4).toInt();

            qDebug()<<QString("id=%1    pwd=%2    phone=%3   email=%4    history=%5").arg(userid).arg(userpwd).arg(userphone).arg(userEmail).arg(userHistory);

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
        QPixmap pic;
        ui->userPic->setPixmap(pic);
    }
//  */
}






