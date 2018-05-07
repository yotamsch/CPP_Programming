
#ifndef __H_FIGHT_INFO_RPS
#define __H_FIGHT_INFO_RPS

#include "FightInfo.h"
#include "GameUtilitiesRPS.h"
#include "PieceRPS.h"
#include "PointRPS.h"
#include <array>

class FightInfoRPS : public FightInfo {
private:
    PointRPS _position; // the fight position (x,y)
    std::array<char, NUM_OF_PLAYERS> _pieceChar; // [0] : player 1 | [1] : player 2 ...
    int _winner; // the winner of the fight

public:
    // basic c'tor
    // gets the right values from both pieces and decides on the winner
    // assumes that (rPieceA->position == rPieceB->position)
    FightInfoRPS(PieceRPS& rPieceA, PieceRPS& rPieceB);

    // d'tor
    ~FightInfoRPS() {}

    // interface defined functions
    // get the position of the fight
    const Point& getPosition() const;
    // get the piece 'char' representation for a player
    char getPiece(int player) const; // R, P, S, B or F (but NOT J)
    // get the winner of the fight
    int getWinner() const;
};

#endif // !__H_FIGHT_INFO_RPS