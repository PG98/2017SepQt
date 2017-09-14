#include "adduser.h"
#include "ui_adduser.h"
#include <QDebug>

addUser::addUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addUser)
{
    ui->setupUi(this);
    ui->checkBox->setStyleSheet("QCheckBox::indicator {width: 13px; height: 13px;}");
    this->setWindowTitle(tr("添加用户"));
    connect(ui->okBtn, SIGNAL(clicked(bool)), this, SLOT(send()));
    ui->pwdEdit->setText("123456");
}

addUser::~addUser()
{
    delete ui;
}

void addUser::send(){
    emit refresh();
}

void addUser::on_cancelBtn_clicked()
{
    this->close();
}

void addUser::on_okBtn_clicked()
{
    int count = User::getCount(), newID;
    newID = Data::user[count-1].id + 1;
    int flag = ui->checkBox->isChecked();
    if(flag)
        flag = 4;
    else flag = 3;
    //Data::user[count].setUser(newID, ui->pwdEdit->text(), ui->phoneEdit->text(), ui->nameEdit->text(), flag);
    Data::user[count].id = newID;
    Data::user[count].name = ui->nameEdit->text();
    Data::user[count].phone = ui->phoneEdit->text();
    Data::user[count].isMember = flag;
    Data::user[count].pwd = ui->pwdEdit->text();
    User::count++;
    qDebug()<<"new account added!";
    this->close();
}
