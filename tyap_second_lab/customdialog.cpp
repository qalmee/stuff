#include "customdialog.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QDebug>

CustomDialog::CustomDialog(QWidget *parent) : QDialog (parent)
{
    layout = new QGridLayout(this);
    buttons = new QGridLayout();
    numberOfStates = new QLineEdit();
    numberOfTerminals = new QLineEdit();
    numberOfStates->setValidator(new QIntValidator(1, 20));
    numberOfTerminals->setValidator(new QIntValidator(1, 20));
    ok = new QPushButton("Ок");
    cancel = new QPushButton("Отмена");
    layout->addWidget(numberOfStates, 0, 1, 1, 1);
    layout->addWidget(numberOfTerminals, 1, 1, 1, 1);
    layout->addLayout(buttons, 2, 0, 1, 5);
    buttons->addWidget(ok, 0, 0);
    buttons->addWidget(cancel, 0, 1);

    numberOfStatesLabel = new QLabel("Количество состояний");
    numberOfTerminalsLabel = new QLabel("Количество терминальных символов");
    layout->addWidget(numberOfStatesLabel, 0, 0, 1, 1);
    layout->addWidget(numberOfTerminalsLabel, 1, 0, 1, 1);

    QObject::connect(ok, &QPushButton::clicked, this, &CustomDialog::okPressed);
    QObject::connect(cancel, &QPushButton::clicked, this, &CustomDialog::cancelPressed);
}

CustomDialog::~CustomDialog()
{
    delete layout;
}

void CustomDialog::okPressed()
{
    int p;
    QString s = numberOfStates->text();
    QString s1 = numberOfTerminals->text();
    if (QValidator::Acceptable != numberOfStates->validator()->validate(s, p)){
        QMessageBox::warning(this, "Ошибка", "Некорректный ввод");
    }
    else if (QValidator::Acceptable != numberOfTerminals->validator()->validate(s1, p)){
        QMessageBox::warning(this, "Ошибка", "Некорректный ввод");
    } else {
        emit finished(numberOfStates->text().toInt(), numberOfTerminals->text().toInt());
    }
}
void CustomDialog::cancelPressed()
{
    emit canceled();
}

void CustomDialog::clear()
{
    this->numberOfStates->clear();
    this->numberOfTerminals->clear();
}
