#ifndef __H_POINT_RPS
#define __H_POINT_RPS

#include "Point.h"

class PointRPS : public Point {
private:
    int _x; // x coordinate (the column)
    int _y; // y coordinate (the row)
public:
    // basic c'tors
    PointRPS()
        : _x(-1)
        , _y(-1)
    {
    }
    PointRPS(int x, int y)
        : _x(x)
        , _y(y)
    {
    }

    // copy c'tor
    PointRPS(const PointRPS& other)
    {
        _x = other.getX();
        _y = other.getY();
    }
    // no need for move c'tor
    PointRPS(PointRPS&& other) = delete;

    // d'tor
    ~PointRPS(){};

    // interface defined functions
    int getX() const { return _x; }
    int getY() const { return _y; }
};

#endif // !__H_POINT_RPS