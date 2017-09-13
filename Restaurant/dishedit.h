#ifndef DISHEDIT_H
#define DISHEDIT_H

#include <QDialog>
#include "data.h"

namespace Ui {
class dishEdit;
}

class dishEdit : public QDialog
{
    Q_OBJECT

public:
    explicit dishEdit(QWidget *parent = 0);
    ~dishEdit();
    int index = 0;
    int id = 0;
    QString dishtype;
    QString name;
    int price;
    QString notes;
    void set();

signals:
    void refresh();

public slots:
    void send();

private slots:
    void on_CancelBtn_clicked();
    void on_OkBtn_clicked();

private:
    Ui::dishEdit *ui;
};

#endif // DISHEDIT_H
