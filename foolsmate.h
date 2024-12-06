#ifndef FOOLSMATE_H
#define FOOLSMATE_H

#include "chessboard.h"
#include <QObject>
#include "draggablepiece.h"

class foolsmate : public QObject
{
    Q_OBJECT
public:
    ChessBoard* board;
    QTimer* timer;

    foolsmate(ChessBoard* board, QObject* parent = nullptr);

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
