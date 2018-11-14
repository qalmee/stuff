#ifndef MACHINE_H
#define MACHINE_H

#include <QString>
#include <QMap>
#include <QVector>
#include "condition.h"

class Machine
{
public:
    Machine(const QMap<QString, QVector<Condition> > *map);

    void run();

    QString getChain() const;
    void setChain(const QString &value);

    QString getStack() const;
    void setStack(const QString &value);

    QChar getEmptySymbol() const;
    void setEmptySymbol(const QChar &value);

    QString getStartState() const;
    void setStartState(const QString &value);

    QVector<QString> *getStates() const;

    QVector<QString> *getFinishStates() const;

    QVector<QChar> *getInputAlphabet() const;

    QVector<QChar> *getStackAlphabet() const;

    const QMap<QString, QVector<Condition> > *getMap() const;

    struct tact{
        QString state, stack;
    };

    const QVector <tact> *getAns() const;

    void setMap(QMap<QString, QVector<Condition> > *value);

private:
    QString chain;
    QString stack;
    QChar emptySymbol;
    QString startState;
    QVector <QString> *states;
    QVector <QString> *finishStates;
    QVector <QChar> *inputAlphabet;
    QVector <QChar> *stackAlphabet;
    const QMap<QString, QVector<Condition>> * m;
    QVector <tact> ans;
};

#endif // MACHINE_H
