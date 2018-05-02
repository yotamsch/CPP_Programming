
#ifndef __H_FIGHT_INFO_RPS
#define __H_FIGHT_INFO_RPS

#include "FightInfo.h"

class FightInfoRPS : public FightInfo {
private:
    const Point& _position;
    char _charOfPlayer1;
    char _charOfPlayer2;
    int _winner;

public:
    FightInfoRPS(const Point& position, char charOfPlayer1, char charOfPlayer2, int winner): _position(position), _charOfPlayer1(charOfPlayer1), _charOfPlayer2(charOfPlayer2), _winner(winner) {
        
    } 
    // D'tor
    ~FightInfoRPS();
    // Other
    const Point& getPosition() const;
	char getPiece(int player) const; // R, P, S, B or F (but NOT J)
    int getWinner() const;
};

#endif // !__H_FIGHT_INFO_RPS