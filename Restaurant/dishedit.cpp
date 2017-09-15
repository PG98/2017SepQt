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
    ui->typeLabel_2->setText(dishtype);
    ui->nameEdit->setText(name);
    ui->priceEdit->setText(QString("%1").arg(price));
    ui->noteEdit->setText(notes);
    if(special)
        ui->checkBox->setCheckState(Qt::Checked);
    else
        ui->checkBox->setCheckState(Qt::Unchecked);
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
    if(Data::hash1.contains(id)){
        Data::hash1[id]->name = ui->nameEdit->text();
        Data::hash1[id]->price = ui->priceEdit->text().toInt();
        Data::hash1[id]->notes = ui->noteEdit->text();
        Data::hash1[id]->special = (int)ui->checkBox->isChecked();
        Data::hash1[id]->demand = -1;
        qDebug()<<Data::hash1[id]->name<<" has been modified";
    }
    else
        qDebug()<<"no such item in hash1: "<<id;
    this->close();
}
