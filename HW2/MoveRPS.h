#ifndef __H_MOVE_RPS
#define __H_MOVE_RPS

#include "Move.h"
#include "PointRPS.h"

class MoveRPS : public Move {
private:
    PointRPS _fromPoint, _toPoint;
public:
    //C'tor
    MoveRPS(const Point& fromPoint, const Point& toPoint): _fromPoint(fromPoint), _toPoint(toPoint){
    }
    // D'tor
    ~MoveRPS(){}
    // Other
    const Point& getFrom() const{
        return _fromPoint;
    }
    const Point& getTo() const{
        return _toPoint;
    }
};

#endif // !__H_MOVE_RPS