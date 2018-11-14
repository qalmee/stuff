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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QLabel *numberOfStatesLabel;
    QLabel *numberOfFinishStatesLabel;
    QLabel *inputAlphabetLabel;
    QLabel *stackAlphabetLabel;
    QLabel *chainLabel;
    QLabel *startStateLabel;
    QLabel *emptySymbolLabel;
    QLabel *startStackLabel;
    QLabel *machineLabel;
    QLabel *outputLabel;

    QLineEdit *numberOfStatesLine;
    QLineEdit *numberOfFinishStatesLine;
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

    QWidget *window;
};

#endif // MAINWINDOW_H
