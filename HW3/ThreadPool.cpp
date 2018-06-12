#include "ThreadPool.h"

//std::queue<std::pair<std::string, std::string>> ThreadPool::pairsOfPlayersQueue;

void ThreadPool::stop() noexcept
{
    // {
    //     std::unique_lock<std::mutex> lock{ mEventMutex };
    //     mStopping = true;
    // }
    // mEventVar.notify_all();
    // for (auto& thread : mThreads) {
    //     thread.join();
    // }
    std::cout << "queue size: " << this->pairsOfPlayersQueue.size() << std::endl;
}

void ThreadPool::start(int numThreads, std::map<std::string, std::atomic_int>& id2Score, std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> id2factory)
{
    for (int i = 0; i < numThreads; i++) {
        mThreads.emplace_back([&] {
            while (true) {
                std::string id_p1, id_p2;
                {
                    std::unique_lock<std::mutex> lock(mEventMutex);
                    mEventVar.wait(lock, [&] { return (mStopping || !pairsOfPlayersQueue.empty()); });
                    if (mStopping) {
                        std::cout << "ending thread: " << std::this_thread::get_id() << std::endl;
                        break;
                    }
                    id_p1 = pairsOfPlayersQueue.front().first;
                    id_p2 = pairsOfPlayersQueue.front().second;
                    pairsOfPlayersQueue.pop();

                    if (pairsOfPlayersQueue.empty()) {
                        mStopping = true;
                    }
                }
                int gameResult = GameManager::GetGameManager().PlayRPS(std::move(id2factory[id_p1]()), std::move(id2factory[id_p2]()));

                if (gameResult == 0) {
                    id2Score[id_p1] += 1;
                    id2Score[id_p2] += 1;
                } 
                if (gameResult == 1) {
                    id2Score[id_p1] += 3;
                } 
                if (gameResult == 2) {
                    id2Score[id_p2] += 3;
                }
            }
        });
        // wake the threads when needed
        if (!pairsOfPlayersQueue.empty())
            mEventVar.notify_all();
    }
}
