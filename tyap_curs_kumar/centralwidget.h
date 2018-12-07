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
    QString getStartChain() const;
    QString getEndChain() const;
    QChar getSymbolM() const;
    int getMultiplicity() const;

    QPushButton * getGenerateRegExpButton() const;
    QPushButton * getGenerateChainsButton() const;

    QString getRegExp() const;
    void setRegExp(const QString &value);

    void setMultiplicity(int value);

signals:

public slots:

private:
    QPushButton *generateRegExp, *generateChains;
    QLineEdit *startChain, *endChain, *alphabet, *multiplicity, *symbolM, *regExp;
    QTextEdit *chains;

    QGridLayout *mainLayout;

};

#endif // CENTRALWIDGET_H
