#include "pawn.h"

Pawn::Pawn(Color color, const QPoint& startLocation, const QPixmap& pixmap, QGraphicsItem* parent)
    : DraggablePiece(color, startLocation, pixmap, parent) {
}
