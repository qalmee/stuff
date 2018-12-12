#ifndef CONDITION_H
#define CONDITION_H

#include <QString>

class Condition
{
public:
    Condition();
    Condition(QChar t, const QString &stackTop,
              const QString &newStackTop,
              const QString &nextState,
              const QString &addToOutput,
              const int number);
    QChar getT() const;
    QString getNextState() const;
    QString getStackTop() const;
    QString getNewStackTop() const;

    void setT(const QChar &value);
    void setStackTop(const QString &value);
    void setNewStackTop(const QString &value);
    void setNextState(const QString &value);

    int getNumber() const;
    void setNumber(int value);
    Condition &operator= (const Condition &other);

    QString getAddToOutput() const;
    void setAddToOutput(const QString &value);

private:
    QChar t;
    QString stackTop;
    QString newStackTop;
    QString nextState;
    QString addToOutput;
    int number;
};

#endif // CONDITION_H
