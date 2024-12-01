#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

class ChessBoard : public QWidget {
    Q_OBJECT

public:
    static const int SQUARE_SIZE;
    static const int BOARD_SIZE;
    QGraphicsScene* scene;

    explicit ChessBoard(QWidget* parent = nullptr);

private:
    void setupBoard();
    void setupPieces();
    QGraphicsView* view;
};

#endif // CHESSBOARD_H
