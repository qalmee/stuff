#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QVector>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QSizePolicy>
#include <QTextEdit>
#include <QScrollArea>

#include "grammar.h"
#include "rules.h"
#include "historydialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    int amountOfRules;
    int maxLength;
    int minLength;
    int amountOfTerminal;
    unsigned int indexTargetSymbol;

    QVector <QString> terminalSymbols;
    QVector <QString> unterminalSymbols;
    QVector <QString> rules;
    bool createdEarlier;

    Grammar *grammarWidget;
    Rules *rulesWidget;
    QTextEdit *words;

    QPushButton *refreshGrammarButton;
    QPushButton *refreshRulesButton;
    QPushButton *showHistoryButton;

    QHBoxLayout *wholeLayout;
    QVBoxLayout *leftUpLayout;
    QVBoxLayout *leftDownLayout;
    QVBoxLayout *rightLayout;
    QVBoxLayout *leftLayout;

    std::unordered_map<std::string, std::string> *parent;

    HistoryDialog *historyDialog;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Initialization();
    void clearLayout(QLayout* , bool );

public slots:
    void rulesRefresherSlot();
    void build();
    void showHistorySlot();

signals:
    void rulesRefreshSignal();

};

#endif // MAINWINDOW_H
