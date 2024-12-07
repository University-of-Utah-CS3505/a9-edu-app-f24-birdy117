#include "startmenu.h"
#include "foolsmate.h"
#include "ui_startmenu.h"
#include <QMessageBox>

StartMenu::StartMenu(ChessBoard *chessBoard, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartMenu)
    , chessBoard(chessBoard)
    , settings("Placeholder", "AppName")
{
    fool = new Foolsmate(chessBoard);

    ui->setupUi(this);
    connect(ui->level1Button, &QPushButton::clicked, this, &StartMenu::level1Start);
    connect(ui->level2Button, &QPushButton::clicked, this, &StartMenu::level2Start);
    connect(ui->level3Button, &QPushButton::clicked, this, &StartMenu::level3Start);
    connect(ui->vsComputerButton, &QPushButton::clicked, this, &StartMenu::vsComputerStart);
    connect(ui->QuitButton, &QPushButton::clicked, this, &StartMenu::quitButtonClicked);
    connect(ui->startButton, &QPushButton::clicked, this, &StartMenu::startClicked);

    // Level 2 slots
    //connect(ui->inputBackRank, &QLineEdit::returnPressed, this, &StartMenu::checkBackRankAnswer);

    //Level 3 slots
    //connect(ui->inputBox, &QLineEdit::returnPressed, this, &StartMenu::checkQueenKingCheckmateAnswer);

    buttons = {ui->level1Button, ui->level2Button, ui->level3Button};

    loadButtonStates();

    QVBoxLayout *layout = new QVBoxLayout;
    ui->chessBoardContainer->setLayout(layout);
    layout->addWidget(chessBoard);
    hideNonStartingWidgets();
}

StartMenu::~StartMenu()
{
    saveButtonStates();
    delete ui;
    delete chessBoard;
    delete fool;
}

const QString StartMenu::foolMateSetup[8][8] = {
    {":/Images/RookW.png",
     ":/Images/KnightW.png",
     ":/Images/BishopW.png",
     ":/Images/KingW.png",
     ":/Images/QueenW.png",
     ":/Images/BishopW.png",
     ":/Images/KnightW.png",
     ":/Images/RookW.png"},
    {":/Images/PawnW.png",
     ":/Images/PawnW.png",
     ":/Images/PawnW.png",
     ":/Images/PawnW.png",
     ":/Images/PawnW.png",
     ":/Images/PawnW.png",
     ":/Images/PawnW.png",
     ":/Images/PawnW.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {":/Images/PawnB.png",
     ":/Images/PawnB.png",
     ":/Images/PawnB.png",
     ":/Images/PawnB.png",
     ":/Images/PawnB.png",
     ":/Images/PawnB.png",
     ":/Images/PawnB.png",
     ":/Images/PawnB.png"},
    {":/Images/RookB.png",
     ":/Images/KnightB.png",
     ":/Images/BishopB.png",
     ":/Images/KingB.png",
     ":/Images/QueenB.png",
     ":/Images/BishopB.png",
     ":/Images/KnightB.png",
     ":/Images/RookB.png"},
    };

const QString StartMenu::backRankMateSetup[8][8] = {
    {"", "", "", "", "", "", ":/Images/KingB.png", ""},
    {"", "", "", "", ":/Images/PawnB.png", ":/Images/PawnB.png", ":/Images/PawnB.png", ":/Images/PawnB.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", ":/Images/BishopB.png", "", "", ""},
    {"", "", "", "", "", "", ":/Images/PawnW.png", ":/Images/PawnW.png"},
    {":Images/RookW.png", "", ":Images/BishopW.png", "", "", "", ":/Images/KingW.png", ""}
};

const QString StartMenu::backRankMateMove1[8][8] = {
    {"", "", "", "", "", "", ":/Images/KingB.png", ""},
    {"", "", "", "", ":/Images/PawnB.png", ":/Images/PawnB.png", ":/Images/PawnB.png", ":/Images/PawnB.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", ":Images/BishopW.png", "", "", ""},
    {"", "", "", "", "", "", ":/Images/PawnW.png", ":/Images/PawnW.png"},
    {":Images/RookW.png", "", "", "", "", "", ":/Images/KingW.png", ""}
};

const QString StartMenu::backRankMateMove2[8][8] = {
    {"", "", "", "", "", ":/Images/KingB.png", "", ""},
    {"", "", "", "", ":/Images/PawnB.png", ":/Images/PawnB.png", ":/Images/PawnB.png", ":/Images/PawnB.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", ":Images/BishopW.png", "", "", ""},
    {"", "", "", "", "", "", ":/Images/PawnW.png", ":/Images/PawnW.png"},
    {":Images/RookW.png", "", "", "", "", "", ":/Images/KingW.png", ""}
};

const QString StartMenu::backRankMateMove3[8][8] = {
    {":Images/RookW.png", "", "", "", "", ":/Images/KingB.png", "", ""},
    {"", "", "", "", ":/Images/PawnB.png", ":/Images/PawnB.png", ":/Images/PawnB.png", ":/Images/PawnB.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", ":Images/BishopW.png", "", "", ""},
    {"", "", "", "", "", "", ":/Images/PawnW.png", ":/Images/PawnW.png"},
    {"", "", "", "", "", "", ":/Images/KingW.png", ""}
};

const QString StartMenu::kingQueenMateSetup[8][8] = {
    {"", "", "", "", "", "", "", ":/Images/KingW.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", ":/Images/KingB.png", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", ":/Images/QueenB.png", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""}
};

const QString StartMenu::kingQueenMateMove1[8][8] = {
    {"", "", "", "", "", "", "", ":/Images/KingW.png"},
    {"", "", "", "", "", ":/Images/KingB.png", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", ":/Images/QueenB.png", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""}
};

const QString StartMenu::kingQueenMateMove2[8][8] = {
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", ":/Images/KingB.png", "", ":/Images/KingW.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", ":/Images/QueenB.png", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""}
};

const QString StartMenu::kingQueenCheckmateG7[8][8] = {
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", ":/Images/KingB.png", ":/Images/QueenB.png", ":/Images/KingW.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""}
};

const QString StartMenu::kingQueenCheckmateH3[8][8] = {
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", ":/Images/KingB.png", "", ":/Images/KingW.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ":/Images/QueenB.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""}
};

const QString StartMenu::kingQueenCheckmateH4[8][8] = {
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", ":/Images/KingB.png", "", ":/Images/KingW.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ":/Images/QueenB.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""}
};

const QString StartMenu::kingQueenCheckmateH5[8][8] = {
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", ":/Images/KingB.png", "", ":/Images/KingW.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ":/Images/QueenB.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""}
};

void StartMenu::hideNonStartingWidgets()
{
    ui->chessBoardContainer->hide();
    ui->QuitButton->hide();
    ui->NextLevelButton->hide();
    ui->CheckmateLabel->hide();

    ui->foolsMateText->hide();
    ui->BackRankText->hide();
    ui->KingQueenText->hide();
    ui->inputBox->hide();
    ui->inputBoxLabel->hide();

    ui->inputBackRank->hide();

    ui->directionsLabel->hide();
    ui->CorrectLabel->hide();

    ui->startButton->hide();
    ui->startButton->setEnabled(false);

    ui->BackRankDesc->hide();
}

void StartMenu::level1Start() {
    hideStartingScreen();
    ui->foolsMateText->show();
    ui->startButton->show();
    ui->startButton->setEnabled(true);
    ui->startButton->raise();
    chessBoard->setupPieces(foolMateSetup);
    // Add row numbers on the left side of the board (1 to BOARD_SIZE)
    for (int row = 0; row < 8; ++row) {
        QGraphicsTextItem *rowNumber = new QGraphicsTextItem(QString::number(row + 1));
        rowNumber->setPos(-4, row * 50 + 50 / 2);  // Adjust for positioning
        rowNumber->setDefaultTextColor(Qt::black);
        chessBoard->scene->addItem(rowNumber);
    }

    // Add column letters on the top side of the board (A to Z)
    for (int col = 0; col < 8; ++col) {
        QGraphicsTextItem *colLetter = new QGraphicsTextItem(QString(QChar('H' - col)));
        colLetter->setPos(col * 50 + 50 / 2 - 28, -6);  // Adjust for positioning
        colLetter->setDefaultTextColor(Qt::black);
        chessBoard->scene->addItem(colLetter);
    }
    ui->Title->setText("Level 1: The Fool's Mate");
    // fool = new foolsmate(chessBoard, this);

    connect(fool, &Foolsmate::updateStatusLabel, this, &StartMenu::updateLabel);
    connect(ui->inputBox, &QLineEdit::returnPressed, this, &StartMenu::checkInputFirstMove);


    fool->moveFirstWhitePawn();
    fool->firstMove();
    connect(fool, &Foolsmate::updateStatusLabel, this, &StartMenu::updateLabel);
    connect(this, &StartMenu::correctInputReceived, fool, &Foolsmate::moveSecondWhitePawn);
    connect(this, &StartMenu::correctSecondInputReceived, fool, &Foolsmate::moveThirdWhitePawn);
}


void StartMenu::level2Start()
{
    hideStartingScreen();
    ui->BackRankText->show();
    ui->startButton->show();
    ui->startButton->setEnabled(true);
    ui->startButton->raise();
    ui->inputBackRank->show();
    ui->directionsLabel->setText("Follow the instructions on the screen");
    ui->BackRankDesc->show();
    ui->BackRankDesc->setText("");

    connect(ui->inputBackRank, &QLineEdit::textChanged, this, &StartMenu::checkBackRankAnswer);

    chessBoard->setupPieces(backRankMateSetup);
    ui->Title->setText("Level 2: The Back Rank Mate");
    ui->TeamCreditsLabel->hide();
    for (int i = 0; i < ui->NamesLayout->count(); ++i) {
        QWidget *widget = ui->NamesLayout->itemAt(i)->widget();
        if (widget) {
            widget->hide();
        }
    }
    backRankMateFirst();
}

void StartMenu::level3Start()
{
    hideStartingScreen();
    ui->KingQueenText->show();
    ui->startButton->show();
    ui->startButton->setEnabled(true);
    ui->startButton->raise();

    ui->BackRankDesc->setText("");

    connect(ui->inputBox, &QLineEdit::returnPressed, this, &StartMenu::checkQueenKingCheckmateAnswer);


    chessBoard->setupPieces(kingQueenMateSetup);
    ui->Title->setText("Level 3: The King and Queen Mate");
    ui->directionsLabel->setText("Move the White King to corner the Black King.");
    ui->TeamCreditsLabel->hide();
    for (int i = 0; i < ui->NamesLayout->count(); ++i) {
        QWidget *widget = ui->NamesLayout->itemAt(i)->widget();
        if (widget) {
            widget->hide();
        }
    }

    // Add row numbers on the left side of the board (1 to BOARD_SIZE)
    for (int row = 0; row < 8; ++row) {
        QGraphicsTextItem *rowNumber = new QGraphicsTextItem(QString::number(row + 1));
        rowNumber->setPos(-4, row * 50 + 50 / 2);  // Adjust for positioning
        rowNumber->setDefaultTextColor(Qt::black);
        chessBoard->scene->addItem(rowNumber);
    }

    // Add column letters on the top side of the board (A to Z)
    for (int col = 0; col < 8; ++col) {
        QGraphicsTextItem *colLetter = new QGraphicsTextItem(QString(QChar('H' - col)));
        colLetter->setPos(col * 50 + 50 / 2 - 28, -6);  // Adjust for positioning
        colLetter->setDefaultTextColor(Qt::black);
        chessBoard->scene->addItem(colLetter);
    }
    QueenKingMateFirst();
}

void StartMenu::startClicked()
{
    showChessBoard();
}

void StartMenu::vsComputerStart()
{
    hideStartingScreen();
    showChessBoard();
    ui->Title->setText("VS Computer");
}

void StartMenu::quitButtonClicked()
{
    if (chessBoard) {
        chessBoard->resetBoard();
    }
    hideChessBoard(); // Todo: aaron doesn't have this in his
    queenKingMove1 = false;
    rankMove1 = false;
    rankMove2 = false;
}

void StartMenu::hideChessBoard()
{
    ui->chessBoardContainer->hide();
    ui->QuitButton->hide();
    ui->NextLevelButton->hide();
    ui->directionsLabel->hide();
    ui->CheckmateLabel->hide();

    ui->CorrectLabel->hide();
    ui->inputBoxLabel->hide();
    ui->inputBox->setText("");
    ui->inputBox->hide();
    ui->inputBackRank->hide();
    ui->BackRankText->hide();
    ui->BackRankDesc->hide();

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

    // Disconnect all signals from the QLineEdit
    disconnect(ui->inputBox, nullptr, nullptr, nullptr);
    ui->Title->setText("Welcome to Checkmate Simulator");
}

void StartMenu::hideStartingScreen()
{
    ui->LevelsLabel->hide();
    ui->level1Button->hide();
    ui->level2Button->hide();
    ui->level3Button->hide();

    ui->GameModeLabel->hide();
    ui->GameModeLabel->setDisabled(false);
    ui->vsComputerButton->hide();

    ui->TeamCreditsLabel->hide();
    for (int i = 0; i < ui->NamesLayout->count(); ++i) {
        QWidget *widget = ui->NamesLayout->itemAt(i)->widget();
        if (widget) {
            widget->hide();
        }
    }
}

void StartMenu::showChessBoard()
{
    ui->foolsMateText->hide();
    ui->BackRankText->hide();
    ui->KingQueenText->hide();
    ui->NextLevelButton->hide();

    ui->startButton->hide();
    ui->startButton->setEnabled(false);

    ui->inputBox->show();

    ui->directionsLabel->show();

    ui->chessBoardContainer->show();
    ui->QuitButton->show();
    ui->NextLevelButton->show();

    ui->inputBoxLabel->show();
    ui->BackRankDesc->show();
}

void StartMenu::displayCorrect()
{
    ui->CorrectLabel->show();

    //move the White King Forward
    chessBoard->resetBoard();
    chessBoard->setupPieces(kingQueenMateMove1);

    //In 3000 ms move the Black King forward
    QTimer::singleShot(3000, this, [this]() {
        chessBoard->resetBoard();
        chessBoard->setupPieces(kingQueenMateMove2);
        ui->inputBox->setText("");
        ui->CorrectLabel->hide();
        ui->directionsLabel->setText("Move the White Queen to force a checkmate.");
        QueenKingMateSecond();
    });
}

void StartMenu::displayRankCorrect1() {
    ui->CorrectLabel->show();
    QTimer::singleShot(1000, this, [this]() {
        chessBoard->resetBoard();
        chessBoard->setupPieces(backRankMateMove1);
    });
    QTimer::singleShot(2000, this, [this]() {
        ui->BackRankDesc->setText("Great job! Notice that the opposing king is "
                                  "stuck behind a wall of pawns. Let's use this to our advantage. "
                                  "Put the opposing king into checkmate");
        backRankMateSecond();
    });
}

void StartMenu::displayRankCorrect2() {
    ui->CorrectLabel->show();
    QTimer::singleShot(1000, this, [this]() {
        chessBoard->resetBoard();
        chessBoard->setupPieces(backRankMateMove3);
    });
    QTimer::singleShot(2000, this, [this]() {
        ui->BackRankDesc->setText("You win!");
        rankMove2 = false;
    });
}

void StartMenu::checkBackRankAnswer() {
    if((ui->inputBackRank->text() == "E3" || ui->inputBackRank->text() == "e3") && rankMove1) {
        displayRankCorrect1();
    }
    if((ui->inputBackRank->text() == "A8" || ui->inputBackRank->text() == "a8") && rankMove2) {
        displayRankCorrect2();
    }
}

void StartMenu::backRankMateFirst() {
    rankMove1 = true;
    rankMove2 = false;
    ui->CorrectLabel->hide();
    ui->inputBackRank->setText("");
    chessBoard->highlightSquare(2, 0, Qt::yellow);
    chessBoard->highlightSquare(4, 2, Qt::darkYellow);
}

void StartMenu::backRankMateSecond() {
    rankMove1 = false;
    ui->CorrectLabel->hide();
    ui->inputBackRank->setText("");
    chessBoard->deleteHighlights();
    chessBoard->resetBoard();
    chessBoard->setupPieces(backRankMateMove2);
    backRankMateThird();
}

void StartMenu::backRankMateThird() {
    rankMove2 = true;
    ui->inputBackRank->setText("");
    chessBoard->highlightSquare(0, 0, Qt::yellow);
    chessBoard->highlightSquare(4, 0, Qt::darkYellow);
}

void StartMenu::checkQueenKingCheckmateAnswer()
{
    QString userInput = ui->inputBox->text();

    if (userInput == "C2" && queenKingMove1 == false) {
        displayCorrect();
        queenKingMove1 = true;
    }
    else if (userInput == "B2" && queenKingMove1 == true) {
        QueenKingB2Checkmate();
    }
    else if (userInput == "A4" && queenKingMove1 == true) {
        QueenKingA4Checkmate();
    }
    else if (userInput == "A5" && queenKingMove1 == true) {
        QueenKingA5Checkmate();
    }
    else if (userInput == "A6" && queenKingMove1 == true) {
        QueenKingA6Checkmate();
    }
    else {
        QMessageBox::warning(this, "Incorrect Answer", "Try again! That move is not correct.");
    }
}

void StartMenu::QueenKingMateFirst() {
    ui->CorrectLabel->hide();
    ui->inputBox->setText("");
    ui->BackRankDesc->setText("The Opponent's King is backed into the corner. Move your King closer to setup a checkmate!");
    chessBoard->highlightSquare(5, 5, Qt::yellow);
    chessBoard->highlightSquare(5, 6, Qt::darkYellow);
}

void StartMenu::QueenKingMateSecond() {
    ui->CorrectLabel->hide();
    ui->inputBox->setText("");
    ui->BackRankDesc->setText("The Opponent's King is backed into the corner. Move your Queen closer to checkmate!");
    chessBoard->highlightSquare(6, 3, Qt::yellow);
    chessBoard->highlightSquare(6, 6, Qt::darkYellow);
    chessBoard->highlightSquare(7, 2, Qt::darkYellow);
    chessBoard->highlightSquare(7, 3, Qt::darkYellow);
    chessBoard->highlightSquare(7, 4, Qt::darkYellow);
}

void StartMenu::QueenKingB2Checkmate()
{
    //move the White Queen to G7
    chessBoard->resetBoard();
    chessBoard->setupPieces(kingQueenCheckmateG7);
    displayCheckmate();
    ui->vsComputerButton->isEnabled();
}

void StartMenu::QueenKingA4Checkmate()
{
    //move the White Queen to H5
    chessBoard->resetBoard();
     chessBoard->setupPieces(kingQueenCheckmateH5);
    displayCheckmate();
    ui->vsComputerButton->isEnabled();
}

void StartMenu::QueenKingA5Checkmate()
{
    //move the White Queen to H4
    chessBoard->resetBoard();
    chessBoard->setupPieces(kingQueenCheckmateH4);
    displayCheckmate();
    ui->vsComputerButton->isEnabled();
}

void StartMenu::QueenKingA6Checkmate()
{
    //move the White Queen to H3
    chessBoard->resetBoard();
    chessBoard->setupPieces(kingQueenCheckmateH3);
    displayCheckmate();
    ui->vsComputerButton->isEnabled();
}

void StartMenu::displayCheckmate() {
    ui->CheckmateLabel->show();
    ui->CheckmateLabel->raise();
    ui->NextLevelButton->setEnabled(1);
}

void StartMenu::saveButtonStates()
{
    settings.beginGroup("ButtonStates");
    for (QPushButton *button : buttons) {
        settings.setValue(button->objectName(), button->isEnabled());
    }
    settings.endGroup();
}

void StartMenu::loadButtonStates()
{
    settings.beginGroup("ButtonStates");
    for (QPushButton *button : buttons) {
        button->setEnabled(settings.value(button->objectName(), true).toBool());
    }
    settings.endGroup();
}

void StartMenu::updateLabel(const QString& message) {
    qDebug() << "Slot received message:" << message;
    ui->directionsLabel->setText(message);
    ui->directionsLabel->setWordWrap(true);
}

void StartMenu::checkInputFirstMove() {
    QString userInput = ui->inputBox->text(); // Get the text from QLineEdit
    QString expectedValue = "E5";   // Define the value you want

    if (fool && userInput == expectedValue) {
        qDebug() << "Input matches the desired value!";
        fool->moveFirstBlackPawn();

        // Disconnect the first move slot
        disconnect(ui->inputBox, &QLineEdit::returnPressed, this, &StartMenu::checkInputFirstMove);

        // Now connect to the second move slot
        connect(ui->inputBox, &QLineEdit::returnPressed, this, &StartMenu::checkInputSecondMove);

        ui->CorrectLabel->show();

        // Hide the label after 2 seconds
        QTimer::singleShot(2000, this, [this]() {
            ui->CorrectLabel->hide();
        });

        emit correctInputReceived();

        fool->secondMove();
    } else {
        qDebug() << "Input does not match. User entered:" << userInput;

    }

    ui->inputBox->clear(); // Clear the input box for retry
}


void StartMenu::checkInputSecondMove() {
    QString userInput = ui->inputBox->text(); // Get the text from QLineEdit
    QString expectedValue = "H4";   // Define the value you want

    if (fool && userInput == expectedValue) {
        qDebug() << "Input matches the desired value!";
        fool->moveBlackQueen();

        // Show the "Correct" label
        ui->CorrectLabel->setText("Correct!");
        ui->CorrectLabel->setStyleSheet("color: green;");
        ui->CorrectLabel->show();

        // Hide the label after 2 seconds
        QTimer::singleShot(2000, this, [this]() {
            ui->CorrectLabel->hide();
        });

        emit correctSecondInputReceived();

        // Disconnect the second move slot
        disconnect(ui->inputBox, &QLineEdit::returnPressed, this, &StartMenu::checkInputSecondMove);

        // Connect to the third move slot
        connect(ui->inputBox, &QLineEdit::returnPressed, this, &StartMenu::checkInputThirdMove);

        fool->thirdMove();
    } else {
        qDebug() << "Input does not match. User entered:" << userInput;

        // Display an error in the "CorrectLabel"
        ui->CorrectLabel->setText("Incorrect! Try again.");
        ui->CorrectLabel->setStyleSheet("color: red;");
        ui->CorrectLabel->show();

        // Hide the label after 2 seconds
        QTimer::singleShot(2000, this, [this]() {
            ui->CorrectLabel->hide();
        });
    }

    ui->inputBox->clear(); // Clear the input box for retry
}

void StartMenu::checkInputThirdMove() {
    QString userInput = ui->inputBox->text(); // Get the text from QLineEdit
    QString expectedValue = "E1";   // Define the value you want

    if (fool && userInput == expectedValue) {
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
