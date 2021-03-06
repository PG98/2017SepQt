#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>
#include "menumanage.h"
#include "usermanage.h"

namespace Ui {
class AdminDialog;
}

class AdminDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdminDialog(QWidget *parent = 0);
    ~AdminDialog();

private slots:
    void on_menuBtn_clicked();

    void on_userBtn_clicked();

    void on_staffBtn_clicked();

private:
    Ui::AdminDialog *ui;
};

#endif // ADMINDIALOG_H
