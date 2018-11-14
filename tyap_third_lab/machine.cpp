#include "machine.h"

Machine::Machine()
{

}

void Machine::run()
{

}

QString Machine::getChain() const
{
    return chain;
}

void Machine::setChain(const QString &value)
{
    chain = value;
}

QString Machine::getStack() const
{
    return stack;
}

void Machine::setStack(const QString &value)
{
    stack = value;
}

QChar Machine::getEmptySymbol() const
{
    return emptySymbol;
}

void Machine::setEmptySymbol(const QChar &value)
{
    emptySymbol = value;
}

QString Machine::getStartState() const
{
    return startState;
}

void Machine::setStartState(const QString &value)
{
    startState = value;
}

QVector<QString> *Machine::getStates() const
{
    return states;
}

void Machine::setStates(QVector<QString> *value)
{
    states = value;
}

QVector<QString> *Machine::getFinishStates() const
{
    return finishStates;
}

void Machine::setFinishStates(QVector<QString> *value)
{
    finishStates = value;
}

QVector<QChar> *Machine::getInputAlphabet() const
{
    return inputAlphabet;
}

void Machine::setInputAlphabet(QVector<QChar> *value)
{
    inputAlphabet = value;
}

QVector<QChar> *Machine::getStackAlphabet() const
{
    return stackAlphabet;
}

void Machine::setStackAlphabet(QVector<QChar> *value)
{
    stackAlphabet = value;
}

QMap<QString, QVector<Condition> > *Machine::getMap() const
{
    return m;
}

void Machine::setMap(QMap<QString, QVector<Condition> > *value)
{
    m = value;
}
