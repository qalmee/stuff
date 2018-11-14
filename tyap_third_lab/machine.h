#ifndef MACHINE_H
#define MACHINE_H

#include <QString>
#include <QMap>
#include <QVector>

class Machine
{
public:
    Machine();

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
    void setStates(QVector<QString> *value);

    QVector<QString> *getFinishStates() const;
    void setFinishStates(QVector<QString> *value);

    QVector<QChar> *getInputAlphabet() const;
    void setInputAlphabet(QVector<QChar> *value);

    QVector<QChar> *getStackAlphabet() const;
    void setStackAlphabet(QVector<QChar> *value);

    QMap<QString, QVector<Condition> > *getMap() const;
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
    QMap<QString, QVector<Condition>> *m;



};

#endif // MACHINE_H
