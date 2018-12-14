#ifndef CHAINSGENERATOR_H
#define CHAINSGENERATOR_H

#include <QString>
#include <QVector>
#include <QSet>
#include <QMutex>
#include <QThread>

class ChainsGenerator : public QThread
{
    Q_OBJECT

public:

    ChainsGenerator();
    ChainsGenerator(const int maxLen, const int minLen, const QString &s);
    ~ChainsGenerator() override;
    void calculate ();
    void run() override;


    int getMaxLength() const;
    void setMaxLength(int value);

    QSet<QString>* getAns() const;
    void setAns(QSet<QString> *value);

    QString getError() const;

    bool timeToStop = false;

private:
    inline void process_op (QVector<QSet<QString>> & st, QChar op);
    inline void process_op1 (QVector<int> & st, QChar op);
    constexpr int priority (QChar op);
    constexpr bool is_op (QChar c);
    inline int bfs(const QSet<QString> &s1, QSet<QString> &res);
    inline void notStarredPartsLength(const QString &s);
    int maxLength, minLength, notStarredPartsLen;
    QSet<QString> *ans;
    QString regExp;
    QString error;
    bool isErr;

signals:
    void resultReady(QSet<QString> *ans, bool err, QString errorText);

};

#endif // CHAINSGENERATOR_H
