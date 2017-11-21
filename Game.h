// 318225851
// Yishay Asher

#ifndef EX2_GAME_H
#define EX2_GAME_H


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
    Display *display;
    Board *board;
    int currPlayer;
    int blacks;
    int whites;

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
    Path* pathOfLandingPoint(std::vector<Path *> paths, const Cell &point);

    /**
     * Flips the  cells given on the board.
     * @param needsToBeFlipped - positions to flip .
     * @param currPlayer - the current player's color .
     */
    void attackThose(const Path& path, Color currPlayer);

public:
    /**
     * Game constructor.
     * @param rows - #of rows in the board .
     * @param columns - #of columns in the board .
     */
    Game(int rows, int columns);

    /**
     * Game destructor .
     */
    ~Game();

    /**
     * Starting the actual game .
     */
    void start();

    /**
     * Deleting the vector.
     * @param points - vector of points.
     */
    template <class T>
    void deleteVector(std::vector<T *> &nodes){
        for (unsigned int i = 0; i < nodes.size(); i++) {
            delete nodes[i];
        }
        nodes.clear();
    }

    void updateScores(Player &curr, Player &other, int score);
};


#endif //EX2_GAME_H
