#include <QApplication>
#include "mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    ChessBoard chessBoard;
    StartMenu startMenu(&chessBoard);
 //   MainWindow w(&chessBoard, &startMenu);
 //   w.show();
    startMenu.show();

    return app.exec();
}


