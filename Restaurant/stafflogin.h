#ifndef STAFFLOGIN_H
#define STAFFLOGIN_H

#include <QDialog>

namespace Ui {
class staffLogin;
}

class staffLogin : public QDialog
{
    Q_OBJECT

public:
    explicit staffLogin(QWidget *parent = 0);
    ~staffLogin();

private slots:
    void on_loginBtn_clicked();

private:
    Ui::staffLogin *ui;
};

#endif // STAFFLOGIN_H
