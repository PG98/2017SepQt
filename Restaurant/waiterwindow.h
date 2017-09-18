#ifndef WAITERWINDOW_H
#define WAITERWINDOW_H

#include <QMainWindow>
#include "keybutton.h"

namespace Ui {
class waiterWindow;
}

class waiterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit waiterWindow(QWidget *parent = 0);
    ~waiterWindow();
    int id;
    int index;

private slots:
    void claimTable(int);
    void on_waterBtn1_clicked();

    void on_remindBtn1_clicked();

    void on_payBtn1_clicked();

    void on_waterBtn2_clicked();

    void on_remindBtn2_clicked();

    void on_payBtn2_clicked();

    void on_refreshBtn_clicked();

private:
    int table1 = -1; //当前服务的桌号下标
    int table2 = -1;
    Ui::waiterWindow *ui;
    void init();    //按钮、布局初始化
    KeyButton* button[10];
    QString path1 = ":/buttons/cloud-computing.png";
    QString path2 = ":/buttons/exclamation-mark.png";
};

#endif // WAITERWINDOW_H
