//
// Created by yishay on 12/4/17.
//

#ifndef EX3_SERVER_H
#define EX3_SERVER_H


class Server {
public:
    Server(int port);

    void start();

private:
    int port;
    int serverSocket; // the socket's file descriptor
    void handleClient(int clientSocket);

    int calc(int arg1, const char op, int arg2) const;

    void stop();
};



#endif //EX3_SERVER_H
