#include "ScoreManager.h"
#define player_1 1
#define player_2 2
#define no_winner 0
#define GAME_IS_STILL_ON -1
void ScoreManager::notifyFight(const FightInfo& rFightInfo){
    if(rFightInfo.getWinner() == player_1){
        if(rFightInfo.getPiece(player_2) == PieceTypeToChar(PieceType::FLAG)){
            decreaseNumOfFlags(player_2);
        }
        else{
            decreaseNumOfMovingPieces(player_2);
        }
    }else if(rFightInfo.getWinner() == player_2){
        if(rFightInfo.getPiece(player_1) == PieceTypeToChar(PieceType::FLAG)){
            decreaseNumOfFlags(player_1);
        }
        else{
            decreaseNumOfMovingPieces(player_1);
        }
    }else{ // both lost the fight
        if(rFightInfo.getPiece(player_1) == PieceTypeToChar(PieceType::FLAG)){
            decreaseNumOfFlags(player_1);
            decreaseNumOfFlags(player_2);
            //TODO handle case all flags are gone in positioning
            
        }
        else{
            decreaseNumOfMovingPieces(player_1);
            decreaseNumOfMovingPieces(player_2);
        }  
    } 
}

void ScoreManager::notifyJokerChange(const JokerChange& rJokerChange, char jokerPreviousRep, int player){
    if(rJokerChange.getJokerNewRep() == jokerPreviousRep)
        return;
    if(rJokerChange.getJokerNewRep() == PieceTypeToChar(PieceType::BOMB)){
        decreaseNumOfMovingPieces(player);
    }
    if(jokerPreviousRep == PieceTypeToChar(PieceType::BOMB)){
        increaseNumOfMovingPieces(player);
    }
}

void ScoreManager::DismissPlayer(int player, Reason reason){
    if(reason == Reason::POSITION_FILE_ERROR){
        if(player == player_1){
            _isBadPositioningP1 = true;
        }else{
            _isBadPositioningP2 = true;
        }
    }
    else if(reason == Reason::BAD_MOVE_ERROR){
        if(player == player_1){
            _isBadMoveP1 = true;
        }else{
            _isBadMoveP2 = true;
        }
    }
}

void ScoreManager::increaseNumOfMovingPieces(int player){
    if(player==1){ _numOfPiecesPlayer1++; }
    else{ _numOfPiecesPlayer2++; }
}
void ScoreManager::decreaseNumOfMovingPieces(int player){
    if(player==1){ _numOfPiecesPlayer1--; }
    else{ _numOfPiecesPlayer2--; }
}
void ScoreManager::decreaseNumOfFlags(int player){
    if(player==1){ _numOfFlagsPlayer1--; }
    else{ _numOfFlagsPlayer2--; }
}

void ScoreManager::increaseNumOfFlags(int player){
    
}
void ScoreManager::increaseNumOfPieces(int player, char pieceChar){
    if(player == player_1){
        if(CharToPieceType(pieceChar) == PieceType::FLAG){
            _numOfFlagsPlayer1++;
        }else{
            _numOfPiecesPlayer1++;
        }
    }
    else{
        if(CharToPieceType(pieceChar) == PieceType::FLAG){
            _numOfFlagsPlayer2++;
        }else{
            _numOfPiecesPlayer2++;
        }
    }
}
bool ScoreManager::isGameOver(){
    if(getWinner() == GAME_IS_STILL_ON){
        return false;
    }
    return true;
}

int ScoreManager::getWinner(){
    if(_isBadPositioningP1 && _isBadPositioningP2){
        _reasonOfFinalResult = RSN_BAD_POSITION_FILE_DOUBLE;
        return no_winner;
    }
    if(_isBadPositioningP1){
        _reasonOfFinalResult = RSN_BAD_POSISION_FILE_SINGLE;
        return player_2;
    }
    if(_isBadPositioningP2){
        _reasonOfFinalResult = RSN_BAD_POSISION_FILE_SINGLE;
        return player_1;
    }
    if(_numOfFlagsPlayer1 == 0 && _numOfFlagsPlayer2 == 0){
        _reasonOfFinalResult = RSN_POSITION_NO_FLAGS;
        return no_winner;
    }
    if(_numOfPiecesPlayer1 == 0 && _numOfPiecesPlayer2 == 0){
        _reasonOfFinalResult = RSN_POSITION_NO_PIECES;
        return no_winner;
    }
    if(_numOfFlagsPlayer1 == 0 || _numOfPiecesPlayer1 == 0){
        _reasonOfFinalResult = !_numOfFlagsPlayer1 ? RSN_ALL_FLAGS_CAPTURED : RSN_ALL_PIECES_EATEN; 
        return player_2;
    }
    if(_numOfFlagsPlayer2 == 0 || _numOfPiecesPlayer2 == 0){
        _reasonOfFinalResult = !_numOfFlagsPlayer2 ? RSN_ALL_FLAGS_CAPTURED : RSN_ALL_PIECES_EATEN;
        return player_1;
    }
    return GAME_IS_STILL_ON;
}

const char* ScoreManager::getReasonOfFinalResult(){ return _reasonOfFinalResult; }