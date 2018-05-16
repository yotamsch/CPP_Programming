#include "FilePlayerAlgorithm.h"
#include "PieceRPS.h"

#include <map>
#include <sstream>
#include <vector>

FilePlayerAlgorithm::FilePlayerAlgorithm(const char* positionFilePath, const char* moveFilePath)
    : _posFilePath(positionFilePath) // path to positions file
    , _moveFilePath(moveFilePath) // path to moves file
{
    // TODO maybe move to another function so can check if there was an error opening files
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

std::string& FilePlayerAlgorithm::trimLine(std::string& s, const std::string& delmiters /*= " \f\n\r\t\v"*/)
{
    return s.erase(s.find_last_not_of(delmiters) + 1).erase(0, s.find_first_not_of(delmiters));
}

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

bool FilePlayerAlgorithm::parseMove(std::unique_ptr<Move>& rpMove)
{
    // get a move from the file and parse it
    // TODO maybe convert to MACRO
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
 * returns null if moves file of this player ended while the other player still has some moves(if he's a file), or is a auto-player.
 * returns a bad move if there was a bad line in moves file
 * returns a Move otherwise
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

std::unique_ptr<JokerChange> FilePlayerAlgorithm::getJokerChange()
{
    return std::move(this->_jokerChange);
}
