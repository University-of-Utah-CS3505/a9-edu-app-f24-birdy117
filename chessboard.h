#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "draggablepiece.h"
#include <QBrush>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QWidget>

class ChessBoard : public QWidget
{
    Q_OBJECT

public:
    QList<DraggablePiece *> allPieces;
    QList<QGraphicsRectItem *> highlights;
    QList<QGraphicsTextItem *> border;

    explicit ChessBoard(QWidget *parent = nullptr);
    void resetBoard();
    void setupPieces(const QString setup[8][8]);
    void highlightSquare(int col, int row, QColor color);
    void deleteHighlights();
    QGraphicsScene *scene;

private:
    void setupBoard();
    void setupPieces();

    static const int SQUARE_SIZE;
    static const int BOARD_SIZE;

    QGraphicsView *view;
};

#endif // CHESSBOARD_H
