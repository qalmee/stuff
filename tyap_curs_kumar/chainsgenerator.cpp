#include "chainsgenerator.h"
#include <QSet>
#include <exception>
#include <QQueue>
#include <QStack>
#include <QtMath>
#include <QDebug>
#include <algorithm>
#include <queue>

ChainsGenerator::ChainsGenerator() : ans(new QSet<QString>()), isErr(false)
{
    maxLength = 0;
}

ChainsGenerator::ChainsGenerator(const int maxLen, const int minLen, const QString &s) :
    maxLength(maxLen), minLength(minLen), ans(new QSet<QString>()), isErr(false)
{
    regExp = s;
    if (maxLength < 0) maxLength = 0;
    if (minLength < 0) minLength = 0;
}

ChainsGenerator::~ChainsGenerator()
{
    delete this->ans;
}

constexpr bool ChainsGenerator::is_op (QChar c) {
    return c=='*' || c=='+' || c=='&' || c == ')' || c == '(';
}

int ChainsGenerator::bfs(const QSet<QString> &s1, QSet<QString> &res)
{
    int count = 0;
    int maxLenForBFS = maxLength - notStarredPartsLen;
    std::queue<QString> q;
    res.clear();
    res.reserve(100000);

    for (const auto &str : s1){
        if (str.size() != 0 && str.size() <= maxLenForBFS){
            q.push(str);
            res.insert(str);
        }
    }
    while (!q.empty()){
        if (count > 15000000) return 1;
        auto t = q.front();
        q.pop();
        for (auto str : s1){
            count++;
            if (str.size() == 0) continue;
            str = t + str;
            if (str.size() <= maxLenForBFS && !res.contains(str)){
                q.push(str);
                res.insert(str);
            }
        }
    }
    res.insert("");
    return 0;
}

void ChainsGenerator::notStarredPartsLength(const QString &s)
{
    QVector <int> lenStack;
    QVector <QChar> operatorStack;
    for (int i=0; i<s.length(); ++i){
        if (s[i] != ' ')
            if (s[i] == '('){
                operatorStack.push_back ('(');
            }
            else if (s[i] == ')') {
                if (operatorStack.isEmpty()){
                    throw new std::runtime_error("Стэк операторов неожиданно пуст.\nКод ошибки 2.");
                }
                while (operatorStack.back() != '('){
                    process_op1 (lenStack, operatorStack.back());
                    operatorStack.pop_back();
                    if (operatorStack.isEmpty()){
                        throw new std::runtime_error("Стэк операторов неожиданно пуст.\nКод ошибки 2.");
                    }
                }
                operatorStack.pop_back();
            }
            else if (is_op (s[i])) {
                QChar curop = s[i];
                while (!operatorStack.empty() && priority(operatorStack.back()) >= priority(s[i])){
                    process_op1 (lenStack, operatorStack.back());
                    operatorStack.pop_back();
                }
                operatorStack.push_back (curop);
            }
            else {
                int length = 0;
                while (i < s.length() && !is_op(s[i])){
                    i++;
                    length++;
                }
                i--;
                lenStack.push_back(length);
            }
    }

    while (!operatorStack.empty()){
        if (lenStack.isEmpty()){
            throw new std::runtime_error("Стэк операндов неожиданно пуст.\nКод ошибки 1");
        }
        process_op1 (lenStack, operatorStack.back());  operatorStack.pop_back();
    }
    if (lenStack.isEmpty()){
        throw new std::runtime_error("Стэк операндов неожиданно пуст.\nКод ошибки 1");
    }
    qDebug() << lenStack[0];
    notStarredPartsLen = lenStack[0];

}

QString ChainsGenerator::getError() const
{
    return error;
}

constexpr int ChainsGenerator::priority (QChar op) {
    return
            op == '+' ? 1 :
                        op == '&' ? 2 :
                                    op == '*' ? 3 :
                                                -1;
}

void ChainsGenerator::process_op (QVector<QSet<QString>> & st, QChar op) {
    if (op == ')' || op == '(') return;
    if (timeToStop) return;
    auto s = st.back();
    st.pop_back();

    if (op == '+'){
        auto s1 = st.back();
        st.pop_back();
        s += s1;
        st.push_back(s);
    } else if (op == '&'){
        auto s1 = st.back();
        st.pop_back();
        QSet<QString> newSet;
        newSet.reserve(s.size() * s1.size() * 2);
        for (const auto &str : s1){
            for (const auto &str1 : s){
                if (str.size() + str1.size() <= maxLength) newSet.insert(str + str1);
            }
        }
        st.push_back(newSet);
    } else if (op == '*'){
        QSet<QString> newSet;
        if (bfs(s, newSet) != 0) timeToStop = true;
        st.push_back(newSet);
    }
}

void ChainsGenerator::process_op1(QVector<int> &st, QChar op)
{
    if (st.empty()){
        throw new std::runtime_error("Стэк операндов неожиданно пуст");
    }
    if (op == ')' || op == '(') return;
    auto n = st.back();
    st.pop_back();

    if (op == '+'){
        if (st.empty()){
            throw new std::runtime_error("Стэк операндов неожиданно пуст");
        }
        auto n1 = st.back();
        st.pop_back();
        st.push_back(std::min(n, n1));
    } else if (op == '&'){
        if (st.empty()){
            throw new std::runtime_error("Стэк операндов неожиданно пуст");
        }
        auto n1 = st.back();
        st.pop_back();
        st.push_back(n + n1);
    } else if (op == '*'){
        st.push_back(0);
    }

}

void ChainsGenerator::calculate() {
    QVector<QSet<QString>> operandStack;
    QVector<QChar> operatorStack;
    QString s = regExp;
    for (int i=0; i<s.length(); ++i){
        if (timeToStop) return;
        if (s[i] != ' ')
            if (s[i] == '('){
                operatorStack.push_back ('(');
            }
            else if (s[i] == ')') {
                while (operatorStack.back() != '('){
                    process_op (operandStack, operatorStack.back());
                    operatorStack.pop_back();
                }
                operatorStack.pop_back();
            }
            else if (is_op (s[i])) {
                QChar curop = s[i];
                while (!operatorStack.empty() && priority(operatorStack.back()) >= priority(s[i])){
                    process_op (operandStack, operatorStack.back());
                    operatorStack.pop_back();
                }
                operatorStack.push_back (curop);
            }
            else {
                QString str;
                while (i < s.length() && !is_op(s[i])){
                    str.push_back(s[i++]);
                }
                i--;
                QSet<QString> tmp;
                tmp.insert(str);
                operandStack.push_back(tmp);
            }
    }

    while (!operatorStack.empty()){
        if (operandStack.isEmpty()){
            throw new std::runtime_error("Стэк операндов неожиданно опустел");
        }
        process_op (operandStack, operatorStack.back());  operatorStack.pop_back();
    }
    ans->reserve(operandStack[0].size() << 1);
    for (auto str : operandStack[0]){
        if (str.size() >= minLength) ans->insert(str);
    }
}

void ChainsGenerator::run()
{
    try{
        notStarredPartsLength(regExp);
    }catch(std::runtime_error *err){
        emit resultReady(ans, true, err->what());
        return;
    }catch(void*){
        emit resultReady(ans, true, "Полный ойойой");
        return;
    }
    calculate();
    if (timeToStop){
        emit resultReady(ans, true, "Превышенно время ожидания");
    }
    emit resultReady(ans, false, "ok");
}

int ChainsGenerator::getMaxLength() const
{
    return maxLength;
}

void ChainsGenerator::setMaxLength(int value)
{
    maxLength = value;
}

QSet<QString>* ChainsGenerator::getAns() const
{
    return ans;
}

void ChainsGenerator::setAns(QSet<QString> *value)
{
    ans = value;
}
