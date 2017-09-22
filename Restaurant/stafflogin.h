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
    void on_waiterBtn_clicked();
    void on_waiterBtn_2_clicked();
    void on_managerBtn_clicked();
    void setButtonStyle();

private:
    Ui::staffLogin *ui;
};

#endif // STAFFLOGIN_H
