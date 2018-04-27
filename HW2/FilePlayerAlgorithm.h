#ifndef __H_FILE_PLAYER_ALGORITHM
#define __H_FILE_PLAYER_ALGORITHM

#include "PlayerAlgorithm.h"

class FilePlayerAlgorithm : public PlayerAlgorithm {
private:
public:
    // D'tor
    ~FilePlayerAlgorithm();
    // Other
    void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill);
	void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights);
	void notifyOnOpponentMove(const Move& move);
	void notifyFightResult(const FightInfo& fightInfo);
	unique_ptr<Move> getMove();
	unique_ptr<JokerChange> getJokerChange();
};

#endif // !__H_FILE_PLAYER_ALGORITHM