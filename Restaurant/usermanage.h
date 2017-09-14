#ifndef USERMANAGE_H
#define USERMANAGE_H

#include <QMainWindow>
#include <QtWidgets>
#include "adduser.h"


namespace Ui {
class UserManage;
}

class UserManage : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserManage(QWidget *parent = 0);
    ~UserManage();

private slots:
    void mySortByColumn(int column);
    void MouseTrackItem(int row, int column);
    void rowSelect();
    void on_action_refresh_triggered();
    void on_action_star_triggered();
    void on_action_D_triggered();
    void on_OkBtn_clicked();
    void on_action_N_triggered();
    void search();

private:
    Ui::UserManage *ui;
    addUser adduser;
    void setBox1();
    void setBox2();
    QHBoxLayout* setButtons();
    QStringList header = QStringList()<<"编号"<<"手机"<<"姓名"<<"会员状态";

    void showUsers();
    void saveCurrent();
};










#endif // USERMANAGE_H
