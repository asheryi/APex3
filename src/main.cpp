
#include "../include/Game.h"

int main(int argc,char* argv[]) {
    const char *serverIp = "127.0.0.1";

    Game game(3, 3, serverIp, 33387);

    game.start();

    return 0;
}