#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include "parser.h"
#include "machine.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void checkChainSlot();
private:
    QLabel *statesLabel;
    QLabel *finishStatesLabel;
    QLabel *inputAlphabetLabel;
    QLabel *stackAlphabetLabel;
    QLabel *chainLabel;
    QLabel *startStateLabel;
    QLabel *emptySymbolLabel;
    QLabel *startStackLabel;
    QLabel *machineLabel;
    QLabel *outputLabel;

    QLineEdit *statesLine;
    QLineEdit *finishStatesLine;
    QLineEdit *inputAlphabetLine;
    QLineEdit *stackAlphabetLine;
    QLineEdit *chainLine;
    QLineEdit *startStateLine;
    QLineEdit *emptySymbolLine;
    QLineEdit *startStackLine;

    QPushButton *checkChainButton;

    QTextEdit *machineTextEdit;
    QTextEdit *outputTextEdit;

    QGridLayout *inputLayout;

    QHBoxLayout *textEditsLayout;
    QVBoxLayout *machineLayout;
    QVBoxLayout *outputLayout;
    QVBoxLayout *wholeLayout;

    Parser *parser;

    QWidget *window;
};

#endif // MAINWINDOW_H
