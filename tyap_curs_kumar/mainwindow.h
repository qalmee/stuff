#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "centralwidget.h"
#include "chainsgenerator.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void generateRegExp();
    void generateChains();
    void check();
    void setAnswer(QSet<QString> *ans, bool err, QString text);
private:
    CentralWidget *centralWidget;
};

#endif // MAINWINDOW_H
