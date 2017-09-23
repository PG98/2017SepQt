#include "registerdialog.h"
#include "ui_registerdialog.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog){
    ui->setupUi(this);
    ui->pwdLineEdit1->setEchoMode(QLineEdit::Password);
    ui->pwdLineEdit2->setEchoMode(QLineEdit::Password);
    connect(ui->OKBtn, SIGNAL(clicked(bool)), this, SLOT(OKBtn_clicked()));
    connect(ui->CancelBtn, SIGNAL(clicked(bool)), this, SLOT(CancelBtn_clicked()));
}

RegisterDialog::~RegisterDialog(){
    delete ui;
}

QString select_max_user = "select max(id) from user";
QString insert_user = "insert into user values (?, ?, ?, ?, ?)";
QString select_phone = "select phone from user";

void RegisterDialog::OKBtn_clicked(){
    bool phoneFlag = false;
    //bool pwdFlag = false;
    int newid;
    QString newpwd = NULL;
    QString newphone = NULL;
    QString newname = ui->EmailLineEdit->text();

    if(ui->pwdLineEdit1->text()==""||ui->pwdLineEdit2->text()==""){
        QMessageBox::warning(this, tr("警告"), tr("请输入密码"));
        ui->pwdLineEdit1->clear();
        ui->pwdLineEdit2->clear();
        ui->pwdLineEdit1->setFocus();
        return;
    }
    else if(ui->pwdLineEdit1->text() != ui->pwdLineEdit2->text()){
        QMessageBox::warning(this, tr("警告"), tr("两次输入密码不同"));
        ui->pwdLineEdit1->clear();
        ui->pwdLineEdit2->clear();
        ui->pwdLineEdit1->setFocus();
        return;
    }
    //以下为数据库操作
    QSqlQuery query;
    //找出最大id编号
    max_id = 0;
    query.prepare(select_max_user);
    if(!query.exec()){
        qDebug()<<query.lastError();
    }
    else{
        while(query.next()){
            max_id = query.value(0).toInt();
            qDebug()<<QString("max id: %1").arg(max_id);   //最大编号（即用户总数）
        }
    }
    newid = max_id +1;
    //查询部分数据,确认是新用户
    if(!query.exec(select_phone)){
        qDebug()<<query.lastError();
    }
    else{
        while(1){
            if(query.next()){       //遍历phone
                QString phone = query.value("phone").toString();
                if(ui->PhoneLineEdit->text()==phone){   //手机号已存在,退出注册界面
                    qDebug()<<"用户已存在";
                    QMessageBox::warning(this, tr("警告"), tr("用户已存在"));
                    ui->PhoneLineEdit->clear();
                    phoneFlag = false;
                    break;
                }
                else{
                    phoneFlag = true;
                }
            }
            else{   //phone列为空（不可能存在的情况
                phoneFlag = true;
                break;
            }
        }
    }

    newid = max_id+1;
    qDebug()<<"new id: ";
    if(phoneFlag == true)
        newphone= ui->PhoneLineEdit->text();
    else return;
    //if(pwdFlag == true)
        newpwd = ui->pwdLineEdit1->text();
    qDebug()<<newname;
    //添加数据
    query.prepare(insert_user);
    query.addBindValue(newid);
    query.addBindValue(newpwd);
    query.addBindValue(newphone);//
    query.addBindValue(newname);
    query.addBindValue(0);
    //
    if(!query.exec()){
        qDebug()<<query.lastError();
    }
    else{
        qDebug()<<"inserted!";      //成功添加数据
        QMessageBox::information(this, tr("注册成功"), QString(newname+", 您已成功注册！"));
    }
    this->close();
}
//数据库能否正常打开
void RegisterDialog::receivedb(QSqlDatabase db){
    //qDebug()<<"receive database";
    database=db;
    if(!database.isOpen()){
        if(!database.open()){
            qDebug()<<database.lastError();//如果无法打开，返回错误信息
            qFatal("failed to connect.");
            return;
        }
        else{
            //否则继续
        }
    }
}

void RegisterDialog::CancelBtn_clicked(){
    this->close();
}





