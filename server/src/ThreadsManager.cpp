
#include <algorithm>
#include <iostream>
#include "../include/ThreadsManager.h"

void ThreadsManager::addThread(pthread_t thread) {
    cout << "ALMOST ADDED THREAD" << endl;
    pthread_mutex_lock(&threads_mutex);
    cout << "AFTER LOCK" << endl;
    threads.push_back(thread);
    cout << "BEFORE UNLOCK" << endl;
    pthread_mutex_unlock(&threads_mutex);
    cout << "ADDED THREAD" << endl;
}

void ThreadsManager::removeThread(pthread_t thread) {
    pthread_mutex_lock(&threads_mutex);
    threads.erase(remove(threads.begin(), threads.end(), thread), threads.end());
    pthread_mutex_unlock(&threads_mutex);
}

ThreadsManager::ThreadsManager() : threads_mutex() {

}

void ThreadsManager::killAllThreads() {
    pthread_mutex_lock(&threads_mutex);
    int threads_size = threads.size();
    for (int i = 0; i < threads_size; i++) {
        pthread_cancel(threads[i]);
    }

    pthread_mutex_unlock(&threads_mutex);

}


