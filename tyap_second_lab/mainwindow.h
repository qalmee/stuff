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

signals:
    void badInput();    

private:

    void prepareView();
    CustomDialog *dialog;
    int numberOfStates;
    int numberOfTerminals;
    QString chainString;

    QVector <QString> statesNames;
    QVector <QString> terminals;
    QVector <QVector<QString>> statesValues;

    QVBoxLayout *wholeLayout;
    QVBoxLayout *chainLayout;
    QGridLayout *tableLayout;

    QVector <QLineEdit*> terminalsLines;
    QVector <QLineEdit*> statesLines;
    QVector <QVector <QLineEdit*>> statesValuesLines;

    QPushButton *checkChainButton;
    QPushButton *returnToDialogButton;

    QWidget *window;
    QLabel *chainLabel;

    QFrame *lineV, *lineH, *secondLineH;

    QApplication *app;
    QLineEdit *chainLine;

};

#endif // MAINWINDOW_H
