#include "startmenu.h"

StartMenu::StartMenu(ChessBoard *chessBoard, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartMenu)
    , chessBoard(chessBoard)
    , stockfishEngine(new StockfishEngine(this))
{
    ui->setupUi(this);
    connect(ui->level1Button, &QPushButton::clicked, this, &StartMenu::level1Start);
    connect(ui->level2Button, &QPushButton::clicked, this, &StartMenu::level2Start);
    connect(ui->level3Button, &QPushButton::clicked, this, &StartMenu::level3Start);
    connect(ui->vsComputerButton, &QPushButton::clicked, this, &StartMenu::vsComputerStart);
    connect(ui->QuitButton, &QPushButton::clicked, this, &StartMenu::quitButtonClicked);

    QVBoxLayout *layout = new QVBoxLayout;
    ui->chessBoardContainer->setLayout(layout);
    layout->addWidget(chessBoard);
    ui->chessBoardContainer->hide();
    ui->QuitButton->hide();
}

StartMenu::~StartMenu()
{
    delete ui;
}

void StartMenu::stockfishStart() {
    // Set up stockfish
    QString basePath = QCoreApplication::applicationDirPath();
    QString stockfishPath = QCoreApplication::applicationDirPath() + "/../../../stockfish.exe";

    stockfishEngine->startEngine(stockfishPath);

    // Can only connect to stockfish through slots or lambda expressions.
    connect(stockfishEngine, &StockfishEngine::engineOutput, this, [](const QString &output) {
        // qDebug() << "STOCKFISH SAYS:" << output;
    });
}

void StartMenu::level1Start() {
    showChessBoard();
    ui->Title->setText("Level 1: Checkmate Name");
    stockfishStart();
}

void StartMenu::level2Start() {
    showChessBoard();
    ui->Title->setText("Level 2: Checkmate Name");
    stockfishStart();

}

void StartMenu::level3Start() {
    showChessBoard();
    ui->Title->setText("Level 3: Checkmate Name");
    stockfishStart();

}

void StartMenu::vsComputerStart() {
    showChessBoard();
    ui->Title->setText("VS Computer");
    stockfishStart();
}

void StartMenu::quitButtonClicked() {
    hideChessBoard();
    if (stockfishEngine) {
        stockfishEngine->terminateEngine();
    }
}

void StartMenu::hideChessBoard() {
    ui->chessBoardContainer->hide();
    ui->QuitButton->hide();

    ui->LevelsLabel->show();
    ui->level1Button->show();
    ui->level2Button->show();
    ui->level3Button->show();

    ui->GameModeLabel->show();
    ui->vsComputerButton->show();

    ui->TeamCreditsLabel->show();

    for (int i = 0; i < ui->NamesLayout->count(); ++i) {
        QWidget *widget = ui->NamesLayout->itemAt(i)->widget();
        if (widget) {
            widget->show();
        }
    }

    ui->Title->setText("Welcome to BetterThanChess.com");
}

void StartMenu::showChessBoard() {
    ui->chessBoardContainer->show();
    ui->QuitButton->show();

    ui->LevelsLabel->hide();
    ui->level1Button->hide();
    ui->level2Button->hide();
    ui->level3Button->hide();

    ui->GameModeLabel->hide();
    ui->vsComputerButton->hide();

    ui->TeamCreditsLabel->hide();

    for (int i = 0; i < ui->NamesLayout->count(); ++i) {
        QWidget *widget = ui->NamesLayout->itemAt(i)->widget();
        if (widget) {
            widget->hide();
        }
    }
}

