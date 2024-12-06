#include "startmenu.h"
#include "foolsmate.h"

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

    // Level 2 slots
    connect(ui->inputBackRank, &QLineEdit::textChanged, this, &StartMenu::checkBackRankAnswer);

    //Level 3 slots
    connect(ui->inputBox, &QLineEdit::textChanged, this, &StartMenu::checkQueenKingCheckmateAnswer);

    buttons = {ui->level2Button, ui->level3Button};

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

// const QString StartMenu::backRankMateMove4[8][8] = {
//     {"", "", "", "", "", "", ":/Images/KingB.png", ""},
//     {":Images/RookW.png", "", "", "", "", ":/Images/PawnB.png", "", ":/Images/PawnB.png"},
//     {"", "", "", "", "", "", ":/Images/PawnB.png", ""},
//     {"", "", "", "", "", "", "", ""},
//     {"", ":/Images/PawnW.png", "", "", "", "", "", ""},
//     {"", "", "", "", "", "", "", ""},
//     {"", ":Images/BishopW.png", "", "", "", "", ":/Images/PawnW.png", ":/Images/PawnW.png"},
//     {"", "", "", "", "", "", ":/Images/KingW.png", ""}
// };

// const QString StartMenu::backRankMateMove5[8][8] = {
//     {":Images/RookW.png", "", "", "", "", "", ":/Images/KingB.png", ""},
//     {"", "", "", "", "", ":/Images/PawnB.png", "", ":/Images/PawnB.png"},
//     {"", "", "", "", "", "", ":/Images/PawnB.png", ""},
//     {"", "", "", "", "", "", "", ""},
//     {"", ":/Images/PawnW.png", "", "", "", "", "", ""},
//     {"", "", "", "", "", "", "", ""},
//     {"", ":Images/BishopW.png", "", "", "", "", ":/Images/PawnW.png", ":/Images/PawnW.png"},
//     {"", "", "", "", "", "", ":/Images/KingW.png", ""}
// };





const QString StartMenu::kingQueenMateSetup[8][8] = {
    {"", "", "", "", "", "", "", ":/Images/KingB.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", ":/Images/KingW.png", "", ""},
    {"", "", "", "", "", "", ":/Images/QueenW.png", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""}
};

const QString StartMenu::kingQueenMateMove1[8][8] = {
    {"", "", "", "", "", "", "", ":/Images/KingB.png"},
    {"", "", "", "", "", ":/Images/KingW.png", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", ":/Images/QueenW.png", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""}
};

const QString StartMenu::kingQueenMateMove2[8][8] = {
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", ":/Images/KingW.png", "", ":/Images/KingB.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", ":/Images/QueenW.png", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""}
};

const QString StartMenu::kingQueenCheckmateG7[8][8] = {
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", ":/Images/KingW.png", ":/Images/QueenW.png", ":/Images/KingB.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""}
};

const QString StartMenu::kingQueenCheckmateH3[8][8] = {
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", ":/Images/KingW.png", "", ":/Images/KingB.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ":/Images/QueenW.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""}
};

const QString StartMenu::kingQueenCheckmateH4[8][8] = {
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", ":/Images/KingW.png", "", ":/Images/KingB.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ":/Images/QueenW.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""}
};

const QString StartMenu::kingQueenCheckmateH5[8][8] = {
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", ":/Images/KingW.png", "", ":/Images/KingB.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ":/Images/QueenW.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""}
};

void StartMenu::hideNonStartingWidgets() {
    ui->chessBoardContainer->hide();
    ui->QuitButton->hide();

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
    ui->Title->setText("Level 1: The Fool's Mate");
    FoolsMate fool(chessBoard);
    ui->TeamCreditsLabel->hide();
    for (int i = 0; i < ui->NamesLayout->count(); ++i) {
        QWidget *widget = ui->NamesLayout->itemAt(i)->widget();
        if (widget) {
            widget->hide();
        }
    }
    // stockfishStart();
}

void StartMenu::level2Start() {
    hideStartingScreen();
    ui->BackRankText->show();
    ui->startButton->show();
    ui->startButton->setEnabled(true);
    ui->startButton->raise();
    ui->inputBackRank->show();
    ui->directionsLabel->setText("Follow the instructions on the screen");
    ui->BackRankDesc->show();
    ui->BackRankDesc->setText("");

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

void StartMenu::level3Start() {
    hideStartingScreen();
    ui->KingQueenText->show();
    ui->startButton->show();
    ui->startButton->setEnabled(true);
    ui->startButton->raise();
    ui->inputBox->show();

    chessBoard->setupPieces(kingQueenMateSetup);
    ui->Title->setText("Level 3: The King and Queen Mate");
    ui->TeamCreditsLabel->hide();
    for (int i = 0; i < ui->NamesLayout->count(); ++i) {
        QWidget *widget = ui->NamesLayout->itemAt(i)->widget();
        if (widget) {
            widget->hide();
        }
    }
    // stockfishStart();
}

void StartMenu::startClicked() {
    showChessBoard();
}

void StartMenu::vsComputerStart() {
    hideStartingScreen();
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
    ui->directionsLabel->hide();

    ui->CorrectLabel->hide();
    ui->inputBoxLabel->hide();
    ui->inputBox->setText("");
    ui->inputBox->hide();
    ui->inputBackRank->hide();
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

    ui->Title->setText("Welcome to Checkmate Simulator");
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
    for (int i = 0; i < ui->NamesLayout->count(); ++i) {
        QWidget *widget = ui->NamesLayout->itemAt(i)->widget();
        if (widget) {
            widget->hide();
        }
    }
}

void StartMenu::showChessBoard() {
    ui->foolsMateText->hide();
    ui->BackRankText->hide();
    ui->KingQueenText->hide();

    ui->startButton->hide();
    ui->startButton->setEnabled(false);

    ui->directionsLabel->show();

    ui->chessBoardContainer->show();
    ui->QuitButton->show();

    ui->inputBoxLabel->show();
    ui->BackRankDesc->setText("Our king is in check! Get rid of the threat.");
}

void StartMenu::displayCorrect() {
    ui->CorrectLabel->show();

    //In 2000 ms move the White King Forward
    QTimer::singleShot(2000, this, [this]() {
        chessBoard->resetBoard();
        chessBoard->setupPieces(kingQueenMateMove1);
    });

    //In 3000 ms move the Black King forward
    QTimer::singleShot(3000, this, [this]() {
        chessBoard->resetBoard();
        chessBoard->setupPieces(kingQueenMateMove2);
        ui->inputBox->setText("");
        ui->CorrectLabel->hide();
        ui->directionsLabel->setText("Move the White Queen to force a checkmate.");
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
    chessBoard->highlightSquare(0, 8, Qt::yellow);
    chessBoard->highlightSquare(0, 2, Qt::darkYellow);

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
    chessBoard->deleteHighlights();
}

void StartMenu::checkQueenKingCheckmateAnswer() {
    if(ui->inputBox->text() == "F2") {
        displayCorrect();
    }
    if(ui->inputBox->text() == "G7") {
        QueenKingG7Checkmate();
    }
    if(ui->inputBox->text() == "H5") {
        QueenKingH5Checkmate();
    }
    if(ui->inputBox->text() == "H4") {
        QueenKingH4Checkmate();
    }
    if(ui->inputBox->text() == "H3") {
        QueenKingH3Checkmate();
    }
}

void StartMenu::QueenKingG7Checkmate() {
    //In 2000 ms move the White Queen to G7
    QTimer::singleShot(2000, this, [this]() {
        chessBoard->resetBoard();
        chessBoard->setupPieces(kingQueenCheckmateG7);
    });
}

void StartMenu::QueenKingH5Checkmate() {
    //In 2000 ms move the White Queen to H5
    QTimer::singleShot(2000, this, [this]() {
        chessBoard->resetBoard();
        chessBoard->setupPieces(kingQueenCheckmateH5);
    });
}

void StartMenu::QueenKingH4Checkmate() {
    //In 2000 ms move the White Queen to H4
    QTimer::singleShot(2000, this, [this]() {
        chessBoard->resetBoard();
        chessBoard->setupPieces(kingQueenCheckmateH4);
    });

}

void StartMenu::QueenKingH3Checkmate() {
    //In 2000 ms move the White Queen to H3
    QTimer::singleShot(2000, this, [this]() {
        chessBoard->resetBoard();
        chessBoard->setupPieces(kingQueenCheckmateH3);
    });
}

void StartMenu::displayCheckmate() {

}

// void StartMenu::backRankMove1() {
//     qDebug() << "1 hit";
// }

// void StartMenu::backRankMove2() {
//     qDebug() << "2 hit";
// }

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
