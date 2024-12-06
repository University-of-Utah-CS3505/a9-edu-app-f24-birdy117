#ifndef STARTMENU_H
#define STARTMENU_H

#include "backrank.h"

#include <QMainWindow>
#include <QTimer.h>
#include "chessboard.h"
#include "stockfishengine.h"
#include "ui_startmenu.h"
#include <QSettings>

namespace Ui {
class StartMenu;
}

class StartMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartMenu(ChessBoard *chessBoard, QWidget *parent = nullptr);
    ~StartMenu();

private:
    Ui::StartMenu *ui;
    QWidget *levelUI;
    ChessBoard *chessBoard;
    bool rankMove1 = false;
    bool rankMove2 = false;

    /// Stockfish executable
    StockfishEngine *stockfishEngine;

    QSettings settings;
    QList<QPushButton *> buttons;

    ///
    /// \brief stockfishStart
    /// Connect to stockfish.
    ///
    void stockfishStart();

    void hideStartingScreen();

    static const QString foolMateSetup[8][8];
    static const QString backRankMateSetup[8][8];
    //Setup and moves for King and Queen Checkmate
    static const QString kingQueenMateSetup[8][8];
    static const QString kingQueenMateMove1[8][8];
    static const QString kingQueenMateMove2[8][8];
    //4 Possible Checkmates
    static const QString kingQueenCheckmateG7[8][8];
    static const QString kingQueenCheckmateH3[8][8];
    static const QString kingQueenCheckmateH4[8][8];
    static const QString kingQueenCheckmateH5[8][8];

    // Setup for back rank checkmate
    static const QString backRankMateMove1[8][8];
    static const QString backRankMateMove2[8][8];
    static const QString backRankMateMove3[8][8];
    static const QString backRankMateMove4[8][8];
    static const QString backRankMateMove5[8][8];

    ///
    /// \brief Hides anything not on the StartMenu
    ///
    void hideNonStartingWidgets();
    void QueenKingG7Checkmate();
    void QueenKingH3Checkmate();
    void QueenKingH4Checkmate();
    void QueenKingH5Checkmate();
    void displayCheckmate();
    void displayRankCorrect1();
    void displayRankCorrect2();

    // Back rank methods
    void backRankMateFirst();
    void backRankMateSecond();
    void backRankMateThird();

private slots:
    void level1Start();
    void level2Start();
    void level3Start();
    void vsComputerStart();
    void quitButtonClicked();
    void hideChessBoard();
    void showChessBoard();
    void displayCorrect();
    void checkQueenKingCheckmateAnswer();
    void saveButtonStates();
    void loadButtonStates();
    void startClicked();
    void checkBackRankAnswer();
};

#endif // STARTMENU_H
