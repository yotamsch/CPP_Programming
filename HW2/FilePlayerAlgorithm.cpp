/**
 * @brief The implementation file of the FilePlayerAlgorithm class.
 * 
 * @file FilePlayerAlgorithm.cpp
 * @author Yotam Sechayk, Tala Amouri
 * @date 2018-05-15
 */
#include "FilePlayerAlgorithm.h"
#include "PieceRPS.h"

#include <map>
#include <sstream>
#include <vector>

FilePlayerAlgorithm::FilePlayerAlgorithm(const char* positionFilePath, const char* moveFilePath)
    : _posFilePath(positionFilePath) // path to positions file
    , _moveFilePath(moveFilePath) // path to moves file
{
    // initialize positions file stream
    initializeFile(this->_f_pos, this->_posFilePath);
    // initialize move file stream
    initializeFile(this->_f_move, this->_moveFilePath);
}

FilePlayerAlgorithm::~FilePlayerAlgorithm()
{
    if (_f_pos.is_open()) {
        _f_pos.close();
    }
    if (_f_move.is_open()) {
        _f_move.close();
    }
}

/**
 * @brief Trims a line by the set of given delimiters
 * 
 * @param s - the string line to be trimmed
 * @param delmiters - the collection of delimiters (also a string)
 * @return std::string& - the string reference for continued work
 */
std::string& FilePlayerAlgorithm::trimLine(std::string& s, const std::string& delmiters /*= " \f\n\r\t\v"*/)
{
    return s.erase(s.find_last_not_of(delmiters) + 1).erase(0, s.find_first_not_of(delmiters));
}

/**
 * @brief 
 * Given a string line the function returns a vector containing the different parts("words") of the string that are seperated by delimters  
 * @param s - string to be splitted
 * @param delimiter  - the string s will be splitted according to this parameter
 * @return std::vector<std::string> - a vector containing the parts of the string that were seperated by delimeter
 */
std::vector<std::string> FilePlayerAlgorithm::splitLine(const std::string& s, const char delimiter)
{
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string word;
    while (std::getline(ss, word, delimiter)) {
        if (word.size() > 0)
            result.push_back(trimLine(word));
    }
    return result;
}

/**
 * @brief 
 * 
 * @param _f - referece of std::ifstream used to open the given file path below
 * @param filePath - file path given as a string 
 * @return true - if file was opened successfully
 * @return false - otherwise
 */
bool FilePlayerAlgorithm::initializeFile(std::ifstream& _f, const char* filePath)
{
    // attempts to open file
    try {
        _f.open(filePath);
    } catch (...) {
        return false;
    }
    return true;
}

/**
 * @brief 
 * Reads a single line from the file pointed at by _f and stores the read line in the parameter line
 * 
 * @param _f - ifstream reference to the current file
 * @param line - reference to a string, populated inside the function with the single read file
 * @return true - if a line was read successfully
 * @return false - otherwise
 */
bool FilePlayerAlgorithm::readLine(std::ifstream& _f, std::string& line)
{
    try {
        if (!_f.eof()) {
            do {
                std::getline(_f, line);
                line = trimLine(line);
            } while (line.size() == 0 && !_f.eof());
        }
    } catch (...) {
        return false;
    }
    return true;
}

/**
 * @brief 
 * Parses the positions' file of a specified player and fills a vector with the pieces found in this file
 * 
 * @param player - the player that the current file belongs to  
 * @param vectorToFill - a vector that is filled by this function with all the pieces that exist in the positons' file of this player
 * @return true - if parsing was done successfully
 * @return false - if: 1.There is a bad formatted line 2.There are not enough flags 3.There are extra pieces than should be 4.There was any other problem in reading a line
 */
bool FilePlayerAlgorithm::parsePositions(int player, std::vector<std::unique_ptr<PiecePosition>>& vectorToFill)
{
    const char delim = ' ';
    char piece_type;
    bool is_joker;
    int x, y;
    std::unique_ptr<PiecePosition> pCurrPiece;
    std::string line;
    std::vector<std::string> s_line;

    // map which holds { key : piece-char, value = amount }
    // where amount is a reverse counter (limit -> 0)
    std::map<char, int> piece_count = { { ROCK_CHR, ROCK_LIMIT }, { PAPER_CHR, PAPER_LIMIT }, { SCISSORS_CHR, SCISSORS_LIMIT }, { FLAG_CHR, FLAG_LIMIT }, { BOMB_CHR, BOMB_LIMIT }, { JOKER_CHR, JOKER_LIMIT } };

    // while file is open and not in the end of the file
    while (_f_pos.is_open() && !_f_pos.eof()) {
        is_joker = false;
        if (!readLine(this->_f_pos, line)) {
            return false;
        }
        s_line = splitLine(line, delim);
        if (s_line.size() == 0) {
            // no more positions to fetch, empty line
            continue;
        }
        if (s_line.size() < 3 || s_line[0].size() != 1 || piece_count.find(s_line[0][0]) == piece_count.end()) {
            return false;
        }
        piece_type = s_line[0][0];
        try {
            x = stoi(s_line[1]) - 1;
            y = stoi(s_line[2]) - 1;
        } catch (...) {
            // number conversion error
            return false;
        }
        --piece_count[piece_type];
        // make sure the user doesn't add too many pieces
        if (piece_count[piece_type] < 0) {
            return false;
        }
        if (piece_type == JOKER_CHR) {
            // joker piece
            is_joker = true;
            if (s_line.size() != 4 || s_line[3].size() != 1) {
                return false;
            }
            // since we don't need to mess with the piece_counter for joker-rep
            // no need to check if it's a valid rep
            // (will be checked in the piece placement)
            piece_type = s_line[3][0];
        }
        s_line.clear();
        // add the piece to the correct vector
        pCurrPiece = std::make_unique<PieceRPS>(player, is_joker, piece_type, PointRPS(x, y));
        vectorToFill.push_back(std::move(pCurrPiece));
    }
    // check if not enough flags entered
    if (piece_count[FLAG_CHR] > 0) {
        return false;
    }
    return true;
}

/**
 * @brief 
 * Parses the next move from the moves' file of current player and places it in the given reference rpMove
 * @param rpMove - a reference of a pointer to a Move object that is filled correctly inside the function with the parsed move 
 * @return false - if there was any problem with openning the moves' file or if the current line in the file is bad formatted
 * @return true - if there was no problem with the current line 
 */
bool FilePlayerAlgorithm::parseMove(std::unique_ptr<Move>& rpMove)
{
    // get a move from the file and parse it
    const char delim = ' ';
    const char* joker_str = "J:";
    std::string line;
    int from_x, from_y, to_x, to_y;
    bool is_j_change = false;
    int joker_x, joker_y;
    char new_j_type;
    std::vector<std::string> s_line;

    // initialization
    rpMove = nullptr;
    this->_jokerChange = nullptr;

    if (!_f_move.is_open() || !readLine(this->_f_move, line)) {
        return false;
    }
    s_line = splitLine(line, delim);
    if (s_line.size() == 0) {
        // reached end of move file (or file is empty)
        // return nullptr(s) to continue with the other player
        // see: http://moodle.tau.ac.il/mod/forum/discuss.php?d=60137
        return true;
    }
    if (s_line.size() < 4) {
        return false;
    }
    if (s_line.size() >= 8) {
        if (s_line[4].compare(joker_str) != 0) {
            return false;
        }
        is_j_change = true;
    }
    try {
        from_x = stoi(s_line[0]) - 1;
        from_y = stoi(s_line[1]) - 1;
        to_x = stoi(s_line[2]) - 1;
        to_y = stoi(s_line[3]) - 1;
    } catch (...) {
        // number conversion error
        return false;
    }
    if (is_j_change) {
        if (s_line.size() != 8 || s_line[7].size() != 1) {
            return false;
        }
        try {
            joker_x = stoi(s_line[5]) - 1;
            joker_y = stoi(s_line[6]) - 1;
        } catch (...) {
            // number conversion error
            return false;
        }
        new_j_type = s_line[7][0];
        if (new_j_type != ROCK_CHR && new_j_type != PAPER_CHR && new_j_type != SCISSORS_CHR && new_j_type != BOMB_CHR) {
            return false;
        }
        // create and place the joker change move
        this->_jokerChange = std::make_unique<JokerChangeRPS>(PointRPS(joker_x, joker_y), new_j_type);
    }
    // all went well, creating the entered move
    rpMove = std::make_unique<MoveRPS>(PointRPS(from_x, from_y), PointRPS(to_x, to_y));
    return true;
}

/**
 * @brief Gets the initial positioning from the positions file. If a bad positioning (line error) was attempted, interts a bad position into the vector.
 * 
 * @param player - the current player id
 * @param vectorToFill - the vector to fill with positions
 */
void FilePlayerAlgorithm::getInitialPositions(int player, std::vector<std::unique_ptr<PiecePosition>>& vectorToFill)
{
    // initialize a "bad" piece [player=0, not-joker, '?', (-1,-1)]
    std::unique_ptr<PiecePosition> badPiece = std::make_unique<PieceRPS>(NO_PLAYER, false, UNKNOWN_CHR, PointRPS());

    if (!this->parsePositions(player, vectorToFill)) {
        // there was an error in one of the lines in the file
        vectorToFill.push_back(std::move(badPiece));
    }
}

/**
 * @brief Gets the next move from the moves file. If a bad move (line error) was found, returns a bad move. If no move was found returns nullptr.
 * 
 * @return std::unique_ptr<Move> - the move to be made by the player
 */
std::unique_ptr<Move> FilePlayerAlgorithm::getMove()
{
    std::unique_ptr<Move> nextMove;

    if (!parseMove(nextMove)) {
        // returns a "bad" move [(-1,-1)->(-1,-1)]
        return std::move(std::make_unique<MoveRPS>(PointRPS(), PointRPS()));
    }
    return std::move(nextMove);
}

/**
 * @brief Gets the joker change that was (if was) attached to the last revrieved move.
 * 
 * @return std::unique_ptr<JokerChange> - the joker change to be made
 */
std::unique_ptr<JokerChange> FilePlayerAlgorithm::getJokerChange()
{
    return std::move(this->_jokerChange);
}
