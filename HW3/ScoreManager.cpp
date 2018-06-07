/**
 * @brief The implementation file of the ScoreManager class
 * 
 * @file ScoreManager.cpp
 * @author Tala Amouri
 * @date 2018-05-18
 */
#include "ScoreManager.h"

ScoreManager::ScoreManager()
{
    for (int i = 0; i < NUM_OF_PLAYERS; i++) {
        this->_flagPiecesCounter[i] = 0;
        this->_movablePiecesCounter[i] = 0;
        this->_isBadPositonOrMove[i] = false;
    }
}

/**
 * @brief The function is called to decrease the number of pieces of specified player in case he lost a fight
 * 
 * @param player - owner player
 * @param piece - a piece that "was eaten/killed"- used to decide which piece type to decrease (classified as moving piece, flag or bomb)
 */
void ScoreManager::decreaseElement(int player, char piece)
{
    switch (piece) {
    case FLAG_CHR:
        decreaseNumOfFlags(player);
        break;
    case BOMB_CHR:
        break;
    default:
        decreaseNumOfMovingPieces(player);
        break;
    }
}

/**
 * @brief given a FightInfo reference, the function updates its member fields accordingly as follows:
 * for each fight, checks who was the winner and decreases the suitable piece counter for the loser
 * 
 * @param rFightInfo - reference to a FighInfo holds the information of latest fight
 */
void ScoreManager::notifyFight(const FightInfo& rFightInfo)
{
    switch (rFightInfo.getWinner()) {
    case PLAYER_1:
        // player 2 lost
        decreaseElement(PLAYER_2, rFightInfo.getPiece(PLAYER_2));
        break;
    case PLAYER_2:
        // playr 1 lost
        decreaseElement(PLAYER_1, rFightInfo.getPiece(PLAYER_1));
        break;
    case NO_PLAYER:
        // both lost
        decreaseElement(PLAYER_1, rFightInfo.getPiece(PLAYER_1));
        decreaseElement(PLAYER_2, rFightInfo.getPiece(PLAYER_2));
        break;
    default:
        break;
    }
}

/**
 * @brief given a reference to JokerChange , extracts infromation of it and decreases/increases the pieces counters accordingly
 * 
 * @param rJokerChange - reference to JokerChange
 * @param jokerPreviousRep - joker's representation before actually performing the change
 * @param player - the player whom joker has just changed
 */
void ScoreManager::notifyJokerChange(const JokerChange& rJokerChange, char jokerPreviousRep, int player)
{
    if (rJokerChange.getJokerNewRep() == jokerPreviousRep) {
        return;
    }
    if (rJokerChange.getJokerNewRep() == BOMB_CHR) {
        decreaseNumOfMovingPieces(player);
    }
    if (jokerPreviousRep == BOMB_CHR) {
        increaseNumOfMovingPieces(player);
    }
}
/**
 * @brief sets the provided player as loser by calling markBadPosition or markBadMove depending on the reason the player has lost
 * 
 * @param player - loser 
 * @param reason - reason of losing: either Reason::POSITION_FILE_ERROR or Reason::BAD_MOVE_ERROR
 */
void ScoreManager::dismissPlayer(int player)
{
    markBadPositionOrMove(player);
}

/**
 * @brief Increase the number of pieces of a player. Calls either increaseNumOfMovingPieces or increaseNumOfFlags according to pieceChar classification
 * 
 * @param player - the player id to perform the action on
 * @param pieceChar - the piece type to increase by
 */
void ScoreManager::increaseNumOfPieces(int player, char pieceChar)
{
    if (pieceChar == FLAG_CHR) {
        increaseNumOfFlags(player);
    } else if (pieceChar != BOMB_CHR) {
        increaseNumOfMovingPieces(player);
    }
}

/**
 * @brief checks status of the game, and if it finds a winner or a tie then returns true
 * 
 * @return true - if an end of game is reached: i.e. if any player lost or there is a tie
 * @return false - if game is still on without a result
 */
bool ScoreManager::isGameOver()
{
    if (getWinner() == GAME_IS_STILL_ON) {
        return false;
    }
    return true;
}

/**
 * @brief checks current status:
 * if counter of moving pieces or counter of flags for any of the players is <= 0 , returns the winner symbol (could be 0,1,2)
 * otherwise if any of the players was announced as loser for having a bad positioning or bad move, returns the winner(could be 0,1,2)
 * otherwise, no winner(0,1,2) is found and GAME_IS_STILL_ON is returned
 * @return int - the result mentioned above
 */
int ScoreManager::getWinner()
{
    if (_isBadPositonOrMove[PLAYER_1 - 1] && _isBadPositonOrMove[PLAYER_2 - 1]) {
        return NO_PLAYER;
    }
    if (_isBadPositonOrMove[PLAYER_1 - 1]) {
        return PLAYER_2;
    }
    if (_isBadPositonOrMove[PLAYER_2 - 1]) {
        return PLAYER_1;
    }
    if (_flagPiecesCounter[PLAYER_1 - 1] <= 0 && _flagPiecesCounter[PLAYER_2 - 1] <= 0) {
        return NO_PLAYER;
    }
    if (_movablePiecesCounter[PLAYER_1 - 1] <= 0 && _movablePiecesCounter[PLAYER_2 - 1] <= 0) {
        return NO_PLAYER;
    }
    if (_flagPiecesCounter[PLAYER_1 - 1] <= 0 || _movablePiecesCounter[PLAYER_1 - 1] <= 0) {
        return PLAYER_2;
    }
    if (_flagPiecesCounter[PLAYER_2 - 1] <= 0 || _movablePiecesCounter[PLAYER_2 - 1] <= 0) {
        return PLAYER_1;
    }
    return GAME_IS_STILL_ON;
}
