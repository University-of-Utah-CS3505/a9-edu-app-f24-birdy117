#ifndef DRAGGABLEPIECE_H
#define DRAGGABLEPIECE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPoint>
#include <QString>

enum Color {
    White,
    Black
};

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

protected:
    // Current position on the board
    QPoint currentLocation;
    // Previous position on the board
    QPoint previousPosition;
    // Color of the piece (white or black)
    Color pieceColor;
    // True if it's the first move
    bool firstMove;
    // True if the piece is captured
    bool hasBeenCaptured;
    // Starting position of the piece
    QPointF dragStartPos;
    // Size of the chess tile
    int const SQUARE_SIZE = 50;

    ///
    /// \brief
    /// Places the piece at the center of the
    /// chess tile.
    ///
    /// \param position - position of the piece
    /// \return new coordinate position of the piece
    ///
    QPointF snapToGrid(const QPointF& position);

public:
    explicit DraggablePiece(Color color, const QPoint& startLocation, const QPixmap& pixmap, QGraphicsItem* parent = nullptr);

    // Getters and setters
    QPoint getCurrentLocation() const { return currentLocation; }
    void setCurrentLocation(const QPoint& location) { currentLocation = location; }
    QPoint getPreviousPosition() const { return previousPosition; }
    virtual void resetPreviousPosition() { previousPosition = QPoint(-1, -1); }
    Color getPieceColor() const { return pieceColor; }
    virtual bool isCaptured() const { return hasBeenCaptured; }
    virtual void setCaptured(bool status) { hasBeenCaptured = status; }
    virtual bool isFirstMove() const { return firstMove; }
    virtual void setFirstMove(bool status) { firstMove = status; }

    // Abstract methods for subclasses to implement
    virtual QString pieceType() const = 0;
    virtual QList<QPoint> calculateValidMoves(int startX, int startY) const = 0;
    virtual QList<QPoint> calculateAttackRange(int startX, int startY) const = 0;

    // Validation and movement methods
    virtual bool isValidMove(const QPoint& destination) const = 0;
    virtual void moveTo(const QPoint& destination);

    // Mouse interaction
    void setInteractive(bool interactive);
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // DRAGGABLEPIECE_H
