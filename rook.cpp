#include "rook.h"

Rook::Rook(Color color, const QPoint &startLocation, const QPixmap &pixmap, QGraphicsItem *parent)
    : DraggablePiece(color, startLocation, pixmap, parent)
{}

// Reset the rook's position
void Rook::resetPreviousPosition()
{
    DraggablePiece::resetPreviousPosition();
}

// Return the piece type as a string
QString Rook::pieceType() const
{
    return "Rook";
}

// Calculate valid moves for the rook
QList<QPoint> Rook::calculateValidMoves(int startX, int startY) const
{
    QList<QPoint> validMoves;

    // The Rook can move any number of squares vertically or horizontally
    for (int i = 1; i < 8; ++i) {
        validMoves.append(QPoint(startX + i, startY)); // Right
        validMoves.append(QPoint(startX - i, startY)); // Left
        validMoves.append(QPoint(startX, startY + i)); // Up
        validMoves.append(QPoint(startX, startY - i)); // Down
    }

    // Filter out moves that go outside the board's boundaries
    validMoves.erase(std::remove_if(validMoves.begin(),
                                    validMoves.end(),
                                    [](const QPoint &move) {
                                        return move.x() < 0 || move.x() >= 8 || move.y() < 0
                                               || move.y() >= 8;
                                    }),
                     validMoves.end());

    return validMoves;
}

// Calculate the attack range for the rook (same as valid moves)
QList<QPoint> Rook::calculateAttackRange(int startX, int startY) const
{
    return calculateValidMoves(startX, startY);
}

// Check if a move is valid for the rook
bool Rook::isValidMove(const QPoint &destination) const
{
    QList<QPoint> validMoves = calculateValidMoves(currentLocation.x(), currentLocation.y());
    return validMoves.contains(destination);
}

// Move the rook to the specified location
void Rook::moveTo(const QPoint &destination)
{
    DraggablePiece::moveTo(destination);
}
