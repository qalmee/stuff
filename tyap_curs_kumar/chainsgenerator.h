#ifndef CHAINSGENERATOR_H
#define CHAINSGENERATOR_H

#include <QString>
#include <QVector>

class ChainsGenerator
{
public:
    ChainsGenerator();
    int calculate (QString & s);
    void process_op (QVector<int> & st, QChar op);
    int priority (QChar op);
    bool is_op (QChar c);
};

#endif // CHAINSGENERATOR_H
