
#ifndef __TOURNAMENT_MANAGER_H_
#define __TOURNAMENT_MANAGER_H_

#include "GameUtilitiesRPS.h"
#include "PlayerAlgorithm.h"
#include "ThreadPool.h"
#include <atomic>
#include <functional>
#include <map>
#include <memory>
#include <queue>
#include <iostream>

class TournamentManager {
private:
    static TournamentManager instance;
    // private default c'tor
    TournamentManager() = default;
    ~TournamentManager() {
        std::cout << "in TournamentManager d'tor" << std::endl;
    }

public:
    // gets the static instance of the tournament manager (singelton)
    static TournamentManager& get() { return instance; }

private:
    std::vector<std::string> soFileNames;
    std::vector<std::string> soIds;
    std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> id2factory;
    std::map<std::string, std::atomic_int> id2Score;
    std::queue<std::pair<std::string, std::string>> pairsOfPlayersQueue;

public:
    // gets the list of algorithm file names
    std::vector<std::string>& getFilesNames() { return soFileNames; }
    // get the scores
    std::map<std::string, std::atomic_int>& getScores() { return id2Score; }
    // add a lib file name to list
    void addFileName(std::string fileName);
    // registers an algorithm into the tournament
    bool registerAlgorithm(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod);
    // run the tournament
    void run(int numOfThreads);

private:
    // arranges and updates fights for the player with id (name)
    void getFightsForPlayer(std::string name);
};

#endif // !__TOURNAMENT_MANAGER_H_