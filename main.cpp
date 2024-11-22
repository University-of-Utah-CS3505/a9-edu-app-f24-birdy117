#include <QApplication>
#include "mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    ChessBoard chessBoard;
    MainWindow w(chessBoard);
    w.show();

    return app.exec();
}


