#ifndef CONDITION_H
#define CONDITION_H

#include <QString>

class Condition
{
public:
    Condition();
    Condition(QChar t, QString stackTop, QString newStackTop, QString nextState);
    QChar getT() const;
    QString getNextState() const;
    QString getStackTop() const;
    QString getNewStackTop() const;

    void setT(const QChar &value);
    void setStackTop(const QString &value);
    void setNewStackTop(const QString &value);
    void setNextState(const QString &value);

private:
    QChar t;
    QString stackTop;
    QString newStackTop;
    QString nextState;
};

#endif // CONDITION_H
