#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setGeometry(200, 200, 800,600);
    wholeLayout = new QHBoxLayout;
    leftUpLayout = new QVBoxLayout;
    leftDownLayout = new QVBoxLayout;
    leftLayout = new QVBoxLayout;
    rightLayout = new QVBoxLayout;
    createdEarlier = false;

    grammarWidget = new Grammar();
    refreshGrammarButton = new QPushButton("Обновить");

    QTextEdit *words = new QTextEdit();

    leftUpLayout->addWidget(grammarWidget);
    leftUpLayout->addWidget(refreshGrammarButton);
    leftLayout->addLayout(leftUpLayout, 33);
    leftLayout->addLayout(leftDownLayout, 66);

    wholeLayout->addLayout(leftLayout, 33);
    wholeLayout->addLayout(rightLayout, 66);
    rightLayout->addWidget(words);

    QWidget *window = new QWidget();
    window->setLayout(wholeLayout);
    setCentralWidget(window);

    connect(refreshGrammarButton, SIGNAL(clicked()), this, SLOT(rulesRefresherSlot()));
}

MainWindow::~MainWindow()
{}

void MainWindow::Initialization()
{

}

void MainWindow::rulesRefresherSlot()
{
    clearLayout(leftDownLayout, createdEarlier);
    Rules *rulesWidget;

    amountOfRules = grammarWidget->getAmountOfUnterminal();
    minLength = grammarWidget->getMinLength();
    maxLength = grammarWidget->getMaxLength();
    amountOfTerminal = grammarWidget->getAmountOfTerminal();

    qDebug() << amountOfRules << " " << minLength << " " << maxLength << " " << amountOfTerminal << endl;

    rulesWidget = new Rules(amountOfRules);
    refreshRulesButton = new QPushButton("Построить цепочки");
    leftDownLayout->addWidget(rulesWidget, 60);
    leftDownLayout->addWidget(refreshRulesButton);
    createdEarlier = true;
}

void MainWindow::clearLayout(QLayout * layout, bool deleteWidgets)
{
    while(QLayoutItem * item = layout->takeAt(0))
    {
        if(deleteWidgets)
        {
            if(QWidget * widget = item->widget())
            {
                widget->deleteLater();
            }
            if (QLayout * childLayout = item->layout())
            {
                clearLayout(childLayout, deleteWidgets);
            }
            delete item;
        }
    }
}

