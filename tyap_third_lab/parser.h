#ifndef PARSER_H
#define PARSER_H

#include <QVector>
#include <QString>
#include <QSet>
#include <QMap>
#include "condition.h"

class Parser
{
public:
    Parser();
    void parseStates(const QString &states);
    void parseFinishStates(const QString &finishStates);
    void parseInputAlphabet(const QString &inputAlphabet);
    void parseStackAlphabet(const QString &stackAlphabet);
    void parseMachineRules(const QString &machineRules);
    void parseSingleMachineRule(int number, const QString &singleRule);

    const QVector<QString> *getStates() const;
    const QVector<QString> *getFinishStates() const;
    const QVector<QChar>* getInputAlphabet() const;
    const QVector<QChar>* getStackAlphabet() const;
    QChar getEmptySymbol() const;
    QString getStack() const;
    QString getChain() const;

    void setEmptySymbol(const QChar &value);
    void setStack(const QString &value);
    void setChain(const QString &value);

    const QMap<QString, QVector<Condition> > *getMap() const;

    QString getStartState() const;
    void setStartState(const QString &value);

private:
    QVector <QString> states;
    QVector <QString> finishStates;
    QVector <QChar> inputAlphabet;
    QVector <QChar> stackAlphabet;
    QString chain;
    QString stack;
    QChar emptySymbol;
    QString startState;
    QMap <QString, QVector<Condition>> map;
};

#endif // PARSER_H
