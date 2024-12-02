#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "draggablepiece.h"
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

class ChessBoard : public QWidget {
    Q_OBJECT

public:
    static const int SQUARE_SIZE;
    static const int BOARD_SIZE;
    QGraphicsScene* scene;
    DraggablePiece* lastMovedPiece = nullptr;

    explicit ChessBoard(QWidget* parent = nullptr);

    QPoint getSquareFromPixels(const QPointF& Position);
    DraggablePiece* getPieceAt(int col, int row);
    void movePiece(const QPoint& start, const QPoint& end);

private:
    void setupBoard();
    void setupPieces();
    QGraphicsView* view;

// signals:
    // void pieceMoved();
};

#endif // CHESSBOARD_H
