#ifndef MENUMANAGE_H
#define MENUMANAGE_H

#include <QMainWindow>

namespace Ui {
class MenuManage;
}

class MenuManage : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuManage(QWidget *parent = 0);
    ~MenuManage();

private:
    Ui::MenuManage *ui;
};

#endif // MENUMANAGE_H
