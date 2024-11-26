#include "stockfishengine.h"
#include <QDebug>
#include <QFile>

StockfishEngine::StockfishEngine(QObject *parent) : QObject(parent) {}

StockfishEngine::~StockfishEngine() {
    if (stockfishProcess.state() == QProcess::Running) {
        stockfishProcess.kill(); // Stop Stockfish gracefully
        stockfishProcess.waitForFinished();
    }
}

void StockfishEngine::startEngine(const QString &path) {
    QFile file(path);
    if (!file.exists()) {
        qDebug() << "Error: File does not exist at the provided path.";
        return;
    }

    // Set up QProcess error handling
    QObject::connect(&stockfishProcess, &QProcess::errorOccurred, this, [](QProcess::ProcessError error) {
        qDebug() << "QProcess error:" << error;
    });

    QObject::connect(&stockfishProcess, &QProcess::readyReadStandardOutput, this, &StockfishEngine::handleReadyRead);

    // Start the Stockfish engine asynchronously
    stockfishProcess.start(path);

    if (!stockfishProcess.waitForStarted()) {
        qDebug() << "FAILED TO START STOCKFISH.";
        return;
    }

    qDebug() << "STOCKFISH STARTED";
    sendCommand("uci"); // Send initial command to Stockfish
}

void StockfishEngine::sendCommand(const QString &command) {
    if (stockfishProcess.state() == QProcess::Running) {
        stockfishProcess.write((command + "\n").toUtf8());
    } else {
        qDebug() << "Cannot send command. Stockfish is not running.";
    }
}

void StockfishEngine::handleReadyRead() {
    QByteArray output = stockfishProcess.readAllStandardOutput();
    QString outputString = QString(output);
    // qDebug() << "STOCKFISH OUTPUT:" << outputString;

    // Emit the output for UI or logic processing
    emit engineOutput(outputString);
}
