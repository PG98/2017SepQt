#include "waiterwindow.h"
#include "ui_waiterwindow.h"
#include "data.h"

waiterWindow::waiterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::waiterWindow)
{
    ui->setupUi(this);
    for(int i=0;i<5;i++){
        if(Data::waiter[i].id == id)
            index = i;
    }
    init();
}

waiterWindow::~waiterWindow()
{
    delete ui;
}

void waiterWindow::init(){
    QHBoxLayout* layout1 = new QHBoxLayout;
    QHBoxLayout* layout2 = new QHBoxLayout;
    for(int i=0;i<10;i++){
        button[i] = new KeyButton(QString("NO.%1").arg(i));
        button[i]->setIndex(i);
        button[i]->setAutoDefault(false);
        if(i<5)
            layout1->addWidget(button[i]);
        else
            layout2->addWidget(button[i]);
        connect(button[i], SIGNAL(keyClicked(int)), this, SLOT(claimTable(int)));
    }
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(layout1);
    layout->addLayout(layout2);
    ui->box->setLayout(layout);
}

void waiterWindow::claimTable(int i){
    if(Data::waiter[index].table1 == 0){
        Data::waiter[index].table1 = i;
        table1 = i;
        ui->box1->setTitle(QString("table %1").arg(i));
        button[i]->setText(tr("老子在这"));
        Data::table[i].state = id;
    }
    else if(Data::waiter[index].table2 == 0){
        Data::waiter[index].table2 = i;
        table2 = i;
        ui->box2->setTitle(QString("table %1").arg(i));
        button[i]->setText(tr("老子在这"));
        Data::table[i].state = id;
    }
    else return;
}

void waiterWindow::on_pushButton_clicked()//refresh
{
    for(int i=0;i<10;i++){
        int state = Data::table[i].state;
        if(state == -1)
            button[i]->setText("来人啊");
        else if(state == 0)
            button[i]->setText("空闲");
        else if(state == id)
            button[i]->setText("老子在这");
        else
            button[i]->setText("被艹");
    }
    if(table1!=0){
        if(Data::table[table1].water == true)
            ui->label->setText("1");
        else ui->label->setText("0");
        if(Data::table[table1].remind == true)
            ui->label_2->setText("1");
        else ui->label_2->setText("0");
    }
    if(table2!=0){
        if(Data::table[table1].water == true)
            ui->label->setText("1");
        else ui->label->setText("0");
    }
}
