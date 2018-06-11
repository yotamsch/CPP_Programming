#include "ThreadPool.h"

std::queue<std::pair<std::string,std::string>> ThreadPool::pairsOfPlayersQueue;

void ThreadPool::stop() noexcept
    {
        {
            std::unique_lock<std::mutex> lock{ mEventMutex };
            mStopping = true;
        }
        mEventVar.notify_all();
        for (auto& thread : mThreads) {
            thread.join();
        }
    }

void ThreadPool::start(int numThreads, std::map<std::string,int>& id2Score, std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> id2factory)
    {
    for(int i = 0; i < numThreads; i++){
        if(!pairsOfPlayersQueue.empty())
            mEventVar.notify_one();

        mThreads.emplace_back([=, &id2Score, &id2factory]{
            while(true){
                std::string id_p1, id_p2;
                {
                    std::unique_lock<std::mutex> lock{mEventMutex};
                    mEventVar.wait(lock, [=]{ return mStopping || !pairsOfPlayersQueue.empty();} );
                    if(mStopping && pairsOfPlayersQueue.empty()){
                        break;
                    }//TODO: check: how do i handle the case where pairsOfPlayersQueue is empty but mStopping == false???
                    //is there any case where this even happens??

                    id_p1 = std::move(pairsOfPlayersQueue.front().first);
                    id_p2 = std::move(pairsOfPlayersQueue.front().second);
                    pairsOfPlayersQueue.pop();
                }
                int gameResult = GameManager::GetGameManager().PlayRPS(id2factory[id_p1](), id2factory[id_p2]());
                if(gameResult == 0){
                    id2Score[id_p1]++;
                    id2Score[id_p2]++;
                }else if(gameResult == 1){
                    id2Score[id_p1]+=3;
                }else{
                    id2Score[id_p2]+=3;
                }
            }
        });
    }
}
