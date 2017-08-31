#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QDialog>
#include "menumanage.h"
#include "usermanage.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = 0);
    ~AdminWindow();

private slots:
    void on_MenuBtn_clicked();

    void on_UserBtn_clicked();

private:
    Ui::AdminWindow *ui;
};

#endif // ADMINWINDOW_H
