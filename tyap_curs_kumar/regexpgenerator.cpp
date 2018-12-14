#include "regexpgenerator.h"
#include <QDebug>
#include <algorithm>

RegExpGenerator::RegExpGenerator()
{

}

RegExpGenerator::RegExpGenerator(const QVector<QChar> &alph, const QString &start, const QString &end, const QChar &symbol, const int mul) :
    alphabet(alph), startChain(start), endChain(end), symbol(symbol), mul(mul)
{

}

QString RegExpGenerator::generate()
{
    generateAnyString();
    QString regExp, secondary, primary;
    int secondaryPart = (mul - (symbolCount(startChain, symbol) + symbolCount(endChain, symbol)) % mul) % mul;
    for (int i = 0; i<secondaryPart; i++){
        secondary += anyString + "*" + QString(1, symbol);
    }
    if (secondaryPart){
        secondary += anyString + "*";
        secondary = "(" + secondary + ")";
    }
    if (mul != 1){
        for (int i = 0; i<mul; i++){
            primary += anyString + "*" + QString(1, symbol);
        }
        primary += anyString + "*";
        primary = "(" + primary + ")*";
    }else{
        primary = generateAnyStringWithoutRestrictions() + "*";
    }
    regExp = startChain + secondary + primary + endChain;
    for (auto str : final()){
        regExp += "+" + str;
    }
    this->regExp = regExp;
    calculateRegExpForRPN();
    return regExp;
}

int RegExpGenerator::symbolCount(const QString &s, const QChar &ch) const
{
    int m = 0;
    for (auto i : s){
        m += (i == ch);
    }
    return m;
}

QString RegExpGenerator::generateAnyString()
{
    QString str = "(";
    for (int i = 0; i<alphabet.size(); i++){
        auto ch = alphabet[i];
        if (ch != symbol){
            str += QString(1, ch);
            str += "+";
        }
    }
    if (str.size() > 1) str.chop(1);
    str += ")";
    this->anyString = str;
    return str;
}

QString RegExpGenerator::generateAnyStringWithoutRestrictions() const {
    QString str = "(";
    for (int i = 0; i<alphabet.size(); i++){
        auto ch = alphabet[i];
        str += QString(1, ch);
        if (i != static_cast<int>(alphabet.size()) - 1) str += "+";
    }
    str += ")";
    return str;
}

QVector<QString> RegExpGenerator::final() const
{
    QVector <QString> v;
    int minLen = std::min(startChain.size(), endChain.size());
    for (int i = 1; i<=minLen; i++){
        if (startChain.right(i) == endChain.left(i) && symbolCount(startChain + endChain.right(endChain.size() - i), symbol) % mul == 0){
            v.push_back(startChain + endChain.right(endChain.size() - i));
        }
    }
    return v;
}

constexpr bool RegExpGenerator::isOperand(const QChar &ch)
{
    return (ch != '(' && ch != ')' && ch != '+' && ch != '*');
}

void RegExpGenerator::setRegExp(const QString &value)
{
    regExp = value;
}

QString RegExpGenerator::getRegExpForRPN() const
{
    return regExpForRPN;
}

void RegExpGenerator::calculateRegExpForRPN()
{
    regExpForRPN = RegExpGenerator::calculateRegExpForRPN(regExp);
    qDebug() << regExpForRPN;
}

QString RegExpGenerator::calculateRegExpForRPN(const QString &s)
{
    QString re = s;
    for (int i =0; i<re.size(); i++){
        if (re[i] == ' ') re.remove(i--, 1);
    }
    for (int i = 1; i<re.size(); i++){
        if ((re[i - 1] != '(' && re[i - 1] != '+' && isOperand(re[i])) ||
            (re[i - 1] != '+' && re[i - 1] != '(' && re[i] == '(')){
            re.insert(i, '&');
            i++;
        }
    }
    qDebug() << re;
    return re;
}

QString RegExpGenerator::getStartChain() const
{
    return startChain;
}

void RegExpGenerator::setStartChain(const QString &value)
{
    startChain = value;
}

QString RegExpGenerator::getEndChain() const
{
    return endChain;
}

void RegExpGenerator::setEndChain(const QString &value)
{
    endChain = value;
}

QChar RegExpGenerator::getSymbol() const
{
    return symbol;
}

void RegExpGenerator::setSymbol(const QChar &value)
{
    symbol = value;
}

int RegExpGenerator::getMul() const
{
    return mul;
}

void RegExpGenerator::setMul(int value)
{
    mul = value;
}

QString RegExpGenerator::getRegExp() const
{
    return regExp;
}


