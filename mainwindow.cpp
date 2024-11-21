#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , chessBoard(chessBoard)
{
    ui->setupUi(this);

    // Set layout and size policies for full canvas display
    QVBoxLayout *layout = new QVBoxLayout;
    ui->chessBoardContainer->setLayout(layout);
    layout->addWidget(&chessBoard);
}


MainWindow::~MainWindow()
{
    delete ui;
}
