#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    numberOfStatesLabel = new QLabel("Множество состояний:");
    numberOfFinishStatesLabel = new QLabel("Множество кон. состояний:");
    inputAlphabetLabel = new QLabel("Входной алфавит:");
    stackAlphabetLabel = new QLabel("Алфавит стека:");
    chainLabel = new QLabel("Цепочка для проверки:");
    startStateLabel = new QLabel("Начальное состояние:");
    emptySymbolLabel = new QLabel("Пустой символ:");
    startStackLabel = new QLabel("Начальный стек:");
    machineLabel = new QLabel("Автомат:");
    outputLabel = new QLabel("Вывод:");

    numberOfStatesLine = new QLineEdit;
    numberOfFinishStatesLine = new QLineEdit;
    inputAlphabetLine = new QLineEdit;
    stackAlphabetLine = new QLineEdit;
    chainLine = new QLineEdit;
    startStateLine = new QLineEdit;
    emptySymbolLine = new QLineEdit;
    startStackLine = new QLineEdit;

    machineTextEdit = new QTextEdit;
    outputTextEdit = new QTextEdit;

    checkChainButton = new QPushButton("Начать проверку");

    inputLayout = new QGridLayout;

    inputLayout->addWidget(numberOfStatesLabel, 0, 0);
    inputLayout->addWidget(numberOfFinishStatesLabel, 1, 0);
    inputLayout->addWidget(inputAlphabetLabel, 2, 0);
    inputLayout->addWidget(stackAlphabetLabel, 3, 0);
    inputLayout->addWidget(chainLabel, 4, 0);
    inputLayout->addWidget(numberOfStatesLine, 0, 1);
    inputLayout->addWidget(numberOfFinishStatesLine, 1,1);
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
}

MainWindow::~MainWindow()
{
}
