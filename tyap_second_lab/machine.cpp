#include "machine.h"
#include <QHash>

Machine::Machine()
{

}

Machine::Machine(QVector<QString> *statesNames, QVector<QString> *terminals,
                 QVector<QVector<QString> > *statesValues, const int start, const int end):
    start(start), end(end), statesNames(statesNames), terminals(terminals), statesValues(statesValues)
{

}

void Machine::setData(QVector<QString> *statesNames, QVector<QString> *terminals, QVector<QVector<QString> > *statesValues, int start, int end)
{
    this->statesNames = statesNames;
    this->statesValues = statesValues;
    this->terminals = terminals;
    this->start = start;
    this->end = end;
}

QVector<QPair<QString, QChar> > Machine::getResult()
{
    return this->result;
}

int Machine::getError()
{
    return error;
}

void Machine::setChain(const QString &chain)
{
    this->chain = chain;
}

void Machine::run()
{
    if (statesNames == nullptr || statesValues == nullptr || terminals == nullptr){
        return;
    }
    result.clear();
    QHash<QString, QHash<QChar, QString>> m;
    for (int i = 0; i<statesNames->size(); i++){
        for (int j = 0; j<terminals->size(); j++){
            m[statesNames->at(i)][terminals->at(j)[0]] = statesValues->at(i).at(j);
        }
    }
    currentState = statesNames->at(start);
    for (auto ch : chain){
        result.push_back({currentState, ch});
        if (!terminals->contains(QString(1, ch))){
            error = Machine::SymbolDoesNotExistInAlphabet;
            return;
        }
        if (!m[currentState].contains(ch)){
            error = Machine::EndWasNotReached;
            return;
        }
        currentState = m[currentState][ch];
    }
    result.push_back({currentState, '\0'});
    if (currentState != statesNames->at(end)){
        error = Machine::NotInTheFinishState;
    }
    error = Machine::isOk;
}

