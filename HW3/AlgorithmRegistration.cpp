#include "AlgorithmRegistration.h"
#include "TournamentManager.h"


// AlgorithmRegistration.cpp
AlgorithmRegistration::AlgorithmRegistration(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod) {
    TournamentManager::getTournamentManager().registerAlgorithm(id, factoryMethod);
}