#ifndef STARTMENU_H
#define STARTMENU_H

#include <QMainWindow>
#include <QSettings>
#include <QTimer.h>
#include <QPushButton>
#include "chessboard.h"
#include "foolsmate.h"

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
    Foolsmate *fool; // Member to hold the foolsmate instance
    bool rankMove1 = false;
    bool rankMove2 = false;
    bool queenKingMove1 = false;

    QSettings settings;
    QList<QPushButton *> buttons;

    void hideStartingScreen();
    void addBorder();

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
    void QueenKingMateFirst();
    void QueenKingMateSecond();
    void QueenKingB2Checkmate();
    void QueenKingA4Checkmate();
    void QueenKingA5Checkmate();
    void QueenKingA6Checkmate();
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


public slots:
    void updateLabel(const QString& message);
    void checkInputFirstMove();
    void checkInputSecondMove();
    void checkInputThirdMove();


signals:
    void correctInputReceived();
    void correctSecondInputReceived();
};

#endif // STARTMENU_H
