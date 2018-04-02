
#include "piece.h"


int Piece::_piece_counter = 0;

/**
 * @brief Overloading on the lower than (<) operator. According to the rules of the game. Returns true only if the left side is lower "in strength" than the right side.
 * 
 * @param p The right hand side to compare to.
 * @return true If the left side is lower "in strength" than the right side
 * @return false Otherwise
 */
bool Piece::operator<(const Piece& p) {
    if (p._piece_type == PieceType::BOMB || (p._piece_type == PieceType::ROCK && _piece_type == PieceType::SCISSORS) || (p._piece_type == PieceType::SCISSORS && _piece_type == PieceType::PAPER) || (p._piece_type == PieceType::PAPER && _piece_type == PieceType::ROCK) || _piece_type == PieceType::FLAG || _piece_type == PieceType::NONE) {
        return true;
    }
    return false;
}

Piece& Piece::operator=(const Piece& p) {
    if (this != &p) {
        this->_index_x = p._index_x;
        this->_index_y = p._index_y;
        this->_is_joker = p._is_joker;
        this->_piece_type = p._piece_type;
        this->_player_type = p._player_type;
    }
    if (DEBUG) cout << "- Counter=" << _piece_counter << endl;
    if (DEBUG) cout << "(" << this->_index_x << "," << this->_index_y << ") " << endl;
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
    if (piece.GetPlayerType() == PlayerType::PLAYER_1) {
        output <<  (char)toupper(PieceTypeToChar(piece.GetPieceType()));
    } else {
        output <<  (char)tolower(PieceTypeToChar(piece.GetPieceType()));
    }
    return output;
}

/**
 * @brief Clears a piece content and nullifies the piece (empty piece).
 * 
 */
void Piece::ClearPiece() {
    this->_piece_type = PieceType::NONE;
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


// ? maybe something to implement
