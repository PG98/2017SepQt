#ifndef MENUMANAGE_H
#define MENUMANAGE_H

#include <QMainWindow>
#include <QtWidgets>
#include "adddish.h"
#include "dishedit.h"

namespace Ui {
class MenuManage;
}

class MenuManage : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuManage(QWidget *parent = 0);
    ~MenuManage();

public slots:

private slots:
    void on_action_N_triggered();
    void changeType(int type);
    void on_OkBtn_clicked();
    void mySortByColumn(int column);    //表头单击排序
    void MouseTrackItem(int row, int column);
    void rowSelect();
    void showDishInfo(int row, int column);
    void on_action_D_triggered();
    void on_action_refresh_triggered();
    void on_action_edit_triggered();

    void on_action_S_triggered();


    void on_backBtn_clicked();

private:
    Ui::MenuManage *ui;
    addDish addDialog;
    dishEdit editDialog;
    QStringList header = QStringList()<<"编号"<<"种类"<<"名字"<<"单价"<<"推荐度";
    //布局
    void setTypeGroupBox();
    void setMenuGroupBox();
    void setDetailGroupBox();
    QHBoxLayout* setButtons();

    void showDishes();//显示所有菜品，按照类别排列
    void deleteDish();
    void saveCurrent();
};

#endif // MENUMANAGE_H
