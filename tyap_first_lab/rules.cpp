#include "rules.h"
#include <QDebug>

Rules::Rules(QWidget *parent) : QWidget(parent)
{

}

Rules::Rules(int amountOfRules, QWidget *parent) : QWidget (parent)
{
    wholeLayout = new QVBoxLayout;
    for (int i = 0; i < amountOfRules; ++i)
    {
        rules.push_back({new QLineEdit(), new QVector<QLineEdit*>(1, new QLineEdit()),
                         new MyPushButton("+", i), new QRadioButton("Целевой символ"),
                        new QVBoxLayout(), new QHBoxLayout(), new QHBoxLayout()});


        rules[i].singleRuleVLayout->addWidget(rules[i].radioButton);
        rules[i].chainLayout->addWidget(rules[i].unterminal);
        rules[i].chainLayout->addWidget(rules[i].chainsVector->at(0));
        rules[i].singleRuleHLayout->addLayout(rules[i].chainLayout);
        rules[i].singleRuleHLayout->addWidget(rules[i].plusButton);
        connect(rules[i].plusButton, &MyPushButton::clicked, this, &Rules::plusButtonSlot);
        rules[i].singleRuleVLayout->addLayout(rules[i].singleRuleHLayout);
        wholeLayout->addLayout(rules[i].singleRuleVLayout);
    }
    setLayout(wholeLayout);
}

int Rules::getTargetSymbolIndex()
{
    for (int i = 0; i < rules.size(); ++i)
    {
        if(rules[i].radioButton->isChecked())
            return i;
    }
}

//std::vector<std::pair<char, std::vector<std::string> > >& Rules::getChainsVector()
//{
//    return vector<>

//}

void Rules::plusButtonSlot(unsigned int index)
{
    qDebug( ) << index;
    rules[index].chainsVector->push_back(new QLineEdit);
    rules[index].chainLayout->addWidget(rules[index].chainsVector->at(rules[index].chainsVector->size() - 1));
}

