#include "parser.h"
#include <stdexcept>
#include <QDebug>
#include <any>

Parser::Parser()
{

}

void Parser::parseStates(const QString &states)
{
    auto list = states.split(" ", QString::SkipEmptyParts);
    for (auto str : list){
        this->states.push_back(str);
    }
}

void Parser::parseFinishStates(const QString &finishStates)
{
    auto list = finishStates.split(" ", QString::SkipEmptyParts);
    for (auto str : list){
        this->finishStates.push_back(str);
    }
}

void Parser::parseInputAlphabet(const QString &inputAlphabet)
{
    auto list = inputAlphabet.split(" ", QString::SkipEmptyParts);
    for (auto str : list){
        if (str.size() != 1){
            throw new std::runtime_error("Something wrong about your alphabet");
        }
        this->inputAlphabet.push_back(str[0]);
    }
}

void Parser::parseStackAlphabet(const QString &stackAlphabet)
{
    auto list = stackAlphabet.split(" ", QString::SkipEmptyParts);
    for (auto str : list){
        if (str.size() != 1){
            throw new std::runtime_error("Something wrong about your stack alphabet");
        }
        this->stackAlphabet.push_back(str[0]);
    }

}

void Parser::parseMachineRules(const QString &machineRules)
{
    int i = 1;
    for (auto str : machineRules.split("\n", QString::SkipEmptyParts))
    {
        parseSingleMachineRule(i++, str);
    }
}

void Parser::parseSingleMachineRule(int number, const QString &singleRule)
{
    QString currentState;
    QString stackTop;
    QString newStackTop;
    QString newState;
    QChar t;
    int i = 0;

    while (singleRule[i] == ' ') i++;
    if (singleRule[i] != '('){
        throw new std::runtime_error("Something wrong with rule number" + QString::number(number).toStdString());
    }
    i++;
    while (singleRule[i] == ' ') i++;
    while (singleRule[i] != ',')
    {
        currentState += singleRule[i++];
    }
    i++;
    while (singleRule[i] == ' ') i++;
    t = singleRule[i++];
    if (singleRule[i++] != ','){
        throw new std::runtime_error("Something wrong with rule number" + QString::number(number).toStdString());
    }
    while (singleRule[i] == ' ') i++;
    while ( (singleRule[i] != ' ') && (singleRule[i] != ')') )
    {
        stackTop += singleRule[i++];
    }
    while (singleRule[i] != '(') i++;
    i++;
    while (singleRule[i] == ' ') i++;
    while (singleRule[i] != ',')
    {
        newState += singleRule[i++];
    }
    i++;
    while (singleRule[i] == ' ') i++;
    while (singleRule[i] != ')')
    {
        newStackTop += singleRule[i++];
    }
    if (i > singleRule.size()){
        throw new std::runtime_error("Something wrong with rule number" + QString::number(number).toStdString());
    }
    if (newStackTop == emptySymbol) newStackTop = "";

    qDebug() << "currentState " << currentState << " t " << t << " stackTop " << stackTop << " newState " << newState << " newStackTop "    <<newStackTop;

    Condition temp(t, stackTop, newState, newStackTop);
    map[currentState].push_back(temp);
}

const QVector<QString> *Parser::getStates() const
{
    return &this->states;
}

const QVector<QString> *Parser::getFinishStates() const
{
    return &this->finishStates;
}

const QVector<QChar> *Parser::getInputAlphabet() const
{
    return &this->inputAlphabet;
}

const QVector<QChar> *Parser::getStackAlphabet() const
{
    return &this->stackAlphabet;
}

void Parser::setEmptySymbol(const QChar &value)
{
    emptySymbol = value;
}

void Parser::setStack(const QString &value)
{
    stack = value;
}

QString Parser::getChain() const
{
    return chain;
}

void Parser::setChain(const QString &value)
{
    chain = value;
}

QString Parser::getStack() const
{
    return stack;
}

QChar Parser::getEmptySymbol() const
{
    return emptySymbol;
}
