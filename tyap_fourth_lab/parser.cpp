#include "parser.h"
#include <stdexcept>
#include <QDebug>
#include <any>
#include <algorithm>

#define inputRuleErrorCheck if(i>=singleRule.size()-1)throw\
    new\
    std::runtime_error("Something is wrong with rule number "+QString::number(number).toStdString())

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

void Parser::parseTranslateAlphabet(const QString &translateAlphabet)
{
    auto list = translateAlphabet.split(" ", QString::SkipEmptyParts);
    for (auto str : list){
        if (str.size() != 1){
            throw new std::runtime_error("Something is wrong about your TranslateAlphabet");
        }
        this->translateAlphabet.push_back(str[0]);
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
            throw new std::runtime_error("Something is wrong about your alphabet");
        }
        this->inputAlphabet.push_back(str[0]);
    }
}

void Parser::parseStackAlphabet(const QString &stackAlphabet)
{
    auto list = stackAlphabet.split(" ", QString::SkipEmptyParts);
    for (auto str : list){
        if (str.size() != 1){
            throw new std::runtime_error("Something is wrong about your stack alphabet ");
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
    for (auto &vector : this->map){
        std::sort(vector.begin(), vector.end(),
                  [this](const Condition &a, const Condition &b) {return (b.getT() == this->emptySymbol && a.getT() != this->emptySymbol);});
    }
}

void Parser::parseSingleMachineRule(int number, const QString &singleRule)
{
    QString currentState;
    QString stackTop;
    QString newStackTop;
    QString newState;
    QString addToOutput;
    QChar t;
    int i = 0;


    while (singleRule[i] == ' ') i++;

    if (singleRule[i] != '('){
        throw new std::runtime_error("Something is wrong with rule number " + QString::number(number).toStdString());
    }

    i++;
    inputRuleErrorCheck;
    while (singleRule[i] == ' ')
    {
        inputRuleErrorCheck;
        i++;
    }
    while (singleRule[i] != ',')
    {
        inputRuleErrorCheck;
        currentState += singleRule[i++];
    }
    inputRuleErrorCheck;
    i++;
    while (singleRule[i] == ' ')
    {
        inputRuleErrorCheck;
        i++;
    }
    t = singleRule[i++];
    inputRuleErrorCheck;
    if (singleRule[i++] != ','){
        throw new std::runtime_error("Something is wrong with rule number " + QString::number(number).toStdString());
    }
    while (singleRule[i] == ' ')
    {
        inputRuleErrorCheck;
        i++;
    }
    while ( (singleRule[i] != ' ') && (singleRule[i] != ')') )
    {
        inputRuleErrorCheck;
        stackTop += singleRule[i++];
    }
    while (singleRule[i] != '(')
    {
        inputRuleErrorCheck;
        i++;
    }
    inputRuleErrorCheck;
    i++;
    while (singleRule[i] == ' ')
    {
        inputRuleErrorCheck;
        i++;
    }
    while (singleRule[i] != ',')
    {
        inputRuleErrorCheck;
        newState += singleRule[i++];
    }
    inputRuleErrorCheck;
    i++;
    while (singleRule[i] == ' ')
    {
        inputRuleErrorCheck;
        i++;
    }
    while (singleRule[i] != ',')
    {
        inputRuleErrorCheck;
        newStackTop += singleRule[i++];
    }
    inputRuleErrorCheck;
    i++;
    while (singleRule[i] == ' ')
    {
        inputRuleErrorCheck;
        i++;
    }
    while (singleRule[i] != ')')
    {
        inputRuleErrorCheck;
        addToOutput += singleRule[i++];
    }

    for (auto ch : stackTop)
    {
        if (!stackAlphabet.contains(ch)){
            throw new std::runtime_error("Rule number " + QString::number(number).toStdString() + " contains symbol not from alphabet");
        }
    }
    for (auto ch : addToOutput)
    {
        if (!translateAlphabet.contains(ch) && !(addToOutput.size() == 1 && addToOutput[0] == emptySymbol)){
            throw new std::runtime_error("Rule number " + QString::number(number).toStdString() + " contains symbol not from alphabet");
        }
    }
    for (auto ch : newStackTop)
    {
        if (!stackAlphabet.contains(ch) && !(newStackTop.size() == 1 && newStackTop[0] == emptySymbol)){
            throw new std::runtime_error("Rule number " + QString::number(number).toStdString() + " contains symbol not from alphabet");
        }
    }
    if (!states.contains(newState)){
        throw new std::runtime_error("");
    }
    if (!states.contains(currentState)){
        throw new std::runtime_error("Something is wrong with rule number " + QString::number(number).toStdString());
    }
    if (!inputAlphabet.contains(t) && t != emptySymbol){
        throw new std::runtime_error("Something is wrong with rule number " + QString::number(number).toStdString());
    }
    if (!states.contains(startState)){
        throw new std::runtime_error("Неизвестное начальное состояние");
    }

    if (i > singleRule.size()){
        throw new std::runtime_error("Something is wrong with rule number " + QString::number(number).toStdString());
    }
    if (newStackTop == emptySymbol) newStackTop = "";

    //qDebug() << "currentState " << currentState << " t " << t << " stackTop " << stackTop << " newState " << newState << " newStackTop "    <<newStackTop;

    map[currentState].push_back(Condition(t, stackTop, newStackTop, newState, addToOutput, number));
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

void Parser::parseChain(const QString &value,const int number)
{
    for (auto ch : value){
        if (!inputAlphabet.contains(ch)){
            throw new std::runtime_error("Входная строка " +
                                         QString::number(number).toStdString() +
                                         " содержит символ, который не входит в алфавит");
        }
    }
}

QString Parser::getChain() const
{
    return chain;
}

const QMap<QString, QVector<Condition> > *Parser::getMap() const
{
    return &map;
}

QString Parser::getStartState() const
{
    return startState;
}

void Parser::setStartState(const QString &value)
{
    startState = value;
}

QString Parser::getStack() const
{
    return stack;
}

QChar Parser::getEmptySymbol() const
{
    return emptySymbol;
}
