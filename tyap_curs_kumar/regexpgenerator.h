#ifndef REGEXPGENERATOR_H
#define REGEXPGENERATOR_H

#include <QString>
#include <QVector>

class RegExpGenerator
{
public:
    RegExpGenerator();
    RegExpGenerator(const QVector<QChar> &alph, const QString &start, const QString &end, const QChar &symbol, const int mul);
    QString generate();

    QString getStartChain() const;
    void setStartChain(const QString &value);

    QString getEndChain() const;
    void setEndChain(const QString &value);

    QChar getSymbol() const;
    void setSymbol(const QChar &value);

    int getMul() const;
    void setMul(int value);

    QString getRegExp() const;
    void setRegExp(const QString &value);
    QString getRegExpForRPN() const;
    void calculateRegExpForRPN();

private:

    int symbolCount(const QString &s, const QChar &ch) const;
    QString generateAnyString();
    QString generateAnyStringWithoutRestrictions() const;
    QVector <QString> final() const;
    bool isOperand(const QChar &ch) const;

    QVector <QChar> alphabet;
    QString startChain, endChain, regExp, regExpForRPN, anyString;
    QChar symbol;
    int mul;
};

#endif // REGEXPGENERATOR_H
