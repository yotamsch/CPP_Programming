/**
 * @brief The implementation file of the Thread Pool class
 * 
 * @file ThreadPool.cpp
 * @author Yotam Sechayk
 * @date 2018-06-11
 */
#include "ThreadPool.h"

void ThreadPool::run(int numThreads)
{
    // threaded play
    if (numThreads >= 1) {
        this->start(numThreads);
    }
    // local play
    else {
        std::string id_p1, id_p2;
        while (!mPlayQueue.empty()) {
            id_p1 = mPlayQueue.front().first;
            id_p2 = mPlayQueue.front().second;

            TournamentManager::get().playMatch(id_p1, id_p2);

            mPlayQueue.pop();
        }
    }
}

void ThreadPool::start(int numThreads)
{
    for (int i = 0; i < numThreads; i++) {
        // add a new worker thread to list
        mThreads.emplace_back([&] {
            while (true) {
                std::string id_p1, id_p2;
                {
                    std::unique_lock<std::mutex> lock(mEventMutex);
                    mEventVar.wait(lock, [&] { return (mStopping || !mPlayQueue.empty()); });
                    if (mStopping) {
                        break;
                    }
                    id_p1 = mPlayQueue.front().first;
                    id_p2 = mPlayQueue.front().second;
                    mPlayQueue.pop();

                    if (mPlayQueue.empty()) {
                        mStopping = true;
                    }
                }
                TournamentManager::get().playMatch(id_p1, id_p2);
            }
        });

        // wake the created threads (if) needed)
        if (!mPlayQueue.empty())
            mEventVar.notify_all();
    }
}
