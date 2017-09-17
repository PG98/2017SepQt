#ifndef ORDERQUERY_H
#define ORDERQUERY_H

#include <QDialog>

namespace Ui {
class orderQuery;
}

class orderQuery : public QDialog
{
    Q_OBJECT

public:
    explicit orderQuery(QWidget *parent = 0);
    ~orderQuery();
    int status;
    int tableid;

private slots:
    void on_pushButton_clicked();

private:
    Ui::orderQuery *ui;
};

#endif // ORDERQUERY_H
