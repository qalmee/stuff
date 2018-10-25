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

class Grammar:public QWidget
{
    Q_OBJECT
private:
    QLabel *amountOfUnterminalLabel;
    QLabel *amountOfTerminalLabel;
    QLabel *lenthOfChainsLabel;
    QLabel *minLengthLabel;
    QLabel *maxLengthLabel;

    QLineEdit *amountOfUnterminalLine;
    QLineEdit *amountOfTerminalLine;
    QLineEdit *minLengthLine;
    QLineEdit *maxLengthLine;

public:
    explicit Grammar(QWidget *parent = nullptr);
    int getAmountOfUnterminal();
    int getAmountOfTerminal();
    int getMinLength();
    int getMaxLength();
};

#endif // GRAMMAR_H
