//
// Created by yishay on 12/4/17.
//

#include "Server.h"
#include <stdlib.h>

using namespace std;

int main() {
    Server server(33387);
    try {
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
}
