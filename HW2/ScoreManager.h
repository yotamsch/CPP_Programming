#include "FightInfo.h"
#include "JokerChangeRPS.h"
#include "GameUtilitiesRPS.h"
class ScoreManager{
private:
    int _numOfPiecesPlayer1, _numOfPiecesPlayer2;
    int _numOfFlagsPlayer1, _numOfFlagsPlayer2;
    bool _isBadPositioningP1, _isBadPositioningP2;
    bool _isBadMoveP1, _isBadMoveP2;
    const char* _reasonOfFinalResult;

public:
    ScoreManager()
    :_numOfPiecesPlayer1(0)
    ,_numOfPiecesPlayer2(0)
    ,_numOfFlagsPlayer1(0)
    ,_numOfFlagsPlayer2(0){
    }
    void notifyFight(const FightInfo& rFightInfo);
    void notifyJokerChange(const JokerChange& rJokerChange, char jokerPreviousRep, int player);
    void DismissPlayer(int player, Reason reason);
    void increaseNumOfMovingPieces(int player);
    void decreaseNumOfMovingPieces(int player);
    void increaseNumOfFlags(int player);
    void decreaseNumOfFlags(int player);
    void increaseNumOfPieces(int player, char pieceChar);
    bool isGameOver();
    int getWinner();
    const char* getReasonOfFinalResult();
};