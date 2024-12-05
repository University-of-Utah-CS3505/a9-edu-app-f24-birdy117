#include "RookPiece.h"
#include "ChessBoard.h"
#include <cmath>

RookPiece::RookPiece(const QPixmap& pixmap, QGraphicsItem* parent)
    : DraggablePiece(pixmap, parent) {}

bool RookPiece::isValidMove(const QPointF& destination) {

    // calculate absolute difference in X and Y direction between start and destination
    int deltaX = std::abs(destination.x() - dragStartPos.x());
    int deltaY = std::abs(destination.y() - dragStartPos.y());

    // check if rook is moving only horizontally or only vertically
    if ((deltaX == 0 && deltaY > 0) || (deltaY == 0 && deltaX > 0)) {
        return true;
    }

    return false;
}
