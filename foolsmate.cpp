#include "FoolsMate.h"
#include <QMessageBox>

FoolsMate::FoolsMate(ChessBoard* board, QObject* parent)
    : QObject(parent)
    , board(board)
    , currentMoveIndex(0)
    , startSquare(4, 6) // e2
    , endSquare(4, 4) // e4 {
 {
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

    // Get the piece at the start position of the expected move
    // QPoint startSquare = expectedMoves[currentMoveIndex]; // Current expected start square
    // QPoint endSquare = expectedMoves[currentMoveIndex + 1]; // Current expected end square

    DraggablePiece* pieceAtStart = board->getPieceAt(startSquare.x(), startSquare.y());
    qDebug() << "startX" << startSquare.x();
    qDebug() << "startY" << startSquare.y();
    qDebug() << "pieceAtStart" << pieceAtStart;

    // TODO: is always null
    if (!pieceAtStart) {
        qDebug() << "No piece at the start square. Returned.";
        return;
    }

    // TODO: the error is coming from here. I think getPieceAt isn't working
    // Verify if the piece was moved to the correct end square
    QPoint actualEndSquare = board->getSquareFromPixels(pieceAtStart->pos());
    qDebug() << "Expected end square:" << endSquare;
    qDebug() << "Actual end square:" << actualEndSquare;

    if (actualEndSquare == endSquare) {
        // Move was correct
        currentMoveIndex += 2;
        clearHighlight();

        if (currentMoveIndex < expectedMoves.size()) {
            // Highlight the next move
            QPoint nextStart = expectedMoves[currentMoveIndex];
            QPoint nextEnd = expectedMoves[currentMoveIndex + 1];
            highlightSquare(nextStart, nextEnd);
        } else {
            // Lesson complete
            emit lessonComplete();
        }
    } else {
        // Invalid move, reset piece to its original position
        QMessageBox::information(nullptr, "Invalid Move", "Please follow the highlighted move.");
        pieceAtStart->setPos(board->getSquareFromPixels(startSquare)); // Reset piece to its start position
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
