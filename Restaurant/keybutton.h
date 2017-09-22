#ifndef KEYBUTTON_H
#define KEYBUTTON_H
#include <QtWidgets>
//抽象出一个类，以便实现（一般pushbutton无法做到的）发送特定的int、QString等信号。
//使用时通过构造keybutton数组减少代码量
class KeyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit KeyButton(const QString& text, QWidget *parent = 0) : QPushButton(parent)
    {
        this->setText(text);
        connect(this, SIGNAL(clicked(bool)), this, SLOT(on_clicked()));
    }
    KeyButton(){
        connect(this, SIGNAL(clicked(bool)), this, SLOT(on_clicked()));
    }

    void setIndex(int n) {index = n;}
private:
    int index;

signals:
    void keyClicked(int index);
public slots:
    void on_clicked(){
        //qDebug()<<"index of this button is "<<index;
        emit this->keyClicked(this->index);
    }
};

#endif // KEYBUTTON_H
