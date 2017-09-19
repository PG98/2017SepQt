#ifndef FINISHDIALOG_H
#define FINISHDIALOG_H

#include <QDialog>

namespace Ui {
class FinishDialog;
}

class FinishDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FinishDialog(QWidget *parent = 0, int tableid = 0);
    FinishDialog() {}
    ~FinishDialog();
    int tableid;

private slots:
    void on_pushButton_clicked();

private:
    Ui::FinishDialog *ui;
    QStringList header = QStringList()<<"菜品评价"<<"打分(1~5)";
    void setBox1();
    void setBox2();
    void conclude();
    void DB_update();
};

#endif // FINISHDIALOG_H
