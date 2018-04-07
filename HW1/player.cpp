
#include "player.h"


void Player::IncrementPieceCount(PieceType type) {
    if (type == PieceType::FLAG) this->_number_of_flags++;
    else if (type != PieceType::BOMB) this->_number_of_pieces++;
}

void Player::DecrementPieceCount(PieceType type) {
    if (type == PieceType::FLAG) this->_number_of_flags--;
    else if (type != PieceType::BOMB) this->_number_of_pieces--;
}

Reason Player::IsLosing() {
    if (_number_of_flags <= 0) return Reason::NO_FLAGS;
    if (_number_of_pieces <= 0) return Reason::NO_PIECES;
    return Reason::SUCCESS;
}

ostream& operator<<(ostream& output, const Player& p) {
    output << "Player " << int(p._type) << " Flags: " << p._number_of_flags << ", Total Pieces: " << p._number_of_pieces;
    return output;
}
