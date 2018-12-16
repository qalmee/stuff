#ifndef CHAINSGENERATOR_H
#define CHAINSGENERATOR_H

#include <QString>
#include <QVector>
#include <QSet>
#include <QThread>
#include <vector>
#include <string>
#include <set>
#include <unordered_set>

using namespace std;

class ChainsGenerator : public QThread
{
    Q_OBJECT

public:

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
    inline void process_op (vector<unordered_set<string>> & st, char op);
    inline void process_op1 (vector<int> & st, char op);
    constexpr int priority (char op);
    constexpr bool is_op (char c);
    inline int bfs(const unordered_set<string> &s1, unordered_set<string> &res);
    inline void notStarredPartsLength(const string &s);
    int maxLength, minLength, notStarredPartsLen;
    QSet<QString> *ans;
    string regExp;
    QString error;
    bool isErr;

signals:
    void resultReady(QSet<QString> *ans, bool err, QString errorText);

};

#endif // CHAINSGENERATOR_H
