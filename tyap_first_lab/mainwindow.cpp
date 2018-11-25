#include "mainwindow.h"
#include "chainbuilder.h"
#include <QDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->parent = nullptr;
    setGeometry(200, 200, 800,600);
    wholeLayout = new QHBoxLayout;
    leftUpLayout = new QVBoxLayout;
    leftDownLayout = new QVBoxLayout;
    leftLayout = new QVBoxLayout;
    rightLayout = new QVBoxLayout;
    createdEarlier = false;

    grammarWidget = new Grammar();
    refreshGrammarButton = new QPushButton("Обновить");

    showHistoryButton = new QPushButton("Показать преобразования");

    words = new QTextEdit();

    leftUpLayout->addWidget(grammarWidget);
    leftUpLayout->addWidget(refreshGrammarButton);

    leftLayout->addLayout(leftUpLayout, 20);
    leftLayout->addLayout(leftDownLayout, 80);

    wholeLayout->addLayout(leftLayout, 70);
    wholeLayout->addLayout(rightLayout, 30);
    rightLayout->addWidget(words);
    rightLayout->addWidget(showHistoryButton);

    QWidget *window = new QWidget();
    window->setLayout(wholeLayout);
    setCentralWidget(window);

    historyDialog = new HistoryDialog();

    connect(refreshGrammarButton, SIGNAL(clicked()), this, SLOT(rulesRefresherSlot()));
    connect(showHistoryButton, &QPushButton::clicked, this, &MainWindow::showHistorySlot);
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

    rulesWidget = new Rules(amountOfRules);
    refreshRulesButton = new QPushButton("Построить цепочки");
    connect(refreshRulesButton, &QPushButton::clicked, this, &MainWindow::build);
    rulesScrollArea->setWidget(rulesWidget);
    leftDownLayout->addWidget(rulesScrollArea);
    leftDownLayout->addWidget(refreshRulesButton);
    createdEarlier = true;
    rulesWidget->resize(540, rulesWidget->height());

    qDebug() << rulesWidget->size() << " " << refreshRulesButton->size() << endl;

}

void MainWindow::build()
{
    if (parent != nullptr) delete parent;
    ChainBuilder chainBuilder;
    auto data = rulesWidget->getChainsVector();
    qDebug()<<rulesWidget->getTargetSymbolIndex()<<endl;
    auto result = chainBuilder.solve(rulesWidget->getTargetSymbolIndex(), std::make_pair(grammarWidget->getMinLength(), grammarWidget->getMaxLength()), &data);
    words->clear();
    for (auto str : *result){
        words->append("\"" + QString::fromUtf8(str.c_str()) + "\" : " + QString::number(str.size()) + "\n");
    }
    parent = chainBuilder.getParent();
}

void MainWindow::showHistorySlot()
{
    if (parent == nullptr) return;
    historyDialog->setParent(parent);
    historyDialog->show();
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

