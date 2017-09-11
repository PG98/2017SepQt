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

private:
    Ui::Order *ui;
};

#endif // ORDER_H
