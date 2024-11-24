#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>


MainWindow::MainWindow(ChessBoard *chessBoard, StartMenu *startMenu, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , chessBoard(chessBoard)
    , startMenu(startMenu)
{
    ui->setupUi(this);


    // Set layout and size policies for full canvas display
    QVBoxLayout *layout = new QVBoxLayout;
    ui->chessBoardContainer->setLayout(layout);
    layout->addWidget(chessBoard);
}


MainWindow::~MainWindow()
{
    delete ui;
}
