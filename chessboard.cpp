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

    for (auto* highlight : highlights) {
        scene->removeItem(highlight);
        delete highlight;
    }
    highlights.clear();

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

            QColor color;
            // Set the color based on the row and column
            if ((row + col) % 2 == 0) {
                color = whiteTile.toImage().pixelColor(0, 0);  // Use image color as base
                square->setBrush(QBrush(whiteTile));
            } else {
                color = greenTile.toImage().pixelColor(0, 0);  // Use image color as base
                square->setBrush(QBrush(greenTile));
            }

            originalColors[row][col] = color; // Store the original color

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

void ChessBoard::unhighlightSquare(int col, int row) {
    // Remove any existing highlights for the square at (col, row)
    for (QGraphicsRectItem* highlight : highlights) {
        if (highlight->rect().x() == col * SQUARE_SIZE && highlight->rect().y() == (BOARD_SIZE - row - 1) * SQUARE_SIZE) {
            scene->removeItem(highlight);
            delete highlight;
            break;
        }
    }

    // Clear the highlights vector
    highlights.clear();

    // Now we need to reset the square's color to its original color
    QColor color = originalColors[row+1][col]; // Get the original color from the array

    // Since each square is a QGraphicsRectItem, we need to find the item for this square
    // This requires iterating through all the squares on the scene and resetting the color
    QList<QGraphicsItem*> items = scene->items();
    for (QGraphicsItem* item : items) {
        // Check if the item is a square and matches the position
        if (QGraphicsRectItem* square = dynamic_cast<QGraphicsRectItem*>(item)) {
            if (square->rect().x() == col * SQUARE_SIZE && square->rect().y() == (BOARD_SIZE - row - 1) * SQUARE_SIZE) {
                // Reset the square's color to the original color
                square->setBrush(QBrush(color));
                break;
            }
        }
    }
}


void ChessBoard::highlightSquare(int col, int row, QColor color) {
    QGraphicsRectItem* highlight = new QGraphicsRectItem();
    highlight->setRect(col * SQUARE_SIZE, (BOARD_SIZE - row - 1) * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE);
    highlight->setBrush(color);
    highlight->setOpacity(0.5);

    scene->addItem(highlight);
    highlight->setZValue(0);
    highlights.push_back(highlight);
}
