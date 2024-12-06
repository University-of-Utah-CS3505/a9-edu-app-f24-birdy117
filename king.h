#ifndef KING_H
#define KING_H
#include "draggablepiece.h"

class King : public DraggablePiece
{
public:
    King(Color color,
         const QPoint &startLocation,
         const QPixmap &pixmap,
         QGraphicsItem *parent = nullptr);

    /// Override to reset the previous position of the piece
    void resetPreviousPosition() override;

    /// Override to specify piece type as "King"
    QString pieceType() const override;

    /// Override to calculate valid moves for the king
    QList<QPoint> calculateValidMoves(int startX, int startY) const override;

    /// Override to get the attack range for the king
    QList<QPoint> calculateAttackRange(int startX, int startY) const override;

    /// Override to check if move is valid for a king
    bool isValidMove(const QPoint &destination) const override;

    /// Override to track move location
    void moveTo(const QPoint &destination) override;
};

#endif
