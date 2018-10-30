#include "resultdialog.h"

ResultDialog::ResultDialog() : QDialog ()
{
    constructStuff();
}

void ResultDialog::setInformation(QString message, QVector<QPair<QString, QChar> > *result, QString chain)
{
    this->chain->setText(chain);
    this->resultMessage->setText(message);
    this->result->clear();
    for (auto x : *result){
        this->result->append(x.first + " (" + QString(1, x.second) + ") ->");
    }
}

void ResultDialog::constructStuff()
{

    layout = new QGridLayout(this);
    //this->setLayout(layout);

    result = new QTextEdit;
    chain = new QLineEdit;
    resultMessage = new QLabel();
    layout->addWidget(resultMessage, 0, 0);
    layout->addWidget(result);
    layout->addWidget(chain);
    chain->setReadOnly(true);
    result->setReadOnly(true);
}
