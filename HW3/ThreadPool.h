#include <functional>
#include <vector>
#include <thread>
#include <condition_variable>
#include <queue>
#include <string>
#include <map>
#include "GameManagerRPS.h"
#include "PlayerAlgorithm.h"

class ThreadPool
{
public:
    explicit ThreadPool
        (int numThreads, const std::queue<std::pair<std::string,std::string>>& mPairsOfPlayersQueue, std::map<std::string,int>& id2Score, std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> id2factory)
    {   
        pairsOfPlayersQueue = mPairsOfPlayersQueue;
        start(numThreads, id2Score, id2factory);
    }
    ~ThreadPool(){
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
    std::vector<std::thread> mThreads;
    std::condition_variable mEventVar;
    static std::queue<std::pair<std::string,std::string>> pairsOfPlayersQueue;
    std::mutex mEventMutex;
    bool mStopping = false;
    void start(int numThreads, std::map<std::string,int>& id2Score, std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> id2factory);
    void stop() noexcept{
        {
            std::unique_lock<std::mutex> lock{mEventMutex};
            mStopping = true;
        }
        mEventVar.notify_all();
        for(auto& thread : mThreads){
            thread.join();
        }
    }

};