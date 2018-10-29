#include "customdialog.h"
#include <QIntValidator>

CustomDialog::CustomDialog() : QDialog ()
{
    layout = new QGridLayout(this);
    buttons = new QHBoxLayout();
    numberOfStates = new QLineEdit();
    numberOfTerminals = new QLineEdit();
    numberOfStates->setValidator(new QIntValidator(0, 20));
    numberOfTerminals->setValidator(new QIntValidator(0, 20));
    ok = new QPushButton("Ок");
    cancel = new QPushButton("Отмена");
    layout->addWidget(numberOfStates, 0, 1, 1, 1);
    layout->addWidget(numberOfTerminals, 1, 1, 1, 1);
    layout->addLayout(buttons, 2, 0, 1, 5);
    buttons->addWidget(ok);
    buttons->addWidget(cancel);

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
    QString s;
    if (QValidator::Acceptable != numberOfStates->validator()->validate(s, p)){
        return;
    }
    if (QValidator::Acceptable != numberOfTerminals->validator()->validate(s, p)){
        return;
    }
    emit finished(numberOfStates->text().toInt(), numberOfTerminals->text().toInt());
}
void CustomDialog::cancelPressed()
{
    emit canceled();
}
