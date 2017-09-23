#include "managerdialog.h"
#include "ui_managerdialog.h"
#include "data.h"
#include <QtWidgets>
#include <QMovie>

managerDialog::managerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::managerDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("经理");
    QImage img;
    img.load(":/images/backgnd.png");
    QPalette palette;
    palette.setBrush(this->backgroundRole(),QBrush(img.scaled(this->width(),this->height())));
    this->setPalette(palette);

    setBox1();
    setBox2();
    setBox3();
    setBox4();
    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->dishTable->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortDishes(int)));
    ui->stackedWidget->addWidget(ui->page1);
    ui->stackedWidget->addWidget(ui->page2);
    connect(ui->button, SIGNAL(clicked(bool)), this, SLOT(switchPage()));
}

managerDialog::~managerDialog()
{
    delete ui;
}


void managerDialog::setBox1(){
    //厨师业绩
    ui->chefTable->verticalHeader()->setVisible(false);
    ui->chefTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->chefTable->setColumnCount(2);
    for(int i=0;Data::chef[i].id!=-1 && i<10;i++){
        ui->chefTable->setRowCount(ui->chefTable->rowCount()+1);
        ui->chefTable->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(Data::chef[i].id)));
        ui->chefTable->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(Data::chef[i].history)));
    }
    ui->chefTable->setHorizontalHeaderLabels(chefHeader);
    ui->chefTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:bisque;}");
    ui->chefTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //服务员业绩
    ui->waiterTable->verticalHeader()->setVisible(false);
    ui->waiterTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->waiterTable->setColumnCount(3);
    for(int i=0;Data::waiter[i].id!=-1 && i<10;i++){
        ui->waiterTable->setRowCount(ui->waiterTable->rowCount()+1);
        ui->waiterTable->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(Data::waiter[i].id)));
        ui->waiterTable->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(Data::waiter[i].history)));
        ui->waiterTable->setItem(i, 2, new QTableWidgetItem(QString("%1").arg(Data::waiter[i].rating)));
    }
    ui->waiterTable->setHorizontalHeaderLabels(waiterHeader);
    ui->waiterTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:bisque;}");
    ui->waiterTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //layout
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(ui->chefTable);
    layout->addWidget(ui->waiterTable);
    ui->box1->setLayout(layout);
}

//菜品反馈
void managerDialog::setBox2(){
    ui->dishTable->verticalHeader()->setVisible(false);
    ui->dishTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->dishTable->setColumnCount(5);
    int k = 0;
    ui->dishTable->setRowCount(Dish::count);
    QHashIterator<int, Dish*> i(Data::hash1);
    while(i.hasNext()){
        i.next();
            ui->dishTable->setItem(k, 0, new QTableWidgetItem(QString("%1").arg(i.value()->id)));
            ui->dishTable->setItem(k, 1, new QTableWidgetItem(i.value()->name));
            if(i.value()->special)
                ui->dishTable->setItem(k, 2, new QTableWidgetItem(QIcon(":/buttons/star.png"), "推荐"));
            else
                ui->dishTable->setItem(k, 2, new QTableWidgetItem(QIcon(":/buttons/graystar.png"), "普通"));
            ui->dishTable->setItem(k, 3, new QTableWidgetItem(QString("%1").arg(i.value()->history)));
            ui->dishTable->setItem(k, 4, new QTableWidgetItem(QString("%1").arg(i.value()->rating)));
       k++;
    }
    sortDishes(0);
    sortDishes(0);
    ui->dishTable->setHorizontalHeaderLabels(dishHeader);
    ui->dishTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:bisque;}");
    ui->dishTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void managerDialog::setBox3(){
   //流水账
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setColumnCount(6);
    int i=0;
    for(orderInfo* info : Data::list){
        ui->tableWidget->setRowCount(i+1);
        int id = info->dishid;
        int status = info->status;
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(info->id)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(info->tableid)));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(Data::hash1[id]->name));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString("%1").arg(info->count)));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(Data::hash1[id]->price));
        if(status == -1){
            ui->tableWidget->setItem(i, 5, new QTableWidgetItem("等待厨师"));
        }
        else if(status == 0){
            ui->tableWidget->setItem(i, 5, new QTableWidgetItem("正在制作"));
        }
        else{
            ui->tableWidget->setItem(i, 5, new QTableWidgetItem("已完成"));
        }
        i++;
    }
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(ui->tableWidget);
    ui->box3->setLayout(layout);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:bisque;}");
    ui->tableWidget->setHorizontalHeaderLabels(streamHeader);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //
    ui->refreshBtn->setIcon(QIcon(":/images/refresh.png"));
    ui->refreshBtn->setStyleSheet("QPushButton{background-color:lightsteelblue;\
                                color: black;   border-radius: 14px;  border: 3px groove gray;\
                                border-style: outset;}"
                               "QPushButton:hover{background-color:white; color: lightsteelblue;}"
                              "QPushButton:pressed{background-color:rgb(85, 170, 255);\
                                               border-style: inset; }"
                               );
}

void managerDialog::setBox4(){
     model = new QSqlTableModel(this);
     model->setTable("journal");


     QHBoxLayout* layout = new QHBoxLayout;
     layout->addWidget(ui->tableView_2);
     ui->box4->setLayout(layout);

     model->select();

     ui->tableView_2->setSortingEnabled(true);
     ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);   //每次选一行
     ui->tableView_2->setSelectionMode(QAbstractItemView::SingleSelection);//鼠标单击的反应
     ui->tableView_2->setShowGrid(false);
     ui->tableView_2->verticalHeader()->hide();
     ui->tableView_2->setAlternatingRowColors(true);
     ui->tableView_2->setModel(model);//
     ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
     ui->tableView_2->show();
}

void managerDialog::sortDishes(int column){
    static bool f = true;
    ui->dishTable->sortByColumn(column, f ? Qt::AscendingOrder : Qt::DescendingOrder);
    f = !f;
}

void managerDialog::switchPage(){
    int index = ui->stackedWidget->currentIndex();
    if(index == 2)
        index = 0;
    else if(index == 0)
        index = 1;
    else if(index == 1)
        index = 2;
    ui->stackedWidget->setCurrentIndex(index);
}

void managerDialog::on_refreshBtn_clicked()
{
    setBox3();
    QMovie* movie = new QMovie(":/images/dalao.gif");
    ui->movieLabel->setMovie(movie);
    movie->start();
}
