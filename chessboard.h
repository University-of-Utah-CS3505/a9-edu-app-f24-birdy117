#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "draggablepiece.h"
#include <QBrush>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QWidget>

///
/// \brief The ChessBoard class
///  Represents a visual of a chessboard with chesspieces
///
class ChessBoard : public QWidget
{
    Q_OBJECT

public:
    ///
    /// \brief List of all chess pieces on board
    ///
    QList<DraggablePiece *> allPieces;

    ///
    /// \brief List of highlighted squares on board
    ///
    QList<QGraphicsRectItem *> highlights;

    ///
    /// \brief List of text items for labeling the board borders
    ///
    QList<QGraphicsTextItem *> border;

    ///
    /// \brief Constructs a ChessBoard object
    /// \param parent
    ///
    explicit ChessBoard(QWidget *parent = nullptr);

    ///
    /// \brief Resets the board to its initial state
    ///
    void resetBoard();

    ///
    /// \brief Sets up the chessboard pieces based on their predefined configuration
    /// \param setup
    ///
    void setupPieces(const QString setup[8][8]);

    ///
    /// \brief Highlights a specific square on the board
    /// \param col
    /// \param row
    /// \param color
    ///
    void highlightSquare(int col, int row, QColor color);

    ///
    /// \brief Removes all highlighted squares from the board
    ///
    void deleteHighlights();

    ///
    /// \brief The GraphicsScene representing the chessboard
    ///
    QGraphicsScene *scene;

private:

    ///
    /// \brief Sets up the chess board with squares and borders
    ///
    void setupBoard();

    ///
    /// \brief Sets up the chess pieces on the board
    ///
    void setupPieces();

    ///
    /// \brief The size of each square on the chess board
    ///
    static const int SQUARE_SIZE;

    ///
    /// \brief The size of the chessboard
    ///
    static const int BOARD_SIZE;

    ///
    /// \brief The GraphicsView used to display the chessboard
    ///
    QGraphicsView *view;
};

#endif // CHESSBOARD_H
