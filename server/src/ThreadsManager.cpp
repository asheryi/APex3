
#include <algorithm>
#include "../include/ThreadsManager.h"

void ThreadsManager::addThread(pthread_t thread) {
    pthread_mutex_lock(&threads_mutex);
    threads.push_back(thread);
    pthread_mutex_unlock(&threads_mutex);
}

void ThreadsManager::removeThread(pthread_t thread) {
    pthread_mutex_lock(&threads_mutex);
    threads.erase(remove(threads.begin(), threads.end(), thread), threads.end());
    pthread_mutex_unlock(&threads_mutex);
}

ThreadsManager::ThreadsManager() : threads_mutex() {

}
