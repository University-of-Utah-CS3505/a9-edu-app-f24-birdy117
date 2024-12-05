#ifndef PAWNPIECE_H
#define PAWNPIECE_H

#include "DraggablePiece.h"

class PawnPiece : public DraggablePiece {
public:

    PawnPiece(const QPixmap& pixmap, QGraphicsItem* parent = nullptr);

    bool isValidMove(const QPointF& destination) override;
};

#endif // PAWNPIECE_H
