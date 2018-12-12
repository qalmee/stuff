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
    void readFromFile();
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
    QLabel *translateLabel;

    QLineEdit *statesLine;
    QLineEdit *finishStatesLine;
    QLineEdit *inputAlphabetLine;
    QLineEdit *stackAlphabetLine;
    QLineEdit *translateAlphabet;
    QTextEdit *chainLine;
    QLineEdit *startStateLine;
    QLineEdit *emptySymbolLine;
    QLineEdit *startStackLine;

    QPushButton *checkChainButton;
    QPushButton *import;

    QTextEdit *machineTextEdit;
    QTextEdit *outputTextEdit;

    QGridLayout *inputLayout;

    QHBoxLayout *textEditsLayout;
    QVBoxLayout *machineLayout;
    QVBoxLayout *outputLayout;
    QVBoxLayout *wholeLayout;


    QWidget *window;
};

#endif // MAINWINDOW_H
