#ifndef BACKRANK_H
#define BACKRANK_H

#include "chessboard.h"
#include <QObject>

class BackRank : public QObject
{
    Q_OBJECT
public:
    ChessBoard* board;
    QTimer* timer;

    BackRank(ChessBoard* board, QObject* parent = nullptr);

public slots:
    void moveRook();
    void moveBlackKing();
    void moveBishop();
};

#endif // BACKRANK_H
