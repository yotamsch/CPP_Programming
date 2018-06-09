#include <functional>
#include <memory>
#include <iostream>
#include <map>
#include <queue>
#include "PlayerAlgorithm.h"
#include "GameManagerRPS.h"
#include "ThreadPool.h"


class TournamentManager {
    static TournamentManager theTournamentManager;
    static std::vector<std::string> so_files_names;
    
    // private ctor
    TournamentManager() {}
public:
    static std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> id2factory;
    static std::map<std::string,int> id2Score;//TODO: correctly initialize map
    static std::queue<std::pair<std::string,std::string>> pairsOfPlayersQueue;//TODO: correctly fill this map, YOTAM's

    static TournamentManager& getTournamentManager() {
        return theTournamentManager;
    }
    static std::vector<std::string>& getSoFilesNames() {
        return so_files_names;
    }
    void registerAlgorithm(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod) {
        if (id2factory.find(id) == id2factory.end())
        {
            //TODO: WARN
            //ID ALREADY EXISTS
        }else{
            id2factory[id] = factoryMethod;
        }
    }
    void run(int numOfThreads)const {
        ThreadPool thread_pool(numOfThreads, pairsOfPlayersQueue, id2Score, id2factory);  
    }
};
