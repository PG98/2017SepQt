#ifndef WAITERWINDOW_H
#define WAITERWINDOW_H

#include <QMainWindow>

namespace Ui {
class waiterWindow;
}

class waiterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit waiterWindow(QWidget *parent = 0);
    ~waiterWindow();

private:
    Ui::waiterWindow *ui;
};

#endif // WAITERWINDOW_H
