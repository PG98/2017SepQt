#include "order.h"
#include "ui_order.h"
#include <QDebug>
#include "data.h"
#include <QHeaderView>
#include <QtWidgets>

int Order::orderCount = 0;

Order::Order(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Order)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("点菜"));
    this->setFixedWidth(this->width());
    setTypeBox();
    setbox1();
    setbox4();
    setbox3();
    showDishes();
    setTableAppearance();
    connect(ui->table1->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(mySortByColumn(int)));//单击表头排序
    connect(ui->table1, SIGNAL(cellEntered(int,int)), this, SLOT(MouseTrackItem(int, int)));//鼠标移动效果
    connect(ui->table1, SIGNAL(cellClicked(int,int)),this, SLOT(rowSelect()));//单击选中行
    connect(ui->table2, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(delRow(int, int)));
    connect(ui->table1, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(addOrder(int)));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(ui->box1, 0, 0);
    layout->addWidget(ui->typeBox, 0, 1);
    layout->addWidget(ui->box3, 1, 0);
    layout->addWidget(ui->box4, 1, 1);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);
    layout->setRowStretch(0, 1);
    layout->setRowStretch(1, 5);

    QWidget* widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
}

Order::~Order()
{
    delete ui;
}

void Order::setbox1(){
    ui->box1->setTitle(tr("点击图标以获得帮助信息"));
    QHBoxLayout* layout = new QHBoxLayout;
    ui->iconBtn->setFixedSize(64, 64);
    ui->label->setFixedWidth(105);
    layout->addWidget(ui->iconBtn);
    layout->addWidget(ui->label);
    layout->addWidget(ui->priceLabel);
    ui->priceLabel->setText("0");
    ui->box1->setLayout(layout);
}

void Order::setTypeBox(){
    ui->typeBox->setTitle("菜品种类");
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
    connect(ui->typeview, SIGNAL(currentIndexChanged(int)), this, SLOT(changeType(int)));
    QGridLayout* layout = new QGridLayout;
    layout->addWidget(ui->typeview, 0, 0);
    ui->typeBox->setLayout(layout);
}

void Order::setbox4(){
    ui->box4->setTitle(tr("菜单"));
    ui->table1->verticalHeader()->setVisible(false);
    ui->table1->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table1->setColumnCount(5);
    ui->table1->setRowCount(Dish::count);
    //showDishes();
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(ui->table1, 0, 0);
    ui->box4->setLayout(layout);
    ui->table1->setHorizontalHeaderLabels(header);  //表头设置放在函数最后否则出错
    ui->table1->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
}

void Order::setbox3(){
    ui->box3->setTitle(tr("已点菜品"));
    ui->table2->verticalHeader()->setVisible(false);
    ui->table2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table2->setColumnCount(5);
    //ui->table2->setRowCount(0);
    ui->table2->setShowGrid(false);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(ui->table2, 0, 0);
    ui->box3->setLayout(layout);
    ui->table2->setHorizontalHeaderLabels(header1);
    ui->table2->setAlternatingRowColors(true);
    //ui->table2->resizeColumnToContents(4);
    ui->table2->horizontalHeader()->setStyleSheet("QHeaderView::section{background:lightcoral;}"); //设置表头背景色
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

void Order::changeType(int type){
    //传入当前下拉菜单项的下标，对应的dish类是type(enum的首项定义为1)
    if(type==0){
        //qDebug()<<"show all";    //按照类别顺序显示表格
        showDishes();
    }
    else{
        int k=0;
        QHashIterator<int, Dish*> i(Data::hash1);
        while(i.hasNext()){
            i.next();
            if(i.value()->id>=type*100 && i.value()->id<(type+1)*100 && i.value()->demand>-3){
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
        ui->table1->setRowCount(k);
        mySortByColumn(0);
        mySortByColumn(0);
    }
}

void Order::setTableAppearance(){
    ui->table1->horizontalHeader()->setSortIndicatorShown(true);
    QFont font = ui->table1->horizontalHeader()->font();
    font.setBold(true);
    ui->table1->horizontalHeader()->setFont(font);//表头文字样式
    ui->table1->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑

    ui->table2->horizontalHeader()->setSortIndicatorShown(true);
    ui->table2->horizontalHeader()->setFont(font);//表头文字样式
    ui->table2->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑
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
    ui->table1->setStyleSheet("selection-background-color:cornflowerblue;"); //选中项的颜色
    ui->table1->setCurrentCell(row, QItemSelectionModel::Select); //设置该行为选中项。

}

void Order::rowSelect(){   //鼠标点击表格效果
    static bool track = true;
    qDebug()<<track;
    if(track){
        ui->table1->setStyleSheet("selection-background-color:khaki;"); //选中项的颜色
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

void Order::delRow(int row, int col){
    Q_UNUSED(col)
    ui->table2->removeRow(row);
    int sub = ui->table2->item(row, 4)->text().toInt();
    orderCount -= sub;  //删除行后减去相应的菜品份数
}

void Order::addOrder(int row){
    int id = ui->table1->item(row, 0)->text().toInt();
    qDebug()<<"add id to order: "<<id;
    for(int i=0;i<ui->table2->rowCount();i++){
        if(ui->table2->item(i, 0)->text().toInt() == id){
            int newcount = ui->table2->item(i, 4)->text().toInt() + 1;
            ui->table2->setItem(i, 4, new QTableWidgetItem(QString("%1").arg(newcount)));
            orderCount++;
            //qDebug()<<Data::hash1[id]->name<<", newCount: "<<newcount;
            return;
        }
    }
    int newRow = ui->table2->rowCount() + 1;
    qDebug()<<"rowCount: "<<newRow<<"  orderCount: "<<orderCount;
    ui->table2->setRowCount(newRow); //newRow为总行数，使用时下标仍从0开始
    if(Data::hash1.contains(id)){
        ui->table2->setItem(newRow-1, 0, new QTableWidgetItem(QString("%1").arg(Data::hash1[id]->id)));
        ui->table2->setItem(newRow-1, 1, new QTableWidgetItem(Data::hash1[id]->name));
        ui->table2->setItem(newRow-1, 2, new QTableWidgetItem(QString("%1").arg(Data::hash1[id]->price)));
        //ui->table2->setItem(newRow-1, 3, new QTableWidgetItem(QString("%1").arg(Data::hash1[id]->special)));
        if(Data::hash1[id]->special)
            ui->table2->setItem(newRow-1, 3, new QTableWidgetItem(QIcon(":/buttons/star.png"), "特别推荐"));
        else
            ui->table2->setItem(newRow-1, 3, new QTableWidgetItem(QIcon(":/buttons/graystar.png"), "普通"));
        ui->table2->setItem(newRow-1, 4, new QTableWidgetItem(QString("1")));
    }
    else{
        qDebug()<<"index fault using hash1";
    }
}
