#include <QApplication>
#include "chessboard.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    ChessBoard chessBoard;
    chessBoard.show();

    return app.exec();
}
