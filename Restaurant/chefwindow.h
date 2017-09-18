#ifndef CHEFWINDOW_H
#define CHEFWINDOW_H

#include <QMainWindow>
#include "data.h"

namespace Ui {
class chefWindow;
}

class chefWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit chefWindow(QWidget *parent = 0);
    ~chefWindow();
    int id;
    int index;

public slots:
        void on_action_R_triggered();

private slots:
    void MouseTrackItem(int row, int column);
    void MouseTrackItem2(int row, int column);
    void rowSelect();
    void rowSelect2();
    void updateCell(int);
    void complete(int);
    void on_action_U_triggered();
    void on_action_F_triggered();

private:
    QStringList header = QStringList()<<"订单号"<<"桌号"<<"菜品编号"<<"名字"<<"份数";
    Ui::chefWindow *ui;
    void setbox1();
    void setbox2();
    void setTableAppearance();
};

#endif // CHEFWINDOW_H
