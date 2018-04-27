#ifndef __H_POINT_RPS
#define __H_POINT_RPS

#include "Point.h"

class PointRPS : public Point {
private:
public:
    // D'tor
    ~PointRPS();
    // Other
    int getX() const;
    int getY() const;
};

#endif // !__H_POINT_RPS