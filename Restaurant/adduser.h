#ifndef ADDUSER_H
#define ADDUSER_H

#include <QDialog>
#include "data.h"

namespace Ui {
class addUser;
}

class addUser : public QDialog
{
    Q_OBJECT

public:
    explicit addUser(QWidget *parent = 0);
    ~addUser();

signals:
    void refresh();

public slots:
    void send();

private slots:
    void on_cancelBtn_clicked();

    void on_okBtn_clicked();

private:
    Ui::addUser *ui;
};

#endif // ADDUSER_H
