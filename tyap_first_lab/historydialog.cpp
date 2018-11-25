#include "historydialog.h"
#include <algorithm>
#include <QDebug>

HistoryDialog::HistoryDialog(QWidget *parent) : QDialog (parent)
{
    layout = new QGridLayout(this);
    inputChain = new QLabel("Введите цепочку для просмотра преобразований :");
    chain = new QLineEdit();
    history = new QTextEdit();
    layout->addWidget(inputChain);
    layout->addWidget(chain);
    layout->addWidget(history);

    connect(chain, &QLineEdit::textEdited, this, &HistoryDialog::search);

}

void HistoryDialog::setParent(std::unordered_map<std::string, std::string> *parent)
{
    this->parent = parent;
}

void HistoryDialog::search(const QString &text)
{
    std::string s = text.toStdString();
    QVector <QString> v;
    history->clear();
    while (parent->count(s)){
        v.push_back(QString::fromStdString(s));
        s = parent->at(s);
    }
    v.push_back(QString::fromStdString(s));
    std::reverse(v.begin(), v.end());
    QString ans;
    for (int i = 0; i<v.size(); i++){
        if (i + 1 < v.size()) ans.append(v[i] + " -> ");
        else ans.append(v[i]);
    }
    history->setText(ans);
}
