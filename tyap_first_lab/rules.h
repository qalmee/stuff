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

class Rules : public QWidget
{
    Q_OBJECT
public:
    explicit Rules(QWidget *parent = nullptr);
    explicit Rules(int amountOfRules, QWidget *parent = nullptr);

private:
    int amountOfRules;

    //QVector <QVector<QString>> rules;
    QVector <QHBoxLayout> layoutOfRule;

    QVector <QLineEdit*> unterminalVector;
    QVector <QLineEdit*> rulesVector;
    QVector <QPushButton*> plusButtonVector;
    QVector <QRadioButton*> radioButtonVector;

    QVBoxLayout *wholeLayout;
    QHBoxLayout *singleRuleHLayout;
    QVBoxLayout *singleRuleVLayout;


};

#endif // RULES_H
