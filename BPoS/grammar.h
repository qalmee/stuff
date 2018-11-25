#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QBoxLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QDebug>
#include <QRadioButton>

class Grammar:public QWidget
{
    Q_OBJECT
private:
    QLabel *amountOfUnterminalLabel;
    QLabel *amountOfTerminalLabel;
    QLabel *lenthOfChainsLabel;
    QLabel *minLengthLabel;
    QLabel *maxLengthLabel;
    QLabel *startChainLabel, *endChainLabel;
    QLabel *multiAccuranceLabel;

    QLineEdit *amountOfUnterminalLine;
    QLineEdit *amountOfTerminalLine;
    QLineEdit *minLengthLine;
    QLineEdit *maxLengthLine;
    QLineEdit *startChain, *endChain;
    QLineEdit *multiAccuranceSymbol, *multiplicity;


    QRadioButton *lp, *rp;

    QVBoxLayout *verticalLayout;
    QHBoxLayout *horFromToLengthLayout, *lpOrRpGrammar;
    QGridLayout *grid;

public:
    explicit Grammar(QWidget *parent = nullptr);
    int getAmountOfUnterminal();
    //int getAmountOfTerminal();
    int getMinLength();
    int getMaxLength();
    bool isLpGrammar() const;
    QString getStartChain() const;
    QString getEndChain() const;
    QPair<QString, int> getMSymbol() const;
    void setMultiplicity(const QString &s);
};

#endif // GRAMMAR_H
