#include "machine.h"
#include <QHash>

Machine::Machine()
{

}

Machine::Machine(QVector<QString> *statesNames, QVector<QString> *terminals,
                 QVector<QVector<QString> > *statesValues, const int start, QVector<bool> &finishStates):
    start(start), finishStates(finishStates), statesNames(statesNames), terminals(terminals), statesValues(statesValues)
{

}

void Machine::setData(QVector<QString> *statesNames, QVector<QString> *terminals,
                      QVector<QVector<QString> > *statesValues, int start, QVector<bool> &finishStates)
{
    this->statesNames = statesNames;
    this->statesValues = statesValues;
    this->terminals = terminals;
    this->start = start;
    this->finishStates = finishStates;
}

QVector<QPair<QString, QChar> > *Machine::getResult()
{
    return &this->result;
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
        if (currentState.isEmpty()){
            error = Machine::EndWasNotReached;
            return;
        }
    }
    result.push_back({currentState, '\0'});
    if (!finishStates[statesNames->indexOf(currentState)]){
        error = Machine::NotInTheFinishState;
        return;
    }
    error = Machine::isOk;
}

