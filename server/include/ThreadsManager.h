#include <netinet/in.h>
#include <vector>
#include <pthread.h>

using namespace std;


#ifndef EX3_THREADSMANAGER_H
#define EX3_THREADSMANAGER_H

// Used to manage all threads in the program .
class ThreadsManager {
private:
    vector<pthread_t> threads;
    pthread_mutex_t threads_mutex;
public:
    ThreadsManager();

    /**
     * Add the thread given to the threads managed.
     * @param thread
     */
    void addThread(pthread_t thread);

    /**
     * Remove this thread from the threds managed.
     * @param thread
     */
    void removeThread(pthread_t thread);

    /**
     * Kill all threads managed here.
     */
    void killAllThreads();
};


#endif //EX3_THREADSMANAGER_H
