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
    id2Factory[id] = factoryMethod;
    soIds.emplace_back(id);
    return true;
}

void TournamentManager::initialize() {
    for (auto& name : this->soIds) {
        // initialization for id2Score
        id2Score[name] = 0;
        // initialization for id2GameNum
        id2GameNum[name] = 0;
        // preprocessing for pairsOfPlayersQueue
        getFightsForPlayer(name);
    }
}

void TournamentManager::getFightsForPlayer(std::string name)
{
    int counter = 0;
    do {
        std::set<std::string> choice = { name };
        do {
            int randIndex = std::rand() % this->soIds.size();
            std::string opp = this->soIds[randIndex];
            if (choice.count(opp) == 0) {
                this->pairsOfPlayersQueue.emplace(std::make_pair(name, opp));
                choice.insert(opp);
                ++counter;
            }
        } while (choice.size() < this->soIds.size());
    } while (counter < NUM_OF_OPP);
}

void TournamentManager::getSortedScores(std::vector<std::pair<std::string, int>>& finalScores)
{
    finalScores.clear();

    for (auto s : this->soIds) {
        finalScores.emplace_back(s, (int)this->id2Score[s]);
    }

    std::sort(finalScores.begin(), finalScores.end(), [](std::pair<std::string, int> const& a, std::pair<std::string, int> const& b) { return a.second > b.second; });
}

void TournamentManager::playMatch(std::string id_p1, std::string id_p2) {
    int gameResult = GameManager::get().PlayRPS(this->getPlayer(id_p1), this->getPlayer(id_p2));
    this->updateScores(id_p1,id_p2, gameResult);
}

void TournamentManager::updateScores(std::string id_p1, std::string id_p2, int winner) {
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