#include "TournamentManager.h"
#include <random>
#include <set>
#include <string>
#include <algorithm>

// initialization of the singelton instance
TournamentManager TournamentManager::instance;

void TournamentManager::addFileName(std::string fileName)
{
    this->soFileNames.emplace_back(fileName);
}

bool TournamentManager::registerAlgorithm(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod)
{
    if (id2factory.find(id) != id2factory.end())
    {
        return false;
    }
    id2factory[id] = factoryMethod;
    soIds.emplace_back(id);
    return true;
}

void TournamentManager::run(int numOfThreads)
{
    for (auto &name : this->soIds)
    {
        // initialization for id2Score
        id2Score[name] = 0;
        // preprocessing for pairsOfPlayersQueue
        getFightsForPlayer(name);
    }
    this->threadPool = std::make_unique<ThreadPool>(numOfThreads, pairsOfPlayersQueue, id2Score, id2factory);
}

void TournamentManager::getFightsForPlayer(std::string name)
{
    int counter = 0;
    do
    {
        std::set<std::string> choice = {name};
        do
        {
            int randIndex = std::rand() % this->soIds.size();
            std::string opp = this->soIds[randIndex];
            if (choice.count(opp) == 0)
            {
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

    for (auto s : this->soIds)
    {
        finalScores.emplace_back(s, (int)this->id2Score[s]);
    }

    std::sort(finalScores.begin(), finalScores.end(), [](std::pair<std::string, int> const &a, std::pair<std::string, int> const &b) { return a.second > b.second; });
}