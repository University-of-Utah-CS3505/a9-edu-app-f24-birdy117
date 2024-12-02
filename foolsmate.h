#ifndef FOOLSMATE_H
#define FOOLSMATE_H

#include "chessboard.h"
#include <QObject>
#include <QGraphicsEllipseItem>
#include <QTimer>

class FoolsMate : public QObject {
    Q_OBJECT

public:
    FoolsMate(ChessBoard* board, QObject* parent = nullptr);

    void startLesson();

    ChessBoard* board;
    QList<QPoint> expectedMoves;
    int currentMoveIndex;
    QPoint startSquare;
    QPoint endSquare;
    QGraphicsRectItem* startHighlight = nullptr;
    QGraphicsRectItem* endHighlight = nullptr;

    void highlightSquare(QPoint start, QPoint end);
    void clearHighlight();
    bool isMoveValid(QPoint start, QPoint end);
    void makeBlackMove();

public slots:
    void handlePlayerMove();

signals:
    void lessonComplete();
};

#endif // FOOLSMATE_H
