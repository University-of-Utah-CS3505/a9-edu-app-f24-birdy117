#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>

class ChessBoard : public QGraphicsScene {
    Q_OBJECT
public:
    explicit ChessBoard(QObject* parent = nullptr);

    // Public static constants for easy access
    static const int SQUARE_SIZE; // Size of each square
    static const int BOARD_SIZE; // Chessboard dimensions

private:
    void setupBoard();
};

#endif // CHESSBOARD_H
