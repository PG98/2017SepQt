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
    DB_update();
    this->close();
}

void FinishDialog::conclude(){//初始化内存中各项数据的状态
    Data::table[tableid].state = 0;
    //服务员历史，评分更新
    int waiterIndex = Data::table[tableid].waiterIndex;
    Data::table[tableid].waiterIndex = -1;  //
    if(Data::waiter[waiterIndex].table1 == tableid){
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
    }
    //菜品评分更新
    for(int i=0;i<ui->tableWidget->rowCount();i++){
        int dishid = ui->tableWidget->item(i, 0)->text().toInt();
        if(ui->tableWidget->item(i, 2)->text()!=""){
            int rating = ui->tableWidget->item(i, 2)->text().toInt();
            double currentRating = Data::hash1[dishid]->rating;
            Data::hash1[dishid]->rating = (currentRating*Data::hash1[dishid]->history + rating)/(Data::hash1[dishid]->history+1);
        }
    }
}

void FinishDialog::DB_update(){
    //

}
