
#include "pieces.h"

/**
 * @brief Converts the recieved type to a representing char
 * 
 * @param type The type to convert (e.g. ROCK, PAPER...)
 * @return char The representing character
 */
char pieceTypeToChar(int type) {
    switch(type) {
        case NONE:
            return '_';
        case ROCK:
            return 'R';
        case PAPER:
            return 'P';
        case SCISSORS:
            return 'S';
        case FLAG:
            return 'F';
        case BOMB:
            return 'B';
        case JOKER:
            return 'J';
        default:
            return '?';
    }
}

/**
 * @brief Overloading on the lower than (<) operator. According to the rules of the game. Returns true only if the left side is lower "in strength" than the right side.
 * 
 * @param p The right hand side to compare to.
 * @return true If the left side is lower "in strength" than the right side
 * @return false Otherwise
 */
bool Piece::operator<(const Piece& p) {
    if (p._piece_type == BOMB || (p._piece_type == ROCK && _piece_type == SCISSORS) || (p._piece_type == SCISSORS && _piece_type == PAPER) || (p._piece_type == PAPER && _piece_type == ROCK) || _piece_type == FLAG || _piece_type == NONE) {
        return true;
    }
    return false;
}

/**
 * @brief Overloading on the print to ostream (<<) operator.
 * 
 * @param output The ostream to output into
 * @param piece The play piece to print
 * @return ostream& The modified ostream
 */
ostream& operator<<(ostream& output, const Piece& piece) {
    if (piece.getPlayerId() == PLAYER_1) {
        output <<  (char)toupper(pieceTypeToChar(piece.getPieceType()));
    } else {
        output <<  (char)tolower(pieceTypeToChar(piece.getPieceType()));
    }
    return output;
}


// ? maybe something to implement
