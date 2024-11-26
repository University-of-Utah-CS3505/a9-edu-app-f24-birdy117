#include "stockfishengine.h"
#include <QDebug>
#include <QFile>

StockfishEngine::StockfishEngine(QObject *parent) : QObject(parent) {}

StockfishEngine::~StockfishEngine() {
    if (stockfishProcess.state() == QProcess::Running) {
        stockfishProcess.close();
    }
}

void StockfishEngine::startEngine(const QString &path) {
    qDebug() << "in startEngine";
    QFile file(path);
    if (!file.exists()) {
        qDebug() << "Error: File does not exist at the provided path.";
        return;
    }
    else {
        qDebug() << "file found in startEngine";
    }

    try {
        stockfishProcess.start(path);
    }
    catch (const std::exception &e)
    {
        qDebug() << "Exception occurred while starting Stockfish:" << e.what();
    }

    // if (!stockfishProcess.waitForStarted()) {
    //     qDebug() << "Failed to start Stockfish process. Error:" << stockfishProcess.errorString();
    //     return;
    // }

    // qDebug() << "path: " << path;
    // if (!stockfishProcess.waitForStarted()) {
    //     qDebug() << "Failed to start Stockfish";
    //     return;
    // }

    // QObject::connect(&stockfishProcess, &QProcess::readyRead, this, &StockfishEngine::handleReadyRead);

    qDebug() << "Stockfish started";
    // sendCommand("uci");
}

void StockfishEngine::sendCommand(const QString &command) {
    if (stockfishProcess.state() == QProcess::Running) {
        stockfishProcess.write((command + "\n").toUtf8());
    }

    qDebug() << "Recieved";
}

QString StockfishEngine::getBestMove(const QString &position) {
    sendCommand("position " + position);
    sendCommand("go movetime 1000");  // 1 second calculation
    stockfishProcess.waitForReadyRead();
    return lastOutput;
}

void StockfishEngine::handleReadyRead() {
    QByteArray output = stockfishProcess.readAll();
    lastOutput = QString(output);
    emit engineOutput(lastOutput);
}
