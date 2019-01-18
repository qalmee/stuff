#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>

class CustomDialog : public QDialog
{
    Q_OBJECT
public:
    CustomDialog(QWidget *parent = nullptr);
    virtual ~CustomDialog();
    bool checkFinalChain();
    void statesFilling();

public slots:
    void okPressed();
    void cancelPressed();
    void clear();
    void checkAlphabetSlot();

signals:
    void finished(int numberOfStates, int numberOfTerminals, QVector <QVector<QString>> states,
                  QVector<QString> terminals, QString finalChain, int mulTimes, QString mulSymbol, int finalState);
    void canceled();

private:
    QGridLayout *layout;
    QGridLayout *buttons;
    QLabel *alphabetLabel, *finalChainLabel, *mulSymbolLabel, *mulTimesLabel;
    QLineEdit *alphabetLine, *finalChainLine, *mulTimesLine;
    QComboBox *mulSymbolBox;
    QPushButton *ok, *cancel;
    QVector <QString> alphabet;
    QString finalChain, mulSymbol;
    int numberOfStates, numberOfTerminals, mulTimes, finalState;
    QVector<QVector<QString>> states;


};

#endif // CUSTOMDIALOG_H
