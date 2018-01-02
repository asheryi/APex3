

#ifndef EX2_GAME_H
#define EX2_GAME_H
#define MAX_COMMAND_SIZE 60


#include "GameLogic.h"
#include "Player.h"
#include "Display.h"
#include "Board.h"
#include "Path.h"

// Game manager class.

class Game {
private:
    GameLogic *gameLogic;
    Player *players[2];
    Display *displays[2];
    Board *board;
    int currPlayer;
    const char *serverIP;
    int serverPort;

    /**
     * Switching the player .
     * @param currPlayerColor
     */
    void nextPlayer(Color &currPlayerColor);

    /**
     * @param point - to check .
     * @return true if the point is out of bounds , false otherwise.
     */
    bool isOutOfBounds(const Cell &point);

    /**
     * checks if the vector contains the point .
     * @param points - vector.
     * @param point - point to check.
     * @return true if the vector contains the point , false otherwise .
     */
    Path *pathOfLandingPoint(std::vector<Path *> paths, const Cell &point);

    /**
     * Flips the  cells given on the board.
     * @param needsToBeFlipped - positions to flip .
     * @param currPlayer - the current player's color .
     */
    void attackThose(const Path &path, Color currPlayer);

public:
    /**
     * Game constructor.
     * @param rows - #of rows in the board .
     * @param columns - #of columns in the board .
     */
    Game(int rows, int columns, const char *serverIp, int serverPort);

    /**
     * Game destructor .
     */
    ~Game();

    /**
     * Starting the actual game .
     */
    void start();

    /**
    * Update the scores of the players.
    * @param curr-Player - the active player now.
    * @param other-Player - the rival of the active player.
    * @param score-int - score to update.
    */
    void updateScores(Player &curr, Player &other, int score);

    /**
   * create the players.
   * @param blacks-int - black disks amount.
   * @param whites-int - white disks amount.
   */
    void createPlayers(int blacks, int whites);

    int connectToServer();

    void prepareGame(int playerIndex, Counter *whitesCounter, Counter *blacksCounter);
};


#endif //EX2_GAME_H
