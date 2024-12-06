#include "startmenu.h"
#include "foolsmate.h"
#include <QMessageBox>

StartMenu::StartMenu(ChessBoard *chessBoard, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartMenu)
    , chessBoard(chessBoard)
    , stockfishEngine(new StockfishEngine(this))
    , settings("Placeholder", "AppName")
{
    ui->setupUi(this);
    connect(ui->level1Button, &QPushButton::clicked, this, &StartMenu::level1Start);
    connect(ui->level2Button, &QPushButton::clicked, this, &StartMenu::level2Start);
    connect(ui->level3Button, &QPushButton::clicked, this, &StartMenu::level3Start);
    connect(ui->vsComputerButton, &QPushButton::clicked, this, &StartMenu::vsComputerStart);
    connect(ui->QuitButton, &QPushButton::clicked, this, &StartMenu::quitButtonClicked);
    connect(ui->startButton, &QPushButton::clicked, this, &StartMenu::startClicked);

    buttons = {ui->level2Button, ui->level3Button};

    loadButtonStates();

    QVBoxLayout *layout = new QVBoxLayout;
    ui->chessBoardContainer->setLayout(layout);
    layout->addWidget(chessBoard);
    ui->chessBoardContainer->hide();
    ui->QuitButton->hide();
    ui->inputBox->hide();
    ui->inputBoxQuestion->hide();

    ui->foolsMateText->hide();
    ui->BackRankText->hide();
    ui->KingQueenText->hide();

    ui->startButton->hide();
    ui->startButton->setEnabled(false);

}

StartMenu::~StartMenu()
{
    saveButtonStates();
    delete ui;
}

void StartMenu::stockfishStart() {
    // Set up stockfish
    //QString basePath = QCoreApplication::applicationDirPath();
    QString stockfishPath = QCoreApplication::applicationDirPath() + "/../../../stockfish.exe";

    // stockfishEngine->startEngine(stockfishPath);

    // Can only connect to stockfish through slots or lambda expressions.
    // connect(stockfishEngine, &StockfishEngine::engineOutput, this, [](const QString &output) {
    //     // qDebug() << "STOCKFISH SAYS:" << output;
    // });
}

const QString StartMenu::foolMateSetup[8][8] = {
    {":/Images/RookW.png", ":/Images/KnightW.png", ":/Images/BishopW.png", ":/Images/KingW.png",
     ":/Images/QueenW.png", ":/Images/BishopW.png", ":/Images/KnightW.png", ":/Images/RookW.png"},
    {":/Images/PawnW.png", ":/Images/PawnW.png", ":/Images/PawnW.png", ":/Images/PawnW.png",
     ":/Images/PawnW.png", ":/Images/PawnW.png", ":/Images/PawnW.png", ":/Images/PawnW.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {":/Images/PawnB.png", ":/Images/PawnB.png", ":/Images/PawnB.png", ":/Images/PawnB.png",
     ":/Images/PawnB.png", ":/Images/PawnB.png", ":/Images/PawnB.png", ":/Images/PawnB.png"},
    {":/Images/RookB.png", ":/Images/KnightB.png", ":/Images/BishopB.png", ":/Images/KingB.png",
     ":/Images/QueenB.png", ":/Images/BishopB.png", ":/Images/KnightB.png", ":/Images/RookB.png"},
    };

const QString StartMenu::backRankMateSetup[8][8] = {
    {"", ":/Images/RookB.png", "", "", "", "", ":/Images/KingB.png", ""},
    {"", "", "", "", "", ":/Images/PawnB.png", ":/Images/PawnB.png", ":/Images/PawnB.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", ":/Images/PawnW.png", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", ":/Images/PawnW.png", ":/Images/PawnW.png", ":/Images/PawnW.png"},
    {"", "", "", "", ":/Images/RookW.png", "", "", ":/Images/KingW.png"}
};

const QString StartMenu::kingQueenMateSetup[8][8] = {
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", ":/Images/KingB.png", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", ":/Images/QueenW.png", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ":/Images/KingW.png"}
};

void StartMenu::level1Start() {
    hideStartingScreen();
    ui->foolsMateText->show();
    ui->startButton->show();
    ui->startButton->setEnabled(true);
    ui->startButton->raise();
    chessBoard->setupPieces(foolMateSetup);
    ui->Title->setText("Level 1: The Fool's Mate");
    fool = new foolsmate(chessBoard, this);

    connect(fool, &foolsmate::updateStatusLabel, this, &StartMenu::updateLabel);
    connect(ui->inputBox, &QLineEdit::returnPressed, this, &StartMenu::checkInputFirstMove);


    fool->moveFirstWhitePawn();
    fool->firstMove();
    connect(fool, &foolsmate::updateStatusLabel, this, &StartMenu::updateLabel);
    connect(this, &StartMenu::correctInputReceived, fool, &foolsmate::moveSecondWhitePawn);
    connect(this, &StartMenu::correctSecondInputReceived, fool, &foolsmate::moveThirdWhitePawn);

    // stockfishStart();
}

void StartMenu::level2Start() {
    hideStartingScreen();
    ui->BackRankText->show();
    ui->startButton->show();
    ui->startButton->setEnabled(true);
    ui->startButton->raise();
    chessBoard->setupPieces(backRankMateSetup);
    ui->Title->setText("Level 2: The Back Rank Mate");
    ui->inputBox->show();
    ui->inputBoxQuestion->show();
    // stockfishStart();
}

void StartMenu::level3Start() {
    hideStartingScreen();
    ui->KingQueenText->show();
    ui->startButton->show();
    ui->startButton->setEnabled(true);
    ui->startButton->raise();
    chessBoard->setupPieces(kingQueenMateSetup);
    ui->Title->setText("Level 3: The King and Queen Mate");
    ui->inputBox->show();
    ui->inputBoxQuestion->show();
    // stockfishStart();
}

void StartMenu::startClicked() {
    showChessBoard();
    ui->inputBox->show();
    ui->inputBoxQuestion->show();
}

void StartMenu::vsComputerStart() {
    showChessBoard();
    ui->Title->setText("VS Computer");
    stockfishStart();
}

void StartMenu::quitButtonClicked() {
    if (chessBoard) {
        chessBoard->resetBoard();
    }
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

void StartMenu::hideStartingScreen() {
    ui->LevelsLabel->hide();
    ui->level1Button->hide();
    ui->level2Button->hide();
    ui->level3Button->hide();

    ui->GameModeLabel->hide();
    ui->GameModeLabel->setDisabled(false);
    ui->vsComputerButton->hide();

    ui->TeamCreditsLabel->hide();
}

void StartMenu::showChessBoard() {
    ui->foolsMateText->hide();
    ui->BackRankText->hide();
    ui->KingQueenText->hide();

    ui->startButton->hide();
    ui->startButton->setEnabled(false);

    ui->chessBoardContainer->show();
    ui->QuitButton->show();

    for (int i = 0; i < ui->NamesLayout->count(); ++i) {
        QWidget *widget = ui->NamesLayout->itemAt(i)->widget();
        if (widget) {
            widget->hide();
        }
    }
}

void StartMenu::saveButtonStates() {
    settings.beginGroup("ButtonStates");
    for (QPushButton *button : buttons)
    {
        settings.setValue(button->objectName(), button->isEnabled());
    }
    settings.endGroup(); }

void StartMenu::loadButtonStates() {
    settings.beginGroup("ButtonStates");
    for (QPushButton *button : buttons) {
        button->setEnabled(settings.value(button->objectName(), true).toBool());
    }
    settings.endGroup();
}

void StartMenu::updateLabel(const QString& message) {
    qDebug() << "Slot received message:" << message;
    ui->inputBoxQuestion->setText(message);
    ui->inputBoxQuestion->setWordWrap(true);
}

void StartMenu::checkInputFirstMove() {
    QString userInput = ui->inputBox->text(); // Get the text from QLineEdit
    QString expectedValue = "E3";   // Define the value you want

    if (userInput == expectedValue) {
        qDebug() << "Input matches the desired value!";
        fool->moveFirstBlackPawn();

        // Disconnect the first move slot
        disconnect(ui->inputBox, &QLineEdit::returnPressed, this, &StartMenu::checkInputFirstMove);

        // Now connect to the second move slot
        connect(ui->inputBox, &QLineEdit::returnPressed, this, &StartMenu::checkInputSecondMove);

        // Create the message box
        QMessageBox* msgBox = new QMessageBox(QMessageBox::Information, "Correct Answer", "Good job! That's the correct move.", QMessageBox::Ok, this);

        // Connect the finished signal to a lambda that will emit the signal
        connect(msgBox, &QMessageBox::finished, this, [this, msgBox](int result) {
            // Check if "OK" button was pressed (QMessageBox::Ok has value 1)
            if (result == QMessageBox::Ok) {
                emit correctInputReceived();
            }
            msgBox->deleteLater(); // Clean up the message box after it's done
        });
        fool->secondMove();

        // Show the message box
        msgBox->exec();
    } else {
        qDebug() << "Input does not match. User entered:" << userInput;

        // Show a message box for incorrect input
        QMessageBox::warning(this, "Incorrect Answer", "Try again! That move is not correct.");
    }
    ui->inputBox->clear(); // Clear the input box for retry

}

void StartMenu::checkInputSecondMove() {
    QString userInput = ui->inputBox->text(); // Get the text from QLineEdit
    QString expectedValue = "H4";   // Define the value you want

    if (userInput == expectedValue) {
        qDebug() << "Input matches the desired value!";
        fool->moveBlackQueen();

        // Disconnect the first move slot
        disconnect(ui->inputBox, &QLineEdit::returnPressed, this, &StartMenu::checkInputFirstMove);

        // Now connect to the second move slot
        connect(ui->inputBox, &QLineEdit::returnPressed, this, &StartMenu::checkInputSecondMove);

        // Create the message box
        QMessageBox* msgBox = new QMessageBox(QMessageBox::Information, "Correct Answer", "Good job! That's the correct move.", QMessageBox::Ok, this);

        // Connect the finished signal to a lambda that will emit the signal
        connect(msgBox, &QMessageBox::finished, this, [this, msgBox](int result) {
            // Check if "OK" button was pressed (QMessageBox::Ok has value 1)
            if (result == QMessageBox::Ok) {
                emit correctSecondInputReceived();
                disconnect(ui->inputBox, &QLineEdit::returnPressed, this, &StartMenu::checkInputSecondMove);
                connect(ui->inputBox, &QLineEdit::returnPressed, this, &StartMenu::checkInputThirdMove);
            }
            msgBox->deleteLater(); // Clean up the message box after it's done
        });

        fool->thirdMove();
        // Show the message box
        msgBox->exec();
    } else {
        qDebug() << "Input does not match. User entered:" << userInput;

        // Show a message box for incorrect input
        QMessageBox::warning(this, "Incorrect Answer", "Try again! That move is not correct.");
    }
    ui->inputBox->clear(); // Clear the input box for retry

}

void StartMenu::checkInputThirdMove() {
    QString userInput = ui->inputBox->text(); // Get the text from QLineEdit
    QString expectedValue = "E1";   // Define the value you want

    if (userInput == expectedValue) {
        qDebug() << "Input matches the desired value!";
        fool->moveBlackQueen2();
        // Create the message box
        QMessageBox* msgBox = new QMessageBox(QMessageBox::Information, "Checkmate!", "Good job! You completed Level 1", QMessageBox::Ok, this);

        // Connect the finished signal to a lambda that will emit the signal
        connect(msgBox, &QMessageBox::finished, this, [this, msgBox](int result) {
            // Check if "OK" button was pressed (QMessageBox::Ok has value 1)
            if (result == QMessageBox::Ok) {

            }
            msgBox->deleteLater(); // Clean up the message box after it's done
        });

        // Show the message box
        msgBox->exec();
    } else {
        qDebug() << "Input does not match. User entered:" << userInput;

        // Show a message box for incorrect input
        QMessageBox::warning(this, "Incorrect Answer", "Try again! That move is not correct.");
    }
    ui->inputBox->clear(); // Clear the input box for retry

}



