#ifndef ROOK_H
#define ROOK_H

#include "draggablepiece.h"

class Rook: public DraggablePiece {
public:
    Rook(Color color, const QPoint& startLocation, const QPixmap& pixmap, QGraphicsItem* parent = nullptr);

    /// Override to reset the previous position of the piece
    void resetPreviousPosition() override;

    /// Override to specify piece type as "Rook"
    QString pieceType() const override;

    /// Override to calculate valid moves for the rook
    QList<QPoint> calculateValidMoves(int startX, int startY) const override;

    /// Override to get the attack range for the rook
    QList<QPoint> calculateAttackRange(int startX, int startY) const override;

    /// Override to check if move is valid for a rook
    bool isValidMove(const QPoint& destination) const override;

    /// Override to track move location
    void moveTo(const QPoint& destination) override;
};

#endif // ROOK_H
