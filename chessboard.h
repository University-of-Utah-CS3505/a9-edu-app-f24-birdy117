#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include "DraggablePiece.h"

class ChessBoard : public QWidget {
    Q_OBJECT

public:
    explicit ChessBoard(QWidget* parent = nullptr);
    void resetBoard();

private:
    void setupBoard();
    void setupPieces();

    static const int SQUARE_SIZE;
    static const int BOARD_SIZE;

    QGraphicsView* view;
    QGraphicsScene* scene;
};

#endif // CHESSBOARD_H
