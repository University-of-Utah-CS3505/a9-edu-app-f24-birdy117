#include "pawn.h"

// TODO: idk if this is working correctly

Pawn::Pawn(Color color, const QPoint& startLocation, const QPixmap& pixmap, QGraphicsItem* parent)
    : DraggablePiece(color, startLocation, pixmap, parent) {
}

void Pawn::resetPreviousPosition() {
    // Call base class method for shared functionality
    DraggablePiece::resetPreviousPosition();
    // Additional Pawn-specific behavior can be added here
}

bool Pawn::isCaptured() const {
    // Inherited from draggablePiece
    return hasBeenCaptured;
}

void Pawn::setCaptured(bool status) {
    hasBeenCaptured = status;
}

bool Pawn::isFirstMove() const {
    return firstMove;
}

void Pawn::setFirstMove(bool status) {
    firstMove = status;
}

QString Pawn::pieceType() const {
    return "Pawn";
}

QList<QPoint> Pawn::calculateValidMoves(int startX, int startY) const {
    QList<QPoint> validMoves;

    // Basic movement: Pawn can move one square forward (dy == 1)
    if (pieceColor == White) {
        validMoves.append(QPoint(startX, startY + 1)); // Move one square forward
        // Add special rules for first move (can move two squares forward)
        if (firstMove) {
            validMoves.append(QPoint(startX, startY + 2)); // First move can be two squares forward
        }
    } else if (pieceColor == Black) {
        validMoves.append(QPoint(startX, startY - 1)); // Move one square forward
        if (firstMove) {
            validMoves.append(QPoint(startX, startY - 2)); // First move can be two squares forward
        }
    }

    return validMoves;
}

QList<QPoint> Pawn::calculateAttackRange(int startX, int startY) const {
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

bool Pawn::isValidMove(const QPoint& destination) const {
    // Check if the destination is within valid move range
    QList<QPoint> validMoves = calculateValidMoves(currentLocation.x(), currentLocation.y());
    return validMoves.contains(destination);
}

void Pawn::moveTo(const QPoint& destination) {
    DraggablePiece::moveTo(destination);
    firstMove = false;
}
