#include "../include/JoinCommand.h"

void JoinCommand::execute(vector<string> args) {
    int sid = atoi(args[0].c_str());
    string gameName = args[1];
    cout << "Welcome to JOIN" << endl;
    cout << "The game you want to join is: " << gameName << endl;

    int respond = 1;

    GameManager *game = gamesHandler->joinGame(gameName, sid);

    if (game != NULL) {
        cout << "you joined to the game" << endl;
        int n = write(game->getSid(0), &respond, sizeof(int));

        if(n == -1){
            throw "BAD";
        } else if(n == 0){
            throw "Socket closed";
        }

        n = write(sid, &respond, sizeof(int)); // TODO all n !+ 0 asking printing ....
        pthread_t gameThread;

        int t = pthread_create(&gameThread, NULL, game->runGame,game);
        if (t) {
            cout << "Error: unable to create thread, " << t << endl;
        } else {
            threadsManager->addThread(gameThread);
        }

    } else {
        cout << "you can not join to the game" << endl;
        respond = -1;
        int n = write(sid, &respond, sizeof(int));

    }

}


JoinCommand::JoinCommand(ThreadsManager *threadsManager_, GamesHandler *gamesHandler_) : Command(gamesHandler_),
                                                                                         threadsManager(
                                                                                                 threadsManager) {
}

JoinCommand::~JoinCommand() {

}
