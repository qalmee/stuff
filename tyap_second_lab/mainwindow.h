#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "customdialog.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QVector>
#include <QString>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>
#include <QRegExpValidator>
#include "QComboBox"
#include <QApplication>
#include "machine.h"
#include "resultdialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QApplication *a, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void cancelDialog();
    void okDialog(int numberOfStates, int numberOfTerminals);
    void checkChainSlot();
    void returnToDialogSlot();
    void badInputSlot();
    void checkStatesSlot();
    void runMachine();

signals:
    void badInput();    

private:

    void prepareView();
    void constructStuff();
    void deleteStuff();

    CustomDialog *dialog;
    ResultDialog *resultDialog;
    int numberOfStates;
    int numberOfTerminals;
    QString chainString;

    QVector <QString> statesNames;
    QVector <QString> terminals;
    QVector <QVector<QString>> statesValues;

    QGridLayout *tableLayout;

    QVector <QLineEdit*> terminalsLines;
    QVector <QLineEdit*> statesLines;
    QVector <QVector <QLineEdit*>> statesValuesLines;

    QPushButton *checkChainButton;
    QPushButton *returnToDialogButton;

    QWidget *window;
    QLabel *chainLabel;
    QLabel *startStateLabel;
    QLabel *finishStateLabel;

    QFrame *lineV, *lineH, *secondLineH, *secondLineV, *thirdLineH;

    QApplication *app;
    QLineEdit *chainLine;

    QRegExp *regExp;
    QRegExpValidator *regExpVal;
    QComboBox *startState;
    QComboBox *finishState;

    Machine *machine;

};

#endif // MAINWINDOW_H
