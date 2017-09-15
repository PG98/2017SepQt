#ifndef CHEFWINDOW_H
#define CHEFWINDOW_H

#include <QMainWindow>

namespace Ui {
class chefWindow;
}

class chefWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit chefWindow(QWidget *parent = 0);
    ~chefWindow();

private:
    Ui::chefWindow *ui;
};

#endif // CHEFWINDOW_H
