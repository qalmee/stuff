#include "centralwidget.h"
#include <QIntValidator>
#include <QRegExpValidator>
#include <QLabel>
#include <QDebug>
#include <QFrame>

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QGridLayout(this);
    generateRegExp = new QPushButton("Сгенерировать регулярное выражение");
    generateChains = new QPushButton("Сгенерировать цепочки");
    startChain = new QLineEdit();
    endChain = new QLineEdit();
    alphabet = new QLineEdit();
    multiplicity = new QLineEdit();
    multiplicity->setValidator(new QIntValidator(1, 99));
    symbolM = new QLineEdit();
    symbolM->setValidator(new QRegExpValidator(QRegExp(".")));
    regExp  = new QLineEdit();
    chains = new QTextEdit();
    minLen = new QLineEdit();
    maxLen = new QLineEdit();
    minLen->setValidator(new QIntValidator(0, 99));
    maxLen->setValidator(new QIntValidator(0, 99));
    chains->setReadOnly(true);
    //mainLayout->setColumnStretch(0, 70);
    //mainLayout->setColumnStretch(4, 70);
    mainLayout->addWidget(new QLabel("Алфавит"), 0, 0, 1, 2);
    mainLayout->addWidget(alphabet, 0, 2, 1, 2);
    mainLayout->addWidget(new QLabel("Начальная подцепочка"), 1, 0, 1 , 2);
    mainLayout->addWidget(startChain, 1, 2, 1, 2);
    mainLayout->addWidget(new QLabel("Конечная подцепочка"), 2, 0, 1, 2);
    mainLayout->addWidget(endChain, 2, 2, 1, 2);
    mainLayout->addWidget(new QLabel("Символ"), 3, 0);
    mainLayout->addWidget(symbolM, 3, 1);
    mainLayout->addWidget(new QLabel("Кратность"), 3, 2);
    mainLayout->addWidget(multiplicity, 3, 3);
    mainLayout->addWidget(new QLabel("Минимальная длина"), 4, 0);
    mainLayout->addWidget(minLen, 4, 1);
    mainLayout->addWidget(new QLabel("Максимальная длина"), 4, 2);
    mainLayout->addWidget(maxLen, 4, 3);

    mainLayout->addWidget(generateRegExp, 5, 0, 1, 4);
    mainLayout->addWidget(regExp, 6, 0, 1, 4);
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Plain);
    line->setLineWidth(2);
    mainLayout->addWidget(line, 7, 0, 1, 4);
    mainLayout->addWidget(generateChains, 8, 0, 1, 4);
    mainLayout->addWidget(chains, 0, 4, 9, 1);

    symbolM->setMaximumWidth(50);
    multiplicity->setMaximumWidth(50);
    minLen->setMaximumWidth(50);
    maxLen->setMaximumWidth(50);

    chains->setMaximumWidth(350);

}

QVector<QChar> CentralWidget::getAlphabet() const
{
    QString text = alphabet->text();
    QVector <QChar> v;
    v.reserve(text.size());
    for (auto ch : text){
        if (ch != ' ' && ch != ',') v.push_back(ch);
    }
    return v;
}

QString CentralWidget::getStartChain() const
{
    return startChain->text();
}

QString CentralWidget::getEndChain() const
{
    return endChain->text();
}

QChar CentralWidget::getSymbolM() const
{
    if (symbolM->text().size()) return symbolM->text().at(0);
    return 0;
}

int CentralWidget::getMultiplicity() const
{
    //qDebug() << symbolM->text() << endl << symbolM->text().toInt();
    if (multiplicity->text().size()) return multiplicity->text().toInt();
    return 0;
}

QPushButton * CentralWidget::getGenerateRegExpButton() const
{
    return generateRegExp;
}

QPushButton *CentralWidget::getGenerateChainsButton() const
{
    return generateChains;
}

QString CentralWidget::getRegExp() const
{
    return regExp->text();
}

void CentralWidget::setRegExp(const QString &value)
{
    regExp->setText(value);
}

void CentralWidget::setMultiplicity(int value)
{
    multiplicity->setText(QString::number(value));
}

int CentralWidget::getMaxLen() const
{
    return maxLen->text().toInt();
}

void CentralWidget::setMaxLen(int value)
{
    maxLen->setText(QString::number(value));
}

int CentralWidget::getMinLen() const
{
    return minLen->text().toInt();
}

void CentralWidget::setMinLen(int value)
{
    minLen->setText(QString::number(value));
}

void CentralWidget::setChains(const QSet<QString> *s)
{
    chains->clear();
    chains->append("Строк найдено: " + QString::number(s->size()));
    for (auto st : *s){
        chains->append("\"" + st + "\" : " + QString::number(st.size()));
    }
}
