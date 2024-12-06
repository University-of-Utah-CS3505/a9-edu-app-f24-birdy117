#ifndef DRAGGABLEPIECE_H
#define DRAGGABLEPIECE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPoint>

///
/// \authors Anne Arnold, Nicole Glazier, Ethan Kerrigan
///          Emily Thai, Aaron Perez
///
/// \date 06 December 2024
///
/// \brief Base class to hold information for chess pieces.
/// It will track the location of the piece, revert to a
/// previous position, and validate movements.
///
class DraggablePiece : public QGraphicsPixmapItem {
public:
    // Starting position of the piece
    QPointF dragStartPos;
    // Size of the chess tile
    int const SQUARE_SIZE = 50;

    DraggablePiece(const QPixmap& pixmap, QGraphicsItem* parent = nullptr);

    ///
    /// \brief moveTo
    /// Moves piece to the desired coordinate.
    /// \param destination - coordinates of new position
    ///
    void moveTo(const QPoint &destination);

    // Mouse interaction
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    ///
    /// \brief
    /// Places the piece at the center of the
    /// chess tile.
    ///
    /// \param position - position of the piece
    /// \return new coordinate position of the piece
    ///
    QPointF snapToGrid(const QPointF &position);
};

#endif // DRAGGABLEPIECE_H
