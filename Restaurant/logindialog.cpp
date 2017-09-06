#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include "mainwindow.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("登陆"));
    this->setFixedSize(this->width(),this->height());//固定窗口大小

    this->setStyleSheet("background-color:lavender;");//窗口背景颜色
    //this->setStyleSheet("border-image:url(:/images/backgnd.png);");//背景图片
    QImage im;
    im.load(":/images/room2.png");
    QPalette palette;
    palette.setBrush(this->backgroundRole(),QBrush(im.scaled(this->width(),this->height())));
    this->setPalette(palette);
    //this->setAutoFillBackground(true);
    //最好不要在顶层窗口使用StyleSheet否则会被所有子部件继承
    ui->pwdLineEdit->setEchoMode(QLineEdit::Password);//密码隐藏显示
    ui->pwdLabel->setStyleSheet("background:transparent;");
    ui->userLabel->setStyleSheet("background:transparent;");
    ui->userPic->setStyleSheet("background:opaque;");
    //ui->pwdLineEdit->setStyleSheet("background:transparent;");
    //设置默认头像
    QImage img;
    QString path0 = ":/images/abc.jpg";
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
    ui->loginBtn->setStyleSheet("QPushButton{background-color:cornflowerblue; color:white;border-radius: 10px;  border: 2px groove gray;border-style: outset;}");
    ui->regBtn->setStyleSheet("QPushButton{background-color:mediumseagreen; color:white;border-radius: 10px;  border: 2px groove gray;border-style: outset;}");

    connect(ui->regBtn, SIGNAL(clicked(bool)), this, SLOT(register_clicked()));
    connect(ui->loginBtn, SIGNAL(clicked(bool)), this, SLOT(login_clicked()));
    connect(ui->nameCmBox, SIGNAL(editTextChanged(QString)), this, SLOT(getUserInfo(QString)));//把手机号编辑框中的字符传给函数，判断账户是否存在

    //打开数据库文件
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
//以下验证table是否存在
        query.prepare(select_table);
        if(!query.exec()){
                    qDebug()<<query.lastError();
                }
                else{
                    QString tableName;
                    while(query.next()){
                        tableName = query.value(0).toString();
                        qDebug()<<tableName;
                        if(tableName.compare("user")){  //string比对相同返回0
                            tableFlag=false;
                            qDebug()<<"table does not exist";
                        }
                        else{
                            tableFlag=true;
                            qDebug()<<"table exists";
                        }
                    }
                }
        if(tableFlag==false)        //初次打开时table不存在
             {
                 query.prepare(create_user);
                 if(!query.exec()){
                     qDebug()<<query.lastError();
                 }
                 else{
                     qDebug()<<"table created!";
                 }
             }
    }
//=============================================对账户数据库的连接结束
    //Data dt;
    //Data::dataInit();

//从数据库取出数据
    /*
    Data dt;
    Data::dataInit();
    qDebug()<<"Data::a=="<<Data::a<<"\n\n";

    QSqlQuery query;
    int id;
    query.prepare("select * from user");
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    while(query.next()){
        id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString tel = query.value(2).toString();
        qDebug()<<QString("id:%1    pwd:%2   phone:%3").arg(id).arg(name).arg(tel);
    }
    qDebug()<<"test";
    query.clear();
*/
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

void LoginDialog::login_clicked(){      //此处应该对一些错误输入有提示功能
    if(matchFlag == false){      //matchFlag在getUserInfo函数中
        qDebug()<<"name invalid";   //用户不存在
        QMessageBox::warning(this, tr("警告"), tr("用户不存在"));
        ui->nameCmBox->clear();
        ui->pwdLineEdit->clear();   //清空用户名密码
        ui->nameCmBox->setFocus();  //光标重新移回输入手机号的LineEdit上
    }
    else{       //手机号在数据库中存在时
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
            if(ui->nameCmBox->currentText() ==""){
                QMessageBox::warning(this,tr("警告"), tr("用户名为空！"));
            }
            //用户名和密码均正确
            else if(ui->nameCmBox->currentText() == "admin"&&ui->pwdLineEdit->text()=="admin"){
                adminDlg= new AdminDialog;
                adminDlg->show();
                //adminDlg->exec();无所谓
                this->close();
            }
            else{
                qDebug()<<"matchflag ="<<matchFlag;
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
    if(!query.exec(tempstring)){    //查找数据库中对应的号码
        qDebug()<<query.lastError();
        matchFlag = false;
    }
    else{
        while(query.next())//仅用于debug
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
        //QPixmap pic;
        //ui->userPic->setPixmap(pic);
        QImage img;
        QString path0 = ":/images/default.png";
        img.load(path0);
        QPixmap def=QPixmap::fromImage(img.scaled(ui->userPic->width(),ui->userPic->height()));
        ui->userPic->setPixmap(def);
    }
//  */
}
