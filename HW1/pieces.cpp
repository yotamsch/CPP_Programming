#include "pieces.h"

int* Piece::_counter = new int[NUM_OF_PIECES_TYPE];

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

Piece::Piece(const Piece& p) {
    this->_is_joker = p._is_joker;
    this->_index_x = p._index_x;
    this->_index_y = p._index_y;
    this->_piece_type = p._piece_type;
    this->_player_id = p._player_id;
}

ostream& operator<<(ostream& output, const Piece& piece) {
    if (piece.getPlayerId() == PLAYER_1) {
        output <<  (char)toupper(pieceTypeToChar(piece.getPieceType()));
    } else {
        output <<  (char)tolower(pieceTypeToChar(piece.getPieceType()));
    }
    return output;
}


// ? maybe something to implement
