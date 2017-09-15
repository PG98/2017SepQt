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
    int maxid=0, newID;
    QHashIterator<int, User*> i(Data::hash0);
    while(i.hasNext()){
        i.next();
        if(i.key()>maxid)
            maxid = i.key();
    }
    newID = maxid+1;
    int flag = ui->checkBox->isChecked();
    if(flag)
        flag = 4;
    else flag = 3;
    User* u = new User;
    u->id = newID;
    u->name = ui->nameEdit->text();
    u->phone = ui->phoneEdit->text();
    u->isMember = flag;
    u->pwd = ui->pwdEdit->text();
    User::count++;
    Data::hash0.insert(maxid, u);
    qDebug()<<"new account added!";
    this->close();
}
