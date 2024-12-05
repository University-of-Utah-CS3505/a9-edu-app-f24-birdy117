#include "chessboard.h"
#include "pawn.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"

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
}

void ChessBoard::resetBoard() {
    // Clear all existing items from the scene
    QList<QGraphicsItem*> items = scene->items();
    for (QGraphicsItem* item : items) {
        if (DraggablePiece* piece = dynamic_cast<DraggablePiece*>(item)) {
            scene->removeItem(piece);
            delete piece;
        }
    }

    // Set up the initial board state again
    // setupPieces();
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
            scene->addItem(square);
        }
    }
}

void ChessBoard::setupPieces(const QString pieceImages[8][8]) {

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (!pieceImages[row][col].isEmpty()) {
                QPixmap pixmap(pieceImages[row][col]);
                DraggablePiece* piece = nullptr;
                Color pieceColor = (row < 2) ? Color::White : Color::Black;

                if (row == 1 || row == 6) {
                    piece = new Pawn(pieceColor, QPoint(col, row), pixmap);
                } else if (pieceImages[row][col].contains("Rook")) {
                    piece = new Rook(pieceColor, QPoint(col, row), pixmap);
                } else if (pieceImages[row][col].contains("King")) {
                    piece = new King(pieceColor, QPoint(col, row), pixmap);
                } else if (pieceImages[row][col].contains("Queen")) {
                    piece = new Queen(pieceColor, QPoint(col, row), pixmap);
                } else if (pieceImages[row][col].contains("Knight")) {
                    piece = new Knight(pieceColor, QPoint(col, row), pixmap);
                } else if (pieceImages[row][col].contains("Bishop")) {
                    piece = new Bishop(pieceColor, QPoint(col, row), pixmap);
                }

                if (piece) {
                    int offsetX = (SQUARE_SIZE - pixmap.width()) / 2;
                    int offsetY = (SQUARE_SIZE - pixmap.height()) / 2;
                    piece->setPos(col * SQUARE_SIZE + offsetX, row * SQUARE_SIZE + offsetY);
                    scene->addItem(piece);
                    piece->setZValue(1);

                    /* NOTE:
                     * Level 1 index order:
                     * 0-7 back row of white, starting with left rook moving right.
                     * 8-15 white pawns
                     * 16-23 black pawns
                     * 24-31 back row of black, starting with left rook moving right.
                     *
                     * Level 2:
                     * 0 black rook
                     * 1 black king
                     * 2-4 black pawns
                     * 5-7 white pawns
                     * 8 white rook
                     * 9 black king
                     *
                     * Level 3:
                     * 0 black king
                     * 1 white queen
                     * 2 white king
                     */
                    allPieces.push_back(piece);
                }
            }
        }
    }
    // int i = 0;
    // for(auto* piece : allPieces) {
    //     qDebug() << i << piece->pieceType();
    //     ++i;
    // }
}

void ChessBoard::highlightSquare(int col, int row, QColor color) {
    QGraphicsRectItem* highlight = new QGraphicsRectItem();
    highlight->setRect(col * SQUARE_SIZE, (BOARD_SIZE - row - 1) * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE);
    highlight->setBrush(color);
    highlight->setOpacity(0.5);

    scene->addItem(highlight);
    highlight->setZValue(0);
}
