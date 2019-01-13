#include "customdialog.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QDebug>

CustomDialog::CustomDialog(QWidget *parent) : QDialog (parent)
{
    layout = new QGridLayout(this);
    buttons = new QGridLayout();
    alphabetLine = new QLineEdit();
    finalChainLine = new QLineEdit();
    mulSymbolBox = new QComboBox();
    mulTimesLine = new QLineEdit();
    ok = new QPushButton("Ок");
    cancel = new QPushButton("Отмена");
    layout->addWidget(alphabetLine, 0, 1, 1, 1);
    layout->addWidget(finalChainLine, 1, 1, 1, 1);
    layout->addWidget(mulSymbolBox, 2, 1, 1, 1);
    layout->addWidget(mulTimesLine, 2, 3, 1, 1);
    layout->addLayout(buttons, 3, 0, 1, 5);
    buttons->addWidget(ok, 0, 0);
    buttons->addWidget(cancel, 0, 1);

    alphabetLabel = new QLabel("Алфавит");
    finalChainLabel = new QLabel("Конечная подцепочка");
    mulSymbolLabel = new QLabel("Кратность символа");
    mulTimesLabel = new QLabel("раз");
    QLabel *ravno = new QLabel ("=");

    layout->addWidget(alphabetLabel, 0, 0, 1, 1);
    layout->addWidget(finalChainLabel, 1, 0, 1, 1);
    layout->addWidget(mulSymbolLabel, 2, 0, 1, 1);
    layout->addWidget(ravno, 2, 2, 1, 1);
    layout->addWidget(mulTimesLabel, 2, 4, 1, 1);

    QObject::connect(ok, &QPushButton::clicked, this, &CustomDialog::okPressed);
    QObject::connect(cancel, &QPushButton::clicked, this, &CustomDialog::cancelPressed);
    QObject::connect(alphabetLine, &QLineEdit::textChanged, this, &CustomDialog::checkAlphabetSlot);
}

CustomDialog::~CustomDialog()
{
    delete layout;
}

bool CustomDialog::checkFinalChain()
{
    bool trig = false;
    QString s = finalChainLine->text();
    for (int i = 0; i < s.length(); ++i)
    {
        trig = false;

        for (int j = 0; j < alphabet.length(); ++j)
        {
            if (s[i] == alphabet[j]) trig = true;
        }

        if (!trig) {qDebug()<<"vse ne ok"; return false;}
    }
    qDebug()<<"vse ok";
    return true;
}

void CustomDialog::statesFilling()
{
    finalChain = finalChainLine->text();
    mulSymbol = alphabet[mulSymbolBox->currentIndex()];
    mulTimes = mulTimesLine->text().toInt();

    bool trig = false;

    for (int i = 0; i < finalChain.length(); ++i)
    {
        if (mulSymbol == finalChain[i]) trig = true;
    }

    if (trig)
    {

    }
    else
    {
        numberOfStates = finalChain.length() + mulTimes;
        numberOfTerminals = alphabet.length();
        QVector<QString> stateTemp;
        stateTemp.resize(alphabet.length());
        int nextCharInt = 2;
        QString nextChar = QString::number(nextCharInt);
        QChar startChar = '1';

        int mulSymbolIndex = 0;
        for (int j = 0; j < alphabet.length(); ++j)
            if (mulSymbol == alphabet[j])
            {
                mulSymbolIndex = j;
            }
            else
            {
                qDebug() << "vse ochen` ploho";
            }

        int repeated = 0;                                           //how many times first symbol repeats
        for (int i = 0; i < finalChain.length(); ++i)
            if (finalChain[0] == finalChain[i]) repeated++;

        for(int i = 0; i < finalChain.length(); ++i)
        {
            int partOfFinalChainIndex = 0;
            for (int j = 0; j < alphabet.length(); ++j)
                if (finalChain[i] == alphabet[j])
                {
                    partOfFinalChainIndex = j;
                    qDebug() << "found";
                }
                else
                {
                    qDebug() << "vse ochen` ploho";
                }


            stateTemp[partOfFinalChainIndex] = QString('q'+ nextChar);

            for (int k = 0; k < alphabet.length(); ++k)
            {
                if (i == 0 && k==mulSymbolIndex)
                {
                    stateTemp[k] = "q" + QString::number(finalChain.length()+2);
                }
                if (k != partOfFinalChainIndex && k != mulSymbolIndex && i == repeated)
                {
                    stateTemp[k] = "q";
                    stateTemp[k] += QString::number(nextCharInt - 1);
                }
                else if (k != partOfFinalChainIndex && k != mulSymbolIndex && i!=repeated)
                {
                    stateTemp[k] = QString ('q' + startChar);
                }
                else if (k == partOfFinalChainIndex)
                {
                    stateTemp[k] += ", q";
                    stateTemp[k] += QString(startChar);
                }

            }
            states.push_back(stateTemp);
            nextCharInt++;
            nextChar = QString::number(nextCharInt);
            stateTemp.clear();
            stateTemp.resize(alphabet.length());

        }

        for (int k = 0; k < alphabet.length(); ++k)
        {
            if (k != mulSymbolIndex)
                stateTemp[k] = QString ('q' + startChar);
        }
        states.push_back(stateTemp);

        nextCharInt++;
        nextChar = QString::number(nextCharInt);

        for (int i = 0; i < mulTimes-1; ++i)
        {
            for (int j = 0; j < alphabet.length(); ++j)
            {
                if (j == mulSymbolIndex && i != mulTimes-2)
                {
                    stateTemp[j] = QString('q' + nextChar);
                }
                else if(j == mulSymbolIndex && i == mulTimes-2)
                {
                    stateTemp[j] = QString('q' + startChar);
                }
                else {
                    stateTemp[j] = QString('q') + QString::number(nextCharInt - 1);
                }
            }
            states.push_back(stateTemp);
            nextCharInt++;
            nextChar = QString::number(nextCharInt);
            stateTemp.clear();
            stateTemp.resize(alphabet.length());
        }
    }
}

void CustomDialog::okPressed()
{
    int p;
    QString s = mulTimesLine->text();

    /*if (QValidator::Acceptable != mulTimesLine->validator()->validate(s, p)){
        QMessageBox::warning(this, "Ошибка", "Кратность символа ввведена некорректно");
    }
    else*/ if (!checkFinalChain()){
        QMessageBox::warning(this, "Ошибка", "Некорректный ввод конечной подцепочки");
    }
    else {
        statesFilling();
        //emit finished(numberOfStates->text().toInt(), numberOfTerminals->text().toInt());
    }
}
void CustomDialog::cancelPressed()
{
    emit canceled();
}

void CustomDialog::clear()
{
    this->alphabetLine->clear();
    this->finalChainLine->clear();
    this->mulSymbolBox->clear();
    this->mulTimesLine->clear();
}

void CustomDialog::checkAlphabetSlot()
{
    alphabet.clear();
    mulSymbolBox->clear();

    QString alphabetString = alphabetLine->text();

    auto list = alphabetString.split(" ", QString::SkipEmptyParts);
    for (auto str : list){
        alphabet.push_back(str);
    }

    for (int i = 0; i < alphabet.length(); ++i)
        mulSymbolBox->addItem(alphabet[i]);
}
