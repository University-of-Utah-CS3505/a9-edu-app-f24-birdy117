#include "DraggablePiece.h"

DraggablePiece::DraggablePiece(const QPixmap& pixmap, const QString& name, QGraphicsItem* parent)
    : QGraphicsPixmapItem(pixmap, parent)
    , pieceName(name) {
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    dragStartPos = pos();
}

void DraggablePiece::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    dragStartPos = pos();
    QGraphicsPixmapItem::mousePressEvent(event);
}

void DraggablePiece::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsPixmapItem::mouseMoveEvent(event);
}

void DraggablePiece::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    // snap the piece to nearest grid position to center piece
    setPos(snapToGrid(pos()));
    QGraphicsPixmapItem::mouseReleaseEvent(event);
}

QPointF DraggablePiece::snapToGrid(const QPointF& position) {
    // calculate nearest square column and row
    int col = (position.x() + SQUARE_SIZE / 2) / SQUARE_SIZE;
    int row = (position.y() + SQUARE_SIZE / 2) / SQUARE_SIZE;

    // calculate center of square
    qreal snappedX = col * SQUARE_SIZE + SQUARE_SIZE / 2 - boundingRect().width() / 2;
    qreal snappedY = row * SQUARE_SIZE + SQUARE_SIZE / 2 - boundingRect().height() / 2;

    return QPointF(snappedX, snappedY);
}

QString DraggablePiece::getPieceName() const {
    return pieceName;
}

void DraggablePiece::setPieceName(const QString& name) {
    pieceName = name;
}
