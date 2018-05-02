
#include "FightInfoRPS.h"

FightInfoRPS::~FightInfoRPS(){}
const Point& FightInfoRPS::getPosition() const{
    return _position;
}

char FightInfoRPS::getPiece(int player) const{
    return player == 1? _charOfPlayer1 : _charOfPlayer2;
}

int FightInfoRPS::getWinner() const{
    return _winner;
}
