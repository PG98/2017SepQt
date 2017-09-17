#include "chefwindow.h"
#include "ui_chefwindow.h"
#include <QtWidgets>
#include <QDebug>
#include <QHeaderView>

chefWindow::chefWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::chefWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("厨师"));
    setbox1();
    setbox2();
    connect(ui->table1, SIGNAL(cellEntered(int,int)), this, SLOT(MouseTrackItem(int, int)));//鼠标移动效果
    connect(ui->table2, SIGNAL(cellEntered(int,int)), this, SLOT(MouseTrackItem2(int, int)));//鼠标移动效果
    connect(ui->table1, SIGNAL(cellClicked(int,int)),this, SLOT(rowSelect()));//单击选中行
    connect(ui->table2, SIGNAL(cellClicked(int,int)),this, SLOT(rowSelect2()));//单击选中行
    //点击功能
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(ui->box1);
    layout->addWidget(ui->box2);
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
    ui->table1->setColumnCount(4);

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
    ui->table2->setColumnCount(3);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(ui->table2);
    ui->box1->setLayout(layout);
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
    int k = 0;
    ui->table1->clearContents();
    for(orderInfo info : Data::list){
        if(info.status == -1){
            ui->table1->setRowCount(ui->table1->rowCount()+1);
            ui->table1->setItem(k, 0, new QTableWidgetItem(QString("%1").arg(info.tableid)));
            ui->table1->setItem(k, 1, new QTableWidgetItem(QString("%1").arg(info.dishid)));
            ui->table1->setItem(k, 2, new QTableWidgetItem(Data::hash1[info.dishid]->name));
            ui->table1->setItem(k, 3, new QTableWidgetItem(QString("%1").arg(info.count)));
            k++;
        }
    }
}
