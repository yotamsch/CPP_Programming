/**
 * @brief The header file of the FilePlayerAlgorithm class.
 * 
 * @file FilePlayerAlgorithm.h
 * @author Yotam Sechayk, Tala Amouri
 * @date 2018-05-15
 */
#ifndef __H_FILE_PLAYER_ALGORITHM
#define __H_FILE_PLAYER_ALGORITHM

#include "GameManagerRPS.h"
#include "GameUtilitiesRPS.h"
#include "JokerChangeRPS.h"
#include "MoveRPS.h"
#include "PlayerAlgorithm.h"
#include <fstream>

#include <string>

/**
 * @brief a class implementing the PlayerAlgorithm abstract class, handles the file player of the game RPS 
 * 
 */
class FilePlayerAlgorithm : public PlayerAlgorithm {
private:
    const char* _posFilePath; //positins' file path
    const char* _moveFilePath; // moves' file path
    std::ifstream _f_pos; //ifstream to open and handle positions' file
    std::ifstream _f_move; //ifstream to open and handle moves' file
    std::unique_ptr<JokerChange> _jokerChange; // will hold the "current" joker move

public:
    // basic c'tor
    FilePlayerAlgorithm(const char* positionFilePath, const char* moveFilePath);

    // d'tor
    ~FilePlayerAlgorithm();

    // interface defined functions
    // gets the positions from position file and populates the vector
    void getInitialPositions(int player, std::vector<std::unique_ptr<PiecePosition>>& vectorToFill);
    // not used - empty implementation
    void notifyOnInitialBoard(const Board& b, const std::vector<std::unique_ptr<FightInfo>>& fights) {}
    // not used - empty implementation
    void notifyOnOpponentMove(const Move& move) {}
    // not used - empty implementation
    void notifyFightResult(const FightInfo& fightInfo) {}
    // gets the next move of the player
    std::unique_ptr<Move> getMove();
    // gets the current joker change if one was accompaneeing the last retrieved move
    std::unique_ptr<JokerChange> getJokerChange();

private:
    // parse the positions file and updates the positions vector
    bool parsePositions(int player, std::vector<std::unique_ptr<PiecePosition>>& vectorToFill);
    // parse the next move from the moves files
    bool parseMove(std::unique_ptr<Move>& rpMove);
    // initializes a file stream from file path
    static bool initializeFile(std::ifstream& _f, const char* filePath);
    // reads the next line in a given file stream
    static bool readLine(std::ifstream& _f, std::string& line);
    // trims a given string line
    static std::string& trimLine(std::string& s, const std::string& delmiters = " \f\n\r\t\v");
    // splits the line into a vector of string by the delimiter
    static std::vector<std::string> splitLine(const std::string& s, const char delimiter);
};

#endif // !__H_FILE_PLAYER_ALGORITHM
