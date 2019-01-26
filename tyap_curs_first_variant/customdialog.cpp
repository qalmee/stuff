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
    finalState = 0;

    bool trig = false;

    for (int i = 0; i < finalChain.length(); ++i)
    {
        if (mulSymbol == finalChain[i]) trig = true;
    }

    if (mulTimes == 1) trig = false;

    if (finalChain.length() == 0)
    {
        numberOfStates = finalChain.length() + mulTimes;
        numberOfTerminals = alphabet.length();
        QVector<QString> stateTemp;
        stateTemp.resize(alphabet.length());
        int nextCharInt = 1;
        if (mulTimes > 1)
            nextCharInt++;

        QString nextChar = QString::number(nextCharInt);
        QChar startChar = '1';

        int mulSymbolIndex = 0;
        for (int j = 0; j < alphabet.length(); ++j)
        {
            if (mulSymbol == alphabet[j])
                mulSymbolIndex = j;
        }

        int currentState = 1;

        for (int i = 0; i < mulTimes; ++i)
        {
            for (int j = 0; j < alphabet.length(); ++j)
            {
                if (j == mulSymbolIndex)
                {
                    if (i != mulTimes - 1)
                        stateTemp[j] = QString('q' + nextChar);
                    else {
                        stateTemp[j] = QString('q' + startChar);
                    }
                }
                else {
                    stateTemp[j] = QString('q') + QString::number(currentState);
                }
            }
            states.push_back(stateTemp);
            nextCharInt++;
            nextChar = QString::number(nextCharInt);
            stateTemp.clear();
            stateTemp.resize(alphabet.length());
            finalState = currentState;
            currentState++;
        }
    }

    else if (trig)
    {
        numberOfTerminals = alphabet.length();
        QVector<QString> stateTemp;
        stateTemp.resize(alphabet.length());
        int nextCharInt = 2;
        QString nextChar = QString::number(nextCharInt);
        QChar startChar = '1';
        int additionalMulSymbols;
        int whereToReturnState = 0;

        int mulSymbolIndex = 0;
        for (int j = 0; j < alphabet.length(); ++j)
            if (mulSymbol == alphabet[j])
                mulSymbolIndex = j;

        int mulSymbolRepeated = 0;
        for (int i = 0; i < finalChain.length(); ++i)
        {
            if (finalChain[i] == mulSymbol) mulSymbolRepeated++;
        }

        if (mulTimes >= mulSymbolRepeated)
        {
            additionalMulSymbols = mulTimes - mulSymbolRepeated;
        }
        else {
            additionalMulSymbols = mulTimes % mulSymbolRepeated - 1;
        }

        int repeated = 0;                                           //how many times first symbol repeats in a row
        bool stillRepeats = 1;
        for (int i = 0; i < finalChain.length(); ++i)
            if (finalChain[0] == finalChain[i] && stillRepeats) repeated++;
            else if (finalChain[0] != finalChain[i]) stillRepeats = false;
        whereToReturnState = repeated;

        numberOfStates = finalChain.length() + additionalMulSymbols + 1;

        for (int i = 0; i < additionalMulSymbols; ++i)
        {
            for (int j = 0; j < alphabet.length(); ++j)
            {
                if (j == mulSymbolIndex)
                    stateTemp[j] = 'q' + nextChar;
                else if (j != mulSymbolIndex)
                    stateTemp[j] = 'q' + QString::number(nextCharInt-1);
            }
            states.push_back(stateTemp);
            finalState = nextCharInt-1;
            nextCharInt++;
            nextChar = QString::number(nextCharInt);
            stateTemp.clear();
            stateTemp.resize(alphabet.length());
        }

        if (finalChain[0] != mulSymbol)
        {
            whereToReturnState += additionalMulSymbols;
            int firstSymbolOfFinalChainIndex = 0;
            for (int j = 0; j < alphabet.length(); ++j)
                if (finalChain[0] == alphabet[j])
                {
                    firstSymbolOfFinalChainIndex = j;
                }

            for(int i = 0; i < finalChain.length() + 1; ++i)
            {
                int partOfFinalChainIndex = 0;

                for (int j = 0; j < alphabet.length(); ++j)
                    if (finalChain[i] == alphabet[j])
                    {
                        partOfFinalChainIndex = j;
                    }
               stateTemp[partOfFinalChainIndex] = 'q' + QString::number(nextCharInt);

               for (int k = 0; k < alphabet.length(); ++k)
               {
                   if (k == partOfFinalChainIndex)
                   {
                       if (i == finalChain.length())
                       {
                            stateTemp[k]  = 'q' + QString::number(whereToReturnState);
                       }
                       else
                            stateTemp[k] = 'q' + nextChar;
                   }
                   else if (k != partOfFinalChainIndex)
                   {
                       if (i != 0)
                           stateTemp[k] = 'q' + QString::number(whereToReturnState);
                       else
                           stateTemp[k] = 'q' + QString::number(nextCharInt-1);
                   }
                   if (k == firstSymbolOfFinalChainIndex)
                   {
                       stateTemp[k] = 'q' + QString::number(whereToReturnState + 1);
                   }
                   if (k == mulSymbolIndex)
                   {
                       if (k != partOfFinalChainIndex || i == finalChain.length())
                       {
                            stateTemp[k] = 'q' + startChar;
                       }
                       else
                            stateTemp[k] = 'q' + nextChar;
                   }
               }

               states.push_back(stateTemp);
               finalState = nextCharInt - 1;
               nextCharInt++;
               nextChar = QString::number(nextCharInt);
               stateTemp.clear();
               stateTemp.resize(alphabet.length());
            }
        }
        else {
            whereToReturnState += additionalMulSymbols;

            for(int i = 0; i < finalChain.length()+1; ++i)
            {
                int partOfFinalChainIndex = 0;

                for (int j = 0; j < alphabet.length(); ++j)
                    if (finalChain[i] == alphabet[j])
                    {
                        partOfFinalChainIndex = j;
                    }
               stateTemp[partOfFinalChainIndex] = 'q' + QString::number(nextCharInt);

               for (int k = 0; k < alphabet.length(); ++k)
               {
                   if (k != partOfFinalChainIndex)
                   {
                       if (i != 0)
                           stateTemp[k] = 'q' + QString::number(whereToReturnState);
                       else
                           stateTemp[k] = 'q' + QString::number(nextCharInt-1);

                       if (k == mulSymbolIndex)
                       {
                            stateTemp[k] = 'q'+ QString::number(2);
                       }
                   }

                   if (k == partOfFinalChainIndex)
                   {
                       if (i == finalChain.length())
                       {
                            stateTemp[k]  = 'q' + QString::number(whereToReturnState);
                       }
                       else
                            stateTemp[k] = 'q' + nextChar;

                       if (k == mulSymbolIndex)
                       {
                           if (i == finalChain.length())
                                stateTemp[k] = 'q'+ QString::number(2);
                           else
                                stateTemp[k] = 'q' + nextChar;
                       }
                   }
               }

               states.push_back(stateTemp);
               finalState = nextCharInt - 1;
               nextCharInt++;
               nextChar = QString::number(nextCharInt);
               stateTemp.clear();
               stateTemp.resize(alphabet.length());
            }
        }

    }
    else
    {
        if (mulTimes > 1)
        {
            numberOfStates = finalChain.length() + mulTimes;
            numberOfTerminals = alphabet.length();
            QVector<QString> stateTemp;
            stateTemp.resize(alphabet.length());
            int nextCharInt = 2;
            int returnSymbolOfFinalChainIndex = 0;
            int whereToReturnState = 1;
            QString nextChar = QString::number(nextCharInt);
            QChar startChar = '1';

            int repeated = 0;                                           //how many times first symbol repeats in a row
            bool stillRepeats = 1;
            for (int i = 0; i < finalChain.length(); ++i)
                if (finalChain[0] == finalChain[i] && stillRepeats) repeated++;
                else if (finalChain[0] != finalChain[i]) stillRepeats = false;
            whereToReturnState = repeated + 1;

            int mulSymbolIndex = 0;
            for (int j = 0; j < alphabet.length(); ++j)
            {
                if (mulSymbol == alphabet[j])
                    mulSymbolIndex = j;
                if (finalChain[repeated-1] == alphabet[j])                //where to return
                    returnSymbolOfFinalChainIndex = j;
            }


            for(int i = 0; i < finalChain.length(); ++i)
            {
                int partOfFinalChainIndex = 0;
                for (int j = 0; j < alphabet.length(); ++j)
                    if (finalChain[i] == alphabet[j])
                        partOfFinalChainIndex = j;


                for (int k = 0; k < alphabet.length(); ++k)
                {
                    if (k == partOfFinalChainIndex)
                    {
                        stateTemp[k] = QString("q" + nextChar);
                    }
                    else if (k == mulSymbolIndex)
                    {
                        stateTemp[k] = "q" + QString::number(finalChain.length()+2);
                    }
                    else if (k == returnSymbolOfFinalChainIndex)
                    {
                        if (i == repeated)
                        {
                            stateTemp[k] = "q";
                            stateTemp[k] += QString::number(whereToReturnState);
                        }
                        else if(i > repeated)
                        {
                            stateTemp[k] = "q";
                            stateTemp[k] += QString::number(whereToReturnState);
                        }

                    }
                    else if (k != partOfFinalChainIndex && k != mulSymbolIndex
                             && k != returnSymbolOfFinalChainIndex)
                    {
                        stateTemp[k] = QString ('q' + startChar);
                        qDebug() << i << k;
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
                if (k == mulSymbolIndex)
                    stateTemp[k] = QString ('q' + QString::number(finalChain.length()+2));
                else if (k != returnSymbolOfFinalChainIndex)
                    stateTemp[k] = QString ('q' + QString::number(whereToReturnState));
                else
                    stateTemp[k] = QString ('q' + startChar);
            }
            finalState = nextCharInt-1;
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
        else {
            qDebug() << "im here";
            numberOfStates = finalChain.length()+1;
            numberOfTerminals = alphabet.length();
            QVector<QString> stateTemp;
            stateTemp.resize(alphabet.length());
            int nextCharInt = 2;
            int returnSymbolOfFinalChainIndex = 0;
            int whereToReturnState = 1;
            QString nextChar = QString::number(nextCharInt);
            QChar startChar = '1';

            int repeated = 0;                                           //how many times first symbol repeats in a row
            bool stillRepeats = 1;
            for (int i = 0; i < finalChain.length(); ++i)
                if (finalChain[0] == finalChain[i] && stillRepeats) repeated++;
                else if (finalChain[0] != finalChain[i]) stillRepeats = false;
            whereToReturnState = repeated + 1;

            for (int j = 0; j < alphabet.length(); ++j)
            {
                if (finalChain[repeated-1] == alphabet[j])                //where to return
                    returnSymbolOfFinalChainIndex = j;
            }

            for(int i = 0; i < finalChain.length()+1; ++i)
            {
                int partOfFinalChainIndex = 0;
                for (int j = 0; j < alphabet.length(); ++j)
                    if (finalChain[i] == alphabet[j])
                        partOfFinalChainIndex = j;

                for (int k = 0; k < alphabet.length(); ++k)
                {
                    if (k == partOfFinalChainIndex)
                    {
                        if (i == finalChain.length())
                        {
                            stateTemp[partOfFinalChainIndex] = 'q' + startChar;
                        }
                        else
                            stateTemp[partOfFinalChainIndex] = 'q' + nextChar;
                    }
                    else if (k == returnSymbolOfFinalChainIndex)
                    {
                            stateTemp[k] = "q";
                            stateTemp[k] += QString::number(whereToReturnState);
                    }
                    else
                    {
                        stateTemp[k] = QString ('q' + startChar);
                        qDebug() << i << k;
                    }
                }
                states.push_back(stateTemp);
                finalState = nextCharInt - 1;
                nextCharInt++;
                nextChar = QString::number(nextCharInt);
                stateTemp.clear();
                stateTemp.resize(alphabet.length());
            }
        }
    }
}

void CustomDialog::okPressed()
{
    int p;
    QString s = mulTimesLine->text();

    if (!checkFinalChain()){
        QMessageBox::warning(this, "Ошибка", "Некорректный ввод конечной подцепочки");
    }
    else {
        statesFilling();
        emit finished(numberOfStates, numberOfTerminals, states, alphabet, finalChain, mulTimes, mulSymbol, finalState);
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
