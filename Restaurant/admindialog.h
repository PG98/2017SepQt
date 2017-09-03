#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>
#include "menumanage.h"

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

private:
    Ui::AdminDialog *ui;
    MenuManage* menuDlg;
};

#endif // ADMINDIALOG_H
