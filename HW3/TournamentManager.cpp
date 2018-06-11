#include "TournamentManager.h"
#include <string>

TournamentManager TournamentManager::instance;
std::vector<std::string> TournamentManager::so_files_names;
std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> TournamentManager::id2factory;
//TODO: correctly initialize map
std::map<std::string, int> TournamentManager::id2Score;
//TODO: correctly fill this map, YOTAM's
std::queue<std::pair<std::string, std::string>> TournamentManager::pairsOfPlayersQueue;

bool TournamentManager::registerAlgorithm(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod)
{
    if (id2factory.find(id) != id2factory.end()) {
        return false;
    }
    id2factory[id] = factoryMethod;
    return true;
}
