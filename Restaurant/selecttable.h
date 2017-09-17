#ifndef SELECTTABLE_H
#define SELECTTABLE_H

#include <QDialog>
#include "keybutton.h"

namespace Ui {
class selectTable;
}

class selectTable : public QDialog
{
    Q_OBJECT

public:
    explicit selectTable(QWidget *parent = 0);
    ~selectTable();
    void setCurrentID(int id) {currentID = id;}

private:
    Ui::selectTable *ui;
    int currentID;
    KeyButton *button[10];

private slots:
    void setTable(int);
    void setTableState();
    void on_toolButton_clicked();
};

#endif // SELECTTABLE_H
