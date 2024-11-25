#ifndef STOCKFISHENGINE_H
#define STOCKFISHENGINE_H

#include <QObject>
#include <QProcess>

class StockfishEngine : public QObject {
    Q_OBJECT
public:
    explicit StockfishEngine(QObject *parent = nullptr);
    ~StockfishEngine();

    void startEngine(const QString &path);
    void sendCommand(const QString &command);
    QString getBestMove(const QString &position);

signals:
    void engineOutput(const QString &output);

private slots:
    void handleReadyRead();

private:
    QProcess stockfishProcess;
    QString lastOutput;
};

#endif // STOCKFISHENGINE_H
