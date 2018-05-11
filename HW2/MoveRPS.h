#ifndef __H_MOVE_RPS
#define __H_MOVE_RPS

#include "Move.h"
#include "PointRPS.h"

class MoveRPS : public Move {
private:
    PointRPS _fromPoint;
    PointRPS _toPoint;

public:
    // basic c'tor
    MoveRPS(const PointRPS& fromPoint, const PointRPS& toPoint)
        : _fromPoint(fromPoint)
        , _toPoint(toPoint)
    {
    }

    // d'tor
    ~MoveRPS() {}

    // interace defined functions
    const Point& getFrom() const
    {
        return _fromPoint;
    }
    const Point& getTo() const
    {
        return _toPoint;
    }
};

#endif // !__H_MOVE_RPS