#include "orderquery.h"
#include "ui_orderquery.h"
#include "data.h"

orderQuery::orderQuery(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::orderQuery)
{
    ui->setupUi(this);
}

orderQuery::~orderQuery(){
    delete ui;
    ui->pushButton->setFocusPolicy(Qt::NoFocus);
}

void orderQuery::on_pushButton_clicked()
{
    int id = ui->lineEdit->text().toInt();
    bool flag = false;
    for(orderInfo* info: Data::list){
        if(info->dishid == id && info->tableid == tableid){
            status = info->status;
            flag = true;
            break;
        }
    }
    if(flag){
        if(status == -1){
            ui->resultLabel->setText(tr("该菜品仍在等候队列中，稍安勿躁。"));
        }
        else if(status == 0){
            ui->resultLabel->setText(tr("烹饪中"));

        }
        else{
            ui->resultLabel->setText(tr("已就绪，服务员即将上菜"));
        }
    }
    else{
        ui->resultLabel->setText(tr("您查询的菜品不存在"));
    }
}
