#include "queen.h"

Queen::Queen(Color color, const QPoint& startLocation, const QPixmap& pixmap, QGraphicsItem* parent)
    : DraggablePiece(color, startLocation, pixmap, parent) {
}

// Reset the queen's position
void Queen::resetPreviousPosition() {
    DraggablePiece::resetPreviousPosition();
}


// Return the piece type as a string
QString Queen::pieceType() const {
    return "Queen";
}

// Calculate valid moves for the queen
QList<QPoint> Queen::calculateValidMoves(int startX, int startY) const {
    QList<QPoint> validMoves;

    // The Queen can move like a Rook (vertically and horizontally)
    for (int i = 1; i < 8; ++i) {
        validMoves.append(QPoint(startX + i, startY)); // Right
        validMoves.append(QPoint(startX - i, startY)); // Left
        validMoves.append(QPoint(startX, startY + i)); // Up
        validMoves.append(QPoint(startX, startY - i)); // Down
    }

    // The Queen can also move like a Bishop (diagonally)
    for (int i = 1; i < 8; ++i) {
        validMoves.append(QPoint(startX + i, startY + i)); // Diagonal up-right
        validMoves.append(QPoint(startX - i, startY + i)); // Diagonal up-left
        validMoves.append(QPoint(startX + i, startY - i)); // Diagonal down-right
        validMoves.append(QPoint(startX - i, startY - i)); // Diagonal down-left
    }

    // Filter out moves that go outside the board's boundaries
    validMoves.erase(std::remove_if(validMoves.begin(), validMoves.end(), [](const QPoint& move) {
                         return move.x() < 0 || move.x() >= 8|| move.y() < 0 || move.y() >= 8;
                     }), validMoves.end());

    return validMoves;
}

// Calculate the attack range for the queen (same as valid moves)
QList<QPoint> Queen::calculateAttackRange(int startX, int startY) const {
    return calculateValidMoves(startX, startY);
}

// Check if a move is valid for the queen
bool Queen::isValidMove(const QPoint& destination) const {
    QList<QPoint> validMoves = calculateValidMoves(currentLocation.x(), currentLocation.y());
    return validMoves.contains(destination);
}

// Move the queen to the specified location
void Queen::moveTo(const QPoint& destination) {
    DraggablePiece::moveTo(destination);
}
