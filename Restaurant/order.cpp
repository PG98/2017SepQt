#include "order.h"
#include "ui_order.h"

Order::Order(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Order)
{
    ui->setupUi(this);
}

Order::~Order()
{
    delete ui;
}
