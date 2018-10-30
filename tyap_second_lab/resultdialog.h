#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include <QDialog>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>

class ResultDialog : public QDialog
{
    Q_OBJECT
public:
    ResultDialog();

public slots:
    void setInformation(QString message,  QVector <QPair<QString, QChar>> *result, QString chain);

private:
    void constructStuff();

    QGridLayout *layout;
    QTextEdit *result;
    QLineEdit *chain;
    QLabel *resultMessage;
};

#endif // RESULTDIALOG_H
