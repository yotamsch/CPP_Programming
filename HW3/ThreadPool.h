#ifndef __THREAD_POOL_H_
#define __THREAD_POOL_H_

#include "GameManagerRPS.h"
#include "PlayerAlgorithm.h"
#include <atomic>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <thread>
#include <vector>

class ThreadPool {
private:
    volatile bool mStopping = false;

    std::queue<std::pair<std::string, std::string>> pairsOfPlayersQueue;
    std::vector<std::thread> mThreads;
    std::condition_variable mEventVar;
    std::mutex mEventMutex;

public:
    // c'tor
    explicit ThreadPool(int numThreads, const std::queue<std::pair<std::string, std::string>>& mPairsOfPlayersQueue, std::map<std::string, std::atomic_int>& id2Score, std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> id2factory)
    {
        this->pairsOfPlayersQueue = mPairsOfPlayersQueue;
        start(numThreads, id2Score, id2factory);
        wait_join();
    }
    // d'tor
    ~ThreadPool()
    {
        std::cout << "in ThreadPool d'tor" << std::endl;
        stop();
    }
    /*
    void enqueue(std::pair<std::string, std::string> pairOfIDs){
        {
            std::unique_lock<std::mutex> lock{mEventMutex};
            pairsOfPlayersQueue.emplace(std::move(pairOfIDs));
        }
        mEventVar.notify_one();
    }
    */
private:
    void start(int numThreads, std::map<std::string, std::atomic_int>& id2Score, std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> id2factory);

    void wait_join()
    {
        for (auto& thread : mThreads) {
            thread.join();
        }
    }

    void stop() noexcept;
};

#endif // !__THREAD_POOL_H_