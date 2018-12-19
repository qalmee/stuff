#include "mainwindow.h"
#include "regexpgenerator.h"
#include "chainsgenerator.h"
#include <QMessageBox>
#include <QSet>
#include <QTimer>
#include <QDebug>
#include <QMenuBar>
#include <QFileDialog>
#include "aboutdialog.h"
#include <QTextCodec>
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
    aboutDialog = new AboutDialog();
    taskDialog = new AboutDialog();

}

MainWindow::~MainWindow(){

}

void MainWindow::generateRegExp()
{
    auto alphabet = centralWidget->getAlphabet();
    auto startChain = centralWidget->getStartChain();
    auto endChain = centralWidget->getEndChain();
    auto symbolM = centralWidget->getSymbolM();
    auto mul = centralWidget->getMultiplicity();
    for (auto ch : alphabet){
        if (ch == '*' || ch == '+' || ch == '(' || ch == ')' || ch == '&'){
            QMessageBox::warning(nullptr, "Ошибка", "Недопустимый символ в алфавите");
            return;
        }
    }
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
    int minLen = centralWidget->getMinLen();
    int maxLen = centralWidget->getMaxLen();
    if (maxLen < minLen){
        QMessageBox::warning(nullptr, "Ошибка", "Максимальная длина меньше минимальной");
        return;
    }
    if (centralWidget->getRegExp().isEmpty()){
        QMessageBox::warning(nullptr, "Ошибка", "Введено пустое РВ");
        return;
    }
    QString copyRegExp = centralWidget->getRegExp();
    copyRegExp = RegExpGenerator::calculateRegExpForRPN(copyRegExp);
    auto chainsGenerator = new ChainsGenerator(maxLen, minLen, copyRegExp);
    connect(chainsGenerator, &ChainsGenerator::resultReady, this, &MainWindow::setAnswer, Qt::ConnectionType::BlockingQueuedConnection);
    connect(chainsGenerator, &ChainsGenerator::finished, this, &MainWindow::check);
    connect(chainsGenerator, &ChainsGenerator::finished, chainsGenerator, &QObject::deleteLater);
    connect(chainsGenerator, &ChainsGenerator::finished, centralWidget, &CentralWidget::setGenerateButtonActive);
    centralWidget->setGenerateButtonDisabled();
    chainsGenerator->start();
}

void MainWindow::check()
{
    qDebug() << "check";
}

void MainWindow::setAnswer(QSet<QString> *ans, bool err, const QString &text)
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
    importFrom = new QAction(tr("Загрузить из файла"), this);
    importFrom->setStatusTip(tr("Импортировать данные из файла в программу"));
    connect(importFrom, &QAction::triggered, this, &MainWindow::importFromSlot);

    exportIn = new QAction(tr("Выгрузить в файл"), this);
    importFrom->setStatusTip(tr("Экспортировать результат в файл"));
    connect(exportIn, &QAction::triggered, this, &MainWindow::exportInSlot);

    about = new QAction(tr("Об авторе"), this);
    connect(about, &QAction::triggered, this, &MainWindow::aboutSlot);

    task = new QAction(tr("Задание"), this);
    connect(task, &QAction::triggered, this, &MainWindow::taskSlot);

    example = new QAction(tr("Показать пример"), this);
    connect(example, &QAction::triggered, this, &MainWindow::exampleSlot);

    exitAct = new QAction(tr("Выход"), this);
    connect(exitAct, &QAction::triggered, myApp, &QApplication::quit);
}

void MainWindow::createMenus()
{
    file = menuBar()->addMenu(tr("Файл"));
    file->addAction(importFrom);
    file->addAction(exportIn);
    file->addSeparator();
    file->addAction(exitAct);

    help = menuBar()->addMenu((QString::fromUtf8("Помощь")));
    help->addAction(task);
    help->addAction(example);
    help->addSeparator();
    help->addAction(about);
}

void MainWindow::importFromSlot(){
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Text (*.txt)");
    if (fileName.isEmpty()) return;
    QFile file(fileName);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream stream(&file);
    QString s;
    stream.readLine();
    centralWidget->setAlphabet(stream.readLine());
    stream.readLine();
    centralWidget->setStartChain(stream.readLine());
    stream.readLine();
    centralWidget->setEndChain(stream.readLine());
    stream.readLine();
    s = stream.readLine();
    if (s.size() > 1) s = "";
    centralWidget->setSymbolM(s);
    stream.readLine();
    centralWidget->setMultiplicity(stream.readLine().toInt());
    stream.readLine();
    centralWidget->setMinLen(stream.readLine().toInt());
    stream.readLine();
    centralWidget->setMaxLen(stream.readLine().toInt());
    file.close();

}
void MainWindow::exportInSlot(){
    QString fileName = QFileDialog::getSaveFileName(this, "Соханить файл", "", "Text (*.txt)");
    if (fileName.isEmpty()) return;
    QFile file(fileName);
    file.open(QFile::WriteOnly | QFile::Text);
    QTextStream stream(&file);
    stream<<tr("Aлфавит: ")<<endl<<centralWidget->getAlphabetString()<<endl;
    stream<<tr("Начальная подцепочка:")<<endl;
    stream<<centralWidget->getStartChain()<<endl;
    stream<<tr("Конечная подцепочка:")<<endl;
    stream<<centralWidget->getEndChain()<<endl;
    stream<<tr("Кратный символ:")<<endl;
    stream<<centralWidget->getSymbolM()<<endl;
    stream<<tr("Кратность:")<<endl;
    stream<<centralWidget->getMultiplicity()<<endl;
    stream<<tr("Минмальная длина цепочки:")<<endl;
    stream<<centralWidget->getMinLen()<<endl;
    stream<<tr("Максимальная длина цепочки:")<<endl;
    stream<<centralWidget->getMaxLen()<<endl;
    stream<<tr("Регулярное выражение:")<<endl;
    stream<<centralWidget->getRegExp()<<endl;
    stream<<centralWidget->getChains();
    file.close();
}
void MainWindow::aboutSlot(){

    aboutDialog->show();
}
void MainWindow::taskSlot(){

    QString s = "Вариант 10.\n";
    s += "Написать программу, которая по предложенному описанию языка\nпостроит ";
    s += "регулярное выражение, задающее этот язык,\nи сгенерирует с";
    s += "его помощью все цепочки языка в заданном диапазоне длин.\nПредусмотреть";
    s += "также возможность генерации цепочек по введённому пользователем";
    s += " РВ.\nЯзык задан так:\n";
    s += "Алфавит, заданные начальная и конечная подцепочки и\nкратность вхождения некоторого символа алфавита во все цепочки языка.";

    AboutDialog *dd = new AboutDialog(s);
    connect(dd, &AboutDialog::finished, dd, &AboutDialog::deleteLater);
    dd->show();
}

void MainWindow::exampleSlot()
{
    centralWidget->setAlphabet("a b");
    centralWidget->setStartChain("aa");
    centralWidget->setEndChain("ab");
    centralWidget->setSymbolM("a");
    centralWidget->setMultiplicity(2);
    centralWidget->setMinLen(0);
    centralWidget->setMaxLen(6);

}
