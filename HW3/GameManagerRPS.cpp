/**
 * @brief the game manager for the Rock Paper Scissors game.
 * 
 * @file GameManagerRPS.cpp
 * @author Tala Amouri
 * @date 2018-05-04
 */
#include "GameManagerRPS.h"
#include "RSPPlayer_312148190.h"
#include "BoardRPS.h"
#include "MoveRPS.h"
#include "PieceRPS.h"
#include "PointRPS.h"
#include "ScoreManager.h"

#include <cassert>
#include <fstream>
#include <map>
#include <memory>

GameManager GameManager::staticGameManager;

/**
 * @brief - Asks for next move of current player and performs the move by calling BoardRPS member function
 * if the move was not legal then it notifies the ScoreManager of current player as loser
 * if the move was legal: 1. it notifies both player of the fight result, in case there was a fight
 * 2. it notifies opponent player of the current move
 * 3. in case there was a joker change, notifies the ScoreManager of it.
 * 
 * @param currPlayerNumber - current player number which this is his turn
 * @param rpCurrPlayer - reference to current player which this is his turn
 * @param rpOppPlayer - reference to opponent player(which this is not his turn)
 * @param myBoard - game board reference
 * @param rScoreManager - ScoreManager reference
 */
void playCurrTurn(int currPlayerNumber, std::unique_ptr<PlayerAlgorithm>& rpCurrPlayer, std::unique_ptr<PlayerAlgorithm>& rpOppPlayer, BoardRPS& myBoard, ScoreManager& rScoreManager)
{
    std::unique_ptr<FightInfo> fightInfo;
    std::unique_ptr<JokerChange> jokerChange;
    bool resultOfMoving, resultOfJokerChange;
    char jokerPrevChar;

    std::unique_ptr<Move> currMove = rpCurrPlayer->getMove();
    if (currMove == nullptr) {
        // no more moves for player, skip turn
        return;
    }
    // execute player move
    resultOfMoving = myBoard.movePiece(currPlayerNumber, currMove, fightInfo);
    if (!resultOfMoving) {
        // announce loser
        rScoreManager.dismissPlayer(currPlayerNumber);
        return;
    }
    // notify the opponent on a move
    rpOppPlayer->notifyOnOpponentMove(*(currMove));
    if (fightInfo != nullptr) {
        // there was a fight
        rpCurrPlayer->notifyFightResult(*fightInfo);
        rpOppPlayer->notifyFightResult(*fightInfo);
        rScoreManager.notifyFight(*fightInfo);
    }
    // handle joker change
    jokerChange = rpCurrPlayer->getJokerChange();
    if (jokerChange != nullptr) {
        auto& jokerPiece = myBoard.getPieceAt(jokerChange->getJokerChangePosition());
        if (jokerPiece == nullptr) {
            rScoreManager.dismissPlayer(currPlayerNumber);
            return;
        }
        jokerPrevChar = myBoard.getPieceAt(jokerChange->getJokerChangePosition())->getJokerRep();
        resultOfJokerChange = myBoard.changeJoker(currPlayerNumber, jokerChange);
        if (!resultOfJokerChange) {
            rScoreManager.dismissPlayer(currPlayerNumber);
            return;
        }
        rScoreManager.notifyJokerChange(*jokerChange, jokerPrevChar, currPlayerNumber);
    }
}

/**
 * @brief - given a reference to a board and a vector of piece positions of one player, and a vector of FightInfo:
 * fills the board by positioning the pieces given at positioningVec. if any of the positions is bad, notifies ScoreManager about current player as loser and returns false
 * fills rpFightInfoVec with FightInfo instances for each fight that happened as a result of positioning the player's pieces on the board
 * 
 * @param rBoard - the board to be filled
 * @param vCurrPlayer - current player number
 * @param positioningVec - vector containing the current player's initial positionings
 * @param rpFightInfoVec - vector to be filled with all the fights that occured as a result of the above positioning on the board
 * @param rScoreManager - reference to the ScoreManager to be notified of a losing player as a result of bad positioning 
 * @return true - if all positionings are legal
 * @return false - if any of the positionings is "bad"
 */
bool fillBoard(BoardRPS& rBoard, int vCurrPlayer, std::vector<std::unique_ptr<PiecePosition>>& positioningVec, std::vector<std::unique_ptr<FightInfo>>& rpFightInfoVec, ScoreManager& rScoreManager)
{
    bool resultOfPositioning;
    char currPiece;
    std::unique_ptr<FightInfo> thisFightInfo;

    for (int i = 0; i < (int)positioningVec.size(); i++) {
        currPiece = positioningVec[i]->getPiece() == JOKER_CHR ? positioningVec[i]->getJokerRep() : positioningVec[i]->getPiece();
        resultOfPositioning = rBoard.placePiece(vCurrPlayer, positioningVec[i], thisFightInfo);
        if (resultOfPositioning == false) {
            // announce vCurrPlayer as losing
            rScoreManager.dismissPlayer(vCurrPlayer);
            return false;
        }
        rScoreManager.increaseNumOfPieces(vCurrPlayer, currPiece);
        if (thisFightInfo != nullptr) {
            rScoreManager.notifyFight(*thisFightInfo);
            rpFightInfoVec.push_back(std::move(thisFightInfo));
        }
    }
    return true;
}
/**
 * @brief The function to actually start a game between player p1 and player p2
 * 
 * @param p1 
 * @param p2 
 * @return int - winner: 0,1 or 2
 */
int GameManager::PlayRPS(std::unique_ptr<PlayerAlgorithm> p1, std::unique_ptr<PlayerAlgorithm> p2)
{
    std::vector<std::unique_ptr<PiecePosition>> initPositionP1;
    std::vector<std::unique_ptr<PiecePosition>> initPositionP2;
    std::vector<std::unique_ptr<FightInfo>> fightsInfoVec;
    bool fillRes1, fillRes2;
    int currentPlayer, turn, winner;

    // positioning
    p1->getInitialPositions(PLAYER_1, initPositionP1);
    p2->getInitialPositions(PLAYER_2, initPositionP2);

    // since will be used only as long as this function in operating, chose to implement using an Lvalue
    ScoreManager scoreManager;
    BoardRPS myBoard(DIM_X, DIM_Y);

    fillRes1 = fillBoard(myBoard, PLAYER_1, initPositionP1, fightsInfoVec, scoreManager);
    fillRes2 = fillBoard(myBoard, PLAYER_2, initPositionP2, fightsInfoVec, scoreManager);
    // if any of the players had bad positioning
    if (!fillRes1 || !fillRes2) {
        myBoard.clearBoard();
        winner = scoreManager.getWinner();
        return winner;
    }

    // notify when game board was fully created
    p1->notifyOnInitialBoard(myBoard, fightsInfoVec);
    p2->notifyOnInitialBoard(myBoard, fightsInfoVec);

    currentPlayer = PLAYER_1;
    turn = 0;

    while (turn < MAX_NUM_OF_MOVES && !scoreManager.isGameOver()) {
        switch (currentPlayer) {
        case PLAYER_1:
            playCurrTurn(PLAYER_1, p1, p2, myBoard, scoreManager);
            break;
        case PLAYER_2:
            playCurrTurn(PLAYER_2, p2, p1, myBoard, scoreManager);
            break;
        default:
            break;
        }
        currentPlayer = (currentPlayer % NUM_OF_PLAYERS) + 1;
        ++turn;
    }

    if (scoreManager.isGameOver()) {
        // game is over with a result
        winner = scoreManager.getWinner();
    } else if (turn >= MAX_NUM_OF_MOVES) {
        // reached max number of turns without a result
        winner = NO_PLAYER;
    }
    return winner;
}