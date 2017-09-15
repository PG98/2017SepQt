#include "adddish.h"
#include "ui_adddish.h"
#include <QDebug>

addDish::addDish(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addDish)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("添加菜品"));
    connect(ui->OkBtn, SIGNAL(clicked(bool)), this, SLOT(send()));

    ui->typeBox->addItem("主食");
    ui->typeBox->addItem("凉菜");
    ui->typeBox->addItem("海鲜");
    ui->typeBox->addItem("荤菜");
    ui->typeBox->addItem("素菜");
    ui->typeBox->addItem("汤类");
    ui->typeBox->addItem("甜点");
    ui->typeBox->addItem("饮料");
}

addDish::~addDish()
{
    delete ui;
}

void addDish::on_CancelBtn_clicked(){
    this->close();
}

void addDish::on_OkBtn_clicked(){
    int k=0, newID;
    //找出当前类别最大id，添加在其后
    int type = ui->typeBox->currentIndex()+1;
    QHashIterator<int, Dish*> i(Data::hash1);
    while(i.hasNext()){
        i.next();
        if(i.key()<type*100 && i.key()<(type+1)*100)
            k++;
    }
    newID = type*100 + k;
    Dish* d = new Dish;
    d->setDish(newID, ui->nameEdit->text(), type, ui->priceEdit->text().toInt(), ui->noteEdit->text(), (int)ui->checkBox->isChecked());
    d->demand = -2;
    Data::hash1.insert(newID, d);
    Dish::count++;
    qDebug()<<"new dish added ";
    this->close();
}

void addDish::send(){
    qDebug()<<"send refresh signal";
    emit refresh();
}
