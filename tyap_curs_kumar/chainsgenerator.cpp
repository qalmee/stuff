#include "chainsgenerator.h"
#include <QSet>
#include <exception>
#include <QQueue>
#include <QStack>
#include <QtMath>
#include <QDebug>
#include <algorithm>
#include <queue>

ChainsGenerator::ChainsGenerator(const int maxLen, const int minLen, const QString &s) :
    maxLength(maxLen), minLength(minLen), ans(new QSet<QString>()), isErr(false)
{
    regExp = s.toStdString();
    if (maxLength < 0) maxLength = 0;
    if (minLength < 0) minLength = 0;
    notStarredPartsLen = 0;
    count = 0 ;
}

ChainsGenerator::~ChainsGenerator()
{
    delete this->ans;
}

constexpr bool ChainsGenerator::is_op (char c) {
    return c=='*' || c=='+' || c=='&' || c == ')' || c == '(';
}

int ChainsGenerator::bfs(const unordered_set<string> &s1, unordered_set<string> &res)
{
    int maxLenForBFS = maxLength - notStarredPartsLen;
    std::queue<string> q;
    res.clear();
    res.reserve(100000);

    for (const auto &str : s1){
        if (!str.empty() && static_cast<int>(str.size()) <= maxLenForBFS){
            q.push(str);
            res.insert(str);
        }
    }
    while (!q.empty()){
        if (count > MAX_COUNT) return 1;
        auto t = q.front();
        q.pop();
        for (auto str : s1){
            count++;
            if (str.empty()) continue;
            str += t;
            if (static_cast<int>(str.size()) <= maxLenForBFS && res.count(str) == 0){
                q.push(str);
                res.insert(str);
            }
        }
    }
    res.insert("");
    return 0;
}

void ChainsGenerator::notStarredPartsLength(const string &s)
{
    vector <int> lenStack;
    vector <char> operatorStack;
    for (size_t i=0; i<s.length(); ++i){
        if (s[i] != ' ')
            if (s[i] == '('){
                operatorStack.push_back ('(');
            }
            else if (s[i] == ')') {
                if (operatorStack.empty()){
                    throw new std::runtime_error("Стэк операторов неожиданно пуст.\nКод ошибки 2.");
                }
                while (operatorStack.back() != '('){
                    process_op1 (lenStack, operatorStack.back());
                    operatorStack.pop_back();
                    if (operatorStack.empty()){
                        throw new std::runtime_error("Стэк операторов неожиданно пуст.\nКод ошибки 2.");
                    }
                }
                operatorStack.pop_back();
            }
            else if (is_op (s[i])) {
                char curop = s[i];
                while (!operatorStack.empty() && priority(operatorStack.back()) >= priority(s[i])){
                    process_op1 (lenStack, operatorStack.back());
                    operatorStack.pop_back();
                }
                operatorStack.push_back(curop);
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
        if (lenStack.empty()){
            throw new std::runtime_error("Стэк операндов неожиданно пуст.\nКод ошибки 1");
        }
        process_op1 (lenStack, operatorStack.back());  operatorStack.pop_back();
    }
    if (lenStack.empty()){
        throw new std::runtime_error("Стэк операндов неожиданно пуст.\nКод ошибки 1");
    }
    qDebug() << lenStack[0];
    notStarredPartsLen = lenStack[0];

}

int ChainsGenerator::numberOfDIgits(size_t a)
{
    int c = 0;
    while (a > 0){
        c++;
        a/=10;
    }
    return c;
}

QString ChainsGenerator::getError() const
{
    return error;
}

constexpr int ChainsGenerator::priority (char op) {
    return
            op == '+' ? 1 :
                        op == '&' ? 2 :
                                    op == '*' ? 3 :
                                                -1;
}

void ChainsGenerator::process_op (vector<unordered_set<string>> & st, char op) {
    if (op == ')' || op == '(') return;
    if (timeToStop) return;
    auto s = st.back();
    st.pop_back();
    qDebug()<<op;

    if (op == '+'){
        auto s1 = st.back();
        st.pop_back();
        unordered_set<string> s2;
        s2 = s1;
        s2.reserve((s2.size() + s1.size()) << 1);
        for (const auto &str : s){
            s2.insert(str);
        }
        st.push_back(s2);
    } else if (op == '&'){
        auto s1 = st.back();
        st.pop_back();
        unordered_set<string> newSet;
        //qDebug() << numberOfDIgits(s.size()) << " " << numberOfDIgits(s1.size());
        if (numberOfDIgits(s.size()) + numberOfDIgits(s1.size()) > 8 || s.size() * s1.size() > 100000000){
            timeToStop = 2;
            return;
        }
        newSet.reserve(s.size() * s1.size() * 2);
        count += s.size() * s1.size();
        if (count > MAX_COUNT) {
            timeToStop = 1;
            return;
        }
        for (const auto &str : s1){
            for (const auto &str1 : s){
                if (static_cast<int>(str.size() + str1.size()) <= maxLength) newSet.insert(str + str1);
            }
        }
        st.push_back(newSet);
    } else if (op == '*'){
        unordered_set<string> newSet;
        if (bfs(s, newSet) != 0) timeToStop = 1;
        st.push_back(newSet);
    }
    //qDebug() << count;
}

void ChainsGenerator::process_op1(vector<int> &st, char op)
{
    if (st.empty()){
        throw new std::runtime_error("Стэк операндов неожиданно пуст.\nКод ошибки 3.");
    }
    if (op == ')' || op == '(') return;
    auto n = st.back();
    st.pop_back();

    if (op == '+'){
        if (st.empty()){
            throw new std::runtime_error("Стэк операндов неожиданно пуст.\nКод ошибки 3.");
        }
        auto n1 = st.back();
        st.pop_back();
        st.push_back(std::min(n, n1));
    } else if (op == '&'){
        if (st.empty()){
            throw new std::runtime_error("Стэк операндов неожиданно пуст.\nКод ошибки 3.");
        }
        auto n1 = st.back();
        st.pop_back();
        st.push_back(n + n1);
    } else if (op == '*'){
        st.push_back(0);
    }

}

void ChainsGenerator::calculate() {
    vector<unordered_set<string>> operandStack;
    vector<char> operatorStack;
    string s = regExp;
    for (size_t i=0; i<s.length(); ++i){
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
                char curop = s[i];
                while (!operatorStack.empty() && priority(operatorStack.back()) >= priority(s[i])){
                    process_op (operandStack, operatorStack.back());
                    operatorStack.pop_back();
                }
                operatorStack.push_back (curop);
            }
            else {
                string str;
                while (i < s.length() && !is_op(s[i])){
                    str.push_back(s[i++]);
                }
                i--;
                unordered_set<string> tmp;
                tmp.insert(str);
                operandStack.push_back(tmp);
            }
    }

    while (!operatorStack.empty()){
        if (operandStack.empty()){
            throw new std::runtime_error("Стэк операндов неожиданно опустел\n.Код ошибки 4.");
        }
        process_op (operandStack, operatorStack.back());  operatorStack.pop_back();
    }
    ans->reserve(static_cast<int>(operandStack[0].size()) << 1);
    for (const auto &str : operandStack[0]){
        if (static_cast<int>(str.size()) >= minLength) ans->insert(QString::fromStdString(str));
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
        emit resultReady(ans, true, "Полный ойойой.");
        return;
    }
    calculate();
    if (timeToStop == 1){
        emit resultReady(ans, true, "Превышенно время ожидания.");
        return;
    }
    else if (timeToStop == 2){
        emit resultReady(ans, true, "Ожидаемое время расчетов слишком велико.\nПопробуйте уменьшить границы генерации цепочек.");
        return;
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
