#ifndef KNIGHT_H
#define KNIGHT_H

#include "draggablepiece.h"

class Knight : public DraggablePiece
{
public:
    Knight(Color color,
           const QPoint &startLocation,
           const QPixmap &pixmap,
           QGraphicsItem *parent = nullptr);

    /// Override to reset the previous position of the piece
    void resetPreviousPosition() override;

    /// Override to specify piece type as "Knight"
    QString pieceType() const override;

    /// Override to calculate valid moves for the knight
    QList<QPoint> calculateValidMoves(int startX, int startY) const override;

    /// Override to get the attack range for the knight
    QList<QPoint> calculateAttackRange(int startX, int startY) const override;

    /// Override to check if move is valid for a knight
    bool isValidMove(const QPoint &destination) const override;

    /// Override to track move location
    void moveTo(const QPoint &destination) override;
};
#endif // KNIGHT_H
