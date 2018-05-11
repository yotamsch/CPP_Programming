#ifndef __H_FILE_PLAYER_ALGORITHM
#define __H_FILE_PLAYER_ALGORITHM

#include "GameManagerRPS.h"
#include "GameUtilitiesRPS.h"
#include "JokerChangeRPS.h"
#include "MoveRPS.h"
#include "PlayerAlgorithm.h"
#include <fstream>

#include <string>

class FilePlayerAlgorithm : public PlayerAlgorithm {
private:
    const char* _posFilePath;
    const char* _moveFilePath;
    std::ifstream _f_pos;
    std::ifstream _f_move;
    std::unique_ptr<JokerChange> _jokerChange; // will hold the "current" joker move

public:
    // basic c'tor
    FilePlayerAlgorithm(const char* positionFilePath, const char* moveFilePath);

    // d'tor
    ~FilePlayerAlgorithm();

    // interface defined functions
    void getInitialPositions(int player, std::vector<std::unique_ptr<PiecePosition>>& vectorToFill);
    void notifyOnInitialBoard(const Board& b, const std::vector<std::unique_ptr<FightInfo>>& fights) {} // empty
    void notifyOnOpponentMove(const Move& move) {} // empty
    void notifyFightResult(const FightInfo& fightInfo) {} // empty
    std::unique_ptr<Move> getMove();
    std::unique_ptr<JokerChange> getJokerChange();

private:
    bool parsePositions(int player, std::vector<std::unique_ptr<PiecePosition>>& vectorToFill);
    bool parseMove(std::unique_ptr<Move>& rpMove);
    // TODO choose static or non-static
    static bool initializeFile(std::ifstream& _f, const char* filePath);
    static bool readLine(std::ifstream& _f, std::string& line);
    static std::string& trimLine(std::string& s, const std::string& delmiters = " \f\n\r\t\v");
    static std::vector<std::string> splitLine(const std::string& s, const char delimiter);
};

#endif // !__H_FILE_PLAYER_ALGORITHM
