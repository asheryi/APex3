//
// Created by yishay on 12/4/17.
//

#include "../include/Server.h"
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

bool getConnectionDetails(int *port);

int main() {
    int port;
    if (getConnectionDetails(&port)) {
        Server server(port);
        try {
            server.start();
        } catch (const char *msg) {
            cout << "Cannot start server. Reason: " << msg << endl;
            exit(-1);
        }
    }
}

bool getConnectionDetails(int *port) {
    string port_;
    ifstream configFile("configFile");
    if (configFile.is_open()) {
        getline(configFile, port_);
        configFile.close();
    } else {
        cout << "Error: config file is missing!";
        return false;
    }
    sscanf(port_.c_str(), "%d", port);
    return true;
}
