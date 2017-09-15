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
        //connect(tm, SIGNAL(timeout()), this, SLOT(on_pressed_last()));
        //connect(this, SIGNAL(pressed()), this, SLOT(on_pressed()));
        //connect(this, SIGNAL(released()), this, SLOT(on_released()));
        //connect(this, SIGNAL(clicked()), this, SLOT(on_clicked()));
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
        qDebug()<<"index of this button is "<<index;
        emit this->keyClicked(this->index);

    }
    /*void on_pressed() { emit this->keyPressed(this->text());
                        tm->start(pauseMsecs); }
    void on_pressed_last() { emit this->keyPressed(this->text());
                             tm->setInterval(intervalMsecs); }
    void on_released() { tm->stop(); emit this->keyReleased(this->text()); }
    void on_clicked() { emit this->keyClicked(this->text()); }  */

};

#endif // KEYBUTTON_H
