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

private:
    Ui::MenuManage *ui;

    void setTypeGroupBox();
    void setMenuGroupBox();
    void setDetailGroupBox();
    QHBoxLayout* setButtons();
};

#endif // MENUMANAGE_H
