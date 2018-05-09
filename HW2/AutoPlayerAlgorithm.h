/**
 * @brief The HEADER file for the auto player (AI) of Rock Paper Scissors game.
 * 
 * @file AutoPlayerAlgorithm.h
 * @author Yotam Sechayk
 * @date 2018-05-04
 */
#ifndef __H_AUTO_PLAYER_ALGORITHM
#define __H_AUTO_PLAYER_ALGORITHM

#include "GameUtilitiesRPS.h"
#include "PlayerAlgorithm.h"
#include <memory>
#include <set>
#include <vector>

class AutoPlayerAlgorithm : public PlayerAlgorithm {
private:
    // the player identifier
    int _player;
    // will have the known board (joker not displayed) <player, piece>
    std::vector<std::pair<int, std::pair<PieceType, bool>>> _knownBoard;
    // will have the positions of the player pieces on the board
    // needs to update regularly
    std::set<int> _playerPieces;

public:
    // C'tor
    AutoPlayerAlgorithm()
        : _knownBoard(DIM_X * DIM_Y){};
    AutoPlayerAlgorithm(const AutoPlayerAlgorithm& other) = delete;
    // D'tor
    ~AutoPlayerAlgorithm(){};
    // Other
    void getInitialPositions(int player,
        std::vector<unique_ptr<PiecePosition>>& vectorToFill);
    void notifyOnInitialBoard(const Board& b,
        const std::vector<unique_ptr<FightInfo>>& fights);
    void notifyOnOpponentMove(const Move& move);
    void notifyFightResult(const FightInfo& fightInfo);
    unique_ptr<Move> getMove();
    unique_ptr<JokerChange> getJokerChange();
    const std::vector<std::pair<int, std::pair<PieceType, bool>>>& getKnownBoard() { return _knownBoard; };
    const std::set<int>& getPlayerPiece() { return _playerPieces; }

private:
    int getPositionNotSelectedYet(const std::set<int>& rPositions);
    void positionPiecesOfType(int player, int vLimit, PieceType vType, std::set<int>& rPositions, std::vector<unique_ptr<PiecePosition>>& vectorToFill);
    void removePlayerPiece(int pos);
    void editPieceInPosition(int vPos, int vPlayer, PieceType vType, bool vIsJoker);
};

#endif // !__H_AUTO_PLAYER_ALGORITHM
