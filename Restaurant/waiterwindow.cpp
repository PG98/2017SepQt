#include "waiterwindow.h"
#include "ui_waiterwindow.h"

waiterWindow::waiterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::waiterWindow)
{
    ui->setupUi(this);
}

waiterWindow::~waiterWindow()
{
    delete ui;
}
