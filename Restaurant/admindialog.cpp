#include "admindialog.h"
#include "ui_admindialog.h"

AdminDialog::AdminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminDialog)
{
    ui->setupUi(this);
}

AdminDialog::~AdminDialog()
{
    delete ui;
}

void AdminDialog::on_menuBtn_clicked()
{
    menuDlg = new MenuManage;
    menuDlg->show();
    this->close();
}
