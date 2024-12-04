#ifndef QUEEN_H
#define QUEEN_H

#include "draggablepiece.h"

class Queen: public DraggablePiece {
public:
    Queen(Color color, const QPoint& startLocation, const QPixmap& pixmap, QGraphicsItem* parent = nullptr);

    /// Override to reset the previous position of the piece
    void resetPreviousPosition() override;

    /// Override to specify piece type as "Queen"
    QString pieceType() const override;

    /// Override to calculate valid moves for the queen
    QList<QPoint> calculateValidMoves(int startX, int startY) const override;

    /// Override to get the attack range for the queen
    QList<QPoint> calculateAttackRange(int startX, int startY) const override;

    /// Override to check if move is valid for a queen
    bool isValidMove(const QPoint& destination) const override;

    /// Override to track move location
    void moveTo(const QPoint& destination) override;
};
#endif // QUEEN_H
