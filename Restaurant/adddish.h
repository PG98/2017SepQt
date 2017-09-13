#ifndef ADDDISH_H
#define ADDDISH_H

#include <QDialog>
#include "data.h"

namespace Ui {
class addDish;
}

class addDish : public QDialog
{
    Q_OBJECT

public:
    explicit addDish(QWidget *parent = 0);
    ~addDish();

signals:
    void refresh();

public slots:
    void send();

private slots:
    void on_CancelBtn_clicked();
    virtual void on_OkBtn_clicked();

private:
    Ui::addDish *ui;
};

#endif // ADDDISH_H
