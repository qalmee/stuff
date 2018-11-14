#ifndef PARSER_H
#define PARSER_H

#include <QVector>
#include <QString>
#include <QSet>

class Parser
{
public:
    Parser();
    void parseStates(const QString &states);
    void parseFinishStates(const QString &finishStates);
    void parseInputAlphabet(const QString &inputAlphabet);
    void parseStackAlphabet(const QString &stackAlphabet);
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

private:
    QVector <QString> states;
    QVector <QString> finishStates;
    QVector <QChar> inputAlphabet;
    QVector <QChar> stackAlphabet;
    QString chain;
    QString stack;
    QChar emptySymbol;

};

#endif // PARSER_H
