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
    QList<DraggablePiece*> allPieces;
    QList<QGraphicsRectItem*> highlights;
    QColor originalColors[8][8];  // Store the original colors of squares


    explicit ChessBoard(QWidget* parent = nullptr);
    void resetBoard();
    void setupPieces(const QString setup[8][8]);
    void highlightSquare(int row, int col, QColor color);
    void unhighlightSquare(int col, int row);

private:
    void setupBoard();
    void setupPieces();

    static const int SQUARE_SIZE;
    static const int BOARD_SIZE;

    QGraphicsView* view;
    QGraphicsScene* scene;
};

#endif // CHESSBOARD_H
