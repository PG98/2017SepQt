#ifndef MENUMANAGE_H
#define MENUMANAGE_H

#include <QDialog>

namespace Ui {
class MenuManage;
}

class MenuManage : public QDialog
{
    Q_OBJECT

public:
    explicit MenuManage(QWidget *parent = 0);
    ~MenuManage();

private slots:
    void on_motherfucker_clicked();

private:
    Ui::MenuManage *ui;
};

#endif // MENUMANAGE_H
