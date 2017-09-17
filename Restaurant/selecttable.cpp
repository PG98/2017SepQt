#include "selecttable.h"
#include "ui_selecttable.h"
#include "keybutton.h"
#include "data.h"
#include "order.h"

selectTable::selectTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selectTable)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("选择餐桌"));
    KeyButton *button[10];
    QHBoxLayout *layout1 = new QHBoxLayout;
    QHBoxLayout *layout2 = new QHBoxLayout;
    QHBoxLayout *layout3 = new QHBoxLayout;
    for(int i=0;i<10;i++){
        button[i] = new KeyButton(QString("NO.%1").arg(i+1));
        button[i]->setIndex(i); //从0开始
        button[i]->setAutoDefault(false);
        if(i<3)
            layout1->addWidget(button[i]);
        else if(i>=3 && i<7)
            layout2->addWidget(button[i]);
        else layout3->addWidget(button[i]);
        connect(button[i], SIGNAL(keyClicked(int)), this, SLOT(setTable(int)));
    }
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(layout1);
    layout->addLayout(layout2);
    layout->addLayout(layout3);
    ui->box->setTitle("餐桌");
    ui->box->setLayout(layout);
}

selectTable::~selectTable()
{
    delete ui;
}

void selectTable::setTable(int i){
    Data::table[i].state = -1;
    qDebug()<<"table: "<<i<<", volume: "<<Data::table[i].volume;
    Order* w = new Order;
    w->currentTable = i;
    w->setCustomerId(currentID);
    w->show();
    this->close();
}
