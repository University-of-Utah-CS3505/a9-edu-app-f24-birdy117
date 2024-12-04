#include "DraggablePiece.h"
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

DraggablePiece::DraggablePiece(Color color, const QPoint& startLocation, const QPixmap& pixmap, QGraphicsItem* parent)
    : QGraphicsPixmapItem(pixmap, parent)
    , currentLocation(startLocation)
    , previousPosition(startLocation)
    , pieceColor(color)
    , firstMove(true)
    , hasBeenCaptured(false)
    , dragStartPos(QPointF(0, 0)) {
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

// General move to a new location
void DraggablePiece::moveTo(const QPoint& destination) {
    previousPosition = currentLocation; // Track current location before moving
    currentLocation = destination;     // Update to the new location
    // moveHistory.push_back(destination); // Record the move in the history
    setPos(destination.x() * pixmap().width(), destination.y() * pixmap().height());
}

// Mouse interaction
void DraggablePiece::setInteractive(bool interactive) {
    setFlag(QGraphicsItem::ItemIsMovable, interactive);
    setFlag(QGraphicsItem::ItemIsSelectable, interactive);
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
