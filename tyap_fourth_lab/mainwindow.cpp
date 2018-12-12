#include "mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    statesLabel = new QLabel("Множество состояний:");
    finishStatesLabel = new QLabel("Множество кон. состояний:");
    inputAlphabetLabel = new QLabel("Входной алфавит:");
    stackAlphabetLabel = new QLabel("Алфавит стека:");
    chainLabel = new QLabel("Цепочки для проверки:");
    startStateLabel = new QLabel("Начальное состояние:");
    emptySymbolLabel = new QLabel("Пустой символ:");
    startStackLabel = new QLabel("Начальный стек:");
    machineLabel = new QLabel("Автомат:");
    outputLabel = new QLabel("Вывод:");
    translateLabel = new QLabel("Алфавит перевода:");

    statesLine = new QLineEdit;
    finishStatesLine = new QLineEdit;
    inputAlphabetLine = new QLineEdit;
    stackAlphabetLine = new QLineEdit;
    chainLine = new QTextEdit;
    startStateLine = new QLineEdit;
    emptySymbolLine = new QLineEdit("&");
    startStackLine = new QLineEdit;
    translateAlphabet = new QLineEdit();

    emptySymbolLine->setReadOnly(true);

    machineTextEdit = new QTextEdit;
    outputTextEdit = new QTextEdit;

    checkChainButton = new QPushButton("Начать проверку");
    import = new QPushButton("Загрузить из файла");

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
    inputLayout->addWidget(chainLine, 4, 1, 2, 1);
    inputLayout->addWidget(translateLabel, 0, 2);
    inputLayout->addWidget(translateAlphabet, 0, 3);
    inputLayout->addWidget(startStateLabel, 1, 2);
    inputLayout->addWidget(emptySymbolLabel, 2, 2);
    inputLayout->addWidget(startStackLabel, 3, 2);
    inputLayout->addWidget(startStateLine, 1, 3);
    inputLayout->addWidget(emptySymbolLine, 2, 3);
    inputLayout->addWidget(startStackLine, 3, 3);
    inputLayout->addWidget(checkChainButton, 4, 3);
    inputLayout->addWidget(import, 5, 3);

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
    QObject::connect(import, &QPushButton::clicked, this, &MainWindow::readFromFile);
}

MainWindow::~MainWindow()
{
}

void MainWindow::checkChainSlot()
{
    Parser *parser = new Parser();
    this->outputTextEdit->clear();
    auto list = chainLine->toPlainText().split("\n", QString::SkipEmptyParts);
    try {
        parser->parseStates(statesLine->text());
        parser->setStartState(startStateLine->text());
        parser->parseFinishStates(finishStatesLine->text());
        parser->parseInputAlphabet(inputAlphabetLine->text());
        parser->parseStackAlphabet(stackAlphabetLine->text());
        parser->setEmptySymbol(emptySymbolLine->text().at(0));
        parser->setStack(startStackLine->text());
        parser->parseTranslateAlphabet(translateAlphabet->text());
        parser->parseMachineRules(machineTextEdit->toPlainText());
    } catch (std::runtime_error *err) {
        QMessageBox::warning(nullptr, "Warning", err->what());
        delete parser;
        return;
    }
    bool wasCathed = false;
    std::string errMessage;
    Machine *machine;
    for (int qwe = 0; qwe<list.size(); qwe++){
        try{
            wasCathed = false;
            machine = new Machine(parser->getMap());
            parser->parseChain(list.at(qwe), qwe + 1);
            machine->setChain(list.at(qwe));
            machine->setStack(this->startStackLine->text());
            machine->setStartState(this->startStateLine->text());
            machine->setEmptySymbol(this->emptySymbolLine->text().at(0));
            machine->setFinishStates(parser->getFinishStates());
            machine->run();
        }catch (std::runtime_error *err){
            wasCathed = true;
            errMessage = err->what();
        }

        int i = 0, j = 1;
        QString chain = list.at(qwe);
        auto answer = *(machine->getAns());
        this->outputTextEdit->append("Цепочка для проверки: " + chain);
        for (auto x : answer){
            this->outputTextEdit->append("(" + x.state + ", " + chain + ", " + x.stack + x.translated + ")|-" +
                                         (i < machine->getRuleSeq()->size() ? QString::number(machine->getRuleSeq()->at(i++)) : ""));
            if (answer.size() > j && !answer[j].isEmptySymbol && chain.size()) chain.remove(0, 1);
            j++;
        }

        if (wasCathed){
            outputTextEdit->append(QString::fromStdString(errMessage));
        }else{
            outputTextEdit->append("Успешно");
        }

        outputTextEdit->append("\n");
        delete machine;

    }

    delete parser;
}

void MainWindow::readFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Images (*.txt)");
    QFile file(fileName);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream stream(&file);
    machineTextEdit->clear();
    while (!stream.atEnd())
        machineTextEdit->append(stream.readLine());

}
