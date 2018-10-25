#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QObject>
#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    MyPushButton(unsigned int index);
    MyPushButton(QString caption, unsigned int index);
public slots:
    void clickedSlot();
signals:
    void clicked(unsigned int);
private:
    unsigned int index;
};

#endif // MYPUSHBUTTON_H
