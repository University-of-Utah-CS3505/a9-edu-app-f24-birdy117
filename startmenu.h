#ifndef STARTMENU_H
#define STARTMENU_H

#include "chessboard.h"
#include "foolsmate.h"
#include <QMainWindow>
#include <QSettings>
#include <QPushButton>

namespace Ui {
class StartMenu;
}
///
/// \authors Anne Arnold, Nicole Glazier, Ethan Kerrigan
///          Emily Thai, Aaron Perez
///
/// \date 06 December 2024
///
/// \brief Handles all user interaction with the UI. Displays
/// the levels and final quiz.
///
class StartMenu : public QMainWindow
{
    Q_OBJECT
public:
    explicit StartMenu(ChessBoard *chessBoard, QWidget *parent = nullptr);
    ~StartMenu();

private:
    // Displays the interface
    Ui::StartMenu *ui;
    // Displays the different levels
    QWidget *levelUI;
    // Holds a chessboard instance
    ChessBoard *chessBoard;
    // Holds a foolsmate instance
    Foolsmate *fool;
    // True if user is on move 1 of back rank mate
    bool rankMove1 = false;
    // True if user is on move 2 of back rank mate
    bool rankMove2 = false;
    // True if user is on move 1 of king and queen mate
    bool queenKingMove1 = false;
    // Holds the settings
    QSettings settings;
    // Stores the buttons in the UI
    QList<QPushButton *> buttons;

    ///
    /// \brief hideStartingScreen
    /// Hides the starting screen
    ///
    void hideStartingScreen();

    ///
    /// \brief addBorder
    /// Adds abc... 123.. around the chessboard.
    ///
    void addBorder();

    // Setup for foolsmate and back rank mate
    static const QString foolMateSetup[8][8];
    static const QString backRankMateSetup[8][8];

    // Setup for back rank checkmate
    static const QString backRankMateMove1[8][8];
    static const QString backRankMateMove2[8][8];
    static const QString backRankMateMove3[8][8];
    static const QString backRankMateMove4[8][8];
    static const QString backRankMateMove5[8][8];

    //Setup and moves for King and Queen Checkmate
    static const QString kingQueenMateSetup[8][8];
    static const QString kingQueenMateMove1[8][8];
    static const QString kingQueenMateMove2[8][8];

    // 4 Possible Checkmates
    static const QString kingQueenCheckmateG7[8][8];
    static const QString kingQueenCheckmateH3[8][8];
    static const QString kingQueenCheckmateH4[8][8];
    static const QString kingQueenCheckmateH5[8][8];

    ///
    /// \brief hideNonStartingWidgets
    /// Hides anything not on the StartMenu
    ///
    void hideNonStartingWidgets();

    ///
    /// \brief QueenKingMateFirst
    /// Controls first move of King and Queen checkmate.
    ///
    void QueenKingMateFirst();

    ///
    /// \brief QueenKingMateSecond
    /// Controls second move of King and Queen checkmate.
    ///
    void QueenKingMateSecond();

    ///
    /// \brief QueenKingB2Checkmate
    /// Calculates possible checkmate in King and Queen checkmate.
    ///
    void QueenKingB2Checkmate();

    ///
    /// \brief QueenKingA4Checkmate
    /// Calculates possible checkmate in King and Queen checkmate.
    ///
    void QueenKingA4Checkmate();

    ///
    /// \brief QueenKingA5Checkmate
    /// Calculates possible checkmate in King and Queen checkmate.
    ///
    void QueenKingA5Checkmate();

    ///
    /// \brief QueenKingA6Checkmate
    /// Calculates possible checkmate in King and Queen checkmate.
    ///
    void QueenKingA6Checkmate();

    ///
    /// \brief displayCheckmate
    /// Calculates possible checkmate in King and Queen checkmate.
    ///
    void displayCheckmate();

    ///
    /// \brief displayRankCorrect1
    /// Calculates possible checkmate in King and Queen checkmate.
    ///
    void displayRankCorrect1();

    ///
    /// \brief displayRankCorrect2
    /// Calculates possible checkmate in King and Queen checkmate.
    ///
    void displayRankCorrect2();

    // Back rank methods
    ///
    /// \brief backRankMateFirst
    /// Controls first move of back rank mate checkmate.
    ///
    void backRankMateFirst();

    ///
    /// \brief backRankMateSecond
    /// Controls second move of back rank mate checkmate.
    ///
    void backRankMateSecond();

    ///
    /// \brief backRankMateThird
    /// Controls third move of back rank mate checkmate.
    ///
    void backRankMateThird();

private slots:
    ///
    /// \brief level1Start
    /// Begin playing level 1.
    ///
    void level1Start();

    ///
    /// \brief level2Start
    /// Begin playing level 2.
    ///
    void level2Start();

    ///
    /// \brief level3Start
    /// Begin playing level 3.
    ///
    void level3Start();

    void vsComputerStart();

    ///
    /// \brief quitButtonClicked
    /// Returns to start menu.
    ///
    void quitButtonClicked();

    ///
    /// \brief hideChessBoard
    /// Hides the chessboard.
    void hideChessBoard();

    ///
    /// \brief showChessBoard
    /// Displays the chessboard.
    ///
    void showChessBoard();

    ///
    /// \brief displayCorrect
    /// Shows "correct".
    ///
    void displayCorrect();

    ///
    /// \brief checkQueenKingCheckmateAnswer
    /// Validates user input. If correct, a "correct"
    /// will be displayed. Otherwise a pop up telling
    /// you to try again will be displayed.
    ///
    void checkQueenKingCheckmateAnswer();

    ///  \brief saveButtonStates
    ///  Saves the current state of the game.
    ///
    void saveButtonStates();

    ///
    /// \brief loadButtonStates
    /// Loads a certain state of the game.
    void loadButtonStates();

    ///
    /// \brief startClicked
    /// Moves from a level info page to
    /// the actual play part of the game.
    ///
    void startClicked();

    ///
    /// \brief checkBackRankAnswer
    /// Validates user input. If correct, a "correct"
    /// will be displayed. Otherwise a pop up telling
    /// you to try again will be displayed.
    ///
    void checkBackRankAnswer();


public slots:
    ///
    /// \brief updateLabel
    /// Updates the level description with
    /// the given message.
    /// \param message - updated message to display
    ///
    void updateLabel(const QString& message);

    ///
    /// \brief checkInputFirstMove
    /// Verifies that input for Foolsmate move 1 is
    /// correct.
    ///
    void checkInputFirstMove();

    ///
    /// \brief checkInputSecondMove
    /// Verifies that input for Foolsmate move 2 is
    /// correct.
    ///
    void checkInputSecondMove();

    ///
    /// \brief checkInputThirdMove
    /// Verifies that input for Foolsmate move 3 is
    /// correct.
    ///
    void checkInputThirdMove();


signals:
    void correctInputReceived();
    void correctSecondInputReceived();
};

#endif // STARTMENU_H
