#ifndef FINISHDIALOG_H
#define FINISHDIALOG_H

#include <QDialog>
#include <QtSql>

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
    void dishRating(int, int);

private:
    Ui::FinishDialog *ui;
    QStringList header = QStringList()<<"菜品编号"<<"名称"<<"打分(1~5)";
    QSqlQuery query;
    void setBox1();
    void setBox2();
    void conclude();
    void saveJournal();
};

#endif // FINISHDIALOG_H
