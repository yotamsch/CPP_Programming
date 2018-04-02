
#include "player.h"


void Player::IncrementPieceCount(PieceType type) {
    if (type == PieceType::FLAG) this->_number_of_flags++;
    this->_number_of_pieces++;
}

void Player::DecrementPieceCount(PieceType type) {
    if (type == PieceType::FLAG) this->_number_of_flags--;
    this->_number_of_pieces--;
}

bool Player::IsLosing() {
    if (_number_of_flags <= 0 || _number_of_pieces <= 0) 
        return true;
    return false; 
}

ostream& operator<<(ostream& output, const Player& p) {
    output << "Player " << int(p._type) << " Flags: " << p._number_of_flags << ", Total Pieces: " << p._number_of_pieces;
    return output;
}
