#include "mainwindow.h"
#include <QApplication>
#include <QLine>
#include "QSplitter"
#include "machine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(&a);
    //w.show();
    return a.exec();
}
