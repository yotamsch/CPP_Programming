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

void BoardRPS::clearBoard()
{
    for (int i = 0; i < this->_board.size(); ++i) {
        this->_board[i] = nullptr;
    }
}

const std::unique_ptr<PieceRPS>& BoardRPS::getPieceAt(const Point& point)
{
    return this->_board[p(point.getX(), point.getY())];
}

BoardRPS& BoardRPS::operator=(BoardRPS&& rrOther)
{
    this->_n = rrOther._n;
    this->_m = rrOther._m;
    std::swap(this->_board, rrOther._board);
    return *this;
}

bool BoardRPS::placePiece(int player, std::unique_ptr<PiecePosition>& rpPiece, std::unique_ptr<FightInfo>& rpFightInfo)
{
    // get needed information
    const int x = rpPiece->getPosition().getX();
    const int y = rpPiece->getPosition().getY();
    bool is_joker = false;
    char type = rpPiece->getPiece();
    if (type == JOKER_CHR) {
        is_joker = true;
        type = rpPiece->getJokerRep();
    }

    // generate 'current piece'
    std::unique_ptr<PieceRPS> rpCurrPiece = std::make_unique<PieceRPS>(player, is_joker, type, PointRPS(x, y));

    // initialize just to be sure
    rpFightInfo = nullptr;
    if (!isPositionValid(x, y)) {
        return false;
    }
    if (is_joker && (type == FLAG_CHR || type == JOKER_CHR)) {
        // joker cannot act like flag or joker
        return false;
    }
    if (this->_board[p(x, y)] != nullptr) {
        if (this->_board[p(x, y)]->getPlayer() == player) {
            // can't position two pieces for same player on board
            return false;
        }
        // a fight exists
        rpFightInfo = std::make_unique<FightInfoRPS>(*this->_board[p(x, y)], *rpCurrPiece, PointRPS(x,y));
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
    this->_board[p(x, y)] = std::move(rpCurrPiece);
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
    if (this->_board[p(x, y)]->getPiece() == BOMB_CHR || this->_board[p(x, y)]->getPiece() == FLAG_CHR || this->_board[p(x, y)]->getJokerRep() == BOMB_CHR) {
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
bool BoardRPS::movePiece(int player, const std::unique_ptr<Move>& rpMove, std::unique_ptr<FightInfo>& rpFightInfo)
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
        rpFightInfo = std::make_unique<FightInfoRPS>(*(this->_board[p(new_x, new_y)]), *(this->_board[p(x, y)]), PointRPS(new_x, new_y));
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
    // place nullptr in origin (just in case)
    this->_board[p(x, y)] = nullptr;
    return true;
}

bool BoardRPS::changeJoker(int player, const std::unique_ptr<JokerChange>& rpJokerChange)
{
    const int x = rpJokerChange->getJokerChangePosition().getX();
    const int y = rpJokerChange->getJokerChangePosition().getY();
    const char new_type = rpJokerChange->getJokerNewRep();

    if (!isPositionValid(x, y) || this->_board[p(x, y)] == nullptr) {
        // position is not valid or piece does not exist
        return false;
    }
    if (this->_board[p(x, y)]->getPlayer() != player || !this->_board[p(x, y)]->isJoker() || new_type == FLAG_CHR || new_type == JOKER_CHR) {
        // the attempted joker change is not accepted
        return false;
    }
    // can change the piece type of the joker
    this->_board[p(x, y)]->setType(new_type);
    return true;
}

int BoardRPS::getPlayer(const Point& pos) const
{
    if (_board[p(pos.getX(), pos.getY())] != nullptr)
        return _board[p(pos.getX(), pos.getY())]->getPlayer();
    // return 0 if empty
    return 0;
}

std::ostream& operator<<(std::ostream& output, const BoardRPS& rBoard)
{
    for (int y = 0; y < rBoard._n; ++y) {
        for (int x = 0; x < rBoard._m; ++x) {
            if (rBoard._board[rBoard.p(x, y)] == nullptr) {
                output << ' ';
            } else {
                output << *(rBoard._board[rBoard.p(x, y)]);
            }
        }
        output << std::endl;
    }
    return output;
}

/**
 * @brief Prints the board.
 * 
 */
void BoardRPS::prettyPrint()
{
    std::cout << std::endl
              << "main board:" << std::endl;
    int idx = 0, i = 0;
    std::cout << "  ";
    for (i = 0; i < DIM_X; ++i)
        std::cout << " " << i << " ";
    i = 0;
    for (int j = 0; j < DIM_X * DIM_Y; ++j) {
        if (j % DIM_X == 0)
            std::cout << std::endl
                      << i++ << " ";
        if (this->_board[j] == nullptr)
            std::cout << "[ ]";
        else if (this->_board[j]->getPlayer() == PLAYER_1)
            std::cout << "["
                      << "\033[0;32m" << this->_board[j]->getPiece() << "\033[0m"
                      << "]";
        else
            std::cout << "["
                      << "\033[1;34m" << (char)std::tolower(this->_board[j]->getPiece()) << "\033[0m"
                      << "]";
    }
    std::cout << std::endl << std::endl;
}
