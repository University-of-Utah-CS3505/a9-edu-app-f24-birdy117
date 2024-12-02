#include "FoolsMate.h"
#include <QMessageBox>

FoolsMate::FoolsMate(ChessBoard* board, QObject* parent)
    : QObject(parent)
    , board(board)
    , currentMoveIndex(0)
    , startSquare(0, 0)
    , endSquare(2, 2) {
// {
    // Define the sequence of moves for Fool's Mate (from, to)
    expectedMoves = {
        {6, 5}, {4, 5},  // White: f2-f3
        {1, 4}, {3, 4},  // Black: e7-e5
        {6, 6}, {4, 6},  // White: g2-g4
        {0, 3}, {4, 7}   // Black: Qd8-h4
    };
    qDebug() << "fools";
}

void FoolsMate::startLesson() {
    // Highlight the first move
    qDebug() << "startLesson";
    highlightSquare(startSquare, endSquare);
}

void FoolsMate::highlightSquare(QPoint start, QPoint end) {
    clearHighlight(); // Clear existing highlights

    qDebug() << "highlight";

    // Create and add start highlight
    startHighlight = new QGraphicsRectItem(start.x() * ChessBoard::SQUARE_SIZE, start.y() * ChessBoard::SQUARE_SIZE, ChessBoard::SQUARE_SIZE, ChessBoard::SQUARE_SIZE);
    startHighlight->setBrush(QBrush(Qt::yellow));  // Choose color for the highlight
    // startHighlight->setZValue(0);
    board->scene->addItem(startHighlight);

    // Create and add end highlight
    endHighlight = new QGraphicsRectItem(end.x() * ChessBoard::SQUARE_SIZE, end.y() * ChessBoard::SQUARE_SIZE, ChessBoard::SQUARE_SIZE, ChessBoard::SQUARE_SIZE);
    endHighlight->setBrush(QBrush(Qt::green));  // Choose color for the highlight
    board->scene->addItem(endHighlight);
}

void FoolsMate::clearHighlight() {
    qDebug() << "clear";

    if (startHighlight != nullptr) {
        board->scene->removeItem(startHighlight);
        delete startHighlight;  // Clean up the memory
        startHighlight = nullptr;  // Reset the pointer
    }

    // Remove end highlight if it exists
    if (endHighlight != nullptr) {
        board->scene->removeItem(endHighlight);
        delete endHighlight;
        endHighlight = nullptr;
    }
}

bool FoolsMate::isMoveValid(QPoint start, QPoint end) {
    // Check if the move matches the expected sequence
    qDebug() << "isMoveValid";

    if (currentMoveIndex >= expectedMoves.size())
        return false;

    QPoint expectedStart = expectedMoves[currentMoveIndex];
    QPoint expectedEnd = expectedMoves[currentMoveIndex + 1];
    return (start == expectedStart && end == expectedEnd);
}

void FoolsMate::handlePlayerMove() {
    qDebug() << "handlePlayerMove";

    // TODO: Get the player's move from the board (implement this logic)
    DraggablePiece* lastMovedPiece = board->getLastMovedPiece(); // You need to implement this in your ChessBoard class
    if (!lastMovedPiece)
        return;

    // Get the starting and ending positions
    QPointF startPos = lastMovedPiece->dragStartPos;  // Assume DraggablePiece stores its drag start position
    QPointF endPos = lastMovedPiece->pos();

    QPoint startSquare = board->getSquareFromPixels(startPos);
    QPoint endSquare = board->getSquareFromPixels(endPos);

    // QPoint start = {0,0}; /* Logic to get starting square */
    // QPoint end = {1,0}; /* Logic to get ending square */

    if (isMoveValid(startSquare, endSquare)) {
        currentMoveIndex += 2;
        clearHighlight();

        if (currentMoveIndex < expectedMoves.size()) {
            // Highlight the next move
            QPoint nextMove = expectedMoves[currentMoveIndex];
            // highlightSquare(startSquare, endSquare);
        }
        else {
            emit lessonComplete();
        }
    }
    // Invalid move
    else {
        // TODO: Add logic here, display a message
        QMessageBox::information(nullptr, "Invalid Move", "Please follow the highlighted move.");
        lastMovedPiece->setPos(startPos);
    }
}

void FoolsMate::makeBlackMove() {
    qDebug() << "makeBlackMove";

    static int moveStep = 0;

    // Define black's moves for Fool's Mate scenario
    // TODO: check that the coordinates are correct.
    // QPoint blackPawn1Start(1, 4); // e7
    // QPoint blackPawn1End(2, 4);   // e5 (should this be (3,4)?
    // QPoint blackPawn2Start(1, 5); // f7
    // QPoint blackPawn2End(2, 5);   // f6

    switch (moveStep) {
    case 0: // Black's first move: e7 to e5
        startSquare = QPoint(1, 4); // e7
        endSquare = QPoint(3, 4);   // e5
        break;
    case 1: // Black's second move: f7 to f6
        startSquare = QPoint(1, 5); // f7
        endSquare = QPoint(2, 5);   // f6
        break;
    default:
        // No more moves for Fool's Mate
        return;
    }

    // Call ChessBoard's movePiece method to handle the move
    board->movePiece(startSquare, endSquare);
    // board->movePiece({0,0}, {1,1});

    moveStep++;
}
