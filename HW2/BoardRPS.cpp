#include "BoardRPS.h"
#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>

bool BoardRPS::isPositionValid(int x, int y)
{
    return (x >= 0 && x < this->_m) && (y >= 0 && y < this->_n);
}

bool BoardRPS::isPositionValid(int x, int y, int new_x, int new_y)
{
    if (!isPositionValid(x, y) || !isPositionValid(new_x, new_y)) {
        return false;
    }
    if ((abs(x - new_x) == 1 && abs(y - new_y) == 1) || (abs(x - new_x) > 1 || abs(y - new_y) > 1)) {
        return false;
    }
    return true;
}

int BoardRPS::getPlayer(const Point& pos) const
{
    if (_board[p(pos.getX(), pos.getY())] != nullptr)
        return _board[p(pos.getX(), pos.getY())]->getPlayer();
    // return 0 if empty
    return 0;
}

BoardRPS& BoardRPS::operator=(BoardRPS&& rrOther)
{
    this->_n = rrOther._n;
    this->_m = rrOther._m;
    std::swap(this->_board, rrOther._board);
    return *this;
}

/**
 * @brief The function creates and places a new piece on the board. 
 * Based on the rules of each piece (found by its type).
 * 
 * @param player The player type (PLAYER_1 or PLAYER_2)
 * @param type The piece type
 * @param x The x position on the board
 * @param y The y position on the board
 * @param is_joker Is the piece a joker piece
 * @return true If everything went fine and the piece has been inserted into the board.
 * @return false If an error occured
 */
bool BoardRPS::placePiece(int player, std::unique_ptr<PiecePosition>& rpPiece, std::unique_ptr<FightInfoRPS>& rpFightInfo)
{
    // get needed information
    char typeInChar = rpPiece->getPiece();
    PieceType type = CharToPieceType(typeInChar);
    const int x = rpPiece->getPosition().getX();
    const int y = rpPiece->getPosition().getY();
    bool is_joker = rpPiece->getJokerRep() == NON_JOKER_FLAG ? false : true;

    // initialize just to be sure
    rpFightInfo = nullptr;
    if (!isPositionValid(x, y)) {
        return false;
    }
    if (is_joker && (type == PieceType::FLAG || type == PieceType::JOKER)) {
        // joker cannot act like flag or joker
        return false;
    }
    if (this->_board[p(x, y)] != nullptr) {
        if (this->_board[p(x, y)]->getPlayer() == player) {
            // can't position two pieces for same player on board
            return false;
        }
        // a fight exists
        rpFightInfo = std::make_unique<FightInfoRPS>(*this->_board[p(x, y)], *rpPiece);
        if (rpFightInfo->getWinner() == this->_board[p(x, y)]->getPlayer()) {
            // existing player won
            rpPiece = nullptr;
            return true;
        }
        if (rpFightInfo->getWinner() == 0) {
            // both lose : remove existing piece
            this->_board[p(x, y)] = nullptr;
            rpPiece = nullptr;
            return true;
        }
    }
    // no fight or 'this' player won
    this->_board[p(x, y)] = std::move(rpPiece);
    return true;
}



/**
 * @brief Checks if a certain move is legal. If not updates a message correctly.
 * 
 * @param x The origin X.
 * @param y The origin Y.
 * @param new_x The destination X.
 * @param new_y The destination Y.
 * @return true The move is legal.
 * @return false The move is illegal.
 */
bool BoardRPS::isMoveLegal(int player, int x, int y, int new_x, int new_y)
{
    // TODO: verify all conditions are met
    if (!isPositionValid(x, y, new_x, new_y) || this->_board[p(x, y)] == nullptr || this->_board[p(x, y)]->getPlayer() != player) {
        return false;
    }
    if (this->_board[p(x, y)]->getPieceType() == PieceType::BOMB || this->_board[p(x, y)]->getPieceType() == PieceType::FLAG) {
        return false;
    }
    if (this->_board[p(new_x, new_y)] != nullptr && this->_board[p(x, y)]->getPlayer() == this->_board[p(new_x, new_y)]->getPlayer()) {
        return false;
    }
    return true;
}

/**
 * @brief Moves a piece from (x,y) to (new_x,new_y). Based on the rules of the game. Message is updated correctly.
 * 
 * @param x The origin X
 * @param y The origin Y
 * @param new_x The destination X
 * @param new_y The destination Y
 */
bool BoardRPS::movePiece(int player, const std::unique_ptr<Move>& rpMove, std::unique_ptr<FightInfoRPS>& rpFightInfo)
{
    // initialize parameters
    const int x = rpMove->getFrom().getX();
    const int y = rpMove->getFrom().getY();
    const int new_x = rpMove->getTo().getX();
    const int new_y = rpMove->getTo().getY();

    int winner = 0;
    if (!isMoveLegal(player, x, y, new_x, new_y)) {
        return false;
    }
    if (this->_board[p(new_x, new_y)] == nullptr) {
        // no fight can move freely
        rpFightInfo = nullptr;
    } else {
        // there is a fight
        rpFightInfo = std::make_unique<FightInfoRPS>(*(this->_board[p(new_x, new_y)]), *(this->_board[p(x, y)]));
        if (rpFightInfo->getWinner() == this->_board[p(new_x, new_y)]->getPlayer()) {
            // destination piece won : empty 'origin' piece
            this->_board[p(x, y)] = nullptr;
            return true;
        }
        if (rpFightInfo->getWinner() == 0) {
            // both lose : empty existing pieces
            this->_board[p(x, y)] = nullptr;
            this->_board[p(new_x, new_y)] = nullptr;
            return true;
        }
    }
    // 'origin' piece won
    this->_board[p(new_x, new_y)] = std::move(this->_board[p(x, y)]);
    // TODO: check if following line is needed
    this->_board[p(x, y)] = nullptr;
    return true;
}


bool BoardRPS::changeJoker(int player, const std::unique_ptr<JokerChange>& rpJokerChange)
{
    const int x = rpJokerChange->getJokerChangePosition().getX();
    const int y = rpJokerChange->getJokerChangePosition().getY();
    const PieceType new_type = CharToPieceType(rpJokerChange->getJokerNewRep());

    if (!isPositionValid(x, y) || this->_board[p(x, y)] == nullptr) {
        // position is not valid or piece does not exist
        return false;
    }
    if (this->_board[p(x, y)]->getPlayer() != player || !this->_board[p(x, y)]->isJoker() || new_type == PieceType::FLAG || new_type == PieceType::JOKER) {
        // the attempted joker change is not accepted
        return false;
    }
    // can change the piece type of the joker
    this->_board[p(x, y)]->setType(new_type);
    return true;
}

std::ostream& operator<<(std::ostream& output, const BoardRPS& rBoard)
{
    for (int y = 0; y < rBoard._n; ++y) {
        for (int x = 0; x < rBoard._m; ++x) {
            output << *(rBoard._board[rBoard.p(x,y)]);
        }
        output << std::endl;
    }
    return output;
}

/**
 * @brief Helper function for BoardRPS::PrettyPrint(). prints a line of dashes based on the number of columns
 * 
 * @param columns An integer
 */
void printLineOfDashes(int columns)
{
    std::cout << "\t";
    for (int i = 0; i < (columns * 4 - 1); ++i) {
        std::cout << "-";
    }
    std::cout << std::endl;
}

/**
 * @brief Prints the board.
 * 
 */
void BoardRPS::prettyPrint()
{
    if (this->_n == 0 && this->_m == 0) {
        std::cout << "[...]" << std::endl;
        return;
    }
    printLineOfDashes(_m);
    for (int y = 0; y < _n; ++y) {
        std::cout << y + 1 << "\t";
        for (int x = 0; x < _m; ++x) {
            if (x % 2 == 1) std::cout << " ";
            std::cout << "[" << *(this->_board[p(x,y)]) << "]";
            if (x % 2 == 1) std::cout << " ";
        }
        std::cout << std::endl;
        printLineOfDashes(_m);
    }
}
