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

private slots:
    void mySortByColumn(int col);
    void MouseTrackItem(int row, int column);
    void rowSelect();

private:
    Ui::Order *ui;
    QStringList header = QStringList()<<"编号"<<"种类"<<"名字"<<"单价"<<"推荐度";
    void setTypeBox();
    void setBox1();
    void setBox2();
    void showDishes();

};

#endif // ORDER_H
