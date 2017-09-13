#ifndef USERMANAGE_H
#define USERMANAGE_H

#include <QMainWindow>

namespace Ui {
class UserManage;
}

class UserManage : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserManage(QWidget *parent = 0);
    ~UserManage();

private:
    Ui::UserManage *ui;
};

#endif // USERMANAGE_H
