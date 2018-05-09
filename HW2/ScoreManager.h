#include "FightInfo.h"
#include "JokerChangeRPS.h"
#include "GameUtilitiesRPS.h"
class ScoreManager{
private:
    int _numOfMovingPiecesPlayer1, _numOfMovingPiecesPlayer2;
    int _numOfFlagsPlayer1, _numOfFlagsPlayer2;
    bool _isBadPositioningP1, _isBadPositioningP2;
    bool _isBadMoveP1, _isBadMoveP2;
    const char* _reasonOfFinalResult;

public:
    ScoreManager()
    :_numOfMovingPiecesPlayer1(0)
    ,_numOfMovingPiecesPlayer2(0)
    ,_numOfFlagsPlayer1(0)
    ,_numOfFlagsPlayer2(0)
    ,_isBadPositioningP1(false)
    ,_isBadPositioningP2(false)
    ,_isBadMoveP1(false)
    ,_isBadMoveP2(false)
    ,_reasonOfFinalResult("")
    {}

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
    void setBadPosition(int player);
    void setBadMove(int player);
};