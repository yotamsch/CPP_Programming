#ifndef __H_FILE_PLAYER_ALGORITHM
#define __H_FILE_PLAYER_ALGORITHM

#include "PlayerAlgorithm.h"
#include "GameManagerRPS.h"
#include "GameUtilitiesRPS.h"
#include "MoveRPS.h"
#include "JokerChangeRPS.h"
#include <string>
#include <fstream>

using namespace std;


class FilePlayerAlgorithm : public PlayerAlgorithm {
private:
	unique_ptr<MoveRPS> _nextMove;
	unique_ptr<JokerChange> _jokerChange;
	vector<unique_ptr<PiecePosition>> _initialPositions;
	const char* _positionFilePath;
	const char* _movesFilePath;
	ifstream _f;
	int _current_line;
	int _current_player;
public:
	// C'tor
	FilePlayerAlgorithm(const char* positionFileName, const char* moveFileName, int player)
	: _positionFilePath(positionFileName)
	, _movesFilePath(moveFileName) 
	, _current_line(0)
	, _current_player(player)
	{
		ManageParsePositionFile();
	}
    // D'tor
    ~FilePlayerAlgorithm();
    // Other
	void setInitialPosition(int player, vector<unique_ptr<PiecePosition>>& initPosVec){
		_initialPositions = initPosVec;
	}

    void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill);
	void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights){/*remains empty*/}
	void notifyOnOpponentMove(const Move& move){/*remains empty*/}
	void notifyFightResult(const FightInfo& fightInfo){/*remains empty*/}
	unique_ptr<Move> getMove();
	unique_ptr<JokerChange> getJokerChange();
	void ManageParsePositionFile();
	Reason ParsePositionFile(int player);
	Reason ParseMove(int player);
	int GetCurrentLineNumber() { return _current_line; }
	bool IsEOF() { return _f.eof(); }
	Reason ReadLine(string& line);
	Reason InitializeFile(const char* filePath);
friend ostream& operator<<(ostream& output, const PlayerAlgorithm& p);
};

#endif // !__H_FILE_PLAYER_ALGORITHM