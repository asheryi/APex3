#include <netinet/in.h>
#include <vector>
#include <pthread.h>

using namespace std;


#ifndef EX3_THREADSMANAGER_H
#define EX3_THREADSMANAGER_H


class ThreadsManager {
private:
    vector<pthread_t> threads;
    pthread_mutex_t threads_mutex;
public:
    ThreadsManager();

    void addThread(pthread_t thread);

    void removeThread(pthread_t thread);
};


#endif //EX3_THREADSMANAGER_H
