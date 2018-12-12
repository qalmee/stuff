#include "condition.h"


Condition::Condition()
{

}

Condition::Condition(QChar t, const QString &stackTop,
                     const QString &newStackTop,
                     const QString &nextState,
                     const QString &addToOutput,
                     const int number) :
    t(t), stackTop(stackTop), newStackTop(newStackTop), nextState(nextState), addToOutput(addToOutput), number(number)
{

}

QChar Condition::getT() const
{
    return t;
}

void Condition::setT(const QChar &value)
{
    t = value;
}

QString Condition::getStackTop() const
{
    return stackTop;
}

void Condition::setStackTop(const QString &value)
{
    stackTop = value;
}

QString Condition::getNewStackTop() const
{
    return newStackTop;
}

void Condition::setNewStackTop(const QString &value)
{
    newStackTop = value;
}

QString Condition::getNextState() const
{
    return nextState;
}

void Condition::setNextState(const QString &value)
{
    nextState = value;
}

int Condition::getNumber() const
{
    return number;
}

void Condition::setNumber(int value)
{
    number = value;
}

Condition &Condition::operator=(const Condition &other)
{
    this->setT(other.getT());
    this->setStackTop(other.getStackTop());
    this->setNumber(other.getNumber());
    this->setNextState(other.getNextState());
    this->setNewStackTop(other.getNewStackTop());
    this->setAddToOutput(other.getAddToOutput());
    return *this;
}

QString Condition::getAddToOutput() const
{
    return addToOutput;
}

void Condition::setAddToOutput(const QString &value)
{
    addToOutput = value;
}

