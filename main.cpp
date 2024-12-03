#include <QApplication>
#include "startmenu.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    qDebug() << "main";

    ChessBoard chessBoard;
    StartMenu startMenu(&chessBoard);
    startMenu.show();

    return app.exec();
}


