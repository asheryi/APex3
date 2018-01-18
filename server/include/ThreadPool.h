

#ifndef EX3_THREADPOOL_H
#define EX3_THREADPOOL_H


#include "Task.h"
#include <queue>
#include <pthread.h>

using namespace std;

// The thread pool .

class ThreadPool {
public:
    // COnstructor based on num of threads ( no more no less)
    ThreadPool(int threadsNum);

    // Add a task to the queue of the tasks waiting for execution.
    void addTask(Task *task);

    // Kill all threads and tasks.
    void terminate();

    virtual ~ThreadPool();

private:
    queue<Task *> tasksQueue;
    pthread_t *threads;

    void executeTasks();

    bool stopped;
    pthread_mutex_t lock;

    static void *execute(void *arg);
};


#endif //EX3_THREADPOOL_H
