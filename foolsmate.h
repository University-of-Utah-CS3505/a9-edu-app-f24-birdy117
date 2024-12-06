#ifndef FOOLSMATE_H
#define FOOLSMATE_H

#include "chessboard.h"
#include <QObject>
// #include "draggablepiece.h"

class Foolsmate : public QObject
{
    Q_OBJECT
public:
    ChessBoard* board;
    // QTimer* timer;

    Foolsmate(ChessBoard* board, QObject* parent = nullptr);
    ~Foolsmate();

    // public slots:
    void moveFirstWhitePawn();
    void firstMove();
    void moveFirstBlackPawn();
    void moveSecondWhitePawn();
    void secondMove();
    void moveBlackQueen();
    void thirdMove();
    void moveBlackQueen2();
    void moveThirdWhitePawn();

signals:
    void updateStatusLabel(const QString& message);
    void firstMoveDone();

};

#endif // FOOLSMATE_H
