#include "king.h"

King::King(Color color, const QPoint &startLocation, const QPixmap &pixmap, QGraphicsItem *parent)
    : DraggablePiece(color, startLocation, pixmap, parent)
{}

// Reset the king's position
void King::resetPreviousPosition()
{
    DraggablePiece::resetPreviousPosition();
}

// Return the piece type as a string
QString King::pieceType() const
{
    return "King";
}

QList<QPoint> King::calculateValidMoves(int startX, int startY) const
{
    QList<QPoint> validMoves;

    // The King can move one square in any direction
    for (int rowOffset = -1; rowOffset <= 1; ++rowOffset) {
        for (int colOffset = -1; colOffset <= 1; ++colOffset) {
            // Skip the current square (no movement)
            if (rowOffset == 0 && colOffset == 0)
                continue;

            validMoves.append(QPoint(startX + colOffset, startY + rowOffset));
        }
    }

    return validMoves;
}

// Calculate the attack range for the King (same as valid moves)
QList<QPoint> King::calculateAttackRange(int startX, int startY) const
{
    // The King attacks the same squares it can move to
    return calculateValidMoves(startX, startY);
}

// Check if a move is valid for the King
bool King::isValidMove(const QPoint &destination) const
{
    QList<QPoint> validMoves = calculateValidMoves(currentLocation.x(), currentLocation.y());
    return validMoves.contains(destination);
}

// Move the King to the specified location
void King::moveTo(const QPoint &destination)
{
    DraggablePiece::moveTo(destination);
    // Additional behavior for the King (e.g., update castling rights) can be added here
}
