
#include "../include/Game.h"

int main(int argc,char* argv[]) {
    const char *serverIp = "127.0.0.1";

    Game game(8, 8, serverIp, 33346);

    game.start();

    return 0;
}