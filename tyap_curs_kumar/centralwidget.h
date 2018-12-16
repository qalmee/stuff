#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = nullptr);
    QVector <QChar> getAlphabet() const;
    QString getAlphabetString() const;
    QString getStartChain() const;
    QString getEndChain() const;
    QChar getSymbolM() const;
    int getMultiplicity() const;

    QPushButton * getGenerateRegExpButton() const;
    QPushButton * getGenerateChainsButton() const;

    QString getRegExp() const;
    void setRegExp(const QString &value);


    int getMaxLen() const;
    void setMaxLen(int value);
    int getMinLen() const;
    void setMinLen(int value);

    void setStartChain(const QString &value);
    void setEndChain(const QString &value);
    void setAlphabet(const QString &value);
    void setMultiplicity(const int value);
    void setSymbolM(const QString &value);

    QString getChains() const;

signals:

public slots:
    void setChains(const QSet<QString> *s);
    void setGenerateButtonActive();
    void setGenerateButtonDisabled();

private:
    QPushButton *generateRegExp, *generateChains;
    QLineEdit *startChain, *endChain, *alphabet, *multiplicity, *symbolM, *regExp, *minLen, *maxLen;
    QTextEdit *chains;

    QGridLayout *mainLayout;

};

#endif // CENTRALWIDGET_H
