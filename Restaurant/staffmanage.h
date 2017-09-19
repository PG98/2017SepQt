#ifndef STAFFMANAGE_H
#define STAFFMANAGE_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class staffManage;
}

class staffManage : public QDialog
{
    Q_OBJECT

public:
    explicit staffManage(QWidget *parent = 0);
    ~staffManage();

private slots:
    void on_showBtn_clicked();

    void on_submitBtn_clicked();

    void on_undoBtn_clicked();

    void on_addBtn_clicked();

    void on_delBtn_clicked();

    void on_addBtn2_clicked();

    void on_delBtn2_clicked();

    void on_backBtn_clicked();

private:
    Ui::staffManage *ui;
    QSqlTableModel* model1;
    QSqlTableModel* model2;
};

#endif // STAFFMANAGE_H
