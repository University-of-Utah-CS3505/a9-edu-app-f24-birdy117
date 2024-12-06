#ifndef STOCKFISHENGINE_H
#define STOCKFISHENGINE_H

#include <QObject>
#include <QProcess>

///
/// \authors Anne Arnold, Nicole Glazier, Ethan Kerrigan
///          Emily Thai, Aaron Perez
/// \date 25 November 2024
/// \brief The StockfishEngine class
/// Connects the current executable with the stockfish
/// executable. Handles input and output from stockfish
/// and terminates the connection.
///
class StockfishEngine : public QObject
{
    Q_OBJECT

public:
    explicit StockfishEngine(QObject *parent = nullptr);
    ~StockfishEngine();

    ///
    /// \brief startEngine
    /// Starts the stockfish executable.
    /// \param path - file path of stockfish executable
    ///
    void startEngine(const QString &path);

    ///
    /// \brief sendCommand
    /// Sends a command to stockfish.
    /// \param command - stockfish command
    ///
    void sendCommand(const QString &command);

    ///
    /// \brief getBestMove
    /// Finds the best chess move,
    /// \param position - position of piece to move
    /// \return best position to move chess piece
    ///
    QString getBestMove(const QString &position);

    ///
    /// \brief terminateEngine
    /// Terminates connection to stockfish executable.
    ///
    void terminateEngine();

signals:
    void engineOutput(const QString &output);

private slots:
    ///
    /// \brief handleReadyRead
    /// Handles stockfish output.
    ///
    void handleReadyRead();

private:
    /// Communicates with stockfish executable.
    QProcess stockfishProcess;
};

#endif // STOCKFISHENGINE_H
