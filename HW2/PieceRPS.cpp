
#include "PieceRPS.h"

/**
 * @brief Overloading on the lower than (<) operator. According to the rules of the game. Returns true only if the left side is lower "in strength" than the right side.
 * 
 * @param p The right hand side to compare to.
 * @return true If the left side is lower "in strength" than the right side
 * @return false Otherwise
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

PieceRPS& PieceRPS::operator=(const PieceRPS& p)
{
    if (this != &p) {
        this->_is_joker = p._is_joker;
        this->_piece_type = p._piece_type;
        this->_player = p._player;
    }
    return *this;
}

void PieceRPS::setType(char type)
{
    if (_is_joker) {
        _piece_type = type;
    }
}

const Point& PieceRPS::getPosition() const
{
    return _position;
}

char PieceRPS::getPiece() const
{
    return this->_is_joker ? JOKER_CHR : _piece_type;
}

char PieceRPS::getJokerRep() const
{
    if (!_is_joker)
        return NON_JOKER_CHR;
    return _piece_type;
}

/**
 * @brief Overloading on the print to ostream (<<) operator.
 * 
 * @param output The ostream to output into
 * @param piece The play piece to print
 * @return ostream& The modified ostream
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