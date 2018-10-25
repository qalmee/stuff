#include "rules.h"

Rules::Rules(QWidget *parent) : QWidget(parent)
{

}

Rules::Rules(int amountOfRules, QWidget *parent) : QWidget (parent)
{
    wholeLayout = new QVBoxLayout;
    for (int i = 0; i < amountOfRules; ++i)
    {
        unterminalVector.push_back(new QLineEdit());
        rulesVector.push_back(new QLineEdit());
        plusButtonVector.push_back(new QPushButton("+"));
        radioButtonVector.push_back(new QRadioButton("Целевой символ"));

        singleRuleHLayout = new QHBoxLayout;
        singleRuleVLayout = new QVBoxLayout;

        singleRuleVLayout->addWidget(radioButtonVector[i]);
        singleRuleHLayout->addWidget(unterminalVector[i]);
        singleRuleHLayout->addWidget(rulesVector[i]);
        singleRuleHLayout->addWidget(plusButtonVector[i]);
        singleRuleVLayout->addLayout(singleRuleHLayout);
        wholeLayout->addLayout(singleRuleVLayout);

    }
    setLayout(wholeLayout);
}
