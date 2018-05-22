/**
 * @brief The implementation file for the PieceRPS class.
 * 
 * @file PieceRPS.cpp
 * @author Yotam Sechayk
 * @date 2018-05-12
 */
#include "PieceRPS.h"

/**
 * @brief Overloading on the lower than (<) operator. According to the rules of the game. Returns true only if the left side is lower "in strength" than the right side.
 * 
 * @param p - the right hand side to compare to.
 * @return true - if the left side is lower "in strength" than the right side
 * @return false - otherwise
 */
bool PieceRPS::operator<(const PieceRPS& p) const
{
    if ((p._piece_type == ROCK_CHR && this->_piece_type == SCISSORS_CHR) || (p._piece_type == SCISSORS_CHR && this->_piece_type == PAPER_CHR) || (p._piece_type == PAPER_CHR && this->_piece_type == ROCK_CHR) || 
        (p._piece_type == BOMB_CHR && this->_piece_type != BOMB_CHR) ||
        (p._piece_type != FLAG_CHR && this->_piece_type == FLAG_CHR)) {
        return true;
    }
    return false;
}

/**
 * @brief Overloading on the copy assignmnet operator
 * 
 * @param p - the piece to copy from
 * @return PieceRPS& - a reference to the current piece
 */
PieceRPS& PieceRPS::operator=(const PieceRPS& p)
{
    if (this != &p) {
        this->_is_joker = p._is_joker;
        this->_piece_type = p._piece_type;
        this->_player = p._player;
    }
    return *this;
}

/**
 * @brief called ONLY when setting a joker's representation. Changes/Sets the calling joker's type(char representation)
 * 
 * @param type - the desired representation of a joker
 */
void PieceRPS::setType(char type)
{
    if (_is_joker) {
        _piece_type = type;
    }
}

/**
 * @brief Gets a reference to the point position of the current piece
 * 
 * @return const Point& - the position of the piece
 */
const Point& PieceRPS::getPosition() const
{
    return _position;
}

/**
 * @brief Gets the char representation (type) of the current piece (R,P,S,F,B,J)
 * 
 * @return char - the representation (type) of the current piece
 */
char PieceRPS::getPiece() const
{
    return this->_is_joker ? JOKER_CHR : _piece_type;
}

/**
 * @brief Gets the joker representation of the current piece, if it is a Joker piece. Otherwise returns '#'
 * 
 * @return char - the representation of the joker piece, or '#'
 */
char PieceRPS::getJokerRep() const
{
    if (!_is_joker)
        return NON_JOKER_CHR;
    return _piece_type;
}

/**
 * @brief Overloading on the print to ostream (<<) operator.
 * 
 * @param output - the ostream to output into
 * @param piece - the play piece to print
 * @return ostream& - the modified ostream
 */
std::ostream& operator<<(std::ostream& output, const PieceRPS& piece)
{
    char type = piece.getPiece();
    if (piece.getPlayer() == PLAYER_1) {
        output << (char)toupper(type);
    } else {
        output << (char)tolower(type);
    }
    return output;
}