#include <sstream>
#include "../include/JoinCommand.h"


void JoinCommand::execute(vector<string> args, int sid) {
    string gameName = args[0];
    cout << "The game sid = " << sid << " want to join is: " << gameName << endl;

    int respond = 1;

    GameManager *game = gamesHandler->joinGame(gameName, sid);


    if (game == NULL) {
        cout << "sid = " << sid << " can not join to the game" << endl;
        respond = -1;
        int n = write(sid, &respond, sizeof(int));
        close(sid);
        return;
    }

    // GAME IS ON:

    cout << "sid = " << sid << " joined to the game : " << gameName << endl;
    int n = write(game->getSid(0), &respond, sizeof(int)); // first player
    if (n == -1) {
        cout << "Unable to write to client (sid = " << sid << ")" << endl;
    } else if (n == 0) {
        cout << "Client with sid = " << sid << ", closed the connection" << endl;
        respond = -1;
        n = write(sid, &respond, sizeof(int)); // second player cannot play because first player disconnected.
        gamesHandler->removeGame(gameName);
        return;
    }

    GamesHandler::StartGameArgs *startGameArgs = new GamesHandler::StartGameArgs();
    startGameArgs->gamesHandler = gamesHandler;
    startGameArgs->gameManager = game;
    startGameArgs->gameName = gameName;
    startGameArgs->threadsManager = threadsManager;

    n = write(sid, &respond, sizeof(int)); // second player
    if (n <= 0) {
        cout << "Player sid(" << sid << ") unavailable" << endl;
        gamesHandler->removeGame(gameName);
        return;
    }

    pthread_t gameThread;
    int t = pthread_create(&gameThread, NULL, gamesHandler->joinAndStartGame, (void *) startGameArgs);

    if (t) {
        cout << "Error: unable to create thread, " << t << endl;
    } else {
        threadsManager->addThread(gameThread);
    }

}


JoinCommand::JoinCommand(ThreadsManager *threadsManager_, GamesHandler *gamesHandler_) : Command(gamesHandler_),
                                                                                         threadsManager(
                                                                                                 threadsManager_) {
}

JoinCommand::~JoinCommand() {

}
