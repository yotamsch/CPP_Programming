
#ifndef __H_FIGHT_INFO_RPS
#define __H_FIGHT_INFO_RPS

#include "FightInfo.h"

class FightInfoRPS : public FightInfo {
private:
public:
    // D'tor
    ~FightInfoRPS();
    // Other
    const Point& getPosition() const;
    char getOpponentPiece() const;
    int getWinner() const;
};

#endif // !__H_FIGHT_INFO_RPS