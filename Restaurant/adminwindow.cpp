#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("管理员登陆"));
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::on_MenuBtn_clicked()
{
    MenuManage menu(this);
    this->hide();
    menu.show();
    menu.exec();
    this->close();
}

void AdminWindow::on_UserBtn_clicked()
{
    UserManage user(this);
    this->hide();
    user.show();
    user.exec();
    this->close();
}
