#ifndef MANAGERDIALOG_H
#define MANAGERDIALOG_H

#include <QDialog>

namespace Ui {
class managerDialog;
}

class managerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit managerDialog(QWidget *parent = 0);
    ~managerDialog();

private slots:
    void sortDishes(int column);
    void switchPage();
    void on_refreshBtn_clicked();

private:
    Ui::managerDialog *ui;
    void setBox1();
    void setBox2();
    void setBox3();
    QStringList chefHeader = QStringList()<<"厨师工号"<<"累计做菜";
    QStringList waiterHeader = QStringList()<<"服务员工号"<<"累计桌数"<<"平均评价";
    QStringList dishHeader = QStringList()<<"菜品编号"<<"品名"<<"推荐程度"<<"累计人气"<<"累计评价";
    QStringList streamHeader = QStringList()<<"编号"<<"桌号"<<"菜品"<<"份数"<<"单价"<<"状态";
};

#endif // MANAGERDIALOG_H
