#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "customdialog.h"
#include <QGridLayout>
#include <QLabel>
#include <QVector>
#include <QString>
#include <QLineEdit>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    CustomDialog *dialog;
    int numberOfStates;
    int numberOfTerminals;

    QVector <QString> statesNames;
    QVector <QString> terminals;
    QVector <QString> statesValues;

    QVBoxLayout *wholeLayout;
    QVBoxLayout *chainLayout;
    QGridLayout *tableLayout;

    QVector <QLineEdit*> terminalsLines;
    QVector <QLineEdit*> statesLines;
    QVector <QVector <QLineEdit*>> statesValuesLines;

    QPushButton *checkChainButton;
    QLineEdit *chain;
};

#endif // MAINWINDOW_H
