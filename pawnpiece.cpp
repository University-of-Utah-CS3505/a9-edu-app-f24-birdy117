#include "PawnPiece.h"
#include "ChessBoard.h"

PawnPiece::PawnPiece(const QPixmap& pixmap, QGraphicsItem* parent)
    : DraggablePiece(pixmap, parent) {}

bool PawnPiece::isValidMove(const QPointF& destination) {

    // calculate the movement delta in x and y directions between the start position and the destination
    int deltaX = destination.x() - dragStartPos.x();
    int deltaY = destination.y() - dragStartPos.y();

    // check if vertical only moved up a square and horizontal is 0(didnt move)
    if (std::abs(deltaY) == SQUARE_SIZE && deltaX == 0) {
        return true;
    }

    return false;
}
