#ifndef MENUMANAGE_H
#define MENUMANAGE_H

#include <QMainWindow>
#include <QtWidgets>

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
    void changeType(int type);


private:
    Ui::MenuManage *ui;
    QStringList header = QStringList()<<"编号"<<"种类"<<"名字"<<"单价"<<"备注";

    void setTypeGroupBox();
    void setMenuGroupBox();
    void setDetailGroupBox();
    QHBoxLayout* setButtons();    

};

#endif // MENUMANAGE_H
