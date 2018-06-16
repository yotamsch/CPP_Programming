
#ifndef __TOURNAMENT_MANAGER_H_
#define __TOURNAMENT_MANAGER_H_

#include "GameUtilitiesRPS.h"
#include "PlayerAlgorithm.h"

#include <atomic>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <string>


class TournamentManager {
private:
    static TournamentManager instance;
    // private default c'tor
    TournamentManager() = default;
    ~TournamentManager()
    {
        std::cout << "in TournamentManager d'tor" << std::endl;
    }

public:
    // gets the static instance of the tournament manager (singelton)
    static TournamentManager& get() { return instance; }

private:
    std::vector<std::string> soIds;
    std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> id2Factory;
    std::map<std::string, int> id2Score;
    std::map<std::string, int> id2GameNum;
    std::queue<std::pair<std::string, std::string>> pairsOfPlayersQueue;

    std::mutex scoreLock;

public:
    // registers an algorithm into the tournament
    bool registerAlgorithm(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod);
    // initialize all the needed elements
    void initialize();
    // clears the algorithm factory list
    void clearAlgorithms() { this->id2Factory.clear(); }
    // gets the sorted scores into the given vector
    void getSortedScores(std::vector<std::pair<std::string, int>>& finalScores);
    // update the player scores based on the play winner
    void updateScores(std::string id_p1, std::string id_p2, int winner);
    // returns a player from id
    std::unique_ptr<PlayerAlgorithm> getPlayer(std::string id) {
        return this->id2Factory[id]();
    }
    // play a match between players
    void playMatch(std::string id_p1, std::string id_p2);
    // returns the play queue
    std::queue<std::pair<std::string, std::string>>& getPlayQueue() {
        return pairsOfPlayersQueue;
    }

private:
    // arranges and updates fights for the player with id (name)
    void getFightsForPlayer(std::string name);
    // update the score of a player by id, when needed
    void updateScoreForId(std::string id, int score) {
        if (id2GameNum[id] < 30) {
            id2Score[id] += score;
        }
    }
};

#endif // !__TOURNAMENT_MANAGER_H_