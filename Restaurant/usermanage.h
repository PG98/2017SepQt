#ifndef USERMANAGE_H
#define USERMANAGE_H

#include <QDialog>

namespace Ui {
class UserManage;
}

class UserManage : public QDialog
{
    Q_OBJECT

public:
    explicit UserManage(QWidget *parent = 0);
    ~UserManage();

private:
    Ui::UserManage *ui;
};

#endif // USERMANAGE_H
