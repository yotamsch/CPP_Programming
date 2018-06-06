/**
 * @brief The header file of the ScoreManager class
 * 
 * @file ScoreManager.h
 * @author Tala Amouri
 * @date 2018-05-18
 */
#include "FightInfo.h"
#include "GameUtilitiesRPS.h"
#include "JokerChange.h"

/**
 * @brief- A class to manage the result of the game RPS.
 *  One instance is created in GameManager and is updated when necessary by calling its member functions from the GameManager.
 *  Holds the final result of the game and decides when the game is over
 * 
 */
class ScoreManager {
private:
    // these arrays support more than 2 players
    // [0] : player 1, [1] : player 2 ...
    int _movablePiecesCounter[NUM_OF_PLAYERS]; //at index 0 holds number of movable pieces of player 1, at index 1 hold number of movable pieces of player 2
    int _flagPiecesCounter[NUM_OF_PLAYERS]; //at index 0 holds number of flag pieces of player 1, at index 1 hold number of flag pieces of player 2
    bool _isBadPositioning[NUM_OF_PLAYERS]; //marks players with either having some bad position or not
    bool _isBadMove[NUM_OF_PLAYERS]; //marks players with either having some bad move or not
    const char* _reasonOfFinalResult; // this will hold the reasoning to the result

public:
    // basic c'tor
    ScoreManager();

    // updates member fields according to the fight info
    void notifyFight(const FightInfo& rFightInfo);
    // updates member according to the joker change
    void notifyJokerChange(const JokerChange& rJokerChange, char jokerPreviousRep, int player);
    // set a player to be the loser
    void dismissPlayer(int player, Reason reason);
    // increase the number of pieces for player
    void increaseNumOfPieces(int player, char pieceChar);
    // returns true iff the game is over (no moves for both players)
    bool isGameOver();
    // get the winner of the game
    int getWinner();
    // gets the reason of the final result of the game
    const char* getReasonOfFinalResult() { return _reasonOfFinalResult; }

private:
    // helper function to decrease the piece count (by type)
    void decreaseElement(int player, char piece);
    // helper function: increases _movablePiecesCounter
    void increaseNumOfMovingPieces(int player) { this->_movablePiecesCounter[--player]++; }
    // helper function: decreases _movablePiecesCounter
    void decreaseNumOfMovingPieces(int player) { this->_movablePiecesCounter[--player]--; }
    // helper function: increases _flagPiecesCounter
    void increaseNumOfFlags(int player) { this->_flagPiecesCounter[--player]++; }
    // helper function: decreases _flagPiecesCounter
    void decreaseNumOfFlags(int player) { this->_flagPiecesCounter[--player]--; }
    // mark current player as having a bad positioning
    void markBadPosition(int player) { this->_isBadPositioning[--player] = true; }
    // mark current player as having a bad move
    void markBadMove(int player) { this->_isBadMove[--player] = true; }
};