#ifndef REGEXPGENERATOR_H
#define REGEXPGENERATOR_H

#include <QString>
#include <QVector>

class RegExpGenerator
{
public:
    RegExpGenerator();
    RegExpGenerator(QVector<QChar> alph, QString start, QString end, const QChar &symbol, const int mul);
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
    static QString calculateRegExpForRPN(const QString &s);
    void calculateRegExpForRPN();

private:

    int symbolCount(const QString &s, const QChar &ch) const;
    QString generateAnyString();
    QString generateAnyStringWithoutRestrictions() const;
    QVector <QString> final() const;
    constexpr static bool isOperand(const QChar &ch);

    QVector <QChar> alphabet;
    QString startChain, endChain, regExp, regExpForRPN, anyString;
    QChar symbol;
    int mul;
};

#endif // REGEXPGENERATOR_H
