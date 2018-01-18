#include <netinet/in.h>
#include <vector>
#include <pthread.h>
#include "Task.h"
#include "ThreadPool.h"

using namespace std;


#ifndef EX3_THREADSMANAGER_H
#define EX3_THREADSMANAGER_H

// Used to manage all threads in the program .
class ThreadsManager {
private:
    vector<pthread_t> threads;
    pthread_mutex_t threads_mutex;
    ThreadPool threadPool;

public:
    ThreadsManager(int threadPoolSize);

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

    void addTaskToThreadPool(Task *task);
};


#endif //EX3_THREADSMANAGER_H
