#include "finishdialog.h"
#include "ui_finishdialog.h"
#include <QtWidgets>
#include "data.h"

FinishDialog::FinishDialog(QWidget *parent, int currentTable) :
    QDialog(parent), tableid(currentTable),
    ui(new Ui::FinishDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("评价");
    this->setFixedSize(this->width(), this->height());
    setBox1();
    setBox2();
    ui->pushButton->setText("完成并退出");
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(ui->box1);
    layout->addWidget(ui->box2);
    layout->addWidget(ui->pushButton);
    //ui->pushButton->setFixedWidth(120);
    this->setLayout(layout);
    connect(ui->tableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(dishRating(int, int)));
    //外观设置
    QImage im;
    im.load(":/images/backgnd1.jpg");
    QPalette palette;
    palette.setBrush(this->backgroundRole(),QBrush(im.scaled(this->width(),this->height())));
    this->setPalette(palette);
}

FinishDialog::~FinishDialog()
{
    delete ui;
}

void FinishDialog::setBox1(){
    ui->box1->setTitle("服务员评价");
    ui->label->setText("对本次服务员作出评价: ");
    ui->lineEdit->setPlaceholderText("1分~5分");
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(ui->label);
    layout->addWidget(ui->lineEdit);
    ui->box1->setLayout(layout);
}

void FinishDialog::setBox2(){
    ui->box2->setTitle("菜品评价");
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setColumnCount(3);
    for(int i=0;i<3;i++){
        ui->tableWidget->setColumnWidth(i, 151);
    }
    int i=0;
    for(orderInfo* info : Data::list){
        if(info->tableid == tableid){
            int dishid = info->dishid;
            ui->tableWidget->setRowCount(i+1);
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(dishid)));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(Data::hash1[dishid]->name)));
            i++;
        }
    }
    QFont font = ui->tableWidget->horizontalHeader()->font();
    font.setBold(true);
    ui->tableWidget->horizontalHeader()->setFont(font);
    //ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//双击编辑
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(ui->tableWidget);
    ui->box2->setLayout(layout);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:tan;}");
}

void FinishDialog::on_pushButton_clicked()
{
    conclude();
    this->close();
}

void FinishDialog::conclude(){//初始化内存中各项数据的状态
    Data::table[tableid].state = 0;
    //服务员历史，评分更新
    int waiterIndex = Data::table[tableid].waiterIndex;
    Data::table[tableid].waiterIndex = -1;  //
    if(waiterIndex == -1){
        qDebug()<<"exiting without being served.";
    }
    else if(Data::waiter[waiterIndex].table1 == tableid){
        qDebug()<<"waiterID"<<Data::waiter[waiterIndex].id<<"table1:"<<Data::waiter[waiterIndex].table1<<"index:"<<tableid<<"tableidID:"<<Data::table[tableid].id;
        Data::waiter[waiterIndex].table1 = -1;  //重置服务员状态
        if(ui->lineEdit->text()!=""){
            int rating = ui->lineEdit->text().toInt();
            double currentRating = Data::waiter[waiterIndex].rating;
            Data::waiter[waiterIndex].rating = (currentRating * Data::waiter[waiterIndex].history + rating)/(Data::waiter[waiterIndex].history+1);
        }
       Data::waiter[waiterIndex].history++;
    }else{
        qDebug()<<"waiterID"<<Data::waiter[waiterIndex].id<<"table1:"<<Data::waiter[waiterIndex].table2<<"index:"<<tableid<<"tableidID:"<<Data::table[tableid].id;
        Data::waiter[waiterIndex].table2 = -1;  //重置服务员状态
        if(ui->lineEdit->text()!=""){
            int rating = ui->lineEdit->text().toInt();
            double currentRating = Data::waiter[waiterIndex].rating;
            Data::waiter[waiterIndex].rating = (currentRating * Data::waiter[waiterIndex].history + rating)/(Data::waiter[waiterIndex].history+1);
        }
        Data::waiter[waiterIndex].history++;
        query.exec(QString("update waiter set history = %1 where id = %2").arg(Data::waiter[waiterIndex].id).arg(Data::waiter[waiterIndex].history));
    }
    saveJournal();
}

//菜品评分更新
void FinishDialog::dishRating(int row, int col){
    if(col == 2){
        int dishid = ui->tableWidget->item(row, 0)->text().toInt();
        qDebug()<<"recording the change of rating of dishid: "<<dishid;
        int rating = ui->tableWidget->item(row, 2)->text().toInt();
        double currentRating = Data::hash1[dishid]->rating;
        Data::hash1[dishid]->rating = (currentRating*Data::hash1[dishid]->history + rating)/(Data::hash1[dishid]->history+1);
        query.exec(QString("update dish set rating = %1 where id = %2").arg(Data::hash1[dishid]->rating).arg(dishid));
    }
}

//存储点菜列表中的信息作为账目表
void FinishDialog::saveJournal(){
    QString tempstring;
    QDate date = QDate::currentDate();
    QString dateStr = date.toString("yyyy-MM-dd");
    for(orderInfo* info : Data::list){
        if(info->tableid == tableid && info->chefid!=-1){   //根据桌号判断要存储的订单
            tempstring = "insert into journal values(?, ?, ?, ?, ?)";
            query.prepare(tempstring);
            query.addBindValue(tableid+1);
            query.addBindValue(Data::hash1[info->dishid]->name);
            query.addBindValue(Data::hash1[info->dishid]->price);
            query.addBindValue(info->count);
            query.addBindValue(dateStr);
            info->chefid = -1;      //防止一天之中桌子重复使用，订单重复添加
            if(!query.exec()){
                qDebug()<<query.lastError();
            }
            else{
                qDebug()<<"inserted: "<<Data::hash1[info->dishid]->name;
            }
            query.next();
        }
    }
    qDebug()<<"insert complete";
}

