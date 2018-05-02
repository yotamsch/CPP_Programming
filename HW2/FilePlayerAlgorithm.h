#ifndef __H_FILE_PLAYER_ALGORITHM
#define __H_FILE_PLAYER_ALGORITHM

#include "PlayerAlgorithm.h"
#include "GameManagerRPS.h"
#include <string>
using namespace std;


class FilePlayerAlgorithm : public PlayerAlgorithm {
private:
	/*COPY OF HW1- player.h*/
	PlayerType _type;
	int _number_of_flags;
	int _number_of_pieces;
	/* END OF COPY */
public:
	// C'tor
	FilePlayerAlgorithm(const char* rPositionFileName, const char* rMoveFileName){

	}
	/*COPY OF HW1- player.h*/
    FilePlayerAlgorithm(PlayerType type) : _type(type), _number_of_flags(0), _number_of_pieces(0) {

	}
	/* END OF COPY */
    // D'tor
    ~FilePlayerAlgorithm();
    // Other
    void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill);
	void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights);
	void notifyOnOpponentMove(const Move& move);
	void notifyFightResult(const FightInfo& fightInfo);
	unique_ptr<Move> getMove();
	unique_ptr<JokerChange> getJokerChange();
	/*COPY OF HW1- player.h*/
	// Get
	PlayerType GetType();
	// Utilities
	void IncrementPieceCount(PieceType type);
	void DecrementPieceCount(PieceType type);
//	Reason IsLosing();

friend ostream& operator<<(ostream& output, const PlayerAlgorithm& p);
	/* END OF COPY */
};

#endif // !__H_FILE_PLAYER_ALGORITHM