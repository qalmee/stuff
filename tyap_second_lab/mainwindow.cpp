#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QApplication *a, QWidget *parent) :
    QMainWindow(parent), app(a)
{
    dialog = new CustomDialog(this);
    dialog->show();

    tableLayout = new QGridLayout;

    QLabel *statesAlphabetlabel = new QLabel("Состояния\\Алфавит");
    tableLayout->addWidget(statesAlphabetlabel, 0, 0);

    statesLines.reserve(numberOfStates);
    terminalsLines.reserve(numberOfTerminals);
    for (int i = 0; i < numberOfStates ; ++i)
    {
        QLineEdit *temp = new QLineEdit();
        statesLines.push_back(temp);
        tableLayout->addWidget(temp, i + 1, 0);
    }

    for (int i = 0; i < numberOfTerminals; ++i)
    {
        QLineEdit *temp = new QLineEdit();
        terminalsLines.push_back(temp);
        tableLayout->addWidget(temp, 0, i + 1);
    }

    statesValuesLines.reserve(numberOfStates);
    for (int i = 0; i < numberOfStates; ++i)
    {
        statesValuesLines.push_back(QVector<QLineEdit*>(numberOfTerminals));
        for (int j = 0; j < numberOfTerminals; ++j)
        {
            QLineEdit *temp = new QLineEdit();
            statesValuesLines[i].push_back(temp);
            tableLayout->addWidget(temp, i + 1, j + 1);
        }
    }

    QLabel *chainLabel = new QLabel ("Введите цепочку:");
    chain = new QLineEdit();
    checkChainButton = new QPushButton ("Проверить цепочку");
    chainLayout = new QVBoxLayout;

    chainLayout->addWidget(chainLabel);
    chainLayout->addWidget(chain);
    chainLayout->addWidget(checkChainButton);

    tableLayout->addLayout(chainLayout, numberOfStates + 2, 1, 3, numberOfTerminals + 1);

    QWidget *window = new QWidget();
    window->setLayout(tableLayout);
    setCentralWidget(window);

    connect(dialog, &CustomDialog::finished, this, &MainWindow::okDialog);
    connect(dialog, &CustomDialog::canceled, this, &MainWindow::cancelDialog);
}

MainWindow::~MainWindow()
{
}

void MainWindow::cancelDialog()
{
    app->quit();
}

void MainWindow::okDialog(int numberOfStates, int numberOfTerminals)
{
    this->numberOfStates = numberOfStates;
    this->numberOfTerminals = numberOfTerminals;
    this->dialog->hide();
    this->dialog->clear();
    this->show();
}
