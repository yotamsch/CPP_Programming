#ifndef __H_FILE_PLAYER_ALGORITHM
#define __H_FILE_PLAYER_ALGORITHM

#include "PlayerAlgorithm.h"
#include "GameManagerRPS.h"
#include "GameUtilitiesRPS.h"
#include <string>
#include <fstream>

using namespace std;


class FilePlayerAlgorithm : public PlayerAlgorithm {
private:
	unique_ptr<MoveRPS> _nextMoveP1;
	unique_ptr<MoveRPS> _nextMoveP2;
	vector<unique_ptr<PiecePosition>> _initialPositionsP1;
	vector<unique_ptr<PiecePosition>> _initialPositionsP2;
	const char* _file_path;
	ifstream _f;
	int _current_line;
public:
	// C'tor
	FilePlayerAlgorithm(const char* rPositionFileName, const char* rMoveFileName, int player){
		ParsePositionFile(player);
	}
    // D'tor
    ~FilePlayerAlgorithm();
    // Other
	void setInitialPosition(int player, vector<unique_ptr<PiecePosition>>& initPosVec){
		if(player==1){
			_initialPositionsP1 = initPosVec;
		}
		if(player==2){
			_initialPositionsP2 = initPosVec;
		}
	}

    void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill);
	void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights){/*remains empty*/}
	void notifyOnOpponentMove(const Move& move){/*remains empty*/}
	void notifyFightResult(const FightInfo& fightInfo){/*remains empty*/}
	unique_ptr<Move> getMove();
	unique_ptr<JokerChange> getJokerChange();

	Reason ParsePositionFile(int player);
	int GetCurrentLineNumber() { return _current_line; }
	bool IsEOF() { return _f.eof(); }
	Reason ReadLine(string& line);
	Reason ParseMoveFile(int player);
friend ostream& operator<<(ostream& output, const PlayerAlgorithm& p);
};

#endif // !__H_FILE_PLAYER_ALGORITHM