#include "staffmanage.h"
#include "ui_staffmanage.h"
#include "admindialog.h"
#include <QDebug>
#include "data.h"
#include <QtWidgets>

staffManage::staffManage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::staffManage)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("内部账号管理"));
    ui->backBtn->setFocusPolicy(Qt::NoFocus);
    ui->backBtn->setDefault(false);

    model1 = new QSqlTableModel(this);
    model2 = new QSqlTableModel(this);
    model1->setTable("waiter");
    model2->setTable("chef");
    model1->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model2->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model1->select();
    model2->select();

    for(int i=0;i<5;i++)
        ui->tableView_1->setColumnWidth(i, 40);
    for(int i=0;i<2;i++)
        ui->tableView_2->setColumnWidth(i, 40);
    //ui->tableView_1->setFixedWidth(500);
    //ui->tableView_2->setFixedWidth(200);

    ui->tableView_1->setSortingEnabled(true);
    ui->tableView_1->setSelectionBehavior(QAbstractItemView::SelectRows);   //每次选一行
    ui->tableView_1->setSelectionMode(QAbstractItemView::SingleSelection);//鼠标单击的反应
    ui->tableView_1->setShowGrid(false);
    ui->tableView_1->verticalHeader()->hide();
    ui->tableView_1->setAlternatingRowColors(true);
    ui->tableView_1->setModel(model1);//
    ui->tableView_1->show();

    ui->tableView_2->setSortingEnabled(true);
    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);   //每次选一行
    ui->tableView_2->setSelectionMode(QAbstractItemView::SingleSelection);//鼠标单击的反应
    ui->tableView_2->setShowGrid(false);
    ui->tableView_2->verticalHeader()->hide();
    ui->tableView_2->setAlternatingRowColors(true);
    ui->tableView_2->setModel(model2);//
    ui->tableView_2->show();
    ui->backBtn->setIcon(QIcon(":/buttons/previous.png"));
    //background
    QImage im;
    im.load(":/images/backgnd.png");
    QPalette palette;
    palette.setBrush(this->backgroundRole(),QBrush(im.scaled(this->width(),this->height())));
    this->setPalette(palette);
}

staffManage::~staffManage()
{
    delete ui;
}

void staffManage::on_showBtn_clicked()
{
    model1->setTable("waiter");
    model1->select();
    model2->setTable("chef");
    model2->select();
}

void staffManage::on_submitBtn_clicked()
{
    model1->database().transaction();
    if(model1->submitAll())
        model1->database().commit();
    else{
        model1->database().rollback();
        QMessageBox::warning(this, tr("tableModel"), QString("%1").arg(model1->lastError().text()));
    }
    model2->database().transaction();
    if(model2->submitAll())
        model2->database().commit();
    else{
        model2->database().rollback();
        QMessageBox::warning(this, tr("tableModel"), QString("%1").arg(model2->lastError().text()));
    }
}

void staffManage::on_undoBtn_clicked()
{
    model1->revertAll();
    model2->revertAll();
}

void staffManage::on_addBtn_clicked()
{
    int row = model1->rowCount();
    QModelIndex index=model1->index(row-1, 0, QModelIndex());//前两个rowNum,columnNum为行列号
    int id = index.data().toInt();
    model1->insertRow(row);
    model1->setData(model1->index(row, 0), id);
}

void staffManage::on_delBtn_clicked()
{
    int curRow = ui->tableView_1->currentIndex().row();
    model1->removeRow(curRow);    //先执行删除

    int ok = QMessageBox::warning(this, tr("删除当前行"), tr("是否确定删除？"), QMessageBox::Yes, QMessageBox::No);
    if(ok == QMessageBox::No){
        model1->revertAll();     //不删除就撤销上一步
    }
    else model1->submitAll();    //否则提交
}

void staffManage::on_addBtn2_clicked()
{
    int row = model2->rowCount();
    QModelIndex index=model2->index(row-1, 0, QModelIndex());//前两个rowNum,columnNum为行列号
    int id = index.data().toInt();
    model2->insertRow(row);
    model2->setData(model2->index(row, 0), id);
}

void staffManage::on_delBtn2_clicked()
{
    int curRow = ui->tableView_2->currentIndex().row();
    model2->removeRow(curRow);    //先执行删除

    int ok = QMessageBox::warning(this, tr("删除当前行"), tr("是否确定删除？"), QMessageBox::Yes, QMessageBox::No);
    if(ok == QMessageBox::No){
        model2->revertAll();     //不删除就撤销上一步
    }
    else model2->submitAll();    //否则提交
}

void staffManage::on_backBtn_clicked()
{
    AdminDialog* a = new AdminDialog;
    a->show();
    this->close();
}
