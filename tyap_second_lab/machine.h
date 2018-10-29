#ifndef MACHINE_H
#define MACHINE_H

#include <QVector>
#include <QString>
#include "QListWidget"
#include "QGroupBox"
#include "QPair"

class Machine : private QObject
{
    Q_OBJECT
public:
    Machine();
    Machine(QVector <QString> *statesNames, QVector <QString> *terminals, QVector <QVector<QString>> *statesValues, int start, const int end);
    QVector <QPair<QString, QChar>> getResult();
    int getError();
    void setChain(const QString &chain);
    void setData(QVector<QString> *statesNames, QVector<QString> *terminals, QVector<QVector<QString> > *statesValues, int start, int end);
    enum Errors{
        isOk,
        EndWasNotReached,
        SymbolDoesNotExistInAlphabet,
        NotInTheFinishState
    };
    Q_ENUM(Errors)

public slots:
    void run();

private:
    QString currentState;
    QString chain;
    int start, end;
    int error = 0;
    QVector <QPair<QString, QChar>> result;
    QVector <QString> *statesNames = nullptr;
    QVector <QString> *terminals = nullptr;
    QVector <QVector<QString>> *statesValues = nullptr;
};

#endif // MACHINE_H
