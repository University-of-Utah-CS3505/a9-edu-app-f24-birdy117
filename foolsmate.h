#ifndef FOOLSMATE_H
#define FOOLSMATE_H

#include "chessboard.h"
#include <QObject>

class FoolsMate : public QObject
{
    Q_OBJECT
public:
    ChessBoard* board;
    QTimer* timer;

    FoolsMate(ChessBoard* board, QObject* parent = nullptr);
    void moveSecondWhitePawn();

    // public slots:
    void moveFirstWhitePawn();
    void firstMove();
};

#endif // FOOLSMATE_H
