#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "centralwidget.h"
#include "chainsgenerator.h"
#include <QMenu>
#include <QAction>
#include <QApplication>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QApplication *app, QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void generateRegExp();
    void generateChains();
    void check();
    void setAnswer(QSet<QString> *ans, bool err, QString text);

    void importFromSlot();
    void exportInSlot();
    void aboutSlot();
    void taskSlot();
private:
    void createActions();
    void createMenus();
    CentralWidget *centralWidget;
    QMenu *help, *file;
    QAction *importFrom, *exportIn, *about, *task, *exitAct;
    QApplication *myApp;
};

#endif // MAINWINDOW_H
