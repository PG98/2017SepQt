#include "selecttable.h"
#include "ui_selecttable.h"
#include "keybutton.h"

selectTable::selectTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selectTable)
{
    ui->setupUi(this);
    KeyButton *button[10];
    QHBoxLayout *layout1 = new QHBoxLayout;
    QHBoxLayout *layout2 = new QHBoxLayout;
    for(int i=0;i<10;i++){
        button[i] = new KeyButton(QString("NO.%1").arg(i+1));
        button[i]->setIndex(i);
        button[i]->setDefault(false);
        if(i<5)
            layout1->addWidget(button[i]);
        else layout2->addWidget(button[i]);
        connect(button[i], SIGNAL(keyClicked(int)), this, SLOT(setTable(int)));
    }
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(layout1);
    layout->addLayout(layout2);
    ui->box->setTitle("餐桌");
    ui->box->setLayout(layout);
}

selectTable::~selectTable()
{
    delete ui;
}

void selectTable::setTable(int i){
    qDebug()<<i;
}
