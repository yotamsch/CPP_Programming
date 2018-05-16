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
        int _M_player = 0;
        bool _M_isJoker = false;
        char _M_piece = '\0';
    };
    struct move {
        int _M_from = -1;
        int _M_to = -1;
    };

// TODO maybe convert to std::vector<std::unique_ptr<...>>
private:
    // the player identifier
    int _player;
    // will have the known board
    std::vector<piece> _knownBoard;
    // will have the positions of the player pieces on the board
    // needs to update regularly
    std::set<int> _playerPieces;
    std::set<int> _oppPieces;
    // the pieces which are thought to be flags
    std::set<int> _playerFlags;
    std::set<int> _oppFlags;
    // will have the move history of the opponent
    std::vector<move> _oppMoveHistory;

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
    void removePiece(int pos);
    void editPieceInPosition(int vPos, int vPlayer, char vType = '\0', bool vIsJoker = false);

    // attempting to locate flags, and update flag statistics
    void updateEnemyFlagsStat(int vPos);
    // is the proposed move legal
    bool isMovePossible(std::vector<piece>& rBoard, int vOriginPos, int vDestPos);
    // get integers of the possible moves of a piece at position
    void getPossibleMovesForPiece(std::vector<piece>& rBoard, int vPos, std::vector<int>& rMoves);
    // is a piece at position in danger
    bool isPieceInDanger(int vPos);
    // will the origin piece win the fight against the destination piece
    bool willWinFight(int vOriginPos, int vDestPos);
    // get the L2 distance from the given piece to the pieces of the opponent (other player)
    float calcL2Distance(int vPlayer, int vPos);
    // performs a move on a given board
    void performMoveOnBoard(std::vector<piece>& rBoard, move vMove);
    // calculate the "score" for a board representation
    float calcPlayerBoardScore(int vPlayer, std::vector<piece>& rBoard);
    // gets the score for a move to be performed on a board
    float getScoreForMove(int player, std::vector<piece> vBoard, move vMove);
    // calculate the best move for a player to perform
    move getBestMoveForPlayer(std::vector<piece>& rBoard, int player, int depth);

    // get the x dimention parameter from a unified position
    static int getXDim(int vPos);
    // get the y dimention parameter from a unified position
    static int getYDim(int vPos);
    // get the unified position parameter
    static int getPos(int vX, int vY);
    // get a random possible joker representation
    static char getRandomJokerRep();
    // get a random position on the board by the boarrd dimensions
    static int getRandomPos();
};

#endif // !__H_AUTO_PLAYER_ALGORITHM
