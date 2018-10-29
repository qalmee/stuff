#include "mypushbutton.h"

MyPushButton::MyPushButton(unsigned int index) : index(index)
{
    connect(this, &QPushButton::clicked, this, &MyPushButton::clickedSlot);
}

MyPushButton::MyPushButton(QString caption, unsigned int index):QPushButton (caption), index(index)
{
    connect(this, &QPushButton::clicked, this, &MyPushButton::clickedSlot);
}

void MyPushButton::clickedSlot()
{
    emit clicked(index);
}
