#include "PlayerAlgorithm.h"
#include "ThreadPool.h"
#include <functional>
#include <map>
#include <memory>
#include <queue>

class TournamentManager {
private:
    static TournamentManager instance;
    static std::vector<std::string> so_files_names;

    // private default c'tor
    TournamentManager() = default;

public:
    static std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> id2factory;
    //TODO: correctly initialize map
    static std::map<std::string, int> id2Score;
    //TODO: correctly fill this map, YOTAM's
    static std::queue<std::pair<std::string, std::string>> pairsOfPlayersQueue;

    // gets the static instance of the tournament manager (singelton)
    static TournamentManager& getTournamentManager() { return instance; }
    // gets the list of algorithm file names
    static std::vector<std::string>& getSoFilesNames() { return so_files_names; }
    // registers an algorithm into the tournament
    bool registerAlgorithm(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod);

    void run(int numOfThreads) const
    {
        ThreadPool thread_pool(numOfThreads, pairsOfPlayersQueue, id2Score, id2factory);
    }
};
