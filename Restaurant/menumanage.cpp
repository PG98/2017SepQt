#include "menumanage.h"
#include "ui_menumanage.h"
#include <QDebug>
#include "data.h"
#include <QHeaderView>

MenuManage::MenuManage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuManage)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("菜单管理"));
    qDebug()<<"dish count:"<<Dish::count<<endl;

    setTypeGroupBox();
    setDetailGroupBox();
    setMenuGroupBox();

    QHBoxLayout* bottomLayout = setButtons();
    //connect W按钮..槽..
    connect(&addDialog, SIGNAL(refresh()), this, SLOT(on_action_refresh_triggered()));//从子窗口传递信号，添加完成后自动刷新显示


    QGridLayout *layout = new QGridLayout;
    layout->addWidget(ui->dishtype, 0, 0);
    layout->addWidget(ui->menu, 1, 0);
    layout->addWidget(ui->detail, 0, 1, 2, 1);
    layout->addLayout(bottomLayout, 2, 0, 1, 2);
    layout->setColumnStretch(1, 1);
    layout->setColumnMinimumWidth(0, 500);
    layout->setRowMinimumHeight(0,100);
/*
    QFont font = ui->tableWidget->horizontalHeader()->font();
    font.setBold(true);
    ui->tableWidget->horizontalHeader()->setFont(font);
    ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);//双击编辑
    for(int i=0;i<ui->tableWidget->rowCount();i++){
        ui->tableWidget->item(i,0)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->item(i,1)->setFlags(Qt::NoItemFlags);
    }
    ui->tableWidget->setMouseTracking(true);
    connect(ui->tableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(mySortByColumn(int)));//单击表头排序
    connect(ui->tableWidget, SIGNAL(cellEntered(int,int)), this, SLOT(MouseTrackItem(int, int)));//鼠标移动效果
    connect(ui->tableWidget, SIGNAL(cellClicked(int,int)),this, SLOT(rowSelect()));//单击选中行
    connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)), this, SLOT(itemEdit(int,int)));//双击编辑
*/
    QWidget* widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
}

MenuManage::~MenuManage()
{
    delete ui;
}

void MenuManage::setTypeGroupBox(){
    ui->dishtype->setTitle("菜品种类");
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
    ui->dishtype->setLayout(layout);
}

void MenuManage::setMenuGroupBox(){
    ui->menu->setTitle("菜单");
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);//可以选中多行

    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setRowCount(Dish::count);
    //按照类别顺序显示表格
    showDishes();
    /*//按下标输出
    for(int i=0;i<ui->tableWidget->rowCount();i++){
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(Data::dish[i].id)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(Data::dish[i].getType()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(Data::dish[i].name));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString("%1").arg(Data::dish[i].price)));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(Data::dish[i].notes));
        //ui->tableWidget->horizontalHeaderItem(i)->setBackgroundColor(QColor(100, 149, 237));//会崩溃
    }*/
    //connect  表格项目点击，激活等
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(ui->tableWidget, 0, 0);
    ui->menu->setLayout(layout);
    ui->tableWidget->setHorizontalHeaderLabels(header);//设置表头
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
}

void MenuManage::setDetailGroupBox(){
    ui->detail->setTitle("详情");
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
//以上各GroupBox初始化
//显示某种菜品 id升序
void MenuManage::changeType(int type){
    //qDebug()<<"type: "<<type+1;
    //传入当前下拉菜单项的下标，对应的dish类是type(enum的首项定义为1)
    if(type==0){
        qDebug()<<"show all";    //按照类别顺序显示表格
        showDishes();
    }
    else{
        qDebug()<<"clear table";
        ui->tableWidget->clearContents();
        int k=0;
        for(int i=0;i<Dish::count;i++){
            //qDebug()<<QString("%1").arg((int)Data::dish[i].type);
            if((int)Data::dish[i].type==type && Data::dish[i].demand>=-1){
                ui->tableWidget->setItem(k, 0, new QTableWidgetItem(QString("%1").arg(Data::dish[i].id)));
                ui->tableWidget->setItem(k, 1, new QTableWidgetItem(Data::dish[i].getType()));
                ui->tableWidget->setItem(k, 2, new QTableWidgetItem(Data::dish[i].name));
                ui->tableWidget->setItem(k, 3, new QTableWidgetItem(QString("%1").arg(Data::dish[i].price)));
                ui->tableWidget->setItem(k, 4, new QTableWidgetItem(Data::dish[i].notes));
                k++;
            }
        }
        for(int i=0;i<k;i++){
            ui->tableWidget->item(i,0)->setFlags(Qt::NoItemFlags);
            ui->tableWidget->item(i,1)->setFlags(Qt::NoItemFlags);
        }
        //ui->tableWidget->setMouseTracking(true);
        //connect(ui->tableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(mySortByColumn(int)));//单击表头排序
        //connect(ui->tableWidget, SIGNAL(cellEntered(int,int)), this, SLOT(MouseTrackItem(int, int)));//鼠标移动效果
        //connect(ui->tableWidget, SIGNAL(cellClicked(int,int)),this, SLOT(rowSelect()));//单击选中行
        //connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)), this, SLOT(itemEdit(int,int)));//双击编辑
    }
}

void MenuManage::on_action_N_triggered()
{
    //addDialog = new addDish;
    addDialog.show();
    addDialog.exec();
}

void MenuManage::on_OkBtn_clicked()
{
    QMessageBox box;          //警告对话框
    box.setWindowTitle("提醒");
    box.setIcon(QMessageBox::Warning);
    box.setText("是否保存？");
    QPushButton *yesBtn = box.addButton(tr("是(&Y)"), QMessageBox::YesRole);
    box.addButton("否(&N)", QMessageBox::NoRole);
    QPushButton *cancelBut = box.addButton("取消", QMessageBox::RejectRole);

    box.exec();
    if(box.clickedButton() == yesBtn)
        return;
    else if (box.clickedButton() == cancelBut)
        return;
}

void MenuManage::showDishes(){
    int j,index=0, temp[8][20];
    for(int i=0;i<8;i++)
        for(int j=0;j<20;j++)
            temp[i][j]=-1;
    for(int i=0;i<Dish::count;i++){
        int t = (int)Data::dish[i].type-1;
        for(j=0;temp[t][j]!=-1;j++);
        temp[t][j]=i;
    }
    for(int i=0;i<8;i++){
        for(j=0;temp[i][j]!=-1;j++){
            if(Data::dish[temp[i][j]].demand>=-1){
                ui->tableWidget->setItem(index, 0, new QTableWidgetItem(QString("%1").arg(Data::dish[temp[i][j]].id)));
                ui->tableWidget->setItem(index, 1, new QTableWidgetItem(Data::dish[temp[i][j]].getType()));
                ui->tableWidget->setItem(index, 2, new QTableWidgetItem(Data::dish[temp[i][j]].name));
                ui->tableWidget->setItem(index, 3, new QTableWidgetItem(QString("%1").arg(Data::dish[temp[i][j]].price)));
                ui->tableWidget->setItem(index, 4, new QTableWidgetItem(Data::dish[temp[i][j]].notes));
                index++;
            }
        }
    }
    QFont font = ui->tableWidget->horizontalHeader()->font();
    font.setBold(true);
    ui->tableWidget->horizontalHeader()->setFont(font);
    ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);//双击编辑
    for(int i=0;i<ui->tableWidget->rowCount();i++){
        ui->tableWidget->item(i,0)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->item(i,1)->setFlags(Qt::NoItemFlags);
    }
    ui->tableWidget->setMouseTracking(true);
    connect(ui->tableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(mySortByColumn(int)));//单击表头排序
    connect(ui->tableWidget, SIGNAL(cellEntered(int,int)), this, SLOT(MouseTrackItem(int, int)));//鼠标移动效果
    connect(ui->tableWidget, SIGNAL(cellClicked(int,int)),this, SLOT(rowSelect()));//单击选中行
    connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)), this, SLOT(itemEdit(int,int)));//双击编辑
}

void MenuManage::mySortByColumn(int column)
{
    static bool f = true;
    qDebug()<<"sort: ";
    ui->tableWidget->sortByColumn(column, f ? Qt::AscendingOrder : Qt::DescendingOrder);
    f = !f;
}


void MenuManage::MouseTrackItem(int row, int column){
    Q_UNUSED(column)
    ui->tableWidget->setStyleSheet("selection-background-color:lightblue;"); //选中项的颜色
    ui->tableWidget->setCurrentCell(row, QItemSelectionModel::Select); //设置该行为选中项。
}

void MenuManage::rowSelect(){
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

void MenuManage::on_action_D_triggered(){
    QMessageBox delBox;
    delBox.setWindowTitle(tr("删除菜单项"));
    delBox.setIcon(QMessageBox::Warning);
    delBox.setText(tr("是否确认删除"));
    QPushButton *yesBtn = delBox.addButton(tr("是(&Y)"), QMessageBox::YesRole);
    QPushButton *noBtn = delBox.addButton(tr("取消"), QMessageBox::NoRole);
    delBox.exec();
    if(delBox.clickedButton()==yesBtn){
        deleteDish();
        showDishes();
        return;
    }
    else if(delBox.clickedButton()==noBtn)
        return;
}

void MenuManage::deleteDish(){
    int row = ui->tableWidget->currentRow();
    QString id = ui->tableWidget->item(row, 0)->text();
    int ID = id.toInt();
    qDebug()<<"delete ID: "<<ID;
    for(int i=0;i<Dish::count;i++){
        if(Data::dish[i].id == ID){
            Data::dish[i].demand = -2;
            Dish::count--;
            break;
        }
    }       //找到id后把该菜品的需求视为-2，即删除
}
//
void MenuManage::on_action_refresh_triggered()
{
    qDebug()<<"refresh..";
    changeType(0);
    connect(ui->tableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(mySortByColumn(int)));//单击表头排序
    connect(ui->tableWidget, SIGNAL(cellEntered(int,int)), this, SLOT(MouseTrackItem(int, int)));//鼠标移动效果
}
//此函数作废
void MenuManage::itemEdit(int row,int column){
    QString id = ui->tableWidget->item(row, 0)->text();
    int ID = id.toInt(),i;
    for(i=0;i<Dish::count;i++){
        if(Data::dish[i].id == ID){
            Data::dish[i].demand = -1;
            break;
        }
    }
    QString Name = ui->tableWidget->item(row,2)->text();
    int price = ui->tableWidget->item(row,3)->text().toInt();
    QString note = ui->tableWidget->item(row,4)->text();
    Data::dish[i].name = ui->tableWidget->item(row,2)->text();
    qDebug()<<"dish name: "<<Name;
    Data::dish[i].price = price;
    Data::dish[i].notes = note;
    qDebug()<<"Edit id: "<<ID;
    return;
}
//

void MenuManage::on_action_edit_triggered()
{

}
