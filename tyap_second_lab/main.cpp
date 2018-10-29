#include "mainwindow.h"
#include <QApplication>
#include <QLine>
#include "QSplitter"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(&a);
    //w.show();

    return a.exec();
}
