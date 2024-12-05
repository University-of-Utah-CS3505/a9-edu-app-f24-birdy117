#ifndef ROOKPIECE_H
#define ROOKPIECE_H

#include "DraggablePiece.h"
#include <QPixmap>

class RookPiece : public DraggablePiece {
public:

    RookPiece(const QPixmap& pixmap, QGraphicsItem* parent = nullptr);

    bool isValidMove(const QPointF& destination) override;
};

#endif // ROOKPIECE_H
