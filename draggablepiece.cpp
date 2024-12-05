#include <QGraphicsScene>
#include "draggablepiece.h"

DraggablePiece::DraggablePiece(const QPixmap& pixmap, QGraphicsItem* parent)
    : QGraphicsPixmapItem(pixmap, parent) {
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

void DraggablePiece::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    dragStartPos = pos();
    QGraphicsPixmapItem::mousePressEvent(event);
}

void DraggablePiece::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsPixmapItem::mouseMoveEvent(event);
}

void DraggablePiece::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    // Get the position after the drag
    QPointF releasePos = snapToGrid(pos());

    QList<QGraphicsItem*> collidingItems = scene()->items(event->scenePos());

    for(QGraphicsItem* item : collidingItems) {
        if(item != this && item->type() == DraggablePiece::Type) {
            if(isValidMove(releasePos)){
                delete item;
            }
        }
    }
    if(isValidMove(releasePos)){
        setPos(releasePos);
    } else{
        setPos(dragStartPos); // back to the start position if invalid
    }

    QGraphicsPixmapItem::mouseReleaseEvent(event);
}

bool DraggablePiece::isValidMove(const QPointF& destination) {
    return false;
}

QPointF DraggablePiece::snapToGrid(const QPointF& position) {
    // Calculate nearest square column and row based on the piece's current position
    int col = (position.x() + SQUARE_SIZE / 2) / SQUARE_SIZE;
    int row = (position.y() + SQUARE_SIZE / 2) / SQUARE_SIZE;

    // Calculate the center of the square the piece is closest to
    qreal snappedX = col * SQUARE_SIZE + SQUARE_SIZE / 2 - boundingRect().width() / 2;
    qreal snappedY = row * SQUARE_SIZE + SQUARE_SIZE / 2 - boundingRect().height() / 2;

    // Return snapped position
    return QPointF(snappedX, snappedY);
}


