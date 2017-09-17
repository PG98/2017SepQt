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
    this->setFixedWidth(this->width());
    setBox1();
    setBox2();

    connect(&adduser, SIGNAL(refresh()), this, SLOT(on_action_refresh_triggered()));
    ui->tableWidget->setMouseTracking(true);
    connect(ui->tableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(mySortByColumn(int)));//单击表头排序
    connect(ui->tableWidget, SIGNAL(cellEntered(int,int)), this, SLOT(MouseTrackItem(int, int)));//鼠标移动效果
    connect(ui->tableWidget, SIGNAL(cellClicked(int,int)),this, SLOT(rowSelect()));//单击选中行
    connect(ui->tableWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(on_action_star_triggered()));//双击加星

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
    ui->box1->setTitle(tr("检索"));
    //LineEdit 设置
    ui->searchEdit->setFocusPolicy(Qt::ClickFocus);
    QPushButton* searchBtn = new QPushButton;
    searchBtn->setCursor(Qt::PointingHandCursor);
    searchBtn->setFixedSize(22,22);
    searchBtn->setToolTip(QStringLiteral("搜索"));
    searchBtn->setStyleSheet("QPushButton{border-image:url(:/buttons/search.png); background:transparent;}");
    QMargins margins = ui->searchEdit->textMargins();
    ui->searchEdit->setTextMargins(margins.left(), margins.top(), searchBtn->width(), margins.bottom());
    ui->searchEdit->setPlaceholderText(QStringLiteral("请输入搜索内容"));
    QHBoxLayout* searchLayout = new QHBoxLayout;
    searchLayout->addStretch();
    searchLayout->addWidget(searchBtn);
    searchLayout->setSpacing(0);
    searchLayout->setContentsMargins(0, 0, 0, 0);
    ui->searchEdit->setLayout(searchLayout);
    connect(searchBtn, SIGNAL(clicked(bool)), this, SLOT(search()));
    connect(ui->searchEdit, SIGNAL(returnPressed()), this, SLOT(search()));

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
    showUsers();
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
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:tan;}");
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
    qDebug()<<"user.count = "<<count;
    ui->tableWidget->setRowCount(count);
    int i=0;
    /*
    for(int k=0;k<count;k++){
        if(Data::user[k].isMember>-2){
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(Data::user[k].id)));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(Data::user[k].phone));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(Data::user[k].name));
            if(Data::user[k].isMember <= 0)
                ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QIcon(":/buttons/graystar.png"), "普通"));
            else
                ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QIcon(":/buttons/star.png"), "会员"));
            i++;
        }
    }*/
    QHashIterator<int, User*> j(Data::hash0);
    while(j.hasNext()){
        j.next();
        if(j.value()->isMember>-2){
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(j.key())));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(j.value()->phone));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(j.value()->name));
            if(j.value()->isMember <= 0)
                ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QIcon(":/buttons/graystar.png"), "普通"));
            else
                ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QIcon(":/buttons/star.png"), "会员"));
            i++;
        }
    }
    ui->tableWidget->setRowCount(i);
    mySortByColumn(0);
    mySortByColumn(0);
    //ui->tableWidget->resizeColumnToContents(2);
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
    ui->tableWidget->setStyleSheet("selection-background-color:lightblue;"); //悬浮项的颜色
    ui->tableWidget->setCurrentCell(row, QItemSelectionModel::Select); //设置该行为选中项。
}

void UserManage::rowSelect(){   //鼠标移动、点击效果
    static bool track = true;
    if(track){
        ui->tableWidget->setStyleSheet("selection-background-color:darkseagreen;"); //选中项的颜色
        int row = ui->tableWidget->currentRow();
        qDebug()<<"row: "<<row<<"   id: "<<ui->tableWidget->item(row, 0)->text();
        ui->tableWidget->setMouseTracking(false);
    }
    else{
        ui->tableWidget->setMouseTracking(true);
        connect(ui->tableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(mySortByColumn(int)));//单击表头排序
        connect(ui->tableWidget, SIGNAL(cellEntered(int,int)), this, SLOT(MouseTrackItem(int, int)));//鼠标移动效果
    }
    track = !track;
}

void UserManage::on_action_refresh_triggered()
{
    showUsers();
}

void UserManage::on_action_star_triggered()
{
    int row = ui->tableWidget->currentRow();
    int id = ui->tableWidget->item(row, 0)->text().toInt();
    qDebug()<<"star id: "<<id;
    /*
    for(int i=0;i<User::getCount();i++){
        if(Data::user[i].id == id){
            if(Data::user[i].isMember <= 0 || Data::user[i].isMember == 3){ //3是新建用户中的‘普通’
                Data::user[i].isMember = 2; //新增会员设为2  以便添加到数据库
                break;
            }else{
                Data::user[i].isMember = -1;
            }
        }
    }*/
    if(Data::hash0.contains(id)){
        if(Data::hash0[id]->isMember <= 0 || Data::hash0[id]->isMember == 3){ //3是新建用户中的‘普通’
            Data::hash0[id]->isMember = 2; //新增会员设为2  以便添加到数据库
        }else{
            Data::hash0[id]->isMember = -1;
        }
    }else{
        qDebug()<<"no such id in hash0: "<<id;
    }
    showUsers();
}

void UserManage::on_action_D_triggered(){
    QMessageBox box;
    box.setWindowTitle(tr("删除用户"));
    box.setIcon(QMessageBox::Warning);
    box.setText(tr("是否确认删除？"));
    QPushButton* yesBtn = box.addButton(tr("删除"), QMessageBox::YesRole);
    QPushButton* noBtn = box.addButton(tr("取消"), QMessageBox::NoRole);
    box.exec();
    if(box.clickedButton()==yesBtn){
        int row = ui->tableWidget->currentRow();
        int id = ui->tableWidget->item(row, 0)->text().toInt();
        /*
        int i;
        for(i=0;i<User::getCount();i++){
            if(Data::user[i].id == id){
                Data::user[i].isMember = -2;
                User::count--;
                qDebug()<<"delete id: "<<id;
                break;
            }
        }
        if(i==0)
            qDebug()<<"failed to delete";
            */
        if(Data::hash0.contains(id)){
            Data::hash0[id]->isMember = -2;
            User::count--;
        }else{
            qDebug()<<"no such id in hash0: "<<id;
        }
        showUsers();
    }
    else if(box.clickedButton()==noBtn)
        return ;
}

void UserManage::on_OkBtn_clicked()
{
    QMessageBox box;
    box.setWindowTitle("完成编辑");
    box.setText("是否退出？");
    QPushButton *yesBtn = box.addButton(tr("退出(&Y)"), QMessageBox::YesRole);
    QPushButton *backBtn = box.addButton(tr("返回上一级(&Y)"), QMessageBox::NoRole);
    QPushButton *cancelBtn = box.addButton(tr("取消"), QMessageBox::RejectRole);
    box.exec();
    if(box.clickedButton()==yesBtn){
        saveCurrent();
            this->close();
            return;
    }
    else if(box.clickedButton()==backBtn){
           saveCurrent();
           AdminDialog* admin = new AdminDialog;
           admin->show();
           this->close();
           return;
    }
    else if(box.clickedButton()==cancelBtn){
           return;
    }
}

void UserManage::saveCurrent(){
    //int count = User::getCount();
    int flag = 0, id = 0;
    QSqlQuery query;
    QString tempstring;
    /*
    for(int i=0;i<count;i++){
        id = Data::user[i].id;
        flag = Data::user[i].isMember;
        if(flag == -2){     //删除
            qDebug()<<"delete an account: id "<<id;
            tempstring = QString("delete from user where id = %1").arg(id);
            query.exec(tempstring);
        }
        else if(flag == -1){    //去除会员属性
            qDebug()<<"'unMember' this id: "<<id;
            tempstring = QString("update user set isMember = 0 where id = %1").arg(id);
            query.exec(tempstring);
        }
        else if(flag == 2){     //加星
            qDebug()<<"'enMember' this id: "<<id;
            tempstring = QString("update user set isMember =1 where id = %1").arg(id);
            query.exec(tempstring);
        }
        else if(flag == 3 || flag == 4){     //新建
            flag -= 3;
            qDebug()<<"insert new user";
            tempstring = QString("insert into user values(%1, ?, ?, ?, %2)").arg(id).arg(flag);
            query.prepare(tempstring);
            query.addBindValue(Data::user[i].pwd);
            query.addBindValue(Data::user[i].phone);
            query.addBindValue(Data::user[i].name);
            if(!query.exec()){
                qDebug()<<"insert failed!";
                qDebug()<<query.lastError();
            }
        }
    }*/
    QHashIterator<int, User*> i(Data::hash0);
    while(i.hasNext()){
        i.next();
        id = i.key();
        flag = i.value()->isMember;
        if(flag == -2){     //删除
            qDebug()<<"delete an account: id "<<id;
            tempstring = QString("delete from user where id = %1").arg(id);
            query.exec(tempstring);
        }
        else if(flag == -1){    //去除会员属性
            qDebug()<<"'unMember' this id: "<<id;
            tempstring = QString("update user set isMember = 0 where id = %1").arg(id);
            query.exec(tempstring);
        }
        else if(flag == 2){     //加星
            qDebug()<<"'enMember' this id: "<<id;
            tempstring = QString("update user set isMember =1 where id = %1").arg(id);
            query.exec(tempstring);
        }
        else if(flag == 3 || flag == 4){     //新建
            flag -= 3;
            qDebug()<<"insert new user";
            tempstring = QString("insert into user values(%1, ?, ?, ?, %2)").arg(id).arg(flag);
            query.prepare(tempstring);
            query.addBindValue(i.value()->pwd);
            query.addBindValue(i.value()->phone);
            query.addBindValue(i.value()->name);
            if(!query.exec()){
                qDebug()<<"insert failed!";
                qDebug()<<query.lastError();
            }
        }
    }
    this->statusBar()->showMessage(tr("保存成功!"), 3000);
}

void UserManage::on_action_N_triggered()
{
    adduser.show();
    adduser.exec();
}

void UserManage::search(){
    ui->tableWidget->clearContents();
    QString str = ui->searchEdit->text();
    int k = 0;
    /*
    for(int i=0;i<User::getCount();i++){
        if(Data::user[i].name == str||Data::user[i].phone == str||QString("%1").arg(Data::user[i].id) == str){
            ui->tableWidget->setItem(k, 0, new QTableWidgetItem(QString("%1").arg(Data::user[i].id)));
            ui->tableWidget->setItem(k, 1, new QTableWidgetItem(Data::user[i].phone));
            ui->tableWidget->setItem(k, 2, new QTableWidgetItem(Data::user[i].name));
            if(Data::user[i].isMember <= 0)
                ui->tableWidget->setItem(k, 3, new QTableWidgetItem(QIcon(":/buttons/graystar.png"), "普通"));
            else
                ui->tableWidget->setItem(k, 3, new QTableWidgetItem(QIcon(":/buttons/star.png"), "会员"));
            k++;
        }
    }*/
    QHashIterator<int, User*> i(Data::hash0);
    while(i.hasNext()){
        i.next();
        if(i.value()->name == str||i.value()->phone == str||QString("%1").arg(i.key())==str){
            ui->tableWidget->setItem(k, 0, new QTableWidgetItem(QString("%1").arg(i.key())));
            ui->tableWidget->setItem(k, 1, new QTableWidgetItem(i.value()->phone));
            ui->tableWidget->setItem(k, 2, new QTableWidgetItem(i.value()->name));
            if(i.value()->isMember <= 0)
                ui->tableWidget->setItem(k, 3, new QTableWidgetItem(QIcon(":/buttons/graystar.png"), "普通"));
            else
                ui->tableWidget->setItem(k, 3, new QTableWidgetItem(QIcon(":/buttons/star.png"), "会员"));
            k++;
        }
    }
    if(k==0){
        QMessageBox::information(this, QString("搜索结果"), QString("没有您想要的内容"));
        showUsers();
    }
}

void UserManage::on_backBtn_clicked()
{
    QMessageBox box;
    box.setWindowTitle("返回上一级");
    box.setText("是否返回？");
    QPushButton *yesBtn = box.addButton(tr("是(&Y)"), QMessageBox::YesRole);
    QPushButton * noBtn = box.addButton(tr("取消"), QMessageBox::NoRole);
    box.exec();
    if(box.clickedButton() == yesBtn){
        AdminDialog* admin = new AdminDialog;
        admin->show();
        this->close();
        return;
    }
    else if(box.clickedButton() == noBtn){
        return;
    }
}

void UserManage::on_action_S_triggered()
{
    saveCurrent();
}
