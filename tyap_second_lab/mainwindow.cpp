#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QApplication *a, QWidget *parent) :
    QMainWindow(parent), app(a)
{
    dialog = new CustomDialog(this);
    dialog->show();

    numberOfStates = 3;
    numberOfTerminals = 3;
    tableLayout = new QGridLayout;

    QLabel *statesAlphabetlabel = new QLabel("Состояния\\Алфавит");
    tableLayout->addWidget(statesAlphabetlabel, 0, 0);

    statesLines.reserve(numberOfStates);
    terminalsLines.reserve(numberOfTerminals);
    for (int i = 0; i < numberOfStates ; ++i)
    {
        QLineEdit *temp = new QLineEdit();
        statesLines.push_back(temp);
        tableLayout->addWidget(temp, i + 2, 0);
    }

    for (int i = 0; i < numberOfTerminals; ++i)
    {
        QLineEdit *temp = new QLineEdit();
        terminalsLines.push_back(temp);
        tableLayout->addWidget(temp, 0, i + 2);
    }

    QFrame *lineV = new QFrame;
    lineV->setFrameShape(QFrame::VLine);
    lineV->setFrameShadow(QFrame::Sunken);
    QFrame *lineH = new QFrame;
    lineH->setFrameShape(QFrame::HLine);
    lineH->setFrameShadow(QFrame::Sunken);
    tableLayout->addWidget(lineH, 1, 0, 1, numberOfTerminals + 2);
    tableLayout->addWidget(lineV, 0, 1, numberOfStates + 2, 1);


    statesValuesLines.reserve(numberOfStates);
    for (int i = 0; i < numberOfStates; ++i)
    {
        statesValuesLines.push_back(QVector<QLineEdit*>(numberOfTerminals));
        for (int j = 0; j < numberOfTerminals; ++j)
        {
            QLineEdit *temp = new QLineEdit();
            statesValuesLines[i].push_back(temp);
            tableLayout->addWidget(temp, i + 2, j + 2);
        }
    }

    QLabel *chainLabel = new QLabel ("Введите цепочку:");
    chainLine = new QLineEdit();
    checkChainButton = new QPushButton ("Проверить цепочку");
    chainLayout = new QVBoxLayout;

    chainLayout->addWidget(chainLabel);
    chainLayout->addWidget(chainLine);
    chainLayout->addWidget(checkChainButton);

    tableLayout->addLayout(chainLayout, numberOfStates + 3, 1, 3, numberOfTerminals + 1);

    QWidget *window = new QWidget();
    window->setLayout(tableLayout);
    setCentralWidget(window);

    QObject::connect(dialog, &CustomDialog::finished, this, &MainWindow::okDialog);
    QObject::connect(dialog, &CustomDialog::canceled, this, &MainWindow::cancelDialog);
    QObject::connect(checkChainButton, &QPushButton::clicked, this, &MainWindow::checkChainSlot);
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
void MainWindow::checkChainSlot()
{
    for (int i = 0; i < numberOfTerminals; ++i)
    {
        terminals.push_back(terminalsLines[i]->text());
    }

    for (int i = 0; i < numberOfStates; ++i)
    {
        statesNames.push_back(statesLines[i]->text());
    }

    for (int i = 0; i < numberOfStates; ++i)
    {
        statesValues.push_back(QVector<QString>(numberOfTerminals));

        for (int j = 0; j < numberOfTerminals; ++j)
        {
            statesValues[i].push_back(statesValuesLines[i][j]->text());
        }
    }

    chainString = chainLine->text();

}
