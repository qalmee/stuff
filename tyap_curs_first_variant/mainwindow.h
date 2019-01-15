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
#include <QCheckBox>
#include <QStandardItemModel>
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
    void okDialog(int _numberOfStates, int _numberOfTerminals, QVector <QVector<QString>> _states,
                  QVector <QString> _terminals, QString _finalChain, int _mulTimes, QString _mulSymbol);

    void checkChainSlot();
    void returnToDialogSlot();
    void badInputSlot();
    void checkStatesSlot();
    void runMachine();
    void finishStateComboBoxSelected(int index);

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
    int mulTimes;
    QString chainString;
    QString mulSymbol;
    QString finalChain;

    QVector <QString> statesNames;
    QVector <QString> terminals;
    QVector <QVector<QString>> statesValues;

    QGridLayout *tableLayout;

    QVector <QLineEdit*> terminalsLines;
    QVector <QLineEdit*> statesLines;
    QVector <QVector <QLineEdit*>> statesValuesLines;
    QVector <QCheckBox*> finishStateCheckBoxes;


    QPushButton *checkChainButton;
    QPushButton *returnToDialogButton;

    QWidget *window;
    QLabel *chainLabel;
    QLabel *startStateLabel;
    QLabel *finishStateLabel;
    QLabel *taskLabel;
    QFrame *lineV, *lineH, *secondLineH, *secondLineV, *thirdLineH;

    QApplication *app;
    QLineEdit *chainLine;

    QRegExp *regExp;
    QRegExpValidator *regExpVal;
    QComboBox *startState;
    QComboBox *finishState;

    QStandardItemModel * modelComboBox;

    Machine *machine;

};

#endif // MAINWINDOW_H
