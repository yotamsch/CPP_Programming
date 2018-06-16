/**
 * @brief The main cpp of the Tournament Manager class
 * 
 * @file TournamentManager.cpp
 * @author Yotam Sechayk
 * @date 2018-06-10
 */
#include "TournamentManager.h"
#include "GameManagerRPS.h"

#include <algorithm>
#include <random>
#include <set>
#include <string>

// initialization of the singelton instance
TournamentManager TournamentManager::instance;

bool TournamentManager::registerAlgorithm(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod)
{
    if (id2Factory.find(id) != id2Factory.end()) {
        return false;
    }
    soIds.emplace_back(id);
    id2Factory[id] = factoryMethod;
    id2GameNum[id] = 0;
    id2Score[id] = 0;
    return true;
}

void TournamentManager::initialize()
{
    std::set<std::pair<std::string, std::string>> playSet;
    for (auto& name : this->soIds) {
        getFightsForPlayer(name, playSet);
    }

    // reset the game numbers
    for (auto& name : this->soIds) {
        id2GameNum[name] = 0;
    }
}

void TournamentManager::getFightsForPlayer(std::string name, 
    std::set<std::pair<std::string, std::string>>& playSet)
{
    int idxCount = id2GameNum[name] + 1;
    std::string opp;
    while (id2GameNum[name] < NUM_OF_OPP) {
        int randIndex = std::rand() % this->soIds.size();
        opp = this->soIds[randIndex];

        if (opp.compare(name) == 0) {
            continue;
        }
        if (idxCount < (int)this->soIds.size()) {
            if (playSet.count({name,opp}) > 0 || playSet.count({opp,name}) > 0)
                continue;
        }
        this->pairsOfPlayersQueue.emplace(std::make_pair(name,opp));
        playSet.emplace(std::make_pair(name,opp));
        ++id2GameNum[name];
        ++id2GameNum[opp];
        ++idxCount;
    }
}

void TournamentManager::getSortedScores(std::vector<std::pair<std::string, int>>& finalScores)
{
    finalScores.clear();

    for (auto s : this->soIds) {
        finalScores.emplace_back(s, (int)this->id2Score[s]);
    }

    std::sort(finalScores.begin(), finalScores.end(), [](std::pair<std::string, int> const& a, std::pair<std::string, int> const& b) { return a.second > b.second; });
}

void TournamentManager::playMatch(std::string id_p1, std::string id_p2)
{
    int gameResult = GameManager::get().PlayRPS(this->getPlayer(id_p1), this->getPlayer(id_p2));
    this->updateScores(id_p1, id_p2, gameResult);
}

void TournamentManager::updateScores(std::string id_p1, std::string id_p2, int winner)
{
    // lock the score board
    std::lock_guard<std::mutex> lock(this->scoreLock);

    if (winner == 0) {
        this->updateScoreForId(id_p1, 1);
        this->updateScoreForId(id_p2, 1);
    }
    if (winner == 1) {
        this->updateScoreForId(id_p1, 3);
    }
    if (winner == 2) {
        this->updateScoreForId(id_p2, 3);
    }
    ++this->id2GameNum[id_p1];
    ++this->id2GameNum[id_p2];
}