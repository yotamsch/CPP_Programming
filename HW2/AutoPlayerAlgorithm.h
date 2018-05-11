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
    // data structures
    struct piece {
        int _M_player;
        bool _M_isJoker;
        char _M_piece;
    };

private:
    // the player identifier
    int _player;
    // will have the known board
    std::vector<piece> _knownBoard;
    // will have the positions of the player pieces on the board
    // needs to update regularly
    std::set<int> _playerPieces;

public:
    // basic c'tor
    AutoPlayerAlgorithm()
        : _knownBoard(DIM_X * DIM_Y)
        , _playerPieces()
    {
    }
    AutoPlayerAlgorithm(const AutoPlayerAlgorithm& other) = delete;

    // d'tor
    ~AutoPlayerAlgorithm() {}

    // interface defined functions
    void getInitialPositions(int player,
        std::vector<unique_ptr<PiecePosition>>& vectorToFill);
    void notifyOnInitialBoard(const Board& b,
        const std::vector<unique_ptr<FightInfo>>& fights);
    void notifyOnOpponentMove(const Move& move);
    void notifyFightResult(const FightInfo& fightInfo);
    unique_ptr<Move> getMove();
    unique_ptr<JokerChange> getJokerChange();

    // utility
    // TODO is this needed?
    const std::vector<piece>& getKnownBoard() { return _knownBoard; };
    const std::set<int>& getPlayerPieces() { return _playerPieces; }

private:
    int getPositionNotSelectedYet() const;
    void positionPiecesOfType(int vLimit, char vType, std::vector<unique_ptr<PiecePosition>>& vectorToFill);
    void removePlayerPiece(int pos);
    void editPieceInPosition(int vPos, int vPlayer, char vType = '\0', bool vIsJoker = false);
    // get the x dimention parameter from a unified position
    static int getXDim(int vPos);
    // get the y dimention parameter from a unified position
    static int getYDim(int vPos);
    // get the unified position parameter
    static int getPos(int vX, int vY);
    // get a random possible joker representation
    static char getRandomJokerPieceType();
    // get a random position on the board by the boarrd dimensions
    static int getRandomPos();
};

#endif // !__H_AUTO_PLAYER_ALGORITHM
