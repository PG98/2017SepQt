#include "dishedit.h"
#include "ui_dishedit.h"
#include <QDebug>

dishEdit::dishEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dishEdit)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("更改"));
    connect(ui->OkBtn, SIGNAL(clicked(bool)), this, SLOT(send()));
}

void dishEdit::set(){
    for(index=0;Data::dish[index].id!=id;index++);
    ui->typeLabel_2->setText(dishtype);
    ui->nameEdit->setText(name);
    ui->priceEdit->setText(QString("%1").arg(price));
    ui->noteEdit->setText(notes);
}

dishEdit::~dishEdit()
{
    delete ui;
}

void dishEdit::send(){
    qDebug()<<"send refresh signal";
    emit refresh();
}
void dishEdit::on_CancelBtn_clicked()
{
    this->close();
}

void dishEdit::on_OkBtn_clicked()
{
    Data::dish[index].name = ui->nameEdit->text();
    Data::dish[index].price = ui->priceEdit->text().toInt();
    Data::dish[index].notes = ui->noteEdit->text();
    Data::dish[index].demand = -1;
    qDebug()<<Data::dish[index].name<<" has been modified";
    this->close();
}
