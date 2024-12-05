#ifndef KNIGHTPIECE_H
#define KNIGHTPIECE_H

#include "DraggablePiece.h"

class KnightPiece : public DraggablePiece {
public:

    KnightPiece(const QPixmap& pixmap, QGraphicsItem* parent = nullptr);

    bool isValidMove(const QPointF& destination) override;
};

#endif // KNIGHTPIECE_H
