#include "chessboard.h"
#include <QBrush>
#include <QVBoxLayout>

const int ChessBoard::SQUARE_SIZE = 50;
const int ChessBoard::BOARD_SIZE = 8;

ChessBoard::ChessBoard(QWidget* parent) : QWidget(parent) {
    // Initialize the QGraphicsScene and QGraphicsView
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);

    // Configure the view
    view->setFixedSize(BOARD_SIZE * SQUARE_SIZE + 2, BOARD_SIZE * SQUARE_SIZE + 2);
    view->setSceneRect(0, 0, BOARD_SIZE * SQUARE_SIZE, BOARD_SIZE * SQUARE_SIZE);

    // Layout the view within the widget
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(view);
    setLayout(layout);

    // Set up the chessboard and pieces
    setupBoard();
    setupPieces();
}


void ChessBoard::setupBoard() {
    QPixmap whiteTile(":/Images/whiteTile.png");
    QPixmap greenTile(":/Images/greenTile.png");

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            // Create a square
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
                DraggablePiece* piece = new DraggablePiece(pixmap);

                // center the piece within the square
                int offsetX = (SQUARE_SIZE - pixmap.width()) / 2;
                int offsetY = (SQUARE_SIZE - pixmap.height()) / 2;
                piece->setPos(col * SQUARE_SIZE + offsetX, row * SQUARE_SIZE + offsetY);
                piece->setZValue(1);
                // add piece to the scene
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

DraggablePiece* ChessBoard::getLastMovedPiece() {
    for (auto* item : scene->items()) {
        auto* piece = dynamic_cast<DraggablePiece*>(item);
        if (piece && piece->isUnderMouse()) {
            return piece;
        }
    }
    return nullptr;
}

void ChessBoard::movePiece(const QPoint& start, const QPoint& end) {
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
}


