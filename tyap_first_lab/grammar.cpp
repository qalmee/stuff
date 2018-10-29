#include "grammar.h"

Grammar::Grammar(QWidget *parent) : QWidget(parent)
{
    amountOfUnterminalLabel = new QLabel("Количество нетерминальных символов");
    //amountOfTerminalLabel = new QLabel("Количество терминальных символов");
    lenthOfChainsLabel = new QLabel("Длина цепочки");
    minLengthLabel = new QLabel("От");
    maxLengthLabel = new QLabel("До");

    amountOfUnterminalLine = new QLineEdit();
    amountOfUnterminalLine->setValidator(new QIntValidator(0,10, this));
    //amountOfTerminalLine = new QLineEdit();
    //amountOfTerminalLine->setValidator(new QIntValidator(0,100, this));
    minLengthLine = new QLineEdit();
    minLengthLine->setValidator(new QIntValidator(0,15, this));
    maxLengthLine = new QLineEdit();
    maxLengthLine->setValidator(new QIntValidator(0,15, this));

    QGridLayout *verticalLayout = new QGridLayout();
    QHBoxLayout *horFromToLengthLayout = new QHBoxLayout();
    horFromToLengthLayout->addWidget(minLengthLabel);
    horFromToLengthLayout->addWidget(minLengthLine);
    horFromToLengthLayout->addWidget(maxLengthLabel);
    horFromToLengthLayout->addWidget(maxLengthLine);

    verticalLayout->addWidget(amountOfUnterminalLabel);
    verticalLayout->addWidget(amountOfUnterminalLine);
    //verticalLayout->addWidget(amountOfTerminalLabel);
    //verticalLayout->addWidget(amountOfTerminalLine);
    verticalLayout->addWidget(lenthOfChainsLabel);
    verticalLayout->addLayout(horFromToLengthLayout);

    setLayout(verticalLayout);
}

int Grammar::getAmountOfUnterminal()
{
    QString temp = amountOfUnterminalLine->text();
    return temp.toInt();
}

/*int Grammar::getAmountOfTerminal()
{
    QString temp = amountOfTerminalLine->text();
    return temp.toInt();
}
*/

int Grammar::getMinLength()
{
    QString temp = minLengthLine->text();
    return temp.toInt();
}

int Grammar::getMaxLength()
{
    QString temp = maxLengthLine->text();
    return temp.toInt();
}




