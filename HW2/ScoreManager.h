#include "FightInfo.h"
#include "GameUtilitiesRPS.h"
#include "JokerChange.h"

class ScoreManager {
private:
    // they arrays support more than 2 players
    // [0] : player 1, [1] : player 2 ...
    int _movablePiecesCounter[NUM_OF_PLAYERS]; 
    int _flagPiecesCounter[NUM_OF_PLAYERS];
    bool _isBadPositioning[NUM_OF_PLAYERS];
    bool _isBadMove[NUM_OF_PLAYERS];
    // this will hold the reasoning to the result
    const char* _reasonOfFinalResult;

public:
    // basic c'tor
    ScoreManager();

    // notify of a fight
    void notifyFight(const FightInfo& rFightInfo);
    // notify of a player joker change
    void notifyJokerChange(const JokerChange& rJokerChange, char jokerPreviousRep, int player);
    // set a player to be the loser
    void dismissPlayer(int player, Reason reason);
    // increase the number of pieces of a player
    void increaseNumOfPieces(int player, char pieceChar);
    // is the game over (i.e. is anyone losing/tie)
    bool isGameOver();
    // get the game winner
    int getWinner();
    // get the reason of the final result
    const char* getReasonOfFinalResult();

private:
    void decreaseElement(int player, char piece);
    void increaseNumOfMovingPieces(int player);
    void decreaseNumOfMovingPieces(int player);
    void increaseNumOfFlags(int player);
    void decreaseNumOfFlags(int player);
    void markBadPosition(int player);
    void markBadMove(int player);
};