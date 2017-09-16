#include "admindialog.h"
#include "ui_admindialog.h"
#include <QSqlError>

AdminDialog::AdminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminDialog)
{
    ui->setupUi(this);

    ui->menuBtn->setStyleSheet("QPushButton{background-color:cornflowerblue;\
                                color: white;   border-radius: 10px;  border: 2px groove gray;\
                                border-style: outset;}"
                               "QPushButton:hover{background-color:white; color: black;}"
                              "QPushButton:pressed{background-color:rgb(85, 170, 255);\
                                               border-style: inset; }"
                               );
    //ui->regBtn->setStyleSheet("QPushButton{background-color:mediumseagreen; color:white;border-radius: 10px;  border: 2px groove gray;border-style: outset;}");
    ui->userBtn->setStyleSheet("QPushButton{background-color:mediumseagreen;\
                              color: white;   border-radius: 10px;  border: 2px groove gray;\
                              border-style: outset;}"
                             "QPushButton:hover{background-color:white; color: black;}"
                            "QPushButton:pressed{background-color:rgb(85, 170, 255);\
                                             border-style: inset; }"
                             );
}

AdminDialog::~AdminDialog()
{
    delete ui;
}

void AdminDialog::on_menuBtn_clicked()
{
    MenuManage* menuWindow = new MenuManage;
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("database.db");
    bool tableFlag=false;
    if(!database.open()){
        qDebug()<<database.lastError();
        qFatal("failed to connect");
    }
    Data::dataInit();
    menuWindow->show();
    this->close();
}

void AdminDialog::on_userBtn_clicked()
{
    UserManage* userWindow = new UserManage;
    //Data::dataInit();
    userWindow->show();
    this->close();
}
