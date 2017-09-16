#ifndef WAITERWINDOW_H
#define WAITERWINDOW_H

#include <QMainWindow>
#include "keybutton.h"

namespace Ui {
class waiterWindow;
}

class waiterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit waiterWindow(QWidget *parent = 0);
    ~waiterWindow();
    int id;
    int index;

private slots:
    void claimTable(int);

    void on_pushButton_clicked();

private:
    int table1 = 0;
    int table2 = 0;
    Ui::waiterWindow *ui;
    void init();
    KeyButton* button[10];
};

#endif // WAITERWINDOW_H
