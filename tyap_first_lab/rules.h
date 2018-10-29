#ifndef RULES_H
#define RULES_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QBoxLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QDebug>
#include <QString>
#include <QRadioButton>
#include <vector>
#include <functional>
#include "mypushbutton.h"

class Rules : public QWidget
{
    Q_OBJECT
public:
    explicit Rules(QWidget *parent = nullptr);
    explicit Rules(int amountOfRules, QWidget *parent = nullptr);
    unsigned int getTargetSymbolIndex();
    QVector <char> getUnterminalVector();
    std::vector<std::pair<char, std::vector<std::string> > > getChainsVector();

public slots:
    void plusButtonSlot(unsigned int index);

private:
    int amountOfRules;

    //QVector <QVector<QString>> rules;
    QVector <QHBoxLayout> layoutOfRule;
/*
    QVector <QLineEdit*> unterminalVector;
    QVector <QLineEdit*> rulesVector;
    QVector <QPushButton*> plusButtonVector;
    QVector <QRadioButton*> radioButtonVector;
*/
    QGridLayout *wholeLayout;

    struct SingleRule
    {
        QLineEdit* unterminal;
        QVector <QLineEdit*> *chainsVector;
        MyPushButton* plusButton;
        QRadioButton* radioButton;
        QGridLayout *singleRuleVLayout;
        QHBoxLayout *singleRuleHLayout;
        QHBoxLayout *chainLayout;
    };

    QVector <SingleRule> rules;

};

#endif // RULES_H
