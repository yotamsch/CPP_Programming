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
    struct joker_change {
        int _M_position;
        char _M_new_rep;
    };
    struct player_info {
        int _M_id;
        std::set<int> _M_pieces; // all pieces except flags (R,P,S,B)
        std::set<int> _M_flags; // all flags (F)
        std::set<int> _M_jokers; // all jokers (J)
    };
    struct info {
        std::array<piece, DIM_X * DIM_Y> _M_board;
        std::vector<move> _M_moves;
        player_info _M_this_player;
        player_info _M_other_player;

        void addPiece(piece p, int position);
        void removePiece(int position);
        void removeFlag(int position);
        void emptyPiece(int position);
        void updateJoker(int position);
        void swapPieces(int pos1, int pos2);
        void addMove(int from, int to);
        const move& peekMove() const;
        void swapPlayers();
    };

private:
    const double UNKNOWN_WIN_CHANCE = 0.66;
    info _info;

public:
    // basic c'tor
    AutoPlayerAlgorithm() {}
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

private:
    // gets a position not used yet
    int getPositionNotSelectedYet() const;
    // position a piece of a givben type
    void positionPiecesOfType(int vLimit, char vType, std::vector<unique_ptr<PiecePosition>>& vectorToFill);

    // is the proposed move legal
    bool isMovePossible(info& data, int vOriginPos, int vDestPos);
    // get integers of the possible moves of a piece at position
    void getPossibleMovesForPiece(info& data, int vPos, std::vector<int>& rMoves);
    // is a piece at position in danger
    bool isPieceInDanger(info& data, int vPos);
    // is the piece threatening another piece
    bool isPieceThreatening(info& data, int vPos);
    // will the origin piece win the fight against the destination piece
    bool willWinFight(info& data, int vOriginPos, int vDestPos);
    // get the average distance from the K closest vFromPlayer pieces
    float calcKNearestDistance(info& data, int vFromPlayer, int vPos, int k);
    // performs a move on a given board
    void performMoveOnBoard(info& data, move vMove);
    // calculate the "score" for a board representation
    float calcPlayerBoardScore(info& data);
    // gets the score for a move to be performed on a board
    float getScoreForMove(info data, move vMove);
    // calculate the best move for a player to perform
    move getBestMoveForPlayer(info& data);

    // get the best joker change if one exists
    joker_change getBestJokerChangeForPlayer(info& data);

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
    // checks if the position or move is valid (location wise)
    static bool isPosValid(int x, int y, int n_x = -1, int n_y = -1);

public:
    void prettyPrint();
    void prettyPrintBoard();
};

#endif // !__H_AUTO_PLAYER_ALGORITHM
