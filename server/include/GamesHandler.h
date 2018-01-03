#ifndef GamesHandler_H
#define GamesHandler_H

#include<map>
#include "GameManager.h"
#include "ThreadsManager.h"
#include <pthread.h>
#include <vector>

//Handles all the games.
class GamesHandler {
private:
    map<string, GameManager *> activeGames;
    map<string, GameManager *> holdOnGames;
    pthread_mutex_t maps_mutex;
    /**
     * isWaitingGame.
     * @param gameName -string, game name.
     * @return true if the game is in holdOnGames otherwise false.
     */
    bool isWaitingGame(string gameName);


public:
    /**
     * GamesHandler Constructor.
     */
    GamesHandler();
    /**
     * exists
     * @param gameName -string, name of the game.
     * @return true if the game exists(in activeGames or in holdOnGames), otherwise false.
     */
    bool exists(string gameName);
    /**
    * joinGame, joins the second player to the game.
    * @param gameName -string, name of the game.
    * @return the gameManger if its exists in holdOnGames otherwise NULL.
    */
    GameManager *joinGame(string gameName, int sid);
    /**
   * addGame, adds new game to holdOnGames.
   * @param gameName -string, name of the game.
   * @param gm -GameManager, the game to be add.
   */
    void addGame(string gameName, GameManager *gm);
    /**
     * removeGame, remove game (if its exists) from holdOnGames or activeGames.
     * @param gameName -string, name of the game.
     */
    void removeGame(string gameName);
    /**
    * joinAndStartGame, the thread function in change of running the game.
    * @param startGameArgs_ -StartGameArgs, arguments required to run the game.
    */
    static void *joinAndStartGame(void *startGameArgs_);
    /**
     * getHoldOnGames.
     * @return the games in holdOnGames.
     */
    string getHoldOnGames();
    /**
   * GamesHandler deconstructor.
   */
    ~GamesHandler();
   /**
    * howManyHoldOnGames.
    * @return the amount of games in holdOnGames.
    */
    unsigned long howManyHoldOnGames();
   /**
    * StartGameArgs,struct required for passing arguments to thread's function.
    */
    typedef struct StartGameArgs {
        GamesHandler *gamesHandler;
        GameManager *gameManager;
        string gameName;
        ThreadsManager *threadsManager;
    } StartGameArgs;
};

#endif

