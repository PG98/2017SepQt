#include "waiterwindow.h"
#include "ui_waiterwindow.h"
#include "data.h"

waiterWindow::waiterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::waiterWindow)
{
    ui->setupUi(this);
    init();
    on_refreshBtn_clicked();
}

waiterWindow::~waiterWindow()
{
    delete ui;
}

void waiterWindow::init(){
    table1 = -1;
    table2 = -1;
    QHBoxLayout* layout1 = new QHBoxLayout;
    QHBoxLayout* layout2 = new QHBoxLayout;
    for(int i=0;i<10;i++){
        button[i] = new KeyButton(QString("桌%1").arg(i));
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
    if(Data::table[i].state > 0){
        QMessageBox::warning(this, QString("警告"), QString("抱歉，该桌已在服务中"));
        on_refreshBtn_clicked();
        return;
    }
    else if(Data::table[i].state == 0){
        QMessageBox::warning(this, QString("警告"), QString("抱歉，该桌没有客人"));
        on_refreshBtn_clicked();
        return;
    }
    //优先填入1
    if(Data::waiter[index].table1 == 0){
        Data::waiter[index].table1 = i;
        Data::table[i].waiterIndex = index;
        table1 = i;
        ui->box1->setTitle(QString("table %1").arg(i));
        button[i]->setText(tr("服务中"));
        Data::table[i].state = id;
        ui->waterBtn1->setEnabled(true);
        ui->remindBtn1->setEnabled(true);
        ui->payBtn1->setEnabled(true);
    }
    else if(Data::waiter[index].table2 == 0){
        Data::waiter[index].table2 = i;
        table2 = i;
        ui->box2->setTitle(QString("table %1").arg(i));
        button[i]->setText(tr("服务中"));
        Data::table[i].state = id;
        ui->waterBtn2->setEnabled(true);
        ui->remindBtn2->setEnabled(true);
        ui->payBtn2->setEnabled(true);
    }
    else{
        QMessageBox::warning(this, QString("警告"), QString("您当前服务已达到上限"));
        return;
    }
    on_refreshBtn_clicked();
}

//应该做成按钮，状态改变更换图标
void waiterWindow::on_refreshBtn_clicked()
{
    for(int i=0;i<10;i++){
        int state = Data::table[i].state;
        if(state == -1){
            button[i]->setText("需要服务");
            button[i]->setEnabled(true);
        }
        else if(state == 0){
            button[i]->setText("空闲");
            button[i]->setEnabled(false);
        }
        else if(state == id){
            button[i]->setText("服务中");
            button[i]->setEnabled(true);
        }
        else{
            button[i]->setText("已被接管");
            button[i]->setEnabled(false);
        }
    }
    if(table1!=-1){
        ui->box1->setTitle(QString("桌号:%1 服务中").arg(table1+1));//starts from 1
        ui->waterBtn1->setIcon(Data::table[table1].water ? QIcon(path2) : QIcon(path1));
        ui->remindBtn1->setIcon(Data::table[table1].remind ? QIcon(path2) : QIcon(path1));
        ui->payBtn1->setIcon(Data::table[table1].pay ? QIcon(path2) : QIcon(path1));
    }
    else{
        ui->box1->setTitle(QString("空缺"));
        ui->waterBtn1->setEnabled(false);
        ui->remindBtn1->setEnabled(false);
        ui->payBtn1->setEnabled(false);
    }
    if(table2!=-1){
        ui->box2->setTitle(QString("桌号:%1 服务中").arg(table2));
        ui->waterBtn2->setIcon(Data::table[table2].water ? QIcon(path2) : QIcon(path1));
        ui->remindBtn2->setIcon(Data::table[table2].remind ? QIcon(path2) : QIcon(path1));
        ui->payBtn2->setIcon(Data::table[table2].pay ? QIcon(path2) : QIcon(path1));
    }
    else{
        ui->box2->setTitle(QString("空缺"));
        ui->waterBtn2->setEnabled(false);
        ui->remindBtn2->setEnabled(false);
        ui->payBtn2->setEnabled(false);
    }
}

void waiterWindow::on_waterBtn1_clicked()
{
    if(table1!=-1){
        if(Data::table[table1].water == true){
            Data::table[table1].water = false;
            ui->payBtn2->setIcon(QIcon(path1));
        }
    }
}

void waiterWindow::on_remindBtn1_clicked()
{
    if(table1!=-1){
        if(Data::table[table1].remind!=-1){
            //找出订单号对应菜品名字
            int dishid = Data::list[Data::table[table1].remind]->dishid;
            QString dish = Data::hash1[dishid]->name;
            QMessageBox::information(this, QString("congratulations"), QString("请向厨师要求对订单号 %1, %2 加快进度。").arg(Data::table[table1].remind).arg(dish));
            int i;
            for(i=0;Data::urgent[i] && i<19;i++);  //遍历，添加订单到末尾
            Data::urgent[i] = Data::table[table2].remind;
            ui->payBtn1->setIcon(QIcon(path1));
        }
    }
}

void waiterWindow::on_payBtn1_clicked()
{
    if(table1!=-1){
        if(Data::table[table1].pay == true){
            Data::table[table1].pay = false;
            ui->payBtn1->setIcon(QIcon(path1));
        }
    }
}

void waiterWindow::on_waterBtn2_clicked()
{
    if(table2 != -1){
        if(Data::table[table2].water == true){
            Data::table[table2].water = false;
            ui->payBtn2->setIcon(QIcon(path1));
        }
    }
}

void waiterWindow::on_remindBtn2_clicked()
{
    if(table2 != -1){
        if(Data::table[table2].remind!=-1){
            int dishid = Data::list[Data::table[table2].remind]->dishid;
            QString dish = Data::hash1[dishid]->name;
            QMessageBox::information(this, QString("congratulations"), QString("请向厨师要求对订单号 %1, %2 加快进度。").arg(Data::table[table2].remind).arg(dish));
            int i;
            for(i=0;Data::urgent[i] && i<19;i++);  //遍历，添加订单到末尾
            Data::urgent[i] = Data::table[table2].remind;
            ui->payBtn2->setIcon(QIcon(path1));
        }
    }
}

void waiterWindow::on_payBtn2_clicked()
{
    if(table2!=-1){
        if(Data::table[table2].pay == true){
            Data::table[table2].pay = false;
            ui->payBtn2->setIcon(QIcon(path1));
        }
    }
}

