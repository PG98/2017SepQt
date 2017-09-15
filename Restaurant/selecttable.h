#ifndef SELECTTABLE_H
#define SELECTTABLE_H

#include <QDialog>

namespace Ui {
class selectTable;
}

class selectTable : public QDialog
{
    Q_OBJECT

public:
    explicit selectTable(QWidget *parent = 0);
    ~selectTable();

private:
    Ui::selectTable *ui;

private slots:
    void setTable(int);
};

#endif // SELECTTABLE_H
