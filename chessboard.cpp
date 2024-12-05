#include "chessboard.h"
#include <QBrush>
#include <QVBoxLayout>
#include "DraggablePiece.h"
#include "pawnpiece.h"
#include "knightpiece.h"
#include "rookpiece.h"

// Define static constants
const int ChessBoard::BOARD_SIZE = 8;
const int ChessBoard::SQUARE_SIZE = 50;

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

                DraggablePiece* piece = nullptr;

                if(pieceImages[row][col].contains("Pawn")){
                    piece = new PawnPiece(pixmap);
                }
                else if(pieceImages[row][col].contains("Knight")){
                    piece = new KnightPiece(pixmap);
                }
                else if(pieceImages[row][col].contains("Rook")){
                    piece = new RookPiece(pixmap);
                }
                // will do other pieces
                else {
                    piece = new DraggablePiece(pixmap);
                }

                // center the piece within the square
                int offsetX = (SQUARE_SIZE - pixmap.width()) / 2;
                int offsetY = (SQUARE_SIZE - pixmap.height()) / 2;
                piece->setPos(col * SQUARE_SIZE + offsetX, row * SQUARE_SIZE + offsetY);

                // add piece to the scene
                scene->addItem(piece);
            }
        }
    }
}




