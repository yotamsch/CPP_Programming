
#include "GameManagerRPS.h"
#include "FilePlayerAlgorithm.h"
#include "AutoPlayerAlgorithm.h"
#include "BoardRPS.h"
#include "PointRPS.h"
#include "PieceRPS.h"
#include "MoveRPS.h"
#include "ScoreManager.h"

#include <memory>
#include <map>
#include <cassert>

#define PLAYER_1 1
#define PLAYER_2 2
#define NO_WINNER 0
#define MAX_NUM_OF_MOVES 100
#define NON_JOKER_FLAG '#'


void playCurrTurn(int currPlayerNumber, std::unique_ptr<PlayerAlgorithm>& rpCurrPlayer, std::unique_ptr<PlayerAlgorithm>& rpOppPlayer, BoardRPS& myBoard, ScoreManager& rScoreManager){
    unique_ptr<Move> currMove = std::move(rpCurrPlayer->getMove());
    if(currMove == nullptr){
        //reached end of file for file-player. Go on normally with other player
        //according to suggestion in the course forum
        return;
    }
    unique_ptr<FightInfo> fightInfo;
    bool resultOfMoving = myBoard.movePiece(currPlayerNumber,currMove, fightInfo);
     
    if(resultOfMoving == false){
        //announce loser
        rScoreManager.DismissPlayer(currPlayerNumber, Reason::BAD_MOVE_ERROR);
        return;
    }
    if(fightInfo!=nullptr){
        //there was a fight
        rpCurrPlayer->notifyFightResult(*fightInfo);
        rpOppPlayer->notifyFightResult(*fightInfo);
        rScoreManager.notifyFight(*fightInfo);
    }
    unique_ptr<JokerChange> jokerChange = rpCurrPlayer->getJokerChange();
    //jokerChange->getJokerChangePosition()
    myBoard.changeJoker(currPlayerNumber, jokerChange);
    rScoreManager.notifyJokerChange(*jokerChange, ' ', currPlayerNumber); //TODO : edit parameters 
    rpOppPlayer->notifyOnOpponentMove(*currMove);
}


// do no call this function with vCurrPlayer=1
int getOppositePlayer(int vCurrPlayer){
    int opp = vCurrPlayer == PLAYER_1? PLAYER_2 : PLAYER_1;
    return opp; 
}

//assume we have scoreManager as a parameter
void fillBoard(BoardRPS& rBoard, int vCurrPlayer, std::vector<unique_ptr<PiecePosition>>& positioningVec, std::vector<std::unique_ptr<FightInfo>>& rpFightInfoVec, ScoreManager& rScoreManager){
    bool resultOfPositioning;
    for(int i=0; i<positioningVec.size(); i++){
        std::unique_ptr<FightInfo> thisFightInfo;
        rScoreManager.increaseNumOfPieces(vCurrPlayer, positioningVec[i]->getPiece());
        resultOfPositioning = rBoard.placePiece(vCurrPlayer, positioningVec[i], thisFightInfo);
        if(resultOfPositioning == false){
            //announce vCurrPlayer as losing
            rScoreManager.DismissPlayer(vCurrPlayer, Reason::POSITION_FILE_ERROR);
            return;
        }
        if(thisFightInfo != nullptr) {
            rScoreManager.notifyFight(*thisFightInfo);
            rpFightInfoVec.push_back(move(thisFightInfo));
        }
    }
}

int PlayRPS(int vGameStyle) {
  //  const char* outfile_path = "./rps.output";
    const char* p1_posfile_path = "./player1.rps_board";
    const char* p2_posfile_path = "./player2.rps_board";
    const char* p1_movfile_path = "./player1.rps_moves";
    const char* p2_movfile_path = "./player2.rps_moves";

    std::unique_ptr<PlayerAlgorithm> p1;
    std::unique_ptr<PlayerAlgorithm> p2;

    switch(vGameStyle){
        case 1:
            p1 = std::make_unique<AutoPlayerAlgorithm>();
            p2 = std::make_unique<AutoPlayerAlgorithm>();
            break;
        case 2:
            p1 = std::make_unique<FilePlayerAlgorithm>(p1_posfile_path, p1_movfile_path, PLAYER_1);
            p2 = std::make_unique<FilePlayerAlgorithm>(p2_posfile_path, p2_movfile_path, PLAYER_2);
            break;
        case 3:
            p1 = std::make_unique<AutoPlayerAlgorithm>();
            p2 = std::make_unique<FilePlayerAlgorithm>(p2_posfile_path, p2_movfile_path, PLAYER_2);
            break;
        case 4:     
            p1 = std::make_unique<FilePlayerAlgorithm>(p1_posfile_path, p1_movfile_path, PLAYER_1);
            p2 = std::make_unique<AutoPlayerAlgorithm>();
            break;
    }
    
    /*positioning*/
    std::vector<unique_ptr<PiecePosition>> initPositionP1, initPositionP2;
    p1->getInitialPositions(PLAYER_1, initPositionP1);
    p2->getInitialPositions(PLAYER_2, initPositionP2);
    std::vector<std::unique_ptr<FightInfo>> fightsInfoVec;
    ScoreManager scoreManager;
    BoardRPS myBoard(DIM_X, DIM_Y);
    fillBoard(myBoard, PLAYER_1, initPositionP1, fightsInfoVec, scoreManager);
    fillBoard(myBoard, PLAYER_2, initPositionP2, fightsInfoVec, scoreManager);

    p1->notifyOnInitialBoard(myBoard, fightsInfoVec);
    p2->notifyOnInitialBoard(myBoard, fightsInfoVec);

    int currentPlayer = PLAYER_1;
    int turn = 0;
    while(turn < MAX_NUM_OF_MOVES && !scoreManager.isGameOver()){
        if(currentPlayer == PLAYER_1){
            playCurrTurn(PLAYER_1, p1, p2, myBoard, scoreManager);
        }
        else{
            playCurrTurn(PLAYER_2, p2, p1, myBoard, scoreManager);
        }
        currentPlayer = getOppositePlayer(currentPlayer);
        turn++;   
    }
    int winner = scoreManager.getWinner();
    const char* reason = scoreManager.getReasonOfFinalResult();
    return 1;
}