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
    string testPrint = "default";

    /**
   * Server constructor.
   * @param port -int, server's port.
   */
    GameManager(int socket_);

    void setPlayerSid(int index, int sid);

    void nextPlayer();

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

    int getSid(int index);


};

#endif


