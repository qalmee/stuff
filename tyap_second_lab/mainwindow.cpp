#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSet>
#include <QMessageBox>

MainWindow::MainWindow(QApplication *a, QWidget *parent) :
    QMainWindow(parent), app(a)
{
    dialog = new CustomDialog(this);
    dialog->show();

    tableLayout = new QGridLayout;
    window = new QWidget();
    setCentralWidget(window);
    window->setLayout(tableLayout);

    QLabel *statesAlphabetlabel = new QLabel("Состояния\\Алфавит");
    tableLayout->addWidget(statesAlphabetlabel, 0, 0);

    lineV = new QFrame;
    lineV->setFrameShape(QFrame::VLine);
    lineV->setFrameShadow(QFrame::Sunken);
    lineH = new QFrame;
    lineH->setFrameShape(QFrame::HLine);
    lineH->setFrameShadow(QFrame::Sunken);
    secondLineH = new QFrame;
    secondLineH->setFrameShape(QFrame::HLine);
    secondLineH->setFrameShadow(QFrame::Sunken);
    secondLineH->setLineWidth(2);

    secondLineV = new QFrame;
    secondLineV->setFrameShape(QFrame::VLine);
    secondLineV->setFrameShadow(QFrame::Sunken);
    secondLineV->setLineWidth(2);

    thirdLineH = new QFrame;
    thirdLineH->setFrameShape(QFrame::HLine);
    thirdLineH->setFrameShadow(QFrame::Plain);
    thirdLineH->setLineWidth(2);



    chainLabel = new QLabel ("Введите цепочку:");
    chainLine = new QLineEdit();
    checkChainButton = new QPushButton ("Проверить цепочку");
    chainLayout = new QVBoxLayout;
    returnToDialogButton = new QPushButton("Вернуться к условию");


    startStateLabel = new QLabel("Начальное состояние:");
    finishStateLabel = new QLabel("Конечное состояние:");
    startState = new QComboBox();
    finishState = new QComboBox();

    QObject::connect(dialog, &CustomDialog::finished, this, &MainWindow::okDialog);
    QObject::connect(dialog, &CustomDialog::canceled, this, &MainWindow::cancelDialog);
    QObject::connect(checkChainButton, &QPushButton::clicked, this, &MainWindow::checkChainSlot);
    QObject::connect(returnToDialogButton, &QPushButton::clicked, this, &MainWindow::returnToDialogSlot);
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
    this->prepareView();
    this->show();
}

void MainWindow::checkChainSlot()
{
    QSet<QString> terminalsSet, statesNamesSet;
    for (int i = 0; i < numberOfTerminals; ++i)
    {
        terminalsSet.insert(terminalsLines[i]->text());
        terminals.push_back(terminalsLines[i]->text());
    }

    for (int i = 0; i < numberOfStates; ++i)
    {
        statesNamesSet.insert(statesLines[i]->text());
        statesNames.push_back(statesLines[i]->text());
    }
    if (terminalsSet.size() != terminals.size() || statesNamesSet.size() != statesNames.size()
            || terminalsSet.contains("") || statesNamesSet.contains("")){
        this->badInputSlot();
        return;
    }

    for (int i = 0; i < numberOfStates; ++i)
    {
        statesValues.push_back(QVector<QString>());

        for (int j = 0; j < numberOfTerminals; ++j)
        {
            if (!statesNamesSet.contains(statesValuesLines[i][j]->text())){
                this->badInputSlot();
                return;
            }
            statesValues[i].push_back(statesValuesLines[i][j]->text());
        }
    }
    chainString = chainLine->text();


}

void MainWindow::badInputSlot()
{
    QMessageBox::warning(this, "Ошибка", "Что-то не так в вашем вводе");
}

void MainWindow::returnToDialogSlot()
{
    this->hide();
    dialog->show();
}

void MainWindow::prepareView()
{
    for (auto &x : statesLines)
        delete x;
    for (auto &x : terminalsLines)
        delete x;
    statesLines.clear();
    terminalsLines.clear();
    for (auto &v : statesValuesLines){
        for (auto &x : v){
            delete x;
        }
    }
    statesValuesLines.clear();
    statesLines.reserve(numberOfStates);
    for (int i = 0; i < numberOfStates ; ++i)
    {
        QLineEdit *temp = new QLineEdit();
        temp->setMaximumWidth(150);
        statesLines.push_back(temp);
        tableLayout->addWidget(temp, i + 2, 0);
        QObject::connect(temp, &QLineEdit::textChanged, this, &MainWindow::checkStatesSlot);

    }

    terminalsLines.reserve(numberOfTerminals);
    for (int i = 0; i < numberOfTerminals; ++i)
    {
        QLineEdit *temp = new QLineEdit();
        temp->setMaximumWidth(60);
        terminalsLines.push_back(temp);
        tableLayout->addWidget(temp, 0, i + 2);
    }

    statesValuesLines.reserve(numberOfStates);
    for (int i = 0; i < numberOfStates; ++i)
    {
        statesValuesLines.push_back(QVector<QLineEdit*>(numberOfTerminals));
        for (int j = 0; j < numberOfTerminals; ++j)
        {
            QLineEdit *temp = new QLineEdit();
            temp->setMaximumWidth(60);
            statesValuesLines[i].push_back(temp);
            tableLayout->addWidget(temp, i + 2, j + 2);
        }
    }

    tableLayout->addWidget(startStateLabel, numberOfStates + 3, 0);
    tableLayout->addWidget(startState, numberOfStates + 4, 0);
    tableLayout->addWidget(finishStateLabel, numberOfStates + 5, 0);
    tableLayout->addWidget(finishState, numberOfStates + 6, 0);

    tableLayout->addWidget(chainLabel, numberOfStates + 3, 2, 1, numberOfTerminals + 1);
    tableLayout->addWidget(chainLine, numberOfStates + 4, 2, 1, numberOfTerminals + 1);
    tableLayout->addWidget(checkChainButton, numberOfStates + 5, 2, 1, numberOfTerminals + 1);

    tableLayout->addWidget(secondLineV, numberOfStates + 2, 1, 6, 1);
    tableLayout->addWidget(secondLineH, numberOfStates + 6, 1, 1, numberOfTerminals + 1);
    tableLayout->addWidget(thirdLineH, numberOfStates + 2, 0, 1, numberOfTerminals+2);

    tableLayout->addWidget(returnToDialogButton, numberOfStates + 7, 2, 1, numberOfTerminals);


    tableLayout->addWidget(lineH, 1, 0, 1, numberOfTerminals + 2);
    tableLayout->addWidget(lineV, 0, 1, numberOfStates + 2, 1);
}

void MainWindow::checkStatesSlot()
{
    bool allEntered = true;
    for (int i = 0; i < numberOfStates; ++i)
    {
        if(statesLines[i]->text().isEmpty()) allEntered = false;
    }
    if (allEntered)
    {
        startState->clear();
        finishState->clear();
        for (int i = 0; i < numberOfStates; ++i)
        {
            startState->addItem(statesLines[i]->text());
            finishState->addItem(statesLines[i]->text());
        }

        startStateLabel->show();
        startState->show();
        finishStateLabel->show();
        finishState->show();
    }
}
