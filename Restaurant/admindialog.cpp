#include "admindialog.h"
#include "ui_admindialog.h"
#include <QSqlError>
#include "staffmanage.h"

AdminDialog::AdminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("管理员"));
    QImage img;
    img.load(":/images/backgnd.png");
    QPalette palette;
    palette.setBrush(this->backgroundRole(),QBrush(img.scaled(this->width(),this->height())));
    this->setPalette(palette);
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
    userWindow->show();
    this->close();
}

void AdminDialog::on_staffBtn_clicked()
{
    staffManage* staffDlg = new staffManage;
    staffDlg->show();
    this->close();
}
