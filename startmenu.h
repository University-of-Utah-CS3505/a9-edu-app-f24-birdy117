#ifndef STARTMENU_H
#define STARTMENU_H

#include <QMainWindow>
#include "chessboard.h"
#include "stockfishengine.h"
#include "ui_startmenu.h"
#include <QSettings>
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
    foolsmate *fool; // Member to hold the foolsmate instance

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
    static const QString kingQueenMateSetup[8][8];

    QLabel* statusLabel;

private slots:
    void level1Start();
    void level2Start();
    void level3Start();
    void vsComputerStart();
    void quitButtonClicked();
    void hideChessBoard();
    void showChessBoard();
    void saveButtonStates();
    void loadButtonStates();
    void startClicked();

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
