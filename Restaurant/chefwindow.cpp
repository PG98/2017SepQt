#include "chefwindow.h"
#include "ui_chefwindow.h"
#include <QtWidgets>
#include <QDebug>
#include <QHeaderView>
#include <QSqlError>

chefWindow::chefWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::chefWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("厨师"));
    //this->setFixedWidth(this->width());
    setbox1();
    setbox2();
    setTableAppearance();
    connect(ui->table1, SIGNAL(cellEntered(int,int)), this, SLOT(MouseTrackItem(int, int)));//鼠标移动效果
    connect(ui->table2, SIGNAL(cellEntered(int,int)), this, SLOT(MouseTrackItem2(int, int)));//鼠标移动效果
    connect(ui->table1, SIGNAL(cellClicked(int,int)),this, SLOT(rowSelect()));//单击选中行
    connect(ui->table2, SIGNAL(cellClicked(int,int)),this, SLOT(rowSelect2()));//单击选中行
    //点击功能
    connect(ui->table1, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(updateCell(int)));
    connect(ui->table2, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(complete(int)));

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(ui->box1, 0, 0, 1, 1);
    layout->addWidget(ui->box2, 0, 1, 1, 1);
    layout->setColumnStretch(0,1);
    layout->setColumnStretch(1,1);
    QWidget* widget = new QWidget;
    widget->setLayout(layout);
    this->setCentralWidget(widget);
}

chefWindow::~chefWindow()
{
    delete ui;
}

void chefWindow::setbox1(){
    ui->box1->setTitle(tr("系统当前待接管菜品"));
    ui->table1->verticalHeader()->setVisible(false);
    ui->table1->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table1->setColumnCount(5);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(ui->table1);
    ui->box1->setLayout(layout);
    ui->table1->setHorizontalHeaderLabels(header);
    ui->table1->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
}

void chefWindow::setbox2(){
    ui->box2->setTitle(tr("正在处理"));
    ui->table2->verticalHeader()->setVisible(false);
    ui->table2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table2->setColumnCount(5);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(ui->table2);
    ui->box2->setLayout(layout);
    ui->table2->setHorizontalHeaderLabels(header);
    ui->table2->horizontalHeader()->setStyleSheet("QHeaderView::section{background:lightcoral;}"); //设置表头背景色
}

void chefWindow::setTableAppearance(){
    ui->table1->horizontalHeader()->setSortIndicatorShown(true);
    QFont font = ui->table1->horizontalHeader()->font();
    font.setBold(true);
    ui->table1->horizontalHeader()->setFont(font);//表头文字样式
    ui->table1->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑

    ui->table2->horizontalHeader()->setSortIndicatorShown(true);
    ui->table2->horizontalHeader()->setFont(font);//表头文字样式
    ui->table2->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑

    for(int i=0;i<5;i++){
        ui->table1->setColumnWidth(i, 80);
        ui->table2->setColumnWidth(i, 80);
    }
    ui->table1->setFixedWidth(402);
    ui->table2->setFixedWidth(402);
}


void chefWindow::MouseTrackItem(int row, int column){
    Q_UNUSED(column);
    ui->table1->setStyleSheet("selection-background-color:cornflowerblue;"); //选中项的颜色
    ui->table1->setCurrentCell(row, QItemSelectionModel::Select); //设置该行为选中项。
}

void chefWindow::MouseTrackItem2(int row, int column){
    Q_UNUSED(column);
    ui->table2->setStyleSheet("selection-background-color:slategray;"); //悬浮项的颜色
    ui->table2->setCurrentCell(row, QItemSelectionModel::Select); //设置该行为选中项。
}

void chefWindow::rowSelect(){   //鼠标点击表格效果
    static bool track = true;
    //qDebug()<<track;
    if(track){
        ui->table1->setStyleSheet("selection-background-color:khaki;"); //选中项的颜色
        //qDebug()<<ui->table1->currentRow();
        ui->table1->setMouseTracking(false);
    }
    else
        ui->table1->setMouseTracking(true);
    track = !track;
}
void chefWindow::rowSelect2(){   //鼠标点击
    static bool track = true;
    if(track){
        ui->table2->setStyleSheet("selection-background-color:wheat;"); //选中项的颜色
        ui->table2->setMouseTracking(false);
    }
    else
        ui->table2->setMouseTracking(true);
    track = !track;
}
//刷新
void chefWindow::on_action_R_triggered(){
     //遍历,每次从头即可
    int j = 0, k = 0;
    ui->table1->clearContents();
    ui->table1->setRowCount(0);
    ui->table2->clearContents();
    ui->table2->setRowCount(0);
    for(orderInfo* info : Data::list){
        if(info->status == -1){
            ui->table1->setRowCount(ui->table1->rowCount()+1);
            ui->table1->setItem(k, 0, new QTableWidgetItem(QString("%1").arg(info->id)));
            ui->table1->setItem(k, 1, new QTableWidgetItem(QString("%1").arg(info->tableid)));
            ui->table1->setItem(k, 2, new QTableWidgetItem(QString("%1").arg(info->dishid)));
            ui->table1->setItem(k, 3, new QTableWidgetItem(Data::hash1[info->dishid]->name));
            ui->table1->setItem(k, 4, new QTableWidgetItem(QString("%1").arg(info->count)));
            k++;
        }
        if(info->chefid == id && info->status == 0){
            ui->table2->setRowCount(ui->table2->rowCount()+1);
            ui->table2->setItem(j, 0, new QTableWidgetItem(QString("%1").arg(info->id)));
            ui->table2->setItem(j, 1, new QTableWidgetItem(QString("%1").arg(info->tableid)));
            ui->table2->setItem(j, 2, new QTableWidgetItem(QString("%1").arg(info->dishid)));
            ui->table2->setItem(j, 3, new QTableWidgetItem(Data::hash1[info->dishid]->name));
            ui->table2->setItem(j, 4, new QTableWidgetItem(QString("%1").arg(info->count)));
            j++;
        }
    }
}

void chefWindow::updateCell(int row){
    int orderid = ui->table1->item(row, 0)->text().toInt();
    for(int i=0;i<5;i++){
        ui->table1->item(row, i)->setFlags(Qt::NoItemFlags);
    }
    //顺序设置下标，操作链表不用遍历
    Data::list[orderid]->status = 0;
    Data::list[orderid]->chefid = id;
    qDebug()<<"cooking...orderid: "<<Data::list[orderid]->id<<", dishid: "<<Data::list[orderid]->dishid<<", chefid: "<<Data::list[orderid]->chefid<<", status: "<<Data::list[orderid]->status;

    int row2 = ui->table2->rowCount();
    ui->table2->setRowCount(row2+1);
    ui->table2->setItem(row2, 0, new QTableWidgetItem(ui->table1->item(row, 0)->text()));
    ui->table2->setItem(row2, 1, new QTableWidgetItem(ui->table1->item(row, 1)->text()));
    ui->table2->setItem(row2, 2, new QTableWidgetItem(ui->table1->item(row, 2)->text()));
    ui->table2->setItem(row2, 3, new QTableWidgetItem(ui->table1->item(row, 3)->text()));
    ui->table2->setItem(row2, 4, new QTableWidgetItem(ui->table1->item(row, 4)->text()));
}

void chefWindow::complete(int row){
    int orderid = ui->table2->item(row, 0)->text().toInt();
    Data::list[orderid]->status = 1;
    for(int i=0;i<5;i++)
        ui->table2->item(row, i)->setFlags(Qt::NoItemFlags);
    Data::chef[index].history++;
}

void chefWindow::on_action_U_triggered()
{
    int history = Data::chef[index].history;
    QSqlQuery query;
    query.prepare(QString("update chef set history = %1 where id = %2").arg(history).arg(id));
    if(!query.exec()){
        qDebug()<<query.lastError();
    }else{
        qDebug()<<"updated: chefid="<<id<<", history="<<history;
    }
}

void chefWindow::on_action_F_triggered()
{
    //得出催单总个数以便输出
    int i;
    for(i=0;Data::urgent[i];i++);
    int total = i;
    QString urge = "需要加快进度的订单号: ";
    for(int i=0;i<total;i++){
        int length = urge.length();
        urge.insert(length, QString("%1, ").arg(Data::urgent[i]));
        qDebug()<<"urgent: "<<Data::urgent[i];
        //urge += QString("%1, ").arg(Data::urgent[i]);
    }
    QMessageBox::information(this, tr("加急订单"), urge);
}
