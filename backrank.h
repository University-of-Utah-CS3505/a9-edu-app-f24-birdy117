#ifndef BACKRANK_H
#define BACKRANK_H

#include <QObject>
#include "chessboard.h"

class BackRank : public QObject
{
    Q_OBJECT
public:
    ChessBoard *board;
    QTimer *timer;

    BackRank(ChessBoard *board, QObject *parent = nullptr);

public slots:
    void moveRook();
    void moveBlackKing();
    void moveBishop();
};

#endif // BACKRANK_H
