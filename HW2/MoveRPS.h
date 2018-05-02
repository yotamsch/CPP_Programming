#ifndef __H_MOVE_RPS
#define __H_MOVE_RPS

#include "Move.h"

class MoveRPS : public Move {
private:
public:
    // D'tor
    ~MoveRPS(){}
    // Other
    const Point& getFrom() const{}
    const Point& getTo() const{}
};

#endif // !__H_MOVE_RPS