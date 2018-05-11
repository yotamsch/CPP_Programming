#include "ScoreManager.h"

// * NOTE: for the function notifyFight iv'e created decreaseElement(int player) function. This function prevents code repetition.

ScoreManager::ScoreManager()
{
    for (int i = 0; i < NUM_OF_PLAYERS; i++) {
        this->_flagPiecesCounter[i] = 0;
        this->_movablePiecesCounter[i] = 0;
        this->_isBadMove[i] = false;
        this->_isBadPositioning[i] = false;
    }
}

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

void ScoreManager::dismissPlayer(int player, Reason reason)
{
    switch (reason) {
    case Reason::POSITION_FILE_ERROR:
        markBadPosition(player);
        break;
    case Reason::BAD_MOVE_ERROR:
        markBadMove(player);
        break;
    default:
        break;
    }
}

void ScoreManager::increaseNumOfMovingPieces(int player)
{
    this->_movablePiecesCounter[--player]++;
}

void ScoreManager::decreaseNumOfMovingPieces(int player)
{
    this->_movablePiecesCounter[--player]--;
}

void ScoreManager::decreaseNumOfFlags(int player)
{
    this->_flagPiecesCounter[--player]--;
}

void ScoreManager::increaseNumOfFlags(int player)
{
    this->_flagPiecesCounter[--player]++;
}

void ScoreManager::increaseNumOfPieces(int player, char pieceChar)
{
    if (pieceChar == FLAG_CHR) {
        increaseNumOfFlags(player);
    } else if (pieceChar != BOMB_CHR) {
        increaseNumOfMovingPieces(player);
    }
}

bool ScoreManager::isGameOver()
{
    if (getWinner() == GAME_IS_STILL_ON) {
        return false;
    }
    return true;
}

const char* ScoreManager::getReasonOfFinalResult()
{
    return _reasonOfFinalResult;
}

void ScoreManager::markBadPosition(int player)
{
    this->_isBadPositioning[--player] = true;
}

void ScoreManager::markBadMove(int player)
{
    this->_isBadMove[--player] = true;
}

// TODO maybe think of a better way to construct this function
int ScoreManager::getWinner()
{
    if (_isBadPositioning[PLAYER_1 - 1] && _isBadPositioning[PLAYER_2 - 1]) {
        _reasonOfFinalResult = RSN_BAD_POSITION_FILE_DOUBLE;
        return NO_PLAYER;
    }
    if (_isBadPositioning[PLAYER_1 - 1]) {
        _reasonOfFinalResult = RSN_BAD_POSISION_FILE_SINGLE;
        return PLAYER_2;
    }
    if (_isBadPositioning[PLAYER_2 - 1]) {
        _reasonOfFinalResult = RSN_BAD_POSISION_FILE_SINGLE;
        return PLAYER_1;
    }
    if (_isBadMove[PLAYER_1 - 1]) {
        _reasonOfFinalResult = RSN_BAD_MOVE_FILE_SINGLE;
        return PLAYER_2;
    }
    if (_isBadMove[PLAYER_2 - 1]) {
        _reasonOfFinalResult = RSN_BAD_MOVE_FILE_SINGLE;
        return PLAYER_1;
    }
    if (_flagPiecesCounter[PLAYER_1 - 1] <= 0 && _flagPiecesCounter[PLAYER_2 - 1] <= 0) {
        _reasonOfFinalResult = RSN_POSITION_NO_FLAGS;
        return NO_PLAYER;
    }
    if (_movablePiecesCounter[PLAYER_1 - 1] <= 0 && _movablePiecesCounter[PLAYER_2 - 1] <= 0) {
        _reasonOfFinalResult = RSN_POSITION_NO_PIECES;
        return NO_PLAYER;
    }
    if (_flagPiecesCounter[PLAYER_1 - 1] <= 0 || _movablePiecesCounter[PLAYER_1 - 1] <= 0) {
        _reasonOfFinalResult = !_flagPiecesCounter[PLAYER_1 - 1] ? RSN_ALL_FLAGS_CAPTURED : RSN_ALL_PIECES_EATEN;
        return PLAYER_2;
    }
    if (_flagPiecesCounter[PLAYER_2 - 1] <= 0 || _movablePiecesCounter[PLAYER_2 - 1] <= 0) {
        _reasonOfFinalResult = !_flagPiecesCounter[PLAYER_2 - 1] ? RSN_ALL_FLAGS_CAPTURED : RSN_ALL_PIECES_EATEN;
        return PLAYER_1;
    }
    return GAME_IS_STILL_ON;
}
