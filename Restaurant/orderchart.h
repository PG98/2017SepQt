#ifndef ORDERCHART_H
#define ORDERCHART_H

#include <QDialog>

namespace Ui {
class orderChart;
}

class orderChart : public QDialog
{
    Q_OBJECT

public:
    explicit orderChart(QWidget *parent = 0);
    ~orderChart();

private:
    Ui::orderChart *ui;
};

#endif // ORDERCHART_H
