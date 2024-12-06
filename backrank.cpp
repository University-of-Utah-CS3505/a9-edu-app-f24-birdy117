#include "backrank.h"

BackRank::BackRank(ChessBoard *board, QObject *parent)
    : QObject(parent)
    , board(board)
{}

void BackRank::moveRook() {}

void BackRank::moveBlackKing() {}

void BackRank::moveBishop() {}
