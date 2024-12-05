#include "KnightPiece.h"
#include <cmath>
#include <QDebug>

KnightPiece::KnightPiece(const QPixmap& pixmap, QGraphicsItem* parent)
    : DraggablePiece(pixmap, parent) {}

bool KnightPiece::isValidMove(const QPointF& destination){

    // convert starting and destination to grid coordinates
    int startX = dragStartPos.x() / SQUARE_SIZE;
    int startY = dragStartPos.y() / SQUARE_SIZE;
    int destX = destination.x() / SQUARE_SIZE;
    int destY = destination.y() / SQUARE_SIZE;

    // calculate absolute difference in X and Y direction between start and destination
    int deltaX = std::abs(destX - startX);
    int deltaY = std::abs(destY - startY);

    // true if the move forms L shape
    if ((deltaX == 2 && deltaY == 1) || (deltaX == 1 && deltaY == 2)) {
        return true;
    }
    return false;
}
