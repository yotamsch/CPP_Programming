#include "FilePlayerAlgorithm.h"

FilePlayerAlgorithm::~FilePlayerAlgorithm(){}
void FilePlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill){

}
void FilePlayerAlgorithm::notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights){

}
void FilePlayerAlgorithm::notifyOnOpponentMove(const Move& move){}
void FilePlayerAlgorithm::notifyFightResult(const FightInfo& fightInfo){}
unique_ptr<Move> FilePlayerAlgorithm::getMove(){}
unique_ptr<JokerChange> FilePlayerAlgorithm::getJokerChange(){}
PlayerType FilePlayerAlgorithm::GetType() { return _type; }
void FilePlayerAlgorithm::IncrementPieceCount(PieceType type){}
void FilePlayerAlgorithm::DecrementPieceCount(PieceType type){}
