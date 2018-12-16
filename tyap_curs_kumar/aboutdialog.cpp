#include "aboutdialog.h"

AboutDialog::AboutDialog(const QString &text)
{
    layout = new QGridLayout(this);
    one = new QLabel(text);
    layout->addWidget(one, 0, 0);
    this->setModal(true);
    this->setFixedSize(QSize(this->size().width() + 150, this->size().height() - 150));

}

AboutDialog::AboutDialog()
{
    layout = new QGridLayout(this);
    one = new QLabel("Работу выполнил:\nКомаревцев Даниил\nГруппа ИП-513");
    layout->addWidget(one, 0, 0);
    this->setModal(true);
    this->setFixedSize(QSize(300, 200));

}

AboutDialog::~AboutDialog()
{
    delete layout;
    delete one;
    delete two;
}
