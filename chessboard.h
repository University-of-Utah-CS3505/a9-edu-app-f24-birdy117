#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

class ChessBoard : public QWidget {
    Q_OBJECT

public:
    explicit ChessBoard(QWidget* parent = nullptr);
    void resetBoard();
    void setupPieces(const QString setup[8][8]);

private:
    void setupBoard();
    void setupPieces();

    static const int SQUARE_SIZE;
    static const int BOARD_SIZE;

    QGraphicsView* view;
    QGraphicsScene* scene;
};

#endif // CHESSBOARD_H
