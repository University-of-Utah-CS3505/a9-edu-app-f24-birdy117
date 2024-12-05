#ifndef DRAGGABLEPIECE_H
#define DRAGGABLEPIECE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class DraggablePiece : public QGraphicsPixmapItem {
public:
    DraggablePiece(const QPixmap& pixmap, QGraphicsItem* parent = nullptr);
    virtual bool isValidMove(const QPointF& destination);
    int SQUARE_SIZE = 50;
    QPointF dragStartPos;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:

    QPointF snapToGrid(const QPointF& position);
};

#endif // DRAGGABLEPIECE_H
