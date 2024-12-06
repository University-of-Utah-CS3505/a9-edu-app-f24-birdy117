#ifndef FOOLSMATE_H
#define FOOLSMATE_H

#include "chessboard.h"
#include <QObject>
// #include "draggablepiece.h"

/**
 * @class Foolsmate
 * @brief The Foolsmate class handles the logic for the Fool's Mate chess scenario.
 *
 * The class is responsible for moving pieces in a specific sequence,
 * highlighting legal moves, and communicating with the UI to guide the player
 * through the Fool's Mate puzzle. It provides the logic for the moves of
 * white and black pieces, specifically pawns and the queen, and signals
 * when the player needs to make a move or when the checkmate condition is reached.
 */
class Foolsmate : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a Foolsmate object.
     *
     * Initializes the Foolsmate with a pointer to a ChessBoard and sets up the initial game state.
     *
     * @param board A pointer to the ChessBoard object that represents the chessboard in the game.
     * @param parent The parent QObject (optional, defaults to nullptr).
     */
    Foolsmate(ChessBoard* board, QObject* parent = nullptr);

    /**
     * @brief Destructor for the Foolsmate object.
     *
     * Deletes the ChessBoard object when the Foolsmate instance is destroyed.
     */
    ~Foolsmate();

    /**
     * @brief Moves the first white pawn to its designated position.
     *
     * This function moves the white pawn at index 10 to position (2, 2) after a 2-second delay.
     */
    void moveFirstWhitePawn();

    /**
     * @brief Initiates the first move by highlighting the white pawn's legal move.
     *
     * This function highlights the square at (3, 1) and prompts the player for their next move.
     * A message is emitted to the UI, asking the player where the highlighted pawn should move.
     */
    void firstMove();

    /**
     * @brief Moves the first black pawn to its designated position.
     *
     * This function moves the black pawn at index 19 to position (3, 4).
     */
    void moveFirstBlackPawn();

    /**
     * @brief Moves the second white pawn to its designated position.
     *
     * This function moves the white pawn at index 9 to position (1, 3) after a 2-second delay.
     */
    void moveSecondWhitePawn();

    /**
     * @brief Initiates the second move by highlighting the white queen's legal move.
     *
     * This function highlights the square at (4, 0) and prompts the player for their next move.
     * A message is emitted to the UI, asking the player where the highlighted queen should move.
     */
    void secondMove();

    /**
     * @brief Moves the black queen to its designated position.
     *
     * This function moves the black queen at index 28 to position (0, 3).
     */
    void moveBlackQueen();

signals:
    /**
     * @brief Signal emitted to update the status label in the UI.
     *
     * The signal sends a message to the UI to indicate what action the player needs to take.
     *
     * @param message A string message that will be displayed in the UI to guide the player.
     */
    void updateStatusLabel(const QString& message);

    /**
     * @brief Signal emitted when the first move has been completed.
     *
     * This signal indicates that the first move has been successfully completed and the game
     * can progress to the next step.
     */
    void firstMoveDone();

private:
    ChessBoard* board; /**< A pointer to the ChessBoard object. */
    // QTimer* timer;  /**< An optional timer for delaying moves (currently unused). */
};

#endif // FOOLSMATE_H
