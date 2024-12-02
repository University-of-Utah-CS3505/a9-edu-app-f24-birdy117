#include "chessboard.h"
#include <QBrush>
#include <QVBoxLayout>

const int ChessBoard::SQUARE_SIZE = 50;
const int ChessBoard::BOARD_SIZE = 8;

ChessBoard::ChessBoard(QWidget* parent) : QWidget(parent) {
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);

    view->setFixedSize(BOARD_SIZE * SQUARE_SIZE + 2, BOARD_SIZE * SQUARE_SIZE + 2);
    view->setSceneRect(0, 0, BOARD_SIZE * SQUARE_SIZE, BOARD_SIZE * SQUARE_SIZE);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(view);
    setLayout(layout);

    setupBoard();
    setupPieces();
}


void ChessBoard::setupBoard() {
    QPixmap whiteTile(":/Images/whiteTile.png");
    QPixmap greenTile(":/Images/greenTile.png");

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            QGraphicsRectItem* square = new QGraphicsRectItem(col * SQUARE_SIZE, row * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE);

            // Set the color based on the row and column
            if ((row + col) % 2 == 0) {
                square->setBrush(QBrush(whiteTile));
            } else {
                square->setBrush(QBrush(greenTile));
            }

            square->setPen(Qt::NoPen);
            square->setZValue(-1);
            scene->addItem(square);
        }
    }
}

void ChessBoard::setupPieces() {
    QString pieceImages[8][8] = {
        {":/Images/RookB.png", ":/Images/KnightB.png", ":/Images/BishopB.png", ":/Images/QueenB.png",
         ":/Images/KingB.png", ":/Images/BishopB.png", ":/Images/KnightB.png", ":/Images/RookB.png"},
        {":/Images/PawnB.png", ":/Images/PawnB.png", ":/Images/PawnB.png", ":/Images/PawnB.png",
         ":/Images/PawnB.png", ":/Images/PawnB.png", ":/Images/PawnB.png", ":/Images/PawnB.png"},
        {"", "", "", "", "", "", "", ""},
        {"", "", "", "", "", "", "", ""},
        {"", "", "", "", "", "", "", ""},
        {"", "", "", "", "", "", "", ""},
        {":/Images/PawnW.png", ":/Images/PawnW.png", ":/Images/PawnW.png", ":/Images/PawnW.png",
         ":/Images/PawnW.png", ":/Images/PawnW.png", ":/Images/PawnW.png", ":/Images/PawnW.png"},
        {":/Images/RookW.png", ":/Images/KnightW.png", ":/Images/BishopW.png", ":/Images/QueenW.png",
         ":/Images/KingW.png", ":/Images/BishopW.png", ":/Images/KnightW.png", ":/Images/RookW.png"}
    };

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (!pieceImages[row][col].isEmpty()) {
                QPixmap pixmap(pieceImages[row][col]);

                // Determine the piece name (e.g., "RookB", "PawnW")
                QString pieceName;
                if (row == 0 || row == 7) {  // Rooks, Knights, Bishops, Queen, King
                    if (col == 0 || col == 7) pieceName = (row == 0 ? "RookB" : "RookW");
                    else if (col == 1 || col == 6) pieceName = (row == 0 ? "KnightB" : "KnightW");
                    else if (col == 2 || col == 5) pieceName = (row == 0 ? "BishopB" : "BishopW");
                    else if (col == 3) pieceName = (row == 0 ? "QueenB" : "QueenW");
                    else if (col == 4) pieceName = (row == 0 ? "KingB" : "KingW");
                }
                else if (row == 1 || row == 6) {  // Pawns
                    pieceName = (row == 1 ? "PawnB" : "PawnW");
                }

                // Create the DraggablePiece and set its name
                DraggablePiece* piece = new DraggablePiece(pixmap, pieceName);

                // Center the piece within the square
                int offsetX = (SQUARE_SIZE - pixmap.width()) / 2;
                int offsetY = (SQUARE_SIZE - pixmap.height()) / 2;
                piece->setPos(col * SQUARE_SIZE + offsetX, row * SQUARE_SIZE + offsetY);
                piece->setZValue(1);
                scene->addItem(piece);
            }
        }
    }
}

QPoint ChessBoard::getSquareFromPixels(const QPointF& position) {
    int col = position.x() / SQUARE_SIZE;
    int row = position.y() / SQUARE_SIZE;
    return QPoint(row, col);
}

DraggablePiece* ChessBoard::getPieceAt(int col, int row) {
    // Convert the grid coordinates to actual pixel positions
    qreal targetX = col * SQUARE_SIZE + SQUARE_SIZE / 2;
    qreal targetY = row * SQUARE_SIZE + SQUARE_SIZE / 2;

    // Iterate through the items in the scene
    for (auto* item : scene->items()) {
        auto* piece = dynamic_cast<DraggablePiece*>(item);
        if (piece) {
            // Calculate the center position of the piece
            QPointF pieceCenter = piece->pos() + QPointF(piece->boundingRect().width() / 2,
                                                         piece->boundingRect().height() / 2);
            // Check if the piece is approximately at the target position
            if (qAbs(pieceCenter.x() - targetX) < 1e-2 && qAbs(pieceCenter.y() - targetY) < 1e-2) {
                return piece;
            }
        }
    }

    // // No piece found at the specified position
    // return nullptr;

    // for (auto* item : scene->items()) {
    //     auto* piece = dynamic_cast<DraggablePiece*>(item);
    //     if (piece && piece->getSquare() == QPoint(x, y)) {
    //         return piece;  // Return the piece found at the position
    //     }
    // }
    return nullptr;
}

void ChessBoard::movePiece(const QPoint& start, const QPoint& end) {
    qDebug() << "movePiece";

    // Calculate pixel positions for the start and end squares
    int startX = start.x() * SQUARE_SIZE;
    int startY = start.y() * SQUARE_SIZE;
    int endX = end.x() * SQUARE_SIZE;
    int endY = end.y() * SQUARE_SIZE;

    // Find the piece at the starting position
    for (auto* item : scene->items(QRectF(startX, startY, SQUARE_SIZE, SQUARE_SIZE))) {
        DraggablePiece* piece = dynamic_cast<DraggablePiece*>(item);
        if (piece) {
            // Move the piece to the end position
            piece->setPos(endX + (SQUARE_SIZE - piece->boundingRect().width()) / 2,
                          endY + (SQUARE_SIZE - piece->boundingRect().height()) / 2);
            return;
        }
    }

    DraggablePiece* movedPiece = getPieceAt(startX, startY);
    if (movedPiece) {
        // Update the piece's position
        movedPiece->setPos(endX, endY);

        // Update the lastMovedPiece
        lastMovedPiece = movedPiece;
    }
}


