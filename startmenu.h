#ifndef STARTMENU_H
#define STARTMENU_H

#include <QMainWindow>
#include "chessboard.h"

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

private slots:
    void level1Start();
    void level2Start();
    void level3Start();
    void vsComputerStart();
    void quitButtonClicked();
    void hideChessBoard();
    void showChessBoard();
};

#endif // STARTMENU_H
