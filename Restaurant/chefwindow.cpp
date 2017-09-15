#include "chefwindow.h"
#include "ui_chefwindow.h"

chefWindow::chefWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::chefWindow)
{
    ui->setupUi(this);
}

chefWindow::~chefWindow()
{
    delete ui;
}
