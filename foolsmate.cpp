#include "FoolsMate.h"

FoolsMate::FoolsMate(ChessBoard* board, QObject* parent)
    : QObject(parent), board(board), currentMoveIndex(0), highlight(nullptr) {
    // Define the sequence of moves for Fool's Mate (from, to)
    expectedMoves = {
        {6, 5}, {4, 5},  // White: f2-f3
        {1, 4}, {3, 4},  // Black: e7-e5
        {6, 6}, {4, 6},  // White: g2-g4
        {0, 3}, {4, 7}   // Black: Qd8-h4
    };
}

void FoolsMate::startLesson() {
    // Highlight the first move
    highlightSquare(6, 5);
}

void FoolsMate::highlightSquare(int row, int col) {
    clearHighlight();
    highlight = new QGraphicsEllipseItem(
        col * ChessBoard::SQUARE_SIZE, row * ChessBoard::SQUARE_SIZE,
        ChessBoard::SQUARE_SIZE, ChessBoard::SQUARE_SIZE);
    highlight->setBrush(QBrush(Qt::yellow));
    highlight->setPen(Qt::NoPen);
    board->scene->addItem(highlight);
}

void FoolsMate::clearHighlight() {
    if (highlight) {
        board->scene->removeItem(highlight);
        delete highlight;
        highlight = nullptr;
    }
}

bool FoolsMate::isMoveValid(QPoint start, QPoint end) {
    // Check if the move matches the expected sequence
    if (currentMoveIndex >= expectedMoves.size())
        return false;

    QPoint expectedStart = expectedMoves[currentMoveIndex];
    QPoint expectedEnd = expectedMoves[currentMoveIndex + 1];
    return (start == expectedStart && end == expectedEnd);
}

void FoolsMate::handlePlayerMove() {
    // TODO: Get the player's move from the board (implement this logic)
    QPoint start = {0,0}; /* Logic to get starting square */
    QPoint end = {0,0}; /* Logic to get ending square */

    if (isMoveValid(start, end)) {
        currentMoveIndex += 2;
        clearHighlight();

        if (currentMoveIndex < expectedMoves.size()) {
            // Highlight the next move
            QPoint nextMove = expectedMoves[currentMoveIndex];
            highlightSquare(nextMove.x(), nextMove.y());
        }
        else {
            emit lessonComplete();
        }
    }
    else {
        // Invalid move feedback
        // TODO: Add logic here, display a message
    }
}

void FoolsMate::makeBlackMove() {
    // Simulate Black's move
    if (currentMoveIndex < expectedMoves.size()) {
        QPoint start = expectedMoves[currentMoveIndex];
        QPoint end = expectedMoves[currentMoveIndex + 1];

        // Move the piece on the board
        // Add your logic here to animate the move

        currentMoveIndex += 2;

        // Highlight the next move for White
        if (currentMoveIndex < expectedMoves.size()) {
            QPoint nextMove = expectedMoves[currentMoveIndex];
            highlightSquare(nextMove.x(), nextMove.y());
        }
    }
}
