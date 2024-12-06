#include "backrank.h"

BackRank::BackRank(ChessBoard* board, QObject* parent)
    : QObject(parent)
    , board(board) {
    moveRook();
    moveBishop();
    qDebug() << "constructor";
}

void BackRank::moveRook() {
    emit rookMoved();
    qDebug() << "rook";
}

void BackRank::moveBlackKing() {

}

void BackRank::moveBishop() {
    emit rookMoved();
    qDebug() << "bishop";
}
