#include "waiterwindow.h"
#include "ui_waiterwindow.h"
#include "data.h"

waiterWindow::waiterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::waiterWindow)
{
    ui->setupUi(this);
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
    else if(Data::table[i].state > 0){
        QMessageBox::warning(this, QString("警告"), QString("抱歉，该桌没有客人"));
        on_refreshBtn_clicked();
        return;
    }
    if(Data::waiter[index].table1 == 0){
        Data::waiter[index].table1 = i;
        Data::table[i].waiterID = id;
        table1 = i;
        ui->box1->setTitle(QString("table %1").arg(i));
        button[i]->setText(tr("服务中"));
        Data::table[i].state = id;
    }
    else if(Data::waiter[index].table2 == 0){
        Data::waiter[index].table2 = i;
        table2 = i;
        ui->box2->setTitle(QString("table %1").arg(i));
        button[i]->setText(tr("老子在这"));
        Data::table[i].state = id;
    }
    else{
        QMessageBox::warning(this, QString("警告"), QString("您当前服务已达到上限"));
        return;
    }

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
            button[i]->setEnabled(false);
        }
        else{
            button[i]->setText("已被接管");
            button[i]->setEnabled(false);
        }
    }
    if(table1){
        ui->waterBtn1->setIcon(Data::table[table1].water ? QIcon(path1) : QIcon(path2));
        ui->remindBtn1->setIcon(Data::table[table1].remind ? QIcon(path1) : QIcon(path2));
        ui->payBtn1->setIcon(Data::table[table1].pay ? QIcon(path1) : QIcon(path2));
    }
    if(table2){
        ui->waterBtn2->setIcon(Data::table[table2].water ? QIcon(path1) : QIcon(path2));
        ui->remindBtn2->setIcon(Data::table[table2].remind ? QIcon(path1) : QIcon(path2));
        ui->payBtn2->setIcon(Data::table[table2].pay ? QIcon(path1) : QIcon(path2));
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
        if(Data::table[table1].remind == true){
            Data::table[table1].remind = false;
            ui->payBtn2->setIcon(QIcon(path1));
        }
    }
}

void waiterWindow::on_payBtn1_clicked()
{
    if(table1!=-1){
        if(Data::table[table1].pay == true){
            Data::table[table1].pay = false;
            ui->payBtn2->setIcon(QIcon(path1));
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
        if(Data::table[table2].remind == true){
            Data::table[table2].remind = false;
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

