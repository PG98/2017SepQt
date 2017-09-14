#include "admindialog.h"
#include "ui_admindialog.h"

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
    menuWindow->show();
    this->close();
}

void AdminDialog::on_userBtn_clicked()
{
    UserManage* userWindow = new UserManage;
    userWindow->show();
    this->close();
}
