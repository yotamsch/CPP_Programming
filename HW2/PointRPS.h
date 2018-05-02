#ifndef __H_POINT_RPS
#define __H_POINT_RPS

#include "Point.h"

class PointRPS : public Point {
private:
    int _x, _y;
public:
    PointRPS(int x, int y): _x(x), _y(y){}
    //? maybe should implement our copy c'tor
    // D'tor
    ~PointRPS();
    // Other
    int getX() const { return _x; }
    int getY() const { return _y; }
};

#endif // !__H_POINT_RPS