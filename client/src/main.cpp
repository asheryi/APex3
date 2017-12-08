
#include "../include/Game.h"
#include <fstream>

bool getConnectionDetails(string *serverIp, int *port);

int main(int argc, char *argv[]) {

    string serverIp;
    int port;
    if (getConnectionDetails(&serverIp, &port)) {
        Game game(8, 8, serverIp.c_str(), port);

        game.start();
    }

    return 0;
}

bool getConnectionDetails(string *serverIp, int *port) {
    string port_;
    string ip;
    ifstream configFile("configFile");
    if (configFile.is_open()) {
        getline(configFile, port_);
        getline(configFile, ip);
        configFile.close();
    } else {
        cout << "Error: config file is missing!";
        return false;
    }
    sscanf(port_.c_str(), "%d", port);
    *serverIp = ip;
    return true;
}