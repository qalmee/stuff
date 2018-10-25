#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QVector>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "grammar.h"
#include "rules.h"
#include <QDebug>
#include <QSizePolicy>
#include <QTextEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    int amountOfRules;
    int maxLength;
    int minLength;
    int amountOfTerminal;
    QVector <QString> terminalSymbols;
    QVector <QString> unterminalSymbols;
    QVector <QString> rules;
    bool createdEarlier;

    Grammar *grammarWidget;

    QPushButton *refreshGrammarButton;
    QPushButton *refreshRulesButton;

    QHBoxLayout *wholeLayout;
    QVBoxLayout *leftUpLayout;
    QVBoxLayout *leftDownLayout;
    QVBoxLayout *rightLayout;
    QVBoxLayout *leftLayout;




public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Initialization();
    void clearLayout(QLayout* , bool );

public slots:
    void rulesRefresherSlot();

signals:
    void rulesRefreshSignal();

};

#endif // MAINWINDOW_H
