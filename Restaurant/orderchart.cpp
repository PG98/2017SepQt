#include "orderchart.h"
#include "ui_orderchart.h"

orderChart::orderChart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::orderChart)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("顾客点菜"));
}

orderChart::~orderChart()
{
    delete ui;
}
