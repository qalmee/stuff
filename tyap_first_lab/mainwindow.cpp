#include "mainwindow.h"
#include "chainbuilder.h"
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

    words = new QTextEdit();

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
    QScrollArea *rulesScrollArea = new QScrollArea;

    amountOfRules = grammarWidget->getAmountOfUnterminal();
    minLength = grammarWidget->getMinLength();
    maxLength = grammarWidget->getMaxLength();
    //amountOfTerminal = grammarWidget->getAmountOfTerminal();


    rulesWidget = new Rules(amountOfRules);
    refreshRulesButton = new QPushButton("Построить цепочки");
    connect(refreshRulesButton, &QPushButton::clicked, this, &MainWindow::build);
    rulesScrollArea->setWidget(rulesWidget);
    leftDownLayout->addWidget(rulesScrollArea);
    leftDownLayout->addWidget(refreshRulesButton);
    createdEarlier = true;

    qDebug() << amountOfRules << " " << minLength << " " << maxLength << endl;

}

void MainWindow::build()
{
    ChainBuilder chainBuilder;
    auto data = rulesWidget->getChainsVector();
    auto result = chainBuilder.solve(rulesWidget->getTargetSymbolIndex(), std::make_pair(minLength, maxLength), &data);
    words->clear();
    QString str;
    for (auto str : *result){
        words->append(QString::fromUtf8(str.c_str()) + "\n");
    }
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

