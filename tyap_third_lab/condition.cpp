#include "condition.h"


Condition::Condition()
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

