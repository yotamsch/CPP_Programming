/**
 * @brief The header file of the RSPPlayer_312148190 (AI) class.
 * 
 * @file RSPPlayer_312148190.h
 * @author Yotam Sechayk
 * @date 2018-05-10
 */
#ifndef __H_RSP_PLAYER_312148190
#define __H_RSP_PLAYER_312148190

#include "GameUtilitiesRPS.h"
#include "PlayerAlgorithm.h"
#include <memory>
#include <set>
#include <vector>

class RSPPlayer_312148190 : public PlayerAlgorithm {
protected:
    // data structures
    // NOTE: The player can't use the classes defined for the game itself since the usage is different, or maybe non existant for him at all. So private simplified structs were implemented to give the player some data structures for representing the thoguht information on the game state. 
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
        int _M_position = -1;
        char _M_new_rep = '\0';
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

        // add a piece to the collection (the player is determined according to the piece itself)
        void addPiece(piece p, int position);
        // removes a piece (flag included) from the collection
        void removePiece(int position);
        // remove a flag from the "thought to be enemy flag" set
        void removeFlag(int position);
        // empties a piece
        void emptyPiece(int position);
        // updates a piece to be a joker when discovered
        void updateJoker(int position);
        // swap pieces at positions
        void swapPieces(int pos1, int pos2);
        // adds a move to the move history
        void addMove(int from, int to);
        // gets a reference to the latest move in the history
        const move& peekMove() const;
    };

private:
    const double UNKNOWN_WIN_CHANCE = 0.60; // how aggressive we want the player to be (1 - very aggressive, 0 - not aggressive at all)

    info _info; // will hold the current info on the thought state of the game
    unsigned _seed_value; // the random seed value

public:
    // basic c'tor
    RSPPlayer_312148190() {}
    // no need for copy c'tor
    RSPPlayer_312148190(const RSPPlayer_312148190& other) = delete;

    // d'tor
    ~RSPPlayer_312148190() {}

    // interface defined functions
    // gets the positioning of the player
    void getInitialPositions(int player,
        std::vector<unique_ptr<PiecePosition>>& vectorToFill);
    // notifies on a the finalization of the board at the start of the game
    void notifyOnInitialBoard(const Board& b,
        const std::vector<unique_ptr<FightInfo>>& fights);
    // notifies when the opponent has executed a move
    void notifyOnOpponentMove(const Move& move);
    // notify if a fight was made (in either turns)
    void notifyFightResult(const FightInfo& fightInfo);
    // gets the next move for the player
    unique_ptr<Move> getMove();
    // gets the next joker change for the player
    unique_ptr<JokerChange> getJokerChange();

private:
    // gets a position not used yet
    int getPositionNotSelectedYet() const;
    // position a piece of a givben type
    void positionPiecesOfType(int vLimit, char vType, std::vector<unique_ptr<PiecePosition>>& vectorToFill);

    // get the number of moving pieces for a player
    int getNumOfMovingPieces(info& data, player_info& player) const;
    // is the proposed move legal
    bool isMovePossible(info& data, int x, int y, int n_x, int n_y);
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
    void performMoveOnBoard(info& data, move& vMove);
    // calculate the "score" for a board representation
    float calcPlayerBoardScore(info& data);
    // gets the score for a move to be performed on a board
    float getScoreForMove(info& data, move& vMove);
    // calculate the best move for a player to perform
    move getBestMoveForPlayer(info& data);

    // calculate the "score" for a board representation
    float getScoreForJokerChange(info data, joker_change vChange);
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
    // checks if the position is valid
    static bool isPosValid(int x, int y);
    // checks if the position and move is valid (location wise)
    static bool isPosValid(int x, int y, int n_x, int n_y);

public:
    // prints the full state of the object nicely
    void prettyPrint();
    // prints the state of the "board" nicely
    void prettyPrintBoard();
};

#endif // !__H_RSP_PLAYER_312148190
