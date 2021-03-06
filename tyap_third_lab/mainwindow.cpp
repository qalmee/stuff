#include "mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    statesLabel = new QLabel("Множество состояний:");
    finishStatesLabel = new QLabel("Множество кон. состояний:");
    inputAlphabetLabel = new QLabel("Входной алфавит:");
    stackAlphabetLabel = new QLabel("Алфавит стека:");
    chainLabel = new QLabel("Цепочка для проверки:");
    startStateLabel = new QLabel("Начальное состояние:");
    emptySymbolLabel = new QLabel("Пустой символ:");
    startStackLabel = new QLabel("Начальный стек:");
    machineLabel = new QLabel("Автомат:");
    outputLabel = new QLabel("Вывод:");

    statesLine = new QLineEdit;
    finishStatesLine = new QLineEdit;
    inputAlphabetLine = new QLineEdit;
    stackAlphabetLine = new QLineEdit;
    chainLine = new QLineEdit;
    startStateLine = new QLineEdit;
    emptySymbolLine = new QLineEdit("&");
    startStackLine = new QLineEdit;

    emptySymbolLine->setReadOnly(true);

    machineTextEdit = new QTextEdit;
    outputTextEdit = new QTextEdit;

    checkChainButton = new QPushButton("Начать проверку");

    inputLayout = new QGridLayout;

    inputLayout->addWidget(statesLabel, 0, 0);
    inputLayout->addWidget(finishStatesLabel, 1, 0);
    inputLayout->addWidget(inputAlphabetLabel, 2, 0);
    inputLayout->addWidget(stackAlphabetLabel, 3, 0);
    inputLayout->addWidget(chainLabel, 4, 0);
    inputLayout->addWidget(statesLine, 0, 1);
    inputLayout->addWidget(finishStatesLine, 1,1);
    inputLayout->addWidget(inputAlphabetLine, 2, 1);
    inputLayout->addWidget(stackAlphabetLine, 3, 1);
    inputLayout->addWidget(chainLine, 4, 1);
    inputLayout->addWidget(startStateLabel, 0, 2);
    inputLayout->addWidget(emptySymbolLabel, 1, 2);
    inputLayout->addWidget(startStackLabel, 2, 2);
    inputLayout->addWidget(startStateLine, 0, 3);
    inputLayout->addWidget(emptySymbolLine, 1, 3);
    inputLayout->addWidget(startStackLine, 2, 3);
    inputLayout->addWidget(checkChainButton, 4, 3);

    machineLayout = new QVBoxLayout;
    outputLayout = new QVBoxLayout;
    textEditsLayout = new QHBoxLayout;
    wholeLayout = new QVBoxLayout;

    machineLayout->addWidget(machineLabel);
    machineLayout->addWidget(machineTextEdit);
    outputLayout->addWidget(outputLabel);
    outputLayout->addWidget(outputTextEdit);
    textEditsLayout->addLayout(machineLayout);
    textEditsLayout->addLayout(outputLayout);
    wholeLayout->addLayout(inputLayout);
    wholeLayout->addLayout(textEditsLayout);

    window = new QWidget();
    setCentralWidget(window);
    window->setLayout(wholeLayout);


    QObject::connect(checkChainButton, &QPushButton::clicked, this,  &MainWindow::checkChainSlot);
}

MainWindow::~MainWindow()
{
}

void MainWindow::checkChainSlot()
{
    Parser *parser = new Parser();
    this->outputTextEdit->clear();
    try {
        parser->parseStates(statesLine->text());
        parser->setStartState(startStateLine->text());
        parser->parseFinishStates(finishStatesLine->text());
        parser->parseInputAlphabet(inputAlphabetLine->text());
        parser->parseStackAlphabet(stackAlphabetLine->text());
        parser->setEmptySymbol(emptySymbolLine->text().at(0));
        parser->setStack(startStackLine->text());
        parser->setChain(chainLine->text());
        parser->parseMachineRules(machineTextEdit->toPlainText());
    } catch (std::runtime_error *err) {
        QMessageBox::warning(nullptr, "Warning", err->what());
        delete parser;
        return;
    }
    Machine machine(parser->getMap());
    machine.setChain(this->chainLine->text());
    machine.setStack(this->startStackLine->text());
    machine.setStartState(this->startStateLine->text());
    machine.setEmptySymbol(this->emptySymbolLine->text().at(0));
    machine.setFinishStates(parser->getFinishStates());

    bool wasCathed = false;
    try {
        machine.run();
    } catch (std::runtime_error *err) {
        wasCathed = true;
        QMessageBox::warning(nullptr, "Warning", err->what());
    }
    if (!wasCathed){
        QMessageBox::information(nullptr, "Ок", "Завершено успешно");
    }

    int i = 0, j = 1;

    QString chain = chainLine->text();
    auto answer = *(machine.getAns());
    for (auto x : answer){
        this->outputTextEdit->append("(" + x.state + ", " + chain + ", "+ x.stack + ")|-" +
                                     (i < machine.getRuleSeq()->size() ? QString::number(machine.getRuleSeq()->at(i++)) : ""));
        if (answer.size() > j && !answer[j].isEmptySymbol && chain.size()) chain.remove(0, 1);
        j++;
    }
    delete parser;
}
