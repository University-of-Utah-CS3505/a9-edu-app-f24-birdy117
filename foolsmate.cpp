#include "foolsmate.h"
#include <QTimer>

/* NOTE:
 * Level 1 index order:
 * 0-7 back row of white, starting with left rook moving right.
 * 8-15 white pawns
 * 16-23 black pawns
 * 24-31 back row of black, starting with left rook moving right.
 */

FoolsMate::FoolsMate(ChessBoard* board, QObject* parent)
    : QObject(parent)
    , board(board) {
    moveFirstWhitePawn();
    firstMove();

    // TODO: Timer not connecting
    // timer = new QTimer(this);
    // timer->setSingleShot(true);
    // timer->start(3000);
    // connect(timer, &QTimer::timeout, this, &FoolsMate::moveFirstWhitePawn);

}

void FoolsMate::moveFirstWhitePawn() {
    DraggablePiece* whitePawn = board->allPieces[12];

    qDebug() << whitePawn->pieceType();
    qDebug() << whitePawn->getPieceColor();

    QPoint pos(4, 3);
    whitePawn->moveTo(pos);
}

void FoolsMate::firstMove() {
    board->highlightSquare(1, 0, Qt::yellow);
    board->highlightSquare(2, 5, Qt::darkYellow);
}
