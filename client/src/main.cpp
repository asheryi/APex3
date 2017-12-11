
#include "../include/Game.h"
#include <fstream>

bool getConnectionDetails(string *serverIp, int *port);

int main(int argc, char *argv[]) {

    string serverIp;
    int port;
    if (getConnectionDetails(&serverIp, &port)) {
        Game game(3, 3, serverIp.c_str(), port);
        game.start();
    }

    return 0;
}
/**
    * Reading from the configurations file the port and ip address of server.
    * @param serverIp - pointer, to the serverIp variable.
    * @param port - pointer, to the port variable.
    * @return true if the file exists otherwise false.
    */
bool getConnectionDetails(string *serverIp, int *port) {
    string port_;
    string ip;
    ifstream configFile("configFileClient");
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