#ifndef KEYBUTTON_H
#define KEYBUTTON_H
#include <QtWidgets>

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

    void setIndex(int n){
        index = n;
    }

private:
    int index;

signals:
    void keyClicked(int index);
    //void keyPressed(const QString &msg);
    //void keyReleased(const QString &msg);
    //void keyClicked(const QString &msg);

public slots:
    void on_clicked(){
        //qDebug()<<"index of this button is "<<index;
        emit this->keyClicked(this->index);

    }
};

#endif // KEYBUTTON_H
