#include "chainsgenerator.h"
#include <QSet>

ChainsGenerator::ChainsGenerator()
{

}

bool ChainsGenerator::is_op (QChar c) {
    return c=='+' || c=='-' || c=='*' || c=='/' || c=='%';
}

int ChainsGenerator::priority (QChar op) {
    return
        op == '+' ? 1 :
        op == '&' ? 2 :
        op == '*' ? 3 :
        -1;
}

void ChainsGenerator::process_op (QVector<int> & st, QChar op) {
    int r = st.back();  st.pop_back();
    int l = st.back();  st.pop_back();
    if (op == '+'){

    } else if (op == '&'){

    } else if (op == '*'){

    }
}

int ChainsGenerator::calculate (QString & s) {
    QVector<int> st;
    QVector<QVector<QString>> operandStack;
    QVector<QChar> operatorStack;
    for (int i=0; i<s.length(); ++i)
        if (s[i] != ' ')
            if (s[i] == '('){
                operatorStack.push_back ('(');
            }
            else if (s[i] == ')') {
                while (operatorStack.back() != '('){
                    process_op (st, operatorStack.back());  operatorStack.pop_back();
                }
                operatorStack.pop_back();
            }
            else if (is_op (s[i])) {
                QChar curop = s[i];
                while (!operatorStack.empty() && priority(operatorStack.back()) >= priority(s[i])){
                    process_op (st, operatorStack.back());  operatorStack.pop_back();
                }
                operatorStack.push_back (curop);
            }
            else {

            }
    while (!operatorStack.empty()){
        process_op (st, operatorStack.back());  operatorStack.pop_back();
    }
    return st.back();
}
