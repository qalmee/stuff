#include "machine.h"
#include <stdexcept>

Machine::Machine(const QMap<QString, QVector<Condition> > *map) : m(map)
{
}

void Machine::run()
{
    QString currentState = this->startState;
    for (int i = 0; i<chain.size(); i++){
        ans.push_back({currentState, stack});
        bool flag = false;
        for (auto con : this->m->value(currentState)){
            if ((con.getT() == chain[i] || con.getT() == emptySymbol) && stack.startsWith(con.getStackTop())){
                flag = true;
                currentState = con.getNextState();
                stack.replace(0, con.getStackTop().size(), con.getNewStackTop());
                break;
            }
        }
        if (!flag){
            throw new std::runtime_error("Конец цепочки не был достигнут");
        }
    }
    ans.push_back({currentState, stack});
    if (!finishStates->contains(currentState)){
        throw  new std::runtime_error("Конечное состояние автомата не было достигнуто");
    }
    if (stack.size() > 0){
        throw  new std::runtime_error("Стэк не пуст");
    }
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

QVector<QString> *Machine::getFinishStates() const
{
    return finishStates;
}

QVector<QChar> *Machine::getInputAlphabet() const
{
    return inputAlphabet;
}

QVector<QChar> *Machine::getStackAlphabet() const
{
    return stackAlphabet;
}

const QMap<QString, QVector<Condition> > *Machine::getMap() const
{
    return m;
}

const QVector<Machine::tact> *Machine::getAns() const
{
    return &this->ans;

}

void Machine::setMap(QMap<QString, QVector<Condition> > *value)
{
    m = value;
}

void Machine::setFinishStates(const QVector<QString> *value)
{
    finishStates = const_cast<QVector <QString> *>(value);
}
