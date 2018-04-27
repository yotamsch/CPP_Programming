
#ifndef __H_BOARD_RPS
#define __H_BOARD_RPS

#include "Board.h"

class BoardRPS : public Board {
private:
public:
    // D'tor
    ~BoardRPS();
    // Other
    int getPlayer(const Point& pos) const;
};

#endif // !__H_BOARD_RPS
