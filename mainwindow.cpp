#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QDebug>

MainWindow::MainWindow(ChessBoard *chessBoard, StartMenu *startMenu, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , chessBoard(chessBoard)
    , startMenu(startMenu)
{
    ui->setupUi(this);
    qDebug() << "start";

    // Set up stockfish
    QString basePath = QCoreApplication::applicationDirPath();  // Get the folder of the running executable
    QString stockfishPath = basePath + "../Other files/stockfish.exe";
    stockfishEngine->startEngine(stockfishPath);

    connect(stockfishEngine, &StockfishEngine::engineOutput, this, [&](const QString &output) {
        qDebug() << "Stockfish Output:" << output;
    });
    stockfishEngine->sendCommand("uci");


    // Set layout and size policies for full canvas display
    QVBoxLayout *layout = new QVBoxLayout;
    ui->chessBoardContainer->setLayout(layout);
    layout->addWidget(chessBoard);
}


MainWindow::~MainWindow()
{
    delete ui;
}
