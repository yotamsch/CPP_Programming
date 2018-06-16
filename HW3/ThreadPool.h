/**
 * @brief The header file of the Thread Pool class
 * 
 * @file ThreadPool.h
 * @author Tala Amouri
 * @date 2018-06-10
 */
#ifndef __THREAD_POOL_H_
#define __THREAD_POOL_H_

#include "TournamentManager.h"

#include <atomic>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <map>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

class ThreadPool {
private:
    volatile bool mStopping = false;

    std::queue<std::pair<std::string, std::string>> mPlayQueue;
    std::vector<std::thread> mThreads;
    std::condition_variable mEventVar;
    std::mutex mEventMutex;

public:
    // c'tor
    explicit ThreadPool(std::queue<std::pair<std::string, std::string>>& playQueue)
    {
        this->mPlayQueue = playQueue;
    }
    // d'tor
    ~ThreadPool()
    {
        stop();
    }
    // waits for all the threads in the pool to finish
    void waitForAll() { this->wait_join(); }
    // fun the match
    void run(int numThreads);

private:
    // start the threads run
    void start(int numThreads);
    // wait for all threads to join
    void wait_join()
    {
        for (auto& thread : mThreads) {
            if (thread.joinable()) thread.join();
        }
    }
    // stop the running of the threads
    void stop() noexcept
    {
        this->mStopping = true;
        wait_join();
    }
};

#endif // !__THREAD_POOL_H_