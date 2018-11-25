#include "grammar.h"

Grammar::Grammar(QWidget *parent) : QWidget(parent)
{
    amountOfUnterminalLabel = new QLabel("Количество нетерминальных символов");
    //amountOfTerminalLabel = new QLabel("Количество терминальных символов");
    lenthOfChainsLabel = new QLabel("Длина цепочки");
    minLengthLabel = new QLabel("От");
    maxLengthLabel = new QLabel("До");

    lp = new QRadioButton("Леволинейная грамматика");
    rp = new QRadioButton("Праволинейная грамматика");
    lp->setChecked(true);

    startChainLabel = new QLabel("Начальная подцепочка");
    endChainLabel = new QLabel("Конечная подцепочка");
    multiAccuranceLabel = new QLabel("Кратность вхождения символа в итоговую цепочку");

    multiplicity = new QLineEdit("0");
    multiplicity->setMaxLength(multiplicity->size().width() / 2);
    multiplicity->setValidator(new QIntValidator(0, 100, this));
    startChain = new QLineEdit();
    endChain = new QLineEdit();
    multiAccuranceSymbol = new QLineEdit("a");
    multiAccuranceSymbol->setValidator(new QRegExpValidator(QRegExp(".")));


    amountOfUnterminalLine = new QLineEdit();
    amountOfUnterminalLine->setValidator(new QIntValidator(0,10, this));
    //amountOfTerminalLine = new QLineEdit();
    //amountOfTerminalLine->setValidator(new QIntValidator(0,100, this));
    minLengthLine = new QLineEdit();
    minLengthLine->setValidator(new QIntValidator(0,15, this));
    maxLengthLine = new QLineEdit();
    maxLengthLine->setValidator(new QIntValidator(0,15, this));

    verticalLayout = new QVBoxLayout();
    horFromToLengthLayout = new QHBoxLayout();
    lpOrRpGrammar = new QHBoxLayout();

    grid = new QGridLayout();
    grid->addWidget(startChainLabel, 0, 0);
    grid->addWidget(endChainLabel, 0, 2);
    grid->addWidget(startChain, 0, 1);
    grid->addWidget(endChain, 0, 3);
    grid->addWidget(multiAccuranceLabel, 1, 0, 1, 2);
    grid->addWidget(multiAccuranceSymbol, 1, 2);
    grid->addWidget(multiplicity, 1, 3);
    grid->addWidget(amountOfUnterminalLabel, 2, 0, 1, 2);
    grid->addWidget(amountOfUnterminalLine, 2, 2, 1, 2);

    multiplicity->setMaxLength(multiplicity->size().width() / 2);
    multiAccuranceSymbol->setMaxLength(multiAccuranceSymbol->size().width() / 2);


    lpOrRpGrammar->addWidget(lp);
    lpOrRpGrammar->addWidget(rp);

    horFromToLengthLayout->addWidget(minLengthLabel);
    horFromToLengthLayout->addWidget(minLengthLine);
    horFromToLengthLayout->addWidget(maxLengthLabel);
    horFromToLengthLayout->addWidget(maxLengthLine);

      verticalLayout->addLayout(grid);

    //verticalLayout->addWidget(amountOfTerminalLabel);
    //verticalLayout->addWidget(amountOfTerminalLine);
    verticalLayout->addWidget(lenthOfChainsLabel);
    verticalLayout->addLayout(horFromToLengthLayout);
    verticalLayout->addLayout(lpOrRpGrammar);


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

bool Grammar::isLpGrammar() const
{
    return lp->isChecked();
}

QString Grammar::getStartChain() const
{
    return startChain->text();

}

QString Grammar::getEndChain() const
{
    return endChain->text();
}

QPair<QString, int> Grammar::getMSymbol() const
{
    return QPair<QString, int>(multiAccuranceSymbol->text(), multiplicity->text().toInt());
}

void Grammar::setMultiplicity(const QString &s)
{
    multiplicity->setText(s);
}
