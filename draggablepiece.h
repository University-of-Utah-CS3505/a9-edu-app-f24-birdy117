#ifndef DRAGGABLEPIECE_H
#define DRAGGABLEPIECE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class DraggablePiece : public QGraphicsPixmapItem {

public:
    QPointF dragStartPos;
    QString pieceName;

    DraggablePiece(const QPixmap& pixmap, const QString& name, QGraphicsItem* parent = nullptr);
    QString getPieceName() const;
    void setPieceName(const QString& name);

signals:
    void pieceMoved();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    int SQUARE_SIZE = 50;
    QPointF snapToGrid(const QPointF& position);
};

#endif // DRAGGABLEPIECE_H
