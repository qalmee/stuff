#include "mainwindow.h"
#include "regexpgenerator.h"
#include "chainsgenerator.h"
#include <QMessageBox>
#include <QSet>
#include <QTimer>
#include <QDebug>
//#include <>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    centralWidget = new CentralWidget();
    this->setCentralWidget(centralWidget);

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
