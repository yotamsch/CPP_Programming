#ifndef __THREAD_POOL_H_
#define __THREAD_POOL_H_

#include "GameManagerRPS.h"
#include "PlayerAlgorithm.h"
#include <condition_variable>
#include <functional>
#include <map>
#include <queue>
#include <string>
#include <thread>
#include <vector>

class ThreadPool {
public:
    // c'tor
    explicit ThreadPool(int numThreads, const std::queue<std::pair<std::string, std::string>>& mPairsOfPlayersQueue, std::map<std::string, int>& id2Score, std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> id2factory)
    {
        pairsOfPlayersQueue = mPairsOfPlayersQueue;
        start(numThreads, id2Score, id2factory);
    }
    // d'tor
    ~ThreadPool() { stop(); }
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
    std::vector<std::thread> mThreads;
    std::condition_variable mEventVar;
    static std::queue<std::pair<std::string, std::string>> pairsOfPlayersQueue;
    std::mutex mEventMutex;
    bool mStopping = false;
    void start(int numThreads, std::map<std::string, int>& id2Score, std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> id2factory);
    void stop() noexcept;
};

#endif // !__THREAD_POOL_H_