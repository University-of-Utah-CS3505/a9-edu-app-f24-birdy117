#include "chessboard.h"

const int ChessBoard::SQUARE_SIZE = 50;
const int ChessBoard::BOARD_SIZE = 8;

ChessBoard::ChessBoard(QWidget *parent)
    : QWidget(parent)
{
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);

    view->setFixedSize(BOARD_SIZE * SQUARE_SIZE + 2, BOARD_SIZE * SQUARE_SIZE + 2);
    view->setSceneRect(0, 0, BOARD_SIZE * SQUARE_SIZE, BOARD_SIZE * SQUARE_SIZE);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(view);
    setLayout(layout);

    setupBoard();
}

void ChessBoard::resetBoard()
{
    // Clear all existing items from the scene
    QList<QGraphicsItem *> items = scene->items();
    for (QGraphicsItem *item : items) {
        if (DraggablePiece *piece = dynamic_cast<DraggablePiece *>(item)) {
            scene->removeItem(piece);
            delete piece;
        }
    }
    for (auto* item : border) {
        scene->removeItem(item);
        delete item;
    }

    deleteHighlights();
    border.clear();
    allPieces.clear();
}

void ChessBoard::setupBoard()
{
    QPixmap whiteTile(":/Images/whiteTile.png");
    QPixmap greenTile(":/Images/greenTile.png");

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            // Create a square
            QGraphicsRectItem *square = new QGraphicsRectItem(col * SQUARE_SIZE,
                                                              row * SQUARE_SIZE,
                                                              SQUARE_SIZE,
                                                              SQUARE_SIZE);

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

void ChessBoard::setupPieces(const QString pieceImages[8][8])
{
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (!pieceImages[row][col].isEmpty()) {
                QPixmap pixmap(pieceImages[row][col]);
                DraggablePiece* piece = new DraggablePiece(pixmap);

                // center the piece within the square
                int offsetX = (SQUARE_SIZE - pixmap.width()) / 2;
                int offsetY = (SQUARE_SIZE - pixmap.height()) / 2;
                piece->setPos(col * SQUARE_SIZE + offsetX, row * SQUARE_SIZE + offsetY);
                scene->addItem(piece);

                if (piece) {
                    int offsetX = (SQUARE_SIZE - pixmap.width()) / 2;
                    int offsetY = (SQUARE_SIZE - pixmap.height()) / 2;
                    piece->setPos(col * SQUARE_SIZE + offsetX, row * SQUARE_SIZE + offsetY);
                    scene->addItem(piece);
                    piece->setZValue(1);
                    allPieces.push_back(piece);
                }
            }
        }
    }
}

void ChessBoard::highlightSquare(int col, int row, QColor color)
{
    QGraphicsRectItem *highlight = new QGraphicsRectItem();
    highlight->setRect(col * SQUARE_SIZE,
                       (BOARD_SIZE - row - 1) * SQUARE_SIZE,
                       SQUARE_SIZE,
                       SQUARE_SIZE);
    highlight->setBrush(color);
    highlight->setOpacity(0.5);

    scene->addItem(highlight);
    highlight->setZValue(0);
    highlights.push_back(highlight);
}

void ChessBoard::deleteHighlights() {
    for (auto* highlight : highlights) {
        scene->removeItem(highlight);
        delete highlight;
    }
    highlights.clear();
}
