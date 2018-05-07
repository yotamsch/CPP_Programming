
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
    if (p._piece_type != PieceType::NONE && this->_piece_type == PieceType::NONE || (p._piece_type == PieceType::ROCK && this->_piece_type == PieceType::SCISSORS) || (p._piece_type == PieceType::SCISSORS && this->_piece_type == PieceType::PAPER) || (p._piece_type == PieceType::PAPER && this->_piece_type == PieceType::ROCK) || (p._piece_type != PieceType::NONE && this->_piece_type == PieceType::FLAG) || p._piece_type == PieceType::BOMB) {
        return true;
    }
    return false;
}

bool PieceRPS::operator>(const PieceRPS& p) const
{
    return (*this) < p || this->_piece_type == p._piece_type ? false : true;
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

void PieceRPS::setType(PieceType type)
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
    return this->_is_joker ? PieceTypeToChar(PieceType::JOKER) : PieceTypeToChar(_piece_type);
}

char PieceRPS::getJokerRep() const
{
    if (!_is_joker)
        return NON_JOKER_FLAG;
    return PieceTypeToChar(_piece_type);
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
    PieceType type = piece._is_joker ? PieceType::JOKER : piece.getPieceType();
    // TODO: concider moving to MACRO only, not enum (of player type)
    if (piece.getPlayer() == (int)PlayerType::PLAYER_1) {
        output << (char)toupper(PieceTypeToChar(type));
    } else {
        output << (char)tolower(PieceTypeToChar(type));
    }
    return output;
}