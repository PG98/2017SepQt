#include "order.h"
#include "ui_order.h"
#include <QDebug>
#include "data.h"
#include <QHeaderView>
#include <QtWidgets>

Order::Order(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Order)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("点菜"));
    setTypeBox();
    setBox1();
    showDishes();
}

Order::~Order()
{
    delete ui;
}

void Order::setTypeBox(){
    ui->box1->setTitle("菜品种类");
    //combobox index  connect()
    ui->typeview->resize(100,20);
    ui->typeview->addItem("<所有>");
    ui->typeview->addItem("主食");
    ui->typeview->addItem("凉菜");
    ui->typeview->addItem("海鲜");
    ui->typeview->addItem("荤菜");
    ui->typeview->addItem("素菜");
    ui->typeview->addItem("汤类");
    ui->typeview->addItem("甜点");
    ui->typeview->addItem("饮料");
    //connect(ui->typeview, SIGNAL(currentIndexChanged(int)), this, SLOT(changeType(int)));
    QGridLayout* layout = new QGridLayout;
    layout->addWidget(ui->typeview, 0, 0);
    ui->typeBox->setLayout(layout);
}

void Order::setBox1(){
    ui->box1->setTitle(tr("菜单"));
    ui->table1->verticalHeader()->setVisible(false);
    ui->table1->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table1->setColumnCount(5);
    ui->table1->setRowCount(Dish::count);
    //showDishes();
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(ui->table1, 0, 0);
    ui->box1->setLayout(layout);
    ui->table1->setHorizontalHeaderLabels(header);
    ui->table1->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
}

void Order::setBox2(){

}

void Order::showDishes(){
    int k=0;
    for(int j=1;j<=8;j++){
        QHashIterator<int, Dish*> i(Data::hash1);
        while(i.hasNext()){
            i.next();
            if(i.key()>=j*100 && i.key()<(j+1)*100 && i.value()->demand>-3){
                ui->table1->setItem(k, 0, new QTableWidgetItem(QString("%1").arg(i.value()->id)));
                ui->table1->setItem(k, 1, new QTableWidgetItem(i.value()->getType()));
                ui->table1->setItem(k, 2, new QTableWidgetItem(i.value()->name));
                ui->table1->setItem(k, 3, new QTableWidgetItem(QString("%1").arg(i.value()->price)));
                if(i.value()->special)
                    ui->table1->setItem(k, 4, new QTableWidgetItem(QIcon(":/buttons/star.png"), "特别推荐"));
                else
                    ui->table1->setItem(k, 4, new QTableWidgetItem(QIcon(":/buttons/graystar.png"), "普通"));
                k++;
            }
        }
    }
    ui->table1->setRowCount(Dish::count);
    mySortByColumn(0);
    mySortByColumn(0);
}

void Order::mySortByColumn(int column)
{
    static bool f = true;
    qDebug()<<"sort: ";
    ui->table1->sortByColumn(column, f ? Qt::AscendingOrder : Qt::DescendingOrder);
    f = !f;
}

void Order::MouseTrackItem(int row, int column){
    Q_UNUSED(column);
    ui->table1->setStyleSheet("selection-background-color:lightblue;"); //选中项的颜色
    ui->table1->setCurrentCell(row, QItemSelectionModel::Select); //设置该行为选中项。

}

void Order::rowSelect(){   //鼠标点击表格效果
    static bool track = true;
    qDebug()<<track;
    if(track){
        ui->table1->setStyleSheet("selection-background-color:burlywood;"); //选中项的颜色
        qDebug()<<ui->table1->currentRow();
        ui->table1->setMouseTracking(false);
    }
    else{
        ui->table1->setMouseTracking(true);
        connect(ui->table1->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(mySortByColumn(int)));//单击表头排序
        connect(ui->table1, SIGNAL(cellEntered(int,int)), this, SLOT(MouseTrackItem(int, int)));//鼠标移动效果
    }
    track = !track;
}
