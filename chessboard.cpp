#include "chessboard.h"
#include <QBrush>
#include <QVBoxLayout>

// Define static constants
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

    // Set up the chessboard
    setupBoard();
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

            square->setPen(Qt::NoPen); // Optional: remove border lines
            scene->addItem(square);
        }
    }
}
