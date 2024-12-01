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

private slots:
    void handlePlayerMove();

private:
    ChessBoard* board;
    QList<QPoint> expectedMoves;
    int currentMoveIndex;
    QGraphicsEllipseItem* highlight;

    void highlightSquare(int row, int col);
    void clearHighlight();
    bool isMoveValid(QPoint start, QPoint end);
    void makeBlackMove();

signals:
    void lessonComplete();
};

#endif // FOOLSMATE_H
