#ifndef PAWN_H
#define PAWN_H

#include "draggablepiece.h"

///
/// \authors Anne Arnold, Nicole Glazier, Ethan Kerrigan
///          Emily Thai, Aaron Perez
///
/// \date 06 December 2024
///
/// \brief Subclass to control the functionality of a pawn.
///
class Pawn : public DraggablePiece {
public:
    // TODO: finish documentation (parameters, returns, etc.)
    Pawn(Color color, const QPoint& startLocation, const QPixmap& pixmap, QGraphicsItem* parent = nullptr);

    /// Override to reset the previous position of the piece
    void resetPreviousPosition() override;

    /// Override to check if the pawn has been captured
    bool isCaptured() const override;

    /// Override to set the capture status of the pawn
    void setCaptured(bool status) override;

    /// Override to get the status of the first move
    bool isFirstMove() const override;

    /// Override to set the status of the first move
    void setFirstMove(bool status) override;

    /// Override to specify piece type as "Pawn"
    QString pieceType() const override;

    /// Override to calculate valid moves for the pawn
    QList<QPoint> calculateValidMoves(int startX, int startY) const override;

    /// Override to get the attack range for the pawn
    QList<QPoint> calculateAttackRange(int startX, int startY) const override;

    /// Override to check if move is valid for a pawn
    bool isValidMove(const QPoint& destination) const override;

    /// Override to track move location
    void moveTo(const QPoint& destination) override;
};

#endif // PAWN_H
