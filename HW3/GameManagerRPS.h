/**
 * @brief The game manager header file.
 * 
 * @file GameManagerRPS.h
 * @author Tala Amouri
 * @date 2018-05-04
 */
#ifndef __H_GAME_MANAGER_RPS
#define __H_GAME_MANAGER_RPS
#include <memory>
#include "PlayerAlgorithm.h"

class GameManager{
    static GameManager staticGameManager;

public:
    static GameManager& GetGameManager() {
        return staticGameManager;
    }

    int PlayRPS(std::unique_ptr<PlayerAlgorithm> p1, std::unique_ptr<PlayerAlgorithm> p2);
};



#endif // !__H_GAME_MANAGER_RPS