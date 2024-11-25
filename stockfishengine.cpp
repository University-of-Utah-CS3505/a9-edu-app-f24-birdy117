#include "stockfishengine.h"
#include <QDebug>

StockfishEngine::StockfishEngine(QObject *parent) : QObject(parent) {}

StockfishEngine::~StockfishEngine() {
    if (stockfishProcess.state() == QProcess::Running) {
        stockfishProcess.close();
    }
}

void StockfishEngine::startEngine(const QString &path) {
    stockfishProcess.start(path);
    qDebug() << "path: " << path;
    if (!stockfishProcess.waitForStarted()) {
        qDebug() << "Failed to start Stockfish";
        return;
    }

    QObject::connect(&stockfishProcess, &QProcess::readyRead, this, &StockfishEngine::handleReadyRead);

    qDebug() << "Stockfish started";
    sendCommand("uci");
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
