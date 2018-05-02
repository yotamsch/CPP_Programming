
#include "GameManagerRPS.h"
#include "FilePlayerAlgorithm.h"
#include "AutoPlayerAlgorithm.h"
#include "BoardRPS.h"
#include "FightInfoRPS.h"
#include "PointRPS.h"
#include "PieceRPS.h"
#include "MoveRPS.h"

#include <memory>
#include <map>
#include <cassert>

#define PLAYER_1 1
#define PLAYER_2 2
#define NO_WINNER 0
#define MAX_NUM_OF_MOVES 100
#define NON_JOKER_FLAG '#'

void informAboutInitialFights(BoardRPS& rBoard1, BoardRPS& rBoard2, std::vector<unique_ptr<FightInfo>>& rFightsInfoVec){
    assert(rBoard1.GetDimentionY() == rBoard2.GetDimentionY());
    assert(rBoard1.GetDimentionX() == rBoard2.GetDimentionX());
    const std::vector<std::vector<PieceRPS>>& rMyBoardVec1 = rBoard1.getBoard();
    const std::vector<std::vector<PieceRPS>>& rMyBoardVec2 = rBoard2.getBoard();
    char charOfPlayer1;
    char charOfPlayer2;
    int winner;
    for (int i=0; i<rBoard1.GetDimentionX(); ++i) {
        for (int j=0; j<rBoard1.GetDimentionY(); ++j) {
            if(rMyBoardVec1[i][j].GetPieceType() == PieceType::NONE || rMyBoardVec2[i][j].GetPieceType() == PieceType::NONE){
                continue; //no fight in this case
            }
            if(rMyBoardVec1[i][j].GetPieceType() == rMyBoardVec2[i][j].GetPieceType()){
                    winner = 0;
            }
            else {
                if (rMyBoardVec1[i][j].GetPieceType() <  rMyBoardVec2[i][j].GetPieceType()) {
                    winner = PLAYER_2;
                } else {
                    winner = PLAYER_1;
                }
                if (rMyBoardVec2[i][j].GetPieceType() != PieceType::NONE && rMyBoardVec1[i][j].GetPieceType() == PieceType::BOMB) {
                    winner = 0;
                }
                if (rMyBoardVec1[i][j].GetPieceType() != PieceType::NONE && rMyBoardVec2[i][j].GetPieceType() == PieceType::BOMB) {
                    winner = 0;
                }
            }
            charOfPlayer1 = PieceTypeToChar(rMyBoardVec1[i][j].GetPieceType());
            charOfPlayer2 = PieceTypeToChar(rMyBoardVec2[i][j].GetPieceType());
            PointRPS fightPosition(i,j);//maybe should pass a unique ptr to this instead of reference
            std::unique_ptr<FightInfoRPS> fightInfoPtr =
                 std::make_unique<FightInfoRPS>(fightPosition, charOfPlayer1, charOfPlayer2, winner);
            rFightsInfoVec.push_back(std::move(fightInfoPtr));
        }
    }
}

int getWinnerOfAFight(PieceRPS& player1Piece, PieceRPS& player2Piece){
    if(player1Piece > player2Piece){
        return PLAYER_1;
    }
    else if(player1Piece <  player2Piece){
        return PLAYER_2;
    }
    else{
        return NO_WINNER;
    }
}

void playCurrTurn(std::unique_ptr<PlayerAlgorithm> pCurrPlayer, std::unique_ptr<PlayerAlgorithm> pOppPlayer, BoardRPS& mergedBoard){
    const Point& fromPosition = pCurrPlayer->getMove()->getFrom();
    const Point& toPosition = pCurrPlayer->getMove()->getTo();
    MoveRPS currMove(fromPosition, toPosition);
    int oldX = fromPosition.getX();
    int oldY = fromPosition.getY(); 
    int newX = toPosition.getX();
    int newY = toPosition.getY();
    PieceRPS& movingPiece = mergedBoard.getBoard()[oldX][oldY];
    PieceRPS& pieceAtDestination = mergedBoard.getBoard()[newX][newY];            
    PlayerType movingPlayer = movingPiece.GetPlayerType();
    if( mergedBoard.IsMoveLegal(oldX, oldY, newX, newY) ){
        if( mergedBoard.isThereAFight(newX, newY) ){
            FightInfoRPS fightInfo(toPosition, movingPiece.getPiece(), pieceAtDestination.getPiece(), getWinnerOfAFight(movingPiece, pieceAtDestination));
            pCurrPlayer->notifyFightResult(fightInfo);
            
            unique_ptr<JokerChange> jokerChange = pCurrPlayer->getJokerChange();
            char jokerNewRep = jokerChange->getJokerNewRep();
            const Point& jokerChangePos = jokerChange->getJokerChangePosition();
            mergedBoard.ChangeJoker(jokerChangePos, CharToPieceType(jokerNewRep));

            pOppPlayer->notifyFightResult(fightInfo);
        }
        if(! mergedBoard.MovePiece(oldX, oldY, newX, newY)) {
            //error couldn't make the move
        }
        pOppPlayer->notifyOnOpponentMove(currMove);
    }
    else{
        //handle illegal move
    }
}

// do no call this function with vCurrPlayer=1
int getOppositePlayer(int vCurrPlayer){
    int opp = vCurrPlayer == PLAYER_1? PLAYER_2 : PLAYER_1;
    return opp; 
}

bool isAFight(Board& rBoard, std::unique_ptr<Move> pMove, int vCurrPlayer){
    const Point& destPoint = pMove->getTo();
    int playerAtDest = rBoard.getPlayer(destPoint);
    if(getOppositePlayer(vCurrPlayer) == playerAtDest){
        return true;
    }
    return false;
}

// may convert this function to a member function of BoardRPS, will be handled
BoardRPS& fillBoard(BoardRPS& rBoard, int vCurrPlayer, std::vector<unique_ptr<PiecePosition>>& positioningVec){
    for(std::vector<unique_ptr<PiecePosition>>::iterator itr = positioningVec.begin(); itr != positioningVec.end(); ++itr){
        const Point& point = (*(itr))->getPosition();
        int x = point.getX();
        int y = point.getY();
        char pieceChar = (*(itr))->getPiece();
        PieceType pieceType = CharToPieceType(pieceChar);
        char jokerRepChar = (*(itr))->getJokerRep();
        bool isJoker = jokerRepChar==NON_JOKER_FLAG? false : true;
        rBoard.PlacePiece(vCurrPlayer, pieceType, x, y, isJoker); //should ensure this function puts the piece on the board correctly
    }
    return rBoard;
}

int PlayRPS(int vGameStyle) {
    vGameStyle++;
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
    
    /*positioning*/
    std::vector<unique_ptr<PiecePosition>> initPositionP1, initPositionP2;
    p1->getInitialPositions(PLAYER_1, initPositionP1);
    p2->getInitialPositions(PLAYER_2, initPositionP2);

    BoardRPS board1(DIM_X, DIM_Y);
    BoardRPS board2(DIM_X, DIM_Y);
    BoardRPS mergedBoard(DIM_X, DIM_Y);
    board1 = fillBoard(board1, PLAYER_1, initPositionP1);
    board2 = fillBoard(board2, PLAYER_2, initPositionP2);
    std::vector<std::unique_ptr<FightInfo>> fightsInfoVec;
    informAboutInitialFights(board1, board2, fightsInfoVec); //fills fightsInfoVec correctly
    /*perform all initial fights*/
    mergedBoard = mergedBoard.Merge(board1).Merge(board2); //performs all initial fights

    p1->notifyOnInitialBoard(mergedBoard,fightsInfoVec);
    p2->notifyOnInitialBoard(mergedBoard,fightsInfoVec);
    int currentPlayer = PLAYER_1;
    int turn = 0;
    int thereIsAWinner = 0;
    while(turn < MAX_NUM_OF_MOVES && !thereIsAWinner){
        if(currentPlayer == PLAYER_1){
            playCurrTurn(std::move(p1), std::move(p2), mergedBoard);
        }
        else{
            playCurrTurn(std::move(p2), std::move(p1), mergedBoard);
        }
        currentPlayer = getOppositePlayer(currentPlayer);
        turn++;
    }
    return 1;
}