#include "AlgorithmRegistration.h"
#include "TournamentManager.h"

// basic c'tor
AlgorithmRegistration::AlgorithmRegistration(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod)
{
    TournamentManager::get().registerAlgorithm(id, factoryMethod);
}