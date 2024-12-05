#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "draggablepiece.h"
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QVBoxLayout>

class ChessBoard : public QWidget {
    Q_OBJECT

public:
    /* NOTE:
 * Level 1 index order:
 * 0-7 back row of white, starting with left rook moving right.
 * 8-15 white pawns
 * 16-23 black pawns
 * 24-31 back row of black, starting with left rook moving right.
 *
 * Level 2:
 * 0 black rook
 * 1 black king
 * 2-4 black pawns
 * 5-7 white pawns
 * 8 white rook
 * 9 black king
 *
 * Level 3:
 * 0 black king
 * 1 white queen
 * 2 white king
 */
    QList<DraggablePiece*> allPieces;

    explicit ChessBoard(QWidget* parent = nullptr);
    void resetBoard();
    void setupPieces(const QString setup[8][8]);
    void highlightSquare(int col, int row, QColor color);

private:
    void setupBoard();
    void setupPieces();

    static const int SQUARE_SIZE;
    static const int BOARD_SIZE;

    QGraphicsView* view;
    QGraphicsScene* scene;
};

#endif // CHESSBOARD_H
