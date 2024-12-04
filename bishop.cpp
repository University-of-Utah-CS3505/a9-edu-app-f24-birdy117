#include "bishop.h"

Bishop::Bishop(Color color, const QPoint& startLocation, const QPixmap& pixmap, QGraphicsItem* parent)
    : DraggablePiece(color, startLocation, pixmap, parent) {
}

void Bishop::resetPreviousPosition() {
    // Call base class method for shared functionality
    DraggablePiece::resetPreviousPosition();
    // Additional Pawn-specific behavior can be added here
}

bool Bishop::isCaptured() const {
    // Inherited from draggablePiece
    return hasBeenCaptured;
}

void Bishop::setCaptured(bool status) {
    hasBeenCaptured = status;
}

void Bishop::setFirstMove(bool status) {
    firstMove = status;
}

QString Bishop::pieceType() const {
    return "Bishop";
}

QList<QPoint> Bishop::calculateValidMoves(int startX, int startY) const {
    QList<QPoint> validMoves;

    // Basic movement: Pawn can move one square forward (dy == 1)
    if (pieceColor == White) {
        validMoves.append(QPoint(startX, startY + 1)); // Move one square forward
    } else if (pieceColor == Black) {
        validMoves.append(QPoint(startX, startY - 1)); // Move one square forward
    }

    return validMoves;
}

QList<QPoint> Bishop::calculateAttackRange(int startX, int startY) const {
    QList<QPoint> attackRange;

    // Attack diagonally
    if (pieceColor == White) {
        // Attack diagonally left forward
        attackRange.append(QPoint(startX - 1, startY + 1));
        // Attack diagonally right forward
        attackRange.append(QPoint(startX + 1, startY + 1));
    } else if (pieceColor == Black) {
        // Attack diagonally left backward
        attackRange.append(QPoint(startX - 1, startY - 1));
        // Attack diagonally right backward
        attackRange.append(QPoint(startX + 1, startY - 1));
    }

    return attackRange;
}

bool Bishop::isValidMove(const QPoint& destination) const {
    // Check if the destination is within valid move range
    QList<QPoint> validMoves = calculateValidMoves(currentLocation.x(), currentLocation.y());
    return validMoves.contains(destination);
}

void Bishop::moveTo(const QPoint& destination) {
    DraggablePiece::moveTo(destination);
    firstMove = false;
}
