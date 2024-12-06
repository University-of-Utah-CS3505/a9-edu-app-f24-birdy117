#include "foolsmate.h"
#include <QTimer>

/* NOTE:
 * Level 1 index order:
 * 0-7 back row of white, starting with left rook moving right.
 * 8-15 white pawns
 * 16-23 black pawns
 * 24-31 back row of black, starting with left rook moving right.
 */

foolsmate::foolsmate(ChessBoard* board, QObject* parent)
    : QObject(parent)
    , board(board) {

}

void foolsmate::moveFirstWhitePawn() {
    DraggablePiece* whitePawn = board->allPieces[10];

    qDebug() << whitePawn->pieceType();
    qDebug() << whitePawn->getPieceColor();

    QPoint pos(2, 2);
    whitePawn->moveTo(pos);
}

void foolsmate::firstMove() {
    board->highlightSquare(4, 1, Qt::yellow);

    QString message = "1. Where should the highlighted pawn move?";
    emit updateStatusLabel(message);
    qDebug() << "Signal emitted:" << message;
}

void foolsmate::moveFirstBlackPawn() {
    DraggablePiece* blackPawn = board->allPieces[20];

    qDebug() << blackPawn->pieceType();
    qDebug() << blackPawn->getPieceColor();

    QPoint pos(4, 4);
    blackPawn->moveTo(pos);
}

void foolsmate::moveSecondWhitePawn() {
    DraggablePiece* whitePawn = board->allPieces[9];

    qDebug() << whitePawn->pieceType();
    qDebug() << whitePawn->getPieceColor();

    QPoint pos(1, 3);
    whitePawn->moveTo(pos);
}

void foolsmate::secondMove() {
    board->unhighlightSquare(4,1);
    board->highlightSquare(4, 0, Qt::yellow);

    QString message = "2. Where should the highlighted queen move?";
    emit updateStatusLabel(message);
    qDebug() << "Signal emitted:" << message;
}

void foolsmate::moveBlackQueen() {
    DraggablePiece* blackQueen = board->allPieces[28];

    qDebug() << blackQueen->pieceType();
    qDebug() << blackQueen->getPieceColor();

    QPoint pos(0, 3);
    blackQueen->moveTo(pos);
}

void foolsmate::thirdMove() {
    board->unhighlightSquare(4,0);
    board->highlightSquare(0, 4, Qt::yellow);

    QString message = "3. Where should the queen move now?";
    emit updateStatusLabel(message);
    qDebug() << "Signal emitted:" << message;
}

void foolsmate::moveThirdWhitePawn() {
    DraggablePiece* whitePawn = board->allPieces[12];

    qDebug() << whitePawn->pieceType();
    qDebug() << whitePawn->getPieceColor();

    QPoint pos(4, 2);
    whitePawn->moveTo(pos);
}

void foolsmate::moveBlackQueen2() {
    DraggablePiece* blackQueen = board->allPieces[28];

    qDebug() << blackQueen->pieceType();
    qDebug() << blackQueen->getPieceColor();

    DraggablePiece* whiteKing = board->allPieces[3];

    // Move the white king off the board (invalid location)
    whiteKing->moveTo(QPoint(-1, -1));  // Move off the board (assuming (-1, -1) is out of bounds)
    qDebug() << "White King has been removed.";

    QPoint pos(3, 0);
    blackQueen->moveTo(pos);
    QString message = "Checkmate";
    emit updateStatusLabel(message);

    board->unhighlightSquare(0,4);

}
