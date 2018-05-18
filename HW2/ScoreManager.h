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
    int _flagPiecesCounter[NUM_OF_PLAYERS];  //at index 0 holds number of flag pieces of player 1, at index 1 hold number of flag pieces of player 2
    bool _isBadPositioning[NUM_OF_PLAYERS]; //marks players with either having some bad position or not
    bool _isBadMove[NUM_OF_PLAYERS];//marks players with either having some bad move or not
    const char* _reasonOfFinalResult;// this will hold the reasoning to the result

public:
    // basic c'tor
    ScoreManager();

    /**
     * @brief given a FightInfo reference, the function updates its member fields accordingly as follows:
     * for each fight, checks who was the winner and decreases the suitable piece counter for the loser
     * 
     * @param rFightInfo - reference to a FighInfo holds the information of latest fight
     */
    void notifyFight(const FightInfo& rFightInfo);

    /**
     * @brief given a reference to JokerChange , extracts infromation of it and decreases/increases the pieces counters accordingly
     * 
     * @param rJokerChange - reference to JokerChange
     * @param jokerPreviousRep - joker's representation before actually performing the change
     * @param player - the player whom joker has just changed
     */
    void notifyJokerChange(const JokerChange& rJokerChange, char jokerPreviousRep, int player);

    // set a player to be the loser
    /**
     * @brief sets the provided player as loser by calling markBadPosition or markBadMove depending on the reason the player has lost
     * 
     * @param player - loser 
     * @param reason - reason of losing: either Reason::POSITION_FILE_ERROR or Reason::BAD_MOVE_ERROR
     */
    void dismissPlayer(int player, Reason reason);

    // increase the number of pieces of a player. calls either increaseNumOfMovingPieces or increaseNumOfFlags according to pieceChar classification
    void increaseNumOfPieces(int player, char pieceChar);
   
    /**
     * @brief checks status of the game, and if it finds a winner or a tie then returns true
     * 
     * @return true - if an end of game is reached: i.e. if any player lost or there is a tie
     * @return false - if game is still on without a result
     */
    bool isGameOver();
   
    /**
     * @brief checks current status:
     * if counter of moving pieces or counter of flags for any of the players is <= 0 , returns the winner symbol (could be 0,1,2)
     * otherwise if any of the players was announced as loser for having a bad positioning or bad move, returns the winner(could be 0,1,2)
     * otherwise, no winner(0,1,2) is found and GAME_IS_STILL_ON is returned
     * @return int - the result mentioned above
     */
    int getWinner();
    // get the reason of the final result
    const char* getReasonOfFinalResult();

private:
    /**
     * @brief the function is called to decrease the number of pieces of specified player in case he lost a fight
     * 
     * @param player - owner player
     * @param piece - a piece that "was eaten/killed"- used to decide which piece type to decrease (classified as moving piece, flag or bomb)
     */
    void decreaseElement(int player, char piece);

    //helper function: increases _movablePiecesCounter
    void increaseNumOfMovingPieces(int player);
    //helper function: decreases _movablePiecesCounter
    void decreaseNumOfMovingPieces(int player);
    //helper function: increases _flagPiecesCounter
    void increaseNumOfFlags(int player);
    //helper function: decreases _flagPiecesCounter
    void decreaseNumOfFlags(int player);
    //mark current player as having a bad positioning
    void markBadPosition(int player);
    //mark current player as having a bad move
    void markBadMove(int player);
};