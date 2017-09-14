#ifndef USERMANAGE_H
#define USERMANAGE_H

#include <QMainWindow>
#include <QtWidgets>


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

private:
    Ui::UserManage *ui;
    void setBox1();
    void setBox2();
    QHBoxLayout* setButtons();
    QStringList header = QStringList()<<"编号"<<"手机"<<"email"<<"会员状态";

    void showUsers();
    void deleteUser();
    void saveCurrent();
};










#endif // USERMANAGE_H
