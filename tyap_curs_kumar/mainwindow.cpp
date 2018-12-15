#include "mainwindow.h"
#include "regexpgenerator.h"
#include "chainsgenerator.h"
#include <QMessageBox>
#include <QSet>
#include <QTimer>
#include <QDebug>
#include <QMenuBar>
//#include <>

MainWindow::MainWindow(QApplication *app, QWidget *parent)
    : QMainWindow(parent), myApp(app)
{
    centralWidget = new CentralWidget();
    this->setCentralWidget(centralWidget);

    createActions();
    createMenus();

    connect(centralWidget->getGenerateRegExpButton(), &QPushButton::clicked, this, &MainWindow::generateRegExp);
    connect(centralWidget->getGenerateChainsButton(), &QPushButton::clicked, this, &MainWindow::generateChains);
}

MainWindow::~MainWindow()
{

}

void MainWindow::generateRegExp()
{
    auto alphabet = centralWidget->getAlphabet();
    auto startChain = centralWidget->getStartChain();
    auto endChain = centralWidget->getEndChain();
    auto symbolM = centralWidget->getSymbolM();
    auto mul = centralWidget->getMultiplicity();
    for (auto ch : startChain){
        if (!alphabet.contains(ch)){
            QMessageBox::warning(nullptr, "Ошибка", "Начальная подцепочка содержит не алфавитный символ");
            return;
        }
    }
    for (auto ch : endChain){
        if (!alphabet.contains(ch)){
            QMessageBox::warning(nullptr, "Ошибка", "Конечная подцепочка содержит не алфавитный символ");
            return;
        }
    }
    if (!alphabet.contains(symbolM)){
        QMessageBox::warning(nullptr, "Ошибка", "Кратный символ отсутсвует в алфавите");
        return;
    }
    if (mul == 0){
        centralWidget->setMultiplicity(1);
        mul = 1;
    }
    RegExpGenerator generator(alphabet, startChain,endChain, symbolM, mul);
    centralWidget->setRegExp(generator.generate());
}

void MainWindow::generateChains()
{
    QString copyRegExp = centralWidget->getRegExp();
    copyRegExp = RegExpGenerator::calculateRegExpForRPN(copyRegExp);
    ChainsGenerator *chainsGenerator =
            new ChainsGenerator(centralWidget->getMaxLen(), centralWidget->getMinLen(), copyRegExp);
    connect(chainsGenerator, &ChainsGenerator::resultReady, this, &MainWindow::setAnswer, Qt::ConnectionType::BlockingQueuedConnection);
    connect(chainsGenerator, &ChainsGenerator::finished, this, &MainWindow::check);
    connect(chainsGenerator, &ChainsGenerator::finished, chainsGenerator, &QObject::deleteLater);
    chainsGenerator->start();
}

void MainWindow::check()
{
    qDebug() << "check";
}

void MainWindow::setAnswer(QSet<QString> *ans, bool err, QString text)
{
    if (err){
        QMessageBox::warning(this, "Ошибка", text);
    }
    else {
        centralWidget->setChains(ans);
    }

}

void MainWindow::createActions()
{
    importFrom = new QAction("Загрузить из фала", this);
    importFrom->setStatusTip("Импортировать данные из файла в программу");
    connect(importFrom, &QAction::triggered, this, &MainWindow::importFromSlot);

    exportIn = new QAction("Выгрузить в файл", this);
    importFrom->setStatusTip("Экспортировать результат в файл");
    connect(exportIn, &QAction::triggered, this, &MainWindow::exportInSlot);

    about = new QAction("Об авторе", this);
    connect(about, &QAction::triggered, this, &MainWindow::aboutSlot);

    task = new QAction("Задание", this);
    connect(task, &QAction::triggered, this, &MainWindow::taskSlot);

    exitAct = new QAction("Выход", this);
    connect(exitAct, &QAction::triggered, myApp, &QApplication::quit);
}

void MainWindow::createMenus()
{
    file = menuBar()->addMenu("Файл");
    file->addAction(importFrom);
    file->addAction(exportIn);
    file->addSeparator();
    file->addAction(exitAct);

    help = menuBar()->addMenu("Помощь");
    help->addAction(task);
    help->addSeparator();
    help->addAction(about);
}

void MainWindow::importFromSlot(){

}
void MainWindow::exportInSlot(){

}
void MainWindow::aboutSlot(){

}
void MainWindow::taskSlot(){

}
