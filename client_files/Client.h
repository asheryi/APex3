//
// Created by yishay on 12/4/17.
//

#ifndef EX3_CLIENT_H
#define EX3_CLIENT_H


class Client {
public:
    Client(const char *serverIP, int serverPort);

    void connectToServer();

    int sendExercise(int arg1, char op, int arg2);

private:
    const char *serverIP;
    int serverPort;
    int clientSocket;
};


#endif //EX3_CLIENT_H
