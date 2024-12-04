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
    for(int i = 0; i < 8; i++){
        // Bishop can move Northwest Diagnolly
        validMoves.append(QPoint(startX - i, startY + i));
        // Bishop can move Northeast Diagnolly
        validMoves.append(QPoint(startX + i, startY + i));
        // Bishop can move Southwest Diagnolly
        validMoves.append(QPoint(startX - i, startY - i));
        // Bishop can move Southeast Diagnolly
        validMoves.append(QPoint(startX + i, startY - i));
    }
    return validMoves;
}

QList<QPoint> Bishop::calculateAttackRange(int startX, int startY) const {
    QList<QPoint> attackRange;  
    for(int i = 0; i < 8; i++){
        // Attack diagonally left forward
        attackRange.append(QPoint(startX - i, startY + i));
        // Attack diagonally right forward
        attackRange.append(QPoint(startX + i, startY + i));
        // Attack diagonally left backward
        attackRange.append(QPoint(startX - i, startY - i));
        // Attack diagonally right backward
        attackRange.append(QPoint(startX + i, startY - i));
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
