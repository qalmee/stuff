#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class CustomDialog : public QDialog
{
    Q_OBJECT
public:
    CustomDialog();
    virtual ~CustomDialog();

public slots:
    void okPressed();
    void cancelPressed();
signals:
    void finished(int numberOfStates, int numberOfTerminals);
    void canceled();

private:
    QGridLayout *layout;
    QGridLayout *buttons;
    QLabel *numberOfStatesLabel, *numberOfTerminalsLabel;
    QLineEdit *numberOfStates, *numberOfTerminals;
    QPushButton *ok, *cancel;
};

#endif // CUSTOMDIALOG_H
