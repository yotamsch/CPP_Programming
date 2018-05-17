
#include "FightInfoRPS.h"

FightInfoRPS::FightInfoRPS(PieceRPS& rPieceA, PieceRPS& rPieceB, PointRPS&& rPos)
    : _position(rPos)
    , _winner(0) // initialize - no winner
{
    // position was set based on rPieceA (should be equal to rPieceB)
    this->_pieceChar[0] = getActualPiece(rPieceA.getPlayer() == PLAYER_1 ? rPieceA : rPieceB);
    this->_pieceChar[1] = getActualPiece(rPieceA.getPlayer() == PLAYER_1 ? rPieceB : rPieceA);

    // find winner if both pieces are different and no one is BOMB
    // norice that if one is bomb then 'both lose'
    if (this->_pieceChar[0] != this->_pieceChar[1] && this->_pieceChar[0] != BOMB_CHR && this->_pieceChar[1] != BOMB_CHR) {
        this->_winner = rPieceA < rPieceB ? rPieceB.getPlayer() : rPieceA.getPlayer();
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

char FightInfoRPS::getActualPiece(PieceRPS& p) {
    if (p.isJoker()) {
        return p.getJokerRep();
    }
    return p.getPiece();
}