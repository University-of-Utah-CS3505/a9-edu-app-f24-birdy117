#include "foolsmate.h"
#include <QTimer>

/* NOTE:
 * Level 1 index order:
 * 0-7 back row of white, starting with left rook moving right.
 * 8-15 white pawns
 * 16-23 black pawns
 * 24-31 back row of black, starting with left rook moving right.
 */

Foolsmate::Foolsmate(ChessBoard* board, QObject* parent)
    : QObject(parent)
    , board(board) {

}

Foolsmate::~Foolsmate() {
    delete board;
}

void Foolsmate::moveFirstWhitePawn() {
    DraggablePiece* whitePawn = board->allPieces[10];

    qDebug() << whitePawn->pieceType();
    qDebug() << whitePawn->getPieceColor();

    QPoint pos(2, 2);
    // Use a QTimer to delay the movement by 1 second
    QTimer::singleShot(2000, this, [whitePawn, pos]() {
        whitePawn->moveTo(pos);
        qDebug() << "White pawn moved to" << pos;
    });
}


void Foolsmate::firstMove() {
    board->highlightSquare(3, 1, Qt::yellow);

    QString message = "1. Where should the highlighted pawn move?";
    emit updateStatusLabel(message);
    qDebug() << "Signal emitted:" << message;
}

void Foolsmate::moveFirstBlackPawn() {
    DraggablePiece* blackPawn = board->allPieces[19];

    qDebug() << blackPawn->pieceType();
    qDebug() << blackPawn->getPieceColor();

    QPoint pos(3, 4);
    blackPawn->moveTo(pos);
}

void Foolsmate::moveSecondWhitePawn() {
    DraggablePiece* whitePawn = board->allPieces[9];

    qDebug() << whitePawn->pieceType();
    qDebug() << whitePawn->getPieceColor();

    QPoint pos(1, 3);

    // Use a QTimer to delay the movement by 1 second
    QTimer::singleShot(2000, this, [whitePawn, pos]() {
        whitePawn->moveTo(pos);
        qDebug() << "White pawn moved to" << pos;
    });
}
void Foolsmate::secondMove() {
    //board->unhighlightSquare(3, 1);
    board-> deleteHighlights();
    board->highlightSquare(4, 0, Qt::yellow);

    QString message = "2. Where should the highlighted queen move?";
    emit updateStatusLabel(message);
    qDebug() << "Signal emitted:" << message;
}

void Foolsmate::moveBlackQueen() {
    DraggablePiece* blackQueen = board->allPieces[28];

    qDebug() << blackQueen->pieceType();
    qDebug() << blackQueen->getPieceColor();

    QPoint pos(0, 3);
    blackQueen->moveTo(pos);
}

void Foolsmate::thirdMove() {
    //board->unhighlightSquare(4,0);
    board->deleteHighlights();
    board->highlightSquare(0, 4, Qt::yellow);

    QString message = "3. Where should the queen move now?";
    emit updateStatusLabel(message);
    qDebug() << "Signal emitted:" << message;
}

void Foolsmate::moveThirdWhitePawn() {
    DraggablePiece* whitePawn = board->allPieces[12];

    qDebug() << whitePawn->pieceType();
    qDebug() << whitePawn->getPieceColor();

    QPoint pos(4, 2);
    // Use a QTimer to delay the movement by 1 second
    QTimer::singleShot(2000, this, [whitePawn, pos]() {
        whitePawn->moveTo(pos);
        qDebug() << "White pawn moved to" << pos;
    });
}

void Foolsmate::moveBlackQueen2() {
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

    //board->unhighlightSquare(0,4);
    board->deleteHighlights();

}
