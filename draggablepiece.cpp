#include "DraggablePiece.h"
#include <QCursor>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

DraggablePiece::DraggablePiece(const QPixmap& pixmap, QGraphicsItem* parent)
    : QGraphicsPixmapItem(pixmap, parent)
    , dragStartPos(QPointF(0, 0)) { }

void DraggablePiece::moveTo(const QPoint &destination)
{
    QPoint point(destination.x() * SQUARE_SIZE, destination.y() * SQUARE_SIZE);
    setPos(snapToGrid(point));
}

void DraggablePiece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    dragStartPos = pos();
    QGraphicsPixmapItem::mousePressEvent(event);
}

void DraggablePiece::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsPixmapItem::mouseMoveEvent(event);
}

void DraggablePiece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem *> collidingItems = scene()->items(event->scenePos());

    for (QGraphicsItem *item : collidingItems) {
        if (item != this && item->type() == DraggablePiece::Type) {
            delete item;
        }
    }
    setPos(snapToGrid(pos()));
    QGraphicsPixmapItem::mouseReleaseEvent(event);
}

QPointF DraggablePiece::snapToGrid(const QPointF &position)
{
    int col = (position.x() + SQUARE_SIZE / 2) / SQUARE_SIZE;
    int row = (position.y() + SQUARE_SIZE / 2) / SQUARE_SIZE;

    // Calculate center of square
    qreal snappedX = col * SQUARE_SIZE + SQUARE_SIZE / 2 - boundingRect().width() / 2;
    qreal snappedY = row * SQUARE_SIZE + SQUARE_SIZE / 2 - boundingRect().height() / 2;

    return QPointF(snappedX, snappedY);
}
