#include "menumanage.h"
#include "ui_menumanage.h"

MenuManage::MenuManage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuManage)
{
    ui->setupUi(this);
}

MenuManage::~MenuManage()
{
    delete ui;
}
