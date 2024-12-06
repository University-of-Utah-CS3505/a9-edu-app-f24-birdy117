#include "knight.h"

Knight::Knight(Color color,
               const QPoint &startLocation,
               const QPixmap &pixmap,
               QGraphicsItem *parent)
    : DraggablePiece(color, startLocation, pixmap, parent)
{}

// Reset the knight's position
void Knight::resetPreviousPosition()
{
    DraggablePiece::resetPreviousPosition();
}

// Return the piece type as a string
QString Knight::pieceType() const
{
    return "Knight";
}

// Calculate valid moves for the knight
QList<QPoint> Knight::calculateValidMoves(int startX, int startY) const
{
    QList<QPoint> validMoves;

    // Knights move in an "L" shape: two squares in one direction, then one square perpendicular
    const QList<QPoint> knightMoves = {QPoint(startX + 2, startY + 1),
                                       QPoint(startX + 2, startY - 1),
                                       QPoint(startX - 2, startY + 1),
                                       QPoint(startX - 2, startY - 1),
                                       QPoint(startX + 1, startY + 2),
                                       QPoint(startX + 1, startY - 2),
                                       QPoint(startX - 1, startY + 2),
                                       QPoint(startX - 1, startY - 2)};

    for (const QPoint &move : knightMoves) {
        // Check if the move is within the board's boundaries
        if (move.x() >= 0 && move.x() < 8 && move.y() >= 0 && move.y() < 8) {
            validMoves.append(move);
        }
    }

    return validMoves;
}

// Calculate the attack range for the knight (same as valid moves)
QList<QPoint> Knight::calculateAttackRange(int startX, int startY) const
{
    return calculateValidMoves(startX, startY);
}

// Check if a move is valid for the knight
bool Knight::isValidMove(const QPoint &destination) const
{
    QList<QPoint> validMoves = calculateValidMoves(currentLocation.x(), currentLocation.y());
    return validMoves.contains(destination);
}

// Move the knight to the specified location
void Knight::moveTo(const QPoint &destination)
{
    DraggablePiece::moveTo(destination);
}
