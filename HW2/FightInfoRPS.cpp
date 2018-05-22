/**
 * @brief The implementation of the FightInfoRPS class.
 * 
 * @file FightInfoRPS.cpp
 * @author Yotam Sechayk
 * @date 2018-05-06
 */
#include "FightInfoRPS.h"

/**
 * @brief Construct a new FightInfoRPS object
 * assumes that (rPieceA->position == rPieceB->position)
 * gets the right values from both pieces and decides on the winner
 * @param rPieceA - the first piece that participates in the fight
 * @param rPieceB - the second piece that participates in the fight
 * @param rPos - the position where the fight happens
 */
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

    // NOTE: The case where the origin piece of MOVE cannot be a BOMB is unrelevant here
    // and is being taken care of in the place which creates the FightInfo instance
}

/**
 * @brief Get the char representation of the Piece object
 * 
 * @param p - reference to PieceRPS object
 * @return char - char representation of p
 */
char FightInfoRPS::getActualPiece(PieceRPS& p) {
    if (p.isJoker()) {
        return p.getJokerRep();
    }
    return p.getPiece();
}