#ifndef AdminDialog_H
#define AdminDialog_H

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
    void on_MenuBtn_clicked();

    void on_UserBtn_clicked();

private:
    Ui::AdminDialog *ui;
};

#endif // AdminDialog_H
