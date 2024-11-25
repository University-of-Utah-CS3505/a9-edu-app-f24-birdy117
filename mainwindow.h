#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chessboard.h"
#include "startmenu.h"
#include "stockfishengine.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(ChessBoard *chessBoard, StartMenu *menu, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ChessBoard *chessBoard;
    StartMenu *startMenu;
    StockfishEngine *stockfishEngine;

private slots:
    //void onStartGame();
};
#endif // MAINWINDOW_H
