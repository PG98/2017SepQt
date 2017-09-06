#include "registerdialog.h"
#include "ui_registerdialog.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);

    connect(ui->OKBtn, SIGNAL(clicked(bool)), this, SLOT(OKBtn_clicked()));
    connect(ui->CancelBtn, SIGNAL(clicked(bool)), this, SLOT(CancelBtn_clicked()));

}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

QString select_max_sql = "select max(id) from user";
QString insert_sql = "insert into user values (?, ?, ?, ?, ?)";
QString select_sql = "select phone from user";

void RegisterDialog::OKBtn_clicked(){
    bool phoneFlag = false;
    bool pwdFlag = false;
    int newid = max_id + 1;
    QString newpwd = NULL;
    QString newphone = NULL;
    QString newmail = ui->EmailLineEdit->text();

    if(ui->pwdLineEdit1->text()==""||ui->pwdLineEdit2->text()==""){
        pwdFlag = false;
    }
    else if(ui->pwdLineEdit1->text() == ui->pwdLineEdit2->text()){
        pwdFlag = true;
    }
    else{       //如果密码输入过程中程序出现其他错误
        qDebug()<<"Password Error!";
        pwdFlag = false;
        return;
    }
    //以下为数据库操作
    QSqlQuery query;
    //找出最大id编号
    max_id = 0;
    query.prepare(select_max_sql);
    if(!query.exec()){
        qDebug()<<query.lastError();
    }
    else{
        while(query.next()){
            max_id = query.value(0).toInt();
            //qDebug()<<QString("max id: %1").arg(max_id);   输出最大编号（即用户总数）
        }
    }

    //查询部分数据,确认是新用户
    if(!query.exec(select_sql)){
        qDebug()<<query.lastError();
    }
    else{
        while(1){
            if(query.next()){       //遍历
                QString phone = query.value("phone").toString();
                qDebug()<<QString("phone number:%1").arg(phone);
                if(ui->PhoneLineEdit->text()==phone){   //手机号已存在
                    qDebug()<<"用户已存在";
                    phoneFlag = false;
                    break;
                }
                else{
                    phoneFlag = true;
                }
            }
            else{
                phoneFlag = true;
                break;
            }
        }
    }

    newid = max_id+1;
    if(phoneFlag == true) newphone= ui->PhoneLineEdit->text();
    else return;
    if(pwdFlag == true) newpwd = ui->pwdLineEdit1->text();
    else return;
    //添加数据
    query.prepare(insert_sql);
    query.addBindValue(newid);
    query.addBindValue(newpwd);
    query.addBindValue(newphone);//
    query.addBindValue(newmail);
    query.addBindValue(0);

    if(!query.exec()){
        qDebug()<<query.lastError();
    }
    else{
        qDebug()<<"inserted!";      //成功添加数据
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





