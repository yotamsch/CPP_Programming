
#include "GameManagerRPS.h"
#include "AutoPlayerAlgorithm.h"
#include "BoardRPS.h"
#include "FilePlayerAlgorithm.h"
#include "MoveRPS.h"
#include "PieceRPS.h"
#include "PointRPS.h"
#include "ScoreManager.h"

#include <cassert>
#include <fstream>
#include <map>
#include <memory>

int outputGameResult(const char* path, const BoardRPS& b, int winner, std::string msg_reason)
{
    std::ofstream out;
    try {
        out.open(path, std::ios::trunc);
        out << "Winner: " << winner << std::endl
            << "Reason: " << msg_reason << std::endl
            << std::endl
            << b;
        out.close();
    } catch (...) {
        return 1;
    }
    return 0;
}

void playCurrTurn(int currPlayerNumber, std::unique_ptr<PlayerAlgorithm>& rpCurrPlayer, std::unique_ptr<PlayerAlgorithm>& rpOppPlayer, BoardRPS& myBoard, ScoreManager& rScoreManager)
{
    std::unique_ptr<FightInfo> fightInfo;
    std::unique_ptr<JokerChange> jokerChange;
    bool resultOfMoving;
    char jokerPrevChar;

    std::unique_ptr<Move> currMove = rpCurrPlayer->getMove();
    if (currMove == nullptr) {
        // no more moves for player, skip turn
        return;
    }
    // execute player move
    resultOfMoving = myBoard.movePiece(currPlayerNumber, currMove, fightInfo);
    if (resultOfMoving == false) {
        // announce loser
        rScoreManager.dismissPlayer(currPlayerNumber, Reason::BAD_MOVE_ERROR);
        return;
    }
    if (fightInfo != nullptr) {
        // there was a fight
        rpCurrPlayer->notifyFightResult(*fightInfo);
        rpOppPlayer->notifyFightResult(*fightInfo);
        rScoreManager.notifyFight(*fightInfo);
    }
    // handle joker change
    jokerChange = rpCurrPlayer->getJokerChange();
    if (jokerChange != nullptr) {
        jokerPrevChar = myBoard.getPieceAt(jokerChange->getJokerChangePosition())->getJokerRep();
        myBoard.changeJoker(currPlayerNumber, jokerChange);
        rScoreManager.notifyJokerChange(*jokerChange, jokerPrevChar, currPlayerNumber);
    }
    // notify the opponent on a move
    rpOppPlayer->notifyOnOpponentMove(*currMove);
}

// assume we have scoreManager as a parameter
void fillBoard(BoardRPS& rBoard, int vCurrPlayer, std::vector<std::unique_ptr<PiecePosition>>& positioningVec, std::vector<std::unique_ptr<FightInfo>>& rpFightInfoVec, ScoreManager& rScoreManager)
{
    bool resultOfPositioning;
    char currPiece;
    std::unique_ptr<FightInfo> thisFightInfo;

    for (int i = 0; i < positioningVec.size(); i++) {
        currPiece = positioningVec[i]->getPiece();
        resultOfPositioning = rBoard.placePiece(vCurrPlayer, positioningVec[i], thisFightInfo);
        if (resultOfPositioning == false) {
            // announce vCurrPlayer as losing
            rScoreManager.dismissPlayer(vCurrPlayer, Reason::POSITION_FILE_ERROR);
            return;
        }
        rScoreManager.increaseNumOfPieces(vCurrPlayer, currPiece);
        if (thisFightInfo != nullptr) {
            rScoreManager.notifyFight(*thisFightInfo);
            rpFightInfoVec.push_back(std::move(thisFightInfo));
        }
    }
}

int PlayRPS(int vGameStyle)
{
    const char* outfile_path = "./rps.output";
    const char* p1_posfile_path = "./player1.rps_board";
    const char* p2_posfile_path = "./player2.rps_board";
    const char* p1_movfile_path = "./player1.rps_moves";
    const char* p2_movfile_path = "./player2.rps_moves";

    std::unique_ptr<PlayerAlgorithm> p1;
    std::unique_ptr<PlayerAlgorithm> p2;
    std::vector<std::unique_ptr<PiecePosition>> initPositionP1;
    std::vector<std::unique_ptr<PiecePosition>> initPositionP2;
    std::vector<std::unique_ptr<FightInfo>> fightsInfoVec;
    int currentPlayer;
    int turn;
    int winner;
    const char* reason;

    switch (vGameStyle) {
    case 1:
        p1 = std::make_unique<AutoPlayerAlgorithm>();
        p2 = std::make_unique<AutoPlayerAlgorithm>();
        break;
    case 2:
        p1 = std::make_unique<FilePlayerAlgorithm>(p1_posfile_path, p1_movfile_path);
        p2 = std::make_unique<FilePlayerAlgorithm>(p2_posfile_path, p2_movfile_path);
        break;
    case 3:
        p1 = std::make_unique<AutoPlayerAlgorithm>();
        p2 = std::make_unique<FilePlayerAlgorithm>(p2_posfile_path, p2_movfile_path);
        break;
    case 4:
        p1 = std::make_unique<FilePlayerAlgorithm>(p1_posfile_path, p1_movfile_path);
        p2 = std::make_unique<AutoPlayerAlgorithm>();
        break;
    }

    // positioning
    p1->getInitialPositions(PLAYER_1, initPositionP1);
    p2->getInitialPositions(PLAYER_2, initPositionP2);

    // TODO maybe move to a unique_ptr of ScoreManager
    ScoreManager scoreManager;
    // TODO maybe create a unique_ptr of BoardRPS
    BoardRPS myBoard(DIM_X, DIM_Y);

    fillBoard(myBoard, PLAYER_1, initPositionP1, fightsInfoVec, scoreManager);
    fillBoard(myBoard, PLAYER_2, initPositionP2, fightsInfoVec, scoreManager);

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
        currentPlayer = (currentPlayer + 1) % (NUM_OF_PLAYERS + 1) + 1;
        ++turn;
    }

    if (scoreManager.isGameOver()) {
        // game is over with a result
        winner = scoreManager.getWinner();
        reason = scoreManager.getReasonOfFinalResult();
    } else if (turn >= MAX_NUM_OF_MOVES) {
        // reached max number of turns without a result
        winner = NO_PLAYER;
        reason = RSN_MOVE_FILES_NO_WINNER;
    } else {
        // TODO there might be an edge case which will reach here
    }

    return outputGameResult(outfile_path, myBoard, winner, reason);
}