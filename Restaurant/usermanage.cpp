#include "usermanage.h"
#include "ui_usermanage.h"
#include <QDebug>
#include "data.h"
#include <QHeaderView>
#include <QSqlError>
#include "admindialog.h"

UserManage::UserManage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserManage)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("用户管理"));
    qDebug()<<Data::user[3].phone;
    setBox1();
    setBox2();

    ui->tableWidget->setMouseTracking(true);
    connect(ui->tableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(mySortByColumn(int)));//单击表头排序
    connect(ui->tableWidget, SIGNAL(cellEntered(int,int)), this, SLOT(MouseTrackItem(int, int)));//鼠标移动效果
    connect(ui->tableWidget, SIGNAL(cellClicked(int,int)),this, SLOT(rowSelect()));//单击选中行

    //QHBoxLayout* bottom = setButtons();
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(ui->box1);
    layout->addWidget(ui->box2);
    layout->addLayout(setButtons());
    QWidget* widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
}

UserManage::~UserManage()
{
    delete ui;
}

void UserManage::setBox1(){
    ui->box2->setTitle(tr("用户检索"));
    //LineEdit 设置

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(ui->searchEdit, 0, 0);
    ui->box1->setLayout(layout);
}

void UserManage::setBox2(){
    ui->box2->setTitle(tr("用户名单"));
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(User::count);
    QFont font = ui->tableWidget->horizontalHeader()->font();
    font.setBold(true);
    ui->tableWidget->horizontalHeader()->setFont(font);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//双击编辑
       /*//可用来禁止编辑
       for(int i=0;i<k;i++){
           ui->tableWidget->item(i,0)->setFlags(Qt::NoItemFlags);
           ui->tableWidget->item(i,1)->setFlags(Qt::NoItemFlags);
       }*/

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(ui->tableWidget, 0, 0);
    ui->box2->setLayout(layout);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:indigo;}");
}

QHBoxLayout* UserManage::setButtons(){
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(ui->backBtn);
    layout->addStretch(1);
    layout->addWidget(ui->OkBtn);
    return layout;
}

void UserManage::showUsers(){
    int count = User::count;
    for(int i=0;i<count;i++){
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(Data::user[i].id)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(Data::user[i].phone));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(Data::user[i].email));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString("%1").arg(Data::user[i].isMember)));
    }
}

void UserManage::mySortByColumn(int column)
{
    static bool f = true;
    qDebug()<<"sort: ";
    ui->tableWidget->sortByColumn(column, f ? Qt::AscendingOrder : Qt::DescendingOrder);
    f = !f;
}

void UserManage::MouseTrackItem(int row, int column){
    Q_UNUSED(column)
    ui->tableWidget->setStyleSheet("selection-background-color:lightblue;"); //选中项的颜色
    ui->tableWidget->setCurrentCell(row, QItemSelectionModel::Select); //设置该行为选中项。
}

void UserManage::rowSelect(){   //鼠标移动、点击效果
    static bool track = true;
    qDebug()<<track;
    if(track){
        ui->tableWidget->setStyleSheet("selection-background-color:burlywood;"); //选中项的颜色
        qDebug()<<ui->tableWidget->currentRow();
        ui->tableWidget->setMouseTracking(false);
    }
    else{
        ui->tableWidget->setMouseTracking(true);
        connect(ui->tableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(mySortByColumn(int)));//单击表头排序
        connect(ui->tableWidget, SIGNAL(cellEntered(int,int)), this, SLOT(MouseTrackItem(int, int)));//鼠标移动效果
    }
    track = !track;
}








