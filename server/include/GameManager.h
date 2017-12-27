#ifndef GameManager_h
#define GameManager_h
#include "Cell.h"
#include <sys/socket.h>
#include <unistd.h>

class GameManager {
public:
    /**
   * Server constructor.
   * @param port -int, server's port.
   */
    GameManager(int socket_,bool* alive_,pthread_mutex_t* alive_mutex);

    void setPlayerSid(int index, int sid);

    void nextPlayer();

    static void play(GameManager *gameManager);

private:
    int serverSocket; // the socket's file descriptor
    bool* alive;
    int currPlayer;
    int playersSid[2];
    pthread_mutex_t* alive_mutex;



    /**
     * gameFlow manages the clients turns.
     */
    void runGame(GameManager* gameManager);

public:
    virtual ~GameManager();

private:
    /**
    * readFromClient reads the client message.
    * @return Cell - client's message(could be next move or indicates message to sever e.g:NoMoves).
    */
    Cell readFromClient();

    /**
    * writeToClient writes message to client.
    */
    void writeToClient(Cell cell);

};
#endif


