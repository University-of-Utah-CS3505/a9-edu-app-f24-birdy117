#include <QApplication>
#include <QGraphicsView>
#include "chessboard.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Create the scene and view
    ChessBoard* chessScene = new ChessBoard();
    QGraphicsView view(chessScene);

    // Set the view size to fit the board
    view.setFixedSize(ChessBoard::BOARD_SIZE * ChessBoard::SQUARE_SIZE + 2,
                      ChessBoard::BOARD_SIZE * ChessBoard::SQUARE_SIZE + 2);
    view.show();

    return app.exec();
}
