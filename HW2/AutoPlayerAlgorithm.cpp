#include "AutoPlayerAlgorithm.h"

AutoPlayerAlgorithm::AutoPlayerAlgorithm(){}
AutoPlayerAlgorithm::~AutoPlayerAlgorithm(){}

void AutoPlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill){

}
void AutoPlayerAlgorithm::notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights){

}
void AutoPlayerAlgorithm::notifyOnOpponentMove(const Move& move){

}
void AutoPlayerAlgorithm::notifyFightResult(const FightInfo& fightInfo){

}
unique_ptr<Move> AutoPlayerAlgorithm::getMove(){

}
unique_ptr<JokerChange> AutoPlayerAlgorithm::getJokerChange(){

}
void AutoPlayerAlgorithm::IncrementPieceCount(PieceType type){

}
void AutoPlayerAlgorithm::DecrementPieceCount(PieceType type){
    
}
