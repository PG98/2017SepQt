#include "selecttable.h"
#include "ui_selecttable.h"
#include "data.h"
#include "order.h"

selectTable::selectTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selectTable)
{
    ui->setupUi(this);
    ui->pushButton->setIcon(QIcon(":/images/refresh.png"));
    this->setWindowTitle(tr("选择餐桌"));
    QHBoxLayout *layout1 = new QHBoxLayout;
    QHBoxLayout *layout2 = new QHBoxLayout;
    QHBoxLayout *layout3 = new QHBoxLayout;
    for(int i=0;i<10;i++){
        button[i] = new KeyButton(QString("NO.%1").arg(i));
        button[i]->setIndex(i); //从0开始
        button[i]->setAutoDefault(false);
        button[i]->setFixedHeight(40);
        if(i<3){
            layout1->addWidget(button[i]);
            button[i]->setText("6人桌");
        }
        else if(i>=3 && i<7){
            layout2->addWidget(button[i]);
            button[i]->setText("10人桌");
        }
        else{
            layout3->addWidget(button[i]);
            button[i]->setText("15人桌");
        }
        connect(button[i], SIGNAL(keyClicked(int)), this, SLOT(setTable(int)));
    }
    setTableState();
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(layout1);
    layout->addLayout(layout2);
    layout->addLayout(layout3);
    ui->box->setLayout(layout);
    //外观设置
    QImage im;
    im.load(":/images/backgnd1.jpg");
    QPalette palette;
    palette.setBrush(this->backgroundRole(),QBrush(im.scaled(this->width(),this->height())));
    this->setPalette(palette);
    ui->pushButton->setIcon(QIcon(":/buttons/refresh.png"));
    ui->pushButton->setStyleSheet("QPushButton{background-color:lightsteelblue;\
                                color: black;   border-radius: 12px;  border: 3px groove gray;\
                                border-style: outset;}"
                               "QPushButton:hover{background-color:white; color: lightsteelblue;}"
                              "QPushButton:pressed{background-color:rgb(85, 170, 255);\
                                               border-style: inset; }"
                               );
}

selectTable::~selectTable()
{
    delete ui;
}

void selectTable::setTable(int i){
    Data::table[i].state = -1;
    qDebug()<<"table: "<<i<<", volume: "<<Data::table[i].volume;
    Order* w = new Order;
    w->currentTable = i;
    w->setCustomerId(currentID);
    w->show();
    this->close();
}

void selectTable::setTableState(){
    for(int i=0;i<10;i++){
        if(Data::table[i].state == 0){
            button[i]->setStyleSheet("QPushButton{background-color:mediumseagreen;\
                                        color: black;   border-radius: 10px;  border: 2px groove gray;\
                                        border-style: outset;}"
                                       "QPushButton:hover{background-color:white; color: lightsteelblue;}"
                                      "QPushButton:pressed{background-color:rgb(85, 170, 255);\
                                                       border-style: inset; }"
                                       );
        }
        else{
            button[i]->setEnabled(false);
            button[i]->setStyleSheet("QPushButton{background-color:lightslategray;\
                                        color: white;   border-radius: 10px;  border: 2px groove gray;\
                                        border-style: outset;}"
                                       );
        }
    }
}

void selectTable::on_pushButton_clicked(){
    setTableState();
}
