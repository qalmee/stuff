#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QGridLayout>


class AboutDialog : public QDialog
{
public:
    AboutDialog();
    AboutDialog(const QString &text);
    ~AboutDialog();
private:
    QGridLayout *layout;
    QLabel *one, *two;
};

#endif // ABOUTDIALOG_H
