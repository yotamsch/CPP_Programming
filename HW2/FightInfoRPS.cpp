
#include "FightInfoRPS.h"

FightInfoRPS::FightInfoRPS(PieceRPS& rPieceA, PieceRPS& rPieceB)
    : _position(rPieceA.getPosition().getX(), rPieceA.getPosition().getY())
    , _winner(0) // initialize - no winner
{
    // TODO: maybe replace with MACRO of player type
    // position was set based on rPieceA (should be equal to rPieceB)
    this->_pieceChar[0] = rPieceA.getPlayer() == (int)PlayerType::PLAYER_1 ? rPieceA.getPiece() : rPieceB.getPiece();
    this->_pieceChar[1] = rPieceA.getPlayer() == (int)PlayerType::PLAYER_1 ? rPieceB.getPiece() : rPieceA.getPiece();

    // find winner if both pieces are different and no one is BOMB
    // norice that if one is bomb then 'both lose'
    if (rPieceA.getPieceType() != rPieceB.getPieceType() && rPieceA.getPieceType() != PieceType::BOMB && rPieceB.getPieceType() != PieceType::BOMB) {
        this->_winner = rPieceA > rPieceB ? rPieceA.getPlayer() : rPieceB.getPlayer();
    }
    
    // NOTE:
    // -----
    // the case where the origin piece of MOVE cannot be a BOMB is unrelevant here
    // and is being taken care of in the place which creates the Fight?Info instance
}

const Point& FightInfoRPS::getPosition() const
{
    return _position;
}

char FightInfoRPS::getPiece(int player) const
{
    return this->_pieceChar[player - 1];
}

int FightInfoRPS::getWinner() const
{
    return _winner;
}
