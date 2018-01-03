#ifndef GameManager_h
#define GameManager_h

#include "Cell.h"
#include <sys/socket.h>
#include <unistd.h>

class GameManager {

private:
    int currPlayer;
    int playersSid[2];


public:
    

    /**
   * GameManager constructor.
   * @param socket_ -int, client's socket.
   */
    GameManager(int socket_);
   /*
    *setPlayerSid.
    * @param index -int, client's index on the GameManger.
    * @param sid -int, client's socket.
    */
    void setPlayerSid(int index, int sid);
    /*
     *nextPlayer. passing the turn to the other player.
     */
    void nextPlayer();
    /**
    * GameManager deconstructor.
    */
    virtual ~GameManager();

    /**
     * gameFlow manages the clients turns.
     */
    void runGame();

    /**
    * readFromClient reads the client message.
    * @return Cell - client's message(could be next move or indicates message to sever e.g:NoMoves).
    */
    Cell readFromClient();

    /**
    * writeToClient writes message to client.
    */
    void writeToClient(Cell cell);
    /**
    * GameManager constructor.
    * @param index -int, client's index in gameManager.
    * @return socket -int, client's socket.
    */
    int getSid(int index);


};

#endif


