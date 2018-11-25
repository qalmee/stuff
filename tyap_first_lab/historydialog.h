#ifndef HISTORYDIALOG_H
#define HISTORYDIALOG_H

#include <QDialog>
#include <QTextEdit>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <unordered_map>
#include <string>

class HistoryDialog : public QDialog
{
    Q_OBJECT
public:
    HistoryDialog(QWidget *parent = nullptr);
    void setParent(std::unordered_map<std::string, std::string> *parent);
public slots:
    void search(const QString &text);
private:
    std::unordered_map<std::string, std::string> *parent;
    QLineEdit *chain;
    QTextEdit *history;
    QGridLayout *layout;
    QLabel *inputChain;

};

#endif // HISTORYDIALOG_H
