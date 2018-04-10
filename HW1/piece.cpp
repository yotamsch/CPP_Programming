
#include "piece.h"


int Piece::_piece_counter = 0;

Piece::Piece(PieceType type, bool is_joker, Player* owner) { 
    _piece_type = type; 
    _is_joker = is_joker;
    _owner = owner;
    ++_piece_counter; 
    _owner->IncrementPieceCount(_piece_type); 
}

/**
 * @brief Overloading on the lower than (<) operator. According to the rules of the game. Returns true only if the left side is lower "in strength" than the right side.
 * 
 * @param p The right hand side to compare to.
 * @return true If the left side is lower "in strength" than the right side
 * @return false Otherwise
 */
bool Piece::operator<(const Piece& p) {
    if (DEBUG) cout << "--> Checking " << *this << " < " << p << " ?" << endl;
    if (_piece_type == PieceType::NONE || p._piece_type == PieceType::BOMB || (p._piece_type == PieceType::ROCK && _piece_type == PieceType::SCISSORS) || (p._piece_type == PieceType::SCISSORS && _piece_type == PieceType::PAPER) || (p._piece_type == PieceType::PAPER && _piece_type == PieceType::ROCK) || (_piece_type == PieceType::FLAG && p._piece_type != PieceType::NONE)) {
        if (DEBUG) cout << "---> true" << endl;
        return true;
    }
    if (DEBUG) cout << "---> false" << endl;
    return false;
}

Piece& Piece::operator=(const Piece& p) {
    if (this != &p) {
        this->_is_joker = p._is_joker;
        this->_piece_type = p._piece_type;
        this->_owner = p._owner;
    }
    return *this;
}

/**
 * @brief Overloading on the print to ostream (<<) operator.
 * 
 * @param output The ostream to output into
 * @param piece The play piece to print
 * @return ostream& The modified ostream
 */
ostream& operator<<(ostream& output, const Piece& piece) {
    PieceType type = piece._is_joker ? PieceType::JOKER : piece.GetPieceType();
    if (piece.GetPlayerType() == PlayerType::PLAYER_1) {
        output <<  (char)toupper(PieceTypeToChar(type));
    } else {
        output <<  (char)tolower(PieceTypeToChar(type));
    }
    return output;
}

/**
 * @brief Clears a piece content and nullifies the piece (empty piece).
 * 
 */
void Piece::NullifyPiece() {
    this->_piece_type = PieceType::NONE;
    this->_owner = nullptr;
    this->_is_joker = false;
}

/**
 * @brief Removed the piece from the owning player.
 * 
 */
void Piece::RemovePieceFromPlayer() {
    if (this->_piece_type == PieceType::NONE)
        return;
    this->_owner->DecrementPieceCount(this->_piece_type);
}

bool Piece::SetType(PieceType type) { 
    if (_is_joker) {
        _owner->DecrementPieceCount(_piece_type);
        _piece_type = type; 
        _owner->IncrementPieceCount(_piece_type);
        return true;
    } 
    return false; 
}

/**
 * @brief Converts the recieved type to a representing char
 * 
 * @param type The type to convert (e.g. ROCK, PAPER...)
 * @return char The representing character
 */
char PieceTypeToChar(PieceType type) {
    switch(type) {
        case PieceType::NONE:
            return ' ';
        case PieceType::ROCK:
            return 'R';
        case PieceType::PAPER:
            return 'P';
        case PieceType::SCISSORS:
            return 'S';
        case PieceType::FLAG:
            return 'F';
        case PieceType::BOMB:
            return 'B';
        case PieceType::JOKER:
            return 'J';
        default:
            return '?';
    }
}

PieceType CharToPieceType(char chr) {
    switch(chr) {
        case 'R':
            return PieceType::ROCK;
        case 'P':
            return PieceType::PAPER;
        case 'S':
            return PieceType::SCISSORS;
        case 'F':
            return PieceType::FLAG;
        case 'B':
            return PieceType::BOMB;
        case 'J':
            return PieceType::JOKER;
        default:
            return PieceType::NONE;
    }
}
