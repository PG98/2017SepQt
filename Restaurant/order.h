#ifndef ORDER_H
#define ORDER_H

#include <QMainWindow>

namespace Ui {
class Order;
}

class Order : public QMainWindow
{
    Q_OBJECT

public:
    explicit Order(QWidget *parent = 0);
    ~Order();
    static int getOrderCount(){return orderCount;}  //总的菜品个数（每种可不止一次）

private slots:
    void mySortByColumn(int col);
    void MouseTrackItem(int row, int column);
    void rowSelect();
    void delRow(int row, int col);
    void addOrder(int row);
    void changeType(int);

private:
    Ui::Order *ui;
    static int orderCount;
    QStringList header = QStringList()<<"编号"<<"种类"<<"名字"<<"单价"<<"推荐度";
    QStringList header1 = QStringList()<<"编号"<<"名字"<<"单价"<<"推荐度"<<"份数";
    void setbox1();
    void setTypeBox();
    void setbox3();
    void setbox4();
    void showDishes();
    void setTableAppearance();

};

#endif // ORDER_H
