/**
 * @brief The game manager header file.
 * 
 * @file GameManagerRPS.h
 * @author Tala Amouri
 * @date 2018-05-04
 */
#ifndef __H_GAME_MANAGER_RPS
#define __H_GAME_MANAGER_RPS

#include "BoardRPS.h"
#include "MoveRPS.h"
#include "PieceRPS.h"
#include "PlayerAlgorithm.h"
#include "PointRPS.h"
#include "ScoreManager.h"

#include <memory>

class GameManager {
private:
    static GameManager instance;
    
    // private c'tor
    GameManager() {}

public:
    static GameManager& get()
    {
        return instance;
    }
    // play the RPS game
    int PlayRPS(std::unique_ptr<PlayerAlgorithm> p1, std::unique_ptr<PlayerAlgorithm> p2);

private:
    // fill the board with player pieces
    bool fillBoard(BoardRPS& rBoard, int vCurrPlayer, std::vector<std::unique_ptr<PiecePosition>>& positioningVec, std::vector<std::unique_ptr<FightInfo>>& rpFightInfoVec, ScoreManager& rScoreManager);
    // play a turn for a player
    void playCurrTurn(int currPlayerNumber, std::unique_ptr<PlayerAlgorithm>& rpCurrPlayer, std::unique_ptr<PlayerAlgorithm>& rpOppPlayer, BoardRPS& myBoard, ScoreManager& rScoreManager);
};

#endif // !__H_GAME_MANAGER_RPS