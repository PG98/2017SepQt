#include "menumanage.h"
#include "ui_menumanage.h"
#include <QDebug>
#include "data.h"

MenuManage::MenuManage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuManage)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(5);//
    ui->tableWidget->setRowCount(10);//

    setTypeGroupBox();
    setDetailGroupBox();
    setMenuGroupBox();
    QHBoxLayout* bottomLayout = setButtons();
    //connect 按钮

    QGridLayout *layout = new QGridLayout;

    layout->addWidget(ui->dishtype, 0, 0);
    layout->addWidget(ui->menu, 1, 0);
    layout->addWidget(ui->detail, 0, 1, 2, 1);
    layout->addLayout(bottomLayout, 2, 0, 1, 2);
    layout->setColumnStretch(1, 1);
    layout->setColumnMinimumWidth(0, 500);
    layout->setRowMinimumHeight(0,100);


    QWidget* widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);


}

MenuManage::~MenuManage()
{
    delete ui;
}

void MenuManage::setTypeGroupBox(){
    //combobox index  connect()
    QGridLayout* layout = new QGridLayout;
    layout->addWidget(ui->typeview, 0, 0);
    ui->dishtype->setLayout(layout);
}

void MenuManage::setMenuGroupBox(){
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"编号"<<"种类"<<"名字"<<"单价"<<"备注");
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

    //connect  表格项目点击，激活等
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(ui->tableWidget, 0, 0);
    ui->menu->setLayout(layout);
}

void MenuManage::setDetailGroupBox(){
    //菜品图片
    ui->imageLabel->setWordWrap(true);
    ui->imageLabel->setAlignment(Qt::AlignCenter);
    //ui->imageLabel->setPixmap(QPixmap(":/images/xxxx"));

    ui->notesLabel->setWordWrap(true);
    ui->notesLabel->setAlignment(Qt::AlignBottom);

    //其他label 可加入
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(ui->imageLabel, 0, 0, 3, 2);
    layout->addWidget(ui->notesLabel, 0, 0);
    ui->detail->setLayout(layout);
}

QHBoxLayout* MenuManage::setButtons(){
    //设置按钮外观
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(ui->backBtn);
    layout->addStretch(1);
    layout->addWidget(ui->OkBtn);
    return layout;
}





















