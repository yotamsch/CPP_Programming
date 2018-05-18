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
    void getInitialPositions(int player, std::vector<std::unique_ptr<PiecePosition>>& vectorToFill);
    void notifyOnInitialBoard(const Board& b, const std::vector<std::unique_ptr<FightInfo>>& fights) {} // empty
    void notifyOnOpponentMove(const Move& move) {} // empty
    void notifyFightResult(const FightInfo& fightInfo) {} // empty
    std::unique_ptr<Move> getMove();
    std::unique_ptr<JokerChange> getJokerChange();

private:

/**
 * @brief 
 * Parses the positions' file of a specified player and fills a vector with the pieces found in this file
 * 
 * @param player - the player that the current file belongs to  
 * @param vectorToFill - a vector that is filled by this function with all the pieces that exist in the positons' file of this player
 * @return true - if parsing was done successfully
 * @return false - if: 1.There is a bad formatted line 2.There are not enough flags 3.There are extra pieces than should be 4.There was any other problem in reading a line
 */
    bool parsePositions(int player, std::vector<std::unique_ptr<PiecePosition>>& vectorToFill);

/**
 * @brief 
 * Parses the next move from the moves' file of current player and places it in the given reference rpMove
 * @param rpMove - a reference of a pointer to a Move object that is filled correctly inside the function with the parsed move 
 * @return false - if there was any problem with openning the moves' file or if the current line in the file is bad formatted
 * @return true - if there was no problem with the current line 
 */
    bool parseMove(std::unique_ptr<Move>& rpMove);

/**
 * @brief 
 * 
 * @param _f - referece of std::ifstream used to open the given file path below
 * @param filePath - file path given as a string 
 * @return true - if file was opened successfully
 * @return false - otherwise
 */
    // TODO choose static or non-static
    static bool initializeFile(std::ifstream& _f, const char* filePath);

/**
 * @brief 
 * Reads a single line from the file pointed at by _f and stores the read line in the parameter line
 * 
 * @param _f - ifstream reference to the current file
 * @param line - reference to a string, populated inside the function with the single read file
 * @return true - if a line was read successfully
 * @return false - otherwise
 */
    static bool readLine(std::ifstream& _f, std::string& line);
   


    static std::string& trimLine(std::string& s, const std::string& delmiters = " \f\n\r\t\v");

/**
 * @brief 
 * Given a string line the function returns a vector containing the different parts("words") of the string that are seperated by delimters  
 * @param s - string to be splitted
 * @param delimiter  - the string s will be splitted according to this parameter
 * @return std::vector<std::string> - a vector containing the parts of the string that were seperated by delimeter
 */
    static std::vector<std::string> splitLine(const std::string& s, const char delimiter);
};

#endif // !__H_FILE_PLAYER_ALGORITHM
